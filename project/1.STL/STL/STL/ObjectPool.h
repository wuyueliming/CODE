#pragma once
#include"common.h"


namespace CMP
{
	template<typename T>
	class ObjectPool
	{
	public:
		ObjectPool() = default;
		~ObjectPool() = default;
		
		T* New() {
			_mutex.lock();
			void* ret = nullptr;	
			if (_freelist) {
				ret = _freelist;
				_freelist = nextptr(_freelist);
			}
			else {
				if (!_memory || _remainBytes < sizeof(T)) {
					_remainBytes = (16 << PAGE_SHIFT);
					_memory = SystemAlloc(_remainBytes);
				}
				ret = _memory;
				_memory = (char*)_memory + sizeof(T);
				_remainBytes -= sizeof(T);
			}
			_mutex.unlock();
			new(ret) T;
			return (T*)ret;
		}

	

		void Delete(T* ptr) {
			_mutex.lock();
			ptr->~T();
			nextptr(ptr) = _freelist;
			_freelist = ptr;
			_mutex.unlock();
		}

	private:
		void* _memory = nullptr;
		size_t _remainBytes = 0;
		void* _freelist = nullptr;
		std::mutex _mutex;
	};
}
