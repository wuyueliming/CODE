#pragma once
#include"common.h"
#include"ObjectPool.h"
#include"ThreadCache.h"
#include"CentralCache.h"
#include"PageCache.h"


namespace CMP
{

	void* ConcurrentAlloc(size_t size) {
		//小于256KB的请求通过三层内存池
		if (size <= MAX_BYTES)
		{
			// 通过TLS,每个线程无锁的获取自己的专属的ThreadCache对象
			if (pTLSThreadCache == nullptr)
			{
				static ObjectPool<ThreadCache> TCpool;
				pTLSThreadCache = TCpool.New();
				//pTLSThreadCache = new ThreadCache;
			}

			//cout << std::this_thread::get_id() << ":" << pTLSThreadCache << endl;
			return pTLSThreadCache->Allocate(size);
		}//大于256KB的请求直接通过PageCache分配
		else {
			size_t kpage = SizeClass::RoundUp(size) >> PAGE_SHIFT;
			Span* pSpan = PageCache::GetInstance()->Allocate(kpage);
			pSpan->_isUse = true;
			pSpan->_objSize = size;
			return (void*)(pSpan->_pageId << PAGE_SHIFT);
		}
	}

	void ConcurrentFree(void* ptr) {
		Span* retSpan = PageCache::GetInstance()->IdmapToSpan((PAGE_ID)ptr >> PAGE_SHIFT);
		assert(retSpan != nullptr);
		size_t size = retSpan->_objSize;

		//ptr只能从分配内存的起始地址开始释放，防止freelist中插入错误的地址再次分配时出问题
		size_t offset = (char*)ptr - (char*)(retSpan->_pageId << PAGE_SHIFT);
		assert(offset % size == 0);
		if (size <= MAX_BYTES) {
			pTLSThreadCache->Deallocate(ptr, size);
		}
		else {//直接从page cache释放
			retSpan->_isUse = false;
			PageCache::GetInstance()->Deallocate(retSpan);
		}
	}

}
