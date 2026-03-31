#pragma once
#include<vector>
#include<unordered_map>


namespace xdh {


	class union_find {
	public:
		typedef long long ll;
		union_find(const size_t N = 0)
			:_parent(N, -1) {
		}

	public:

		bool merge(const size_t& X, const size_t& Y) {
			ll x = find(X);
			ll y = find(Y);
			if (x == y) {
				return false;
			}
			else if (abs(_parent[x]) < abs(_parent[y])) {
				_parent[y] += _parent[x];
				_parent[x] = y;
			}
			else {
				_parent[x] += _parent[y];
				_parent[y] = x;
			}
			return true;
		}

		ll find(const size_t x) {
			ll parent = x;
			while (_parent[parent] >= 0)
			{
				parent = _parent[parent];
			}
			return parent;
		}


	public:
		bool empty() const {
			return _parent.empty();
		}

		size_t size() const {
			return _parent.size();
		}

		void clear() {
			_parent.clear();
		}

	private:
		std::vector<ll> _parent;
	};

}
