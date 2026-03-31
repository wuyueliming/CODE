#pragma once
#include"common.h"
#include"ObjectPool.h"
#include"PageMap.h"

namespace CMP
{
	class PageCache {
	public:
		static PageCache _instance;
	public:
		PageCache(){}
		PageCache(const PageCache&) = delete;
		
		static PageCache* GetInstance() {
			return &_instance;
		}
	public:
		//分配Span
		Span* Allocate(size_t kpage);
		//回收Span
		void Deallocate(Span* pSpan);
		//工具函数
		Span* IdmapToSpan(PAGE_ID id);//使用基数树实现映射，除ensure会改变树结构外，get和set都是线程安全的。
		inline std::mutex& GetMutex() {
			return _mutex;
		}
	private:
		Span* NewSpan(size_t kpage);
		Span* SplitKSpan(size_t i, size_t kpage);
		void MergeFreeSpan(Span* pSpan);
		
		Span* BuildIdMap(Span* pSpan);
		void EraseIdMap(Span* pSpan);
	private:
		SpanList _SpanList[NPAGES];
		std::mutex _mutex;         
		//std::unordered_map<PAGE_ID, Span*> _IdSpanMap; //页号到span的映射，需要注意保护map的线程安全
#ifdef _WIN64
		TCMalloc_PageMap3<64 - PAGE_SHIFT> _IdSpanMap;
#elif _WIN32
		TCMalloc_PageMap3<32 - PAGE_SHIFT> _IdSpanMap;
#else
		// linux
#endif

		ObjectPool<Span> _SpanPool;
	};
};

