#include"PageCache.h"

namespace CMP
{
	Span* PageCache::Allocate(size_t kpage) {
		//std::unique_lock<std::mutex> lock(_mutex);
		if (kpage >= NPAGES) {
			//Span* newspan = new Span;
			Span* newspan = _SpanPool.New();
			void* ptr = SystemAlloc(kpage);
			newspan->_n = kpage;
			newspan->_pageId = (PAGE_ID)ptr >> PAGE_SHIFT;

			_mutex.lock();
			_IdSpanMap.Ensure(newspan->_pageId, 1);
			_IdSpanMap.set(newspan->_pageId, newspan);
			//_IdSpanMap[newspan->_pageId] = newspan;
			_mutex.unlock();
			return newspan;
		}
		else {
			_mutex.lock();
			Span* ret = NewSpan(kpage);
			_mutex.unlock();
			return ret;
		}
	}
	
	Span* PageCache::NewSpan(size_t kpage) {
		//检查是否有空闲的kpage span
		if (!_SpanList[kpage].empty()) {
			return BuildIdMap(_SpanList[kpage].popFront());
		}

		//没有空闲span，找到更大页数的span进行切分
		for (size_t i = kpage + 1; i < NPAGES; i++) {
			if (_SpanList[i].empty()) {
				continue;
			}
			//找到大span，进行切分
			return SplitKSpan(i, kpage);
		}

		//没有空闲大span，申请一个128页的大span
		//Span* newspan = new Span;
		Span* newspan = _SpanPool.New();
		newspan->_n = NPAGES - 1;
		newspan->_pageId = (PAGE_ID)SystemAlloc(NPAGES - 1) >> PAGE_SHIFT;
		_SpanList[NPAGES - 1].pushFront(newspan);
		//给新span建立首尾id到span的映射
		_IdSpanMap.Ensure(newspan->_pageId, 1);
		_IdSpanMap.Ensure(newspan->_pageId + newspan->_n - 1, 1);
		_IdSpanMap.set(newspan->_pageId, newspan);
		_IdSpanMap.set(newspan->_pageId + newspan->_n - 1, newspan);
		
		return SplitKSpan(NPAGES - 1, kpage);
	}

	Span* PageCache::SplitKSpan(size_t i, size_t kpage) {
		Span* bigspan = _SpanList[i].popFront();
		//Span* kSpan = new Span;
		Span* kSpan = _SpanPool.New();
		kSpan->_pageId = bigspan->_pageId;
		kSpan->_n = kpage;
		bigspan->_pageId += kpage;
		bigspan->_n -= kpage;
		_SpanList[bigspan->_n].pushFront(bigspan);
		
		//处理映射
		_IdSpanMap.Ensure(bigspan->_pageId, 1);
		_IdSpanMap.set(bigspan->_pageId, bigspan);
		_IdSpanMap.set(bigspan->_pageId + bigspan->_n - 1, bigspan);
		return BuildIdMap(kSpan);
	}


	


	void PageCache::Deallocate(Span* pSpan) {
		if (pSpan->_n >= NPAGES) {
			_IdSpanMap.set(pSpan->_pageId, nullptr);
			SystemFree((void*)(pSpan->_pageId << PAGE_SHIFT));
			_SpanPool.Delete(pSpan);
		}
		else {
			_mutex.lock();
			//合并返回的span
			EraseIdMap(pSpan);
			MergeFreeSpan(pSpan);
			_mutex.unlock();
		}
	}
	void PageCache::MergeFreeSpan(Span* pSpan) {
		//向前合并
		while (1) {
			Span* prev_span = IdmapToSpan(pSpan->_pageId - 1);
			if (prev_span == nullptr || prev_span->_isUse) {
				break;
			}
			if (pSpan->_n + prev_span->_n > NPAGES - 1) {
				break;
			}//清理不用映射，避免合并后查到野指针
			_IdSpanMap.set(pSpan->_pageId-1, nullptr);
			_IdSpanMap.set(pSpan->_pageId, nullptr);
			_SpanList[prev_span->_n].Erase(prev_span);

			pSpan->_pageId = prev_span->_pageId;
			pSpan->_n += prev_span->_n;
			_SpanPool.Delete(prev_span);
		}
		_IdSpanMap.set(pSpan->_pageId, pSpan);
		_IdSpanMap.set(pSpan->_pageId + pSpan->_n -1, pSpan);

		//向后合并
		while (1) {
			Span* next_span = IdmapToSpan(pSpan->_pageId - 1);
			if (next_span == nullptr || next_span->_isUse) {
				break;
			}
			if (pSpan->_n + next_span->_n > NPAGES - 1) {
				break;
			}
			_IdSpanMap.set(pSpan->_pageId + pSpan->_n -1, nullptr);
			_IdSpanMap.set(pSpan->_pageId + pSpan->_n, nullptr);
			_SpanList[next_span->_n].Erase(next_span);

			pSpan->_n += next_span->_n;
			_SpanPool.Delete(next_span);
		}
		_IdSpanMap.set(pSpan->_pageId, pSpan);
		_IdSpanMap.set(pSpan->_pageId + pSpan->_n - 1, pSpan);
		
		pSpan->_isUse = false;
		pSpan->_freeList = nullptr;
		_SpanList[pSpan->_n].pushFront(pSpan);
	}


	Span* PageCache::IdmapToSpan(PAGE_ID id) {
		/*auto ret = _IdSpanMap.find(id);
		if (ret == _IdSpanMap.end()) {
			return nullptr;
		}
		else {
			return ret->second;
		}*/
		return (Span*)_IdSpanMap.get(id);
	}



	Span* PageCache::BuildIdMap(Span* pSpan) {
		_IdSpanMap.Ensure(pSpan->_pageId, pSpan->_n);
		for (size_t i = 0; i < pSpan->_n; i++) {
			//_IdSpanMap[pSpan->_pageId + i] = pSpan;
			_IdSpanMap.set(pSpan->_pageId + i, pSpan);
		}
		return pSpan;
	}

	void PageCache::EraseIdMap(Span* pSpan) {
		for (size_t i = 0; i < pSpan->_n; i++) {
			_IdSpanMap.set(pSpan->_pageId + i, nullptr);
			//_IdSpanMap.erase(pSpan->_pageId + i);
		}
	}

	PageCache PageCache::_instance;
};


