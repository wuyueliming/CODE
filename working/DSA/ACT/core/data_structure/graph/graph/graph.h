#pragma once
#include"union_find.h"
#include"indexed_vector.h"
#include<queue>

namespace xdh {

	enum status_vertex {
		UNDISCOVERED,
		DISCOVERED,
		VISITED
	};
	enum type_edge {
		UNDETERMINED,
		TREE,
		CROSS,
		FORWARD,
		BACKWARD 
	};



	template<class T>
	class vertex {
	public:
		vertex(const T& data = T())
			:data(data) {
		}
		void reset() {
			inDegree = 0;
			outDegree = 0;
			status = UNDISCOVERED;
			dtime = 0;
			ftime = 0;
			parent = -1;
			priority = -1;
		}
		void clear() {
			data = T();
			reset();
		}
		bool operator==(const vertex& other) const {
			return data == other.data && inDegree == other.inDegree && outDegree == other.outDegree &&
				status == other.status && dtime == other.dtime && ftime == other.ftime &&
				parent == other.parent && priority == other.priority;
		}
	public:
		T data;
		size_t inDegree;
		size_t  outDegree;
		status_vertex status;
		size_t dtime;//discovery time
		size_t ftime;//finish time
		size_t parent;//parent vertex index
		size_t priority;//priority in priority queue	
	};

	template<class T ,long long MAX_W=LLONG_MAX>
	class edge {
	public:
		edge(const T& data = T())
			:data(data) {
		}

		bool operator==(const edge& other) const {
			return data == other.data && type == other.type && weight == other.weight;
		}

		void reset() {
			type = UNDETERMINED;
		}
		void clear() {
			data = T();
			reset();
		}
	public:
		T data;
		long long weight;	
		type_edge type;
	};



	//有可能继承实现一个用vector整数索引的graph，一个用indexed_vector索引的indexed_graph
	template<class TV, class TE>//   class code_TV,class VertexTable=indexed_vector>
	class graph {
	public:
		typedef vertex<TV> Vertex;
		typedef edge<TE> Edge;
		class vertex_code;
		typedef xdh::indexed_vector<Vertex, vertex_code>  VertexTable;
		typedef std::vector<std::vector<Edge*>> Matrix;

		class vertex_code {
		public:
			size_t operator()(const Vertex& v) const {
				return std::hash<TV>()(v.data);
			}
		};
		
		template<typename T>
		class default_visit {
			public:
				void operator()(const T& v) const {
					std::cout << v.data << ' ';
				}
		};
		

	public:
		graph() = default;
		graph(const graph& g) {
			_vertices.reserve(g._vertices.size());
			_matrix.reserve(g._matrix.size());
			for (const auto& v : g._vertices) {
				_vertices.push_back(v);
			}
			for (const auto& e : g._matrix) {
				_matrix.push_back(e);
			}
		}
		graph& operator=(graph temp) {
			if (this != &temp) {
				swap(temp);
			}
			return *this;
		}
		~graph() {
			clear();
		}

	public://vertex
		void add_vertex(const TV& data) {
			_vertices.push_back(Vertex(data));
			
            _matrix.push_back(std::vector<Edge*>(size(), nullptr));
			for(size_t i = 0; i < _matrix.size(); ++i) {
				_matrix[i].resize(size(), nullptr);
			}
		}

		size_t	del_vertex(const size_t index) {
			check_vertex(index);

			_vertices.erase(_vertices.begin() + index);
			for(size_t i = 0; i < size(); ++i) {
				if(_matrix[index][i]) {
					delete _matrix[index][i];
					varify_update(index, i);
				}
				if (_matrix[i][index] && _matrix[i][index]!=_matrix[index][i]) {
					delete _matrix[i][index];
					varify_update(i, index);
				}
				_matrix[i][index] = _matrix[index][i] = nullptr;
			}
			_matrix.erase(_matrix.begin() + index);
			for (auto& row : _matrix) {
				row.erase(row.begin() + index);
			}
			return 1;
		}

		size_t index_of(const TV& data){
			return _vertices.index_of(data);
		}

		vector<size_t> indices_of(const TV& data) {
			return _vertices.indices_of(data);
		}

		Vertex* vertex(size_t index) {
			check_vertex(index);
			return _vertices.at(index);
		}
		Vertex* operator()(size_t index) {
			return vertex(index);
		}

		int inDegree(const size_t index) const {
			check_vertex(index);
			return _vertices[index].inDegree;
		}

		int outDegree(const size_t index) const {
			check_vertex(index);
			return _vertices[index].outDegree;
		}

		status_vertex status(const size_t index) const {
			check_vertex(index);
			return _vertices[index].status;
		}

		size_t& priority(size_t i) {
			check_vertex(i);
			return _vertices[i].priority;
		}

		size_t vertex_count() const {
			return _vertices.size();
		}
		
	public://edge
		Edge* edge(const size_t src, const size_t dst) {
			check_edge(src, dst);
			return _matrix[src][dst];
		}
		vector<Edge*>& operator[](const size_t index) {
			check_vertex(index);
			return _matrix[index];
		}

		type_edge type(const size_t src, const size_t dst) const {
			check_edge(src, dst);
			return _matrix[src][dst]->_type;
		}

		bool exists(const size_t src, const size_t dst){
			check_edge(src, dst);
			return _matrix[src][dst] || _matrix[dst][src];
		}

		bool is_edge_between(const size_t v1, const size_t  v2) {
			return exists(v1, v2) && _matrix[v1][v2] == _matrix[v2][v1];
		}

		void arc_to_edge(const size_t src, const size_t dst) {
			check_edge(src, dst);
			if (_matrix[src][dst] && _matrix[dst][src]!=_matrix[src][dst]) {
				delete _matrix[dst][src];
				if (!_matrix[dst][src]) {
					varify_update(dst, src);
				}
				_matrix[dst][src] = _matrix[src][dst];
			}
		}	

		void edge_to_arc(const size_t v1, const size_t v2) {
			check_edge(v1, v2);
			if (_matrix[v1][v2] && _matrix[v2][v1] == _matrix[v1][v2]) {
				varify_update(v2, v1);
				_matrix[v2][v1] = nullptr;
			}
		}

		bool add_arc(size_t src, size_t dst, const TE& data) {
			check_edge(src, dst);
			if (!_matrix[src][dst] || _matrix[src][dst] == _matrix[dst][src]) {
				_matrix[src][dst] = new Edge(data);
				if (!_matrix[src][dst]) {
					varify_update(src, dst);
				}
				return true;
			} else {
				_matrix[src][dst]->clear();
				_matrix[src][dst]->data = data;
				return false;
			}
		}
		bool add_edge(size_t v1, size_t v2, const TE& data) {
			check_edge(v1, v2);
			if (!_matrix[v1][v2] && !_matrix[v2][v1]) {
				varify_update(v1, v2);
				varify_update(v2, v1);
				_matrix[v1][v2] = _matrix[v2][v1] = new Edge(data);
				return true;
			}
			else if(_matrix[v1][v2] == _matrix[v2][v1]) {
				_matrix[v1][v2]->clear();
				_matrix[v1][v2]->data = data;
			}
			else {
				if(_matrix[v1][v2] && _matrix[v2][v1]) {
					delete _matrix[v1][v2];
					varify_update(v1, v2);
					_matrix[v1][v2] = nullptr;
				}
				if (!_matrix[v1][v2]) {
					varify_update(v1, v2);
					_matrix[v1][v2] = _matrix[v2][v1];
				}
				if (!_matrix[v2][v1]) {
					varify_update(v2, v1);
					_matrix[v2][v1] = _matrix[v1][v2];
				}
				_matrix[v1][v2]->clear();
				_matrix[v1][v2]->data = data;
			}
			return false;
		}

		bool del_arc(const size_t src,const size_t dst) {
			check_edge(src, dst);
			if (!_matrix[src][dst])return false;

			if (_matrix[dst][src] != _matrix[src][dst]) {
				delete _matrix[src][dst];
			}
			varify_update(src, dst);
			_matrix[src][dst] = nullptr;
			return true;
		}
		bool del_edge(const size_t v1, const size_t v2) {
			check_edge(v1, v2);
			if (!_matrix[v1][v2])return false;
			
			if(_matrix[v1][v2] == _matrix[v2][v1]) {
				delete _matrix[v1][v2];
				varify_update(v1, v2);
				varify_update(v2, v1);
				_matrix[v1][v2] = _matrix[v2][v1] = nullptr;
			}
			else {
				if(!_matrix[v1][v2]) {
					delete _matrix[v1][v2];
					varify_update(v1, v2);
					_matrix[v1][v2] = nullptr;
				}
				if(_matrix[v2][v1]) {
					delete _matrix[v2][v1];
					varify_update(v2, v1);
					_matrix[v2][v1] = nullptr;
				}
			}
			return true;
		}

		long long& weight(size_t src, size_t dst) {
			check_edge(src, dst);
			return _matrix[src][dst]->weight;
		}

		size_t edge_count() const {
			return count_arc;
		}

		

	public://algorithm
		//minimum spanning tree
		void prim(size_t src) {
			class update {
			public:
				void operator()(graph* G, size_t src, size_t dst) {
					G->priority(dst) = (*G)[src][dst]->weight;
				}
			};
			PFS<update>(src);
		}
		void kruskal() {
			union_find uf(size());
			for (size_t i = 0; i < size(); ++i) {
				for (size_t j = i + 1; j < size(); ++j) {
					if (_matrix[i][j]) {
						uf.union_set(i, j, _matrix[i][j]->weight);
					}
				}
			}
			for (size_t i = 0; i < size(); ++i) {
				for (size_t j = i + 1; j < size(); ++j) {
					if (_matrix[i][j] && uf.find(i) == uf.find(j)) {
						cout << "Edge: " << i << "-" << j << " Weight: " << _matrix[i][j]->weight << endl;
					}
				}
			}
		}

		//shortest path
		void dijkstra(size_t src) {
			class update {
			public:
				void operator()(graph* G, size_t src, size_t dst) {
					for(size_t i = 0; i < G->size(); ++i) {
						if (G->_matrix[src][i] && G->_matrix[src][i]->weight + G->_vertices[src].priority < G->_vertices[i].priority) {
							G->_vertices[i].priority = G->_matrix[src][i]->weight + G->_vertices[src].priority;
						}
					}
				}
			};
			PFS<update>(src);
		}
		void floyd() {
			for (size_t k = 0; k < size(); ++k) {
				for (size_t i = 0; i < size(); ++i) {
					for (size_t j = 0; j < size(); ++j) {
						if (_matrix[i][k] && _matrix[k][j]) {
							long long new_weight = _matrix[i][k]->weight + _matrix[k][j]->weight;
							if (!_matrix[i][j] || new_weight < _matrix[i][j]->weight) {
								if (_matrix[i][j]) {
									_matrix[i][j]->weight = new_weight;
								} else {
									_matrix[i][j] = new Edge(new_weight);
								}
							}
						}
					}
				}
			}
		}	


		//traverse	
		template<typename visitor = default_visit<Vertex>>
		void DFS(size_t src) {
			reset();
			size_t i = src;
			do {
				if (_vertices[i].status == UNDISCOVERED) {
					dfs<visitor>(i);
				}
				i = (i + 1) % size();
			} while (i != src);
		}

		template<typename visitor=default_visit<Vertex>>
		void BFS(size_t src,size_t max_level=-1) {
			reset();
			size_t i = src;
			do{
				if(_vertices[i].status == UNDISCOVERED) {
					bfs<visitor>(i,max_level);
				}
				i = (i + 1) % size();
			} while (i!=src);
		}

		template<class prioupdator, typename visitor = default_visit<Vertex>>
		void PFS(size_t src) {
			reset();
			size_t i = src;
			do {
				if (_vertices[i].status == UNDISCOVERED) {
					pfs<prioupdator,visitor>(i);
				}
				i = (i + 1) % size();
			} while (i != src);
		}

		template<class prioupdator, typename visitor=default_visit<Vertex>>
		void pfs(size_t start) {
			prioupdator update; visitor visit;
			check_vertex(start);
			visit(_vertices[start]);
			_vertices[start].status = VISITED;
			_vertices[start].parent = -1;	

			while(true) {
				for (size_t v = 0; v < size(); v++) {
					if (_vertices[v].status == UNDISCOVERED && _matrix[start][v]) {
						_vertices[v].status = DISCOVERED;	
						update(this,start, v);
					}
				}
				size_t next = start;//start必定访问过
				size_t min = -1;

				for(size_t v = 0; v < size(); v++) {
					if (_vertices[v].status == DISCOVERED) {
						if (_vertices[v].priority < min) {
							min = _vertices[v].priority;
							next = v;
						}
					}
				}
				if (next == start)return;//没有可访问的顶点了
				visit(_vertices[next]);
				_vertices[next].parent = start;
				_vertices[next].status = VISITED;
				start = next;
			}
		}

		template<typename visitor>
		void dfs(const size_t start) {
			_vertices[start].status = DISCOVERED;
			visitor()(_vertices[start]);
			for(size_t i = 0; i < size(); ++i) {
				if (_matrix[start][i]) {
					switch (_vertices[i].status) {
					case UNDISCOVERED:
						_vertices[i].parent = start;
						_matrix[start][i]->type = TREE;
						dfs<visitor>(i);
						break;
					case DISCOVERED:
						_matrix[start][i]->type = BACKWARD;
						break;
					case VISITED:
						_vertices[i].dtime > _vertices[start].dtime ?
							_matrix[start][i]->type = FORWARD : _matrix[start][i]->type = CROSS;
					}
				}
			}
			_vertices[start].status = VISITED;
		}

		template<typename visitor>
		void bfs(const size_t start,size_t max_level) {
			check_vertex(start);
			std::queue<size_t> q;
			size_t cur_last = start;
			size_t next_last = -1;
			size_t level = 0;	

			_vertices[start].status = DISCOVERED;
			q.push(start);
			while (!q.empty()) {
				size_t v = q.front();
				q.pop();
				for (size_t i = 0; i < size(); ++i) {
					if (_matrix[v][i]) {
						if (_vertices[i].status == UNDISCOVERED) {
							_vertices[i].status = DISCOVERED;
							_vertices[i].parent = v;
							_matrix[v][i]->type = TREE;
							q.push(i);
							next_last = i;
						}
						else {
							_matrix[v][i]->type = CROSS;
						}						
					}
				}
				visitor()(_vertices[v]);
				_vertices[v].status = VISITED;
				if(v == cur_last && next_last!=-1) {
					cur_last = next_last;	
					level++;
				}
				if (level > max_level) {
					return;
				}
			}
		}


	public://functions
		void hehe() {
			for (size_t i = 0; i < size(); i++) {
				for (size_t j = 0; j < size(); j++) {
					if (_matrix[i][j]) {
						_matrix[i][j]->weight = _matrix[i][j]->data;
					}
				}
			}
		}

		void show() {
			cout << "Vertices:\n";
			print_vertices();
			cout << endl; 

			printf("Matrix: \n");
			print_matrix();
		}

		void reset() {
			for(auto& v : _vertices) {
				v->reset();
			}
			for(auto& row : _matrix) {
				for(auto& e : row) {
					if(e) {
						e->reset();
					}
				}
			}
		}

		void shrink() {
			_vertices.shrink_to_fit();
			_matrix.shrink_to_fit();
			for (auto& row : _matrix) {
				row.shrink_to_fit();
			}
		}

		void check_vertex(const size_t index){
			assert(index < size());
		}

		void check_edge(const size_t src, const size_t dst){
			assert(src < size() && dst < size());
		}

		void clear() {
			_vertices.clear();
			for(size_t i = 0; i < size(); ++i) {
				for (size_t j = 0; j < size(); ++j) {
					if(_matrix[i][j] ) {
						delete _matrix[i][j];
						if (_matrix[i][j] == _matrix[j][i]) {
							_matrix[j][i] = nullptr;
						}
						_matrix[i][j] = nullptr;
					}
				}
			}
			for (auto& row : _matrix) {
				row.clear();
			}
			_matrix.clear();
			count_arc = 0;
		}

		size_t size() const{
			return vertex_count();
		}

		bool empty() {
			return size() == 0;
		}

		bool check() {
			bool count = true;
			for(const auto& row : _matrix) {
				if(row.size() != size()) {
					count = false;
					break;
				}
			}
			return count && _vertices.size() == size();
		}

		void swap(graph& other) {
			std::swap(_vertices, other._vertices);
			std::swap(_matrix, other._matrix);
			std::swap(count_arc, other.count_arc);
		}
	private://tools
		void varify_update(size_t src, size_t dst) {
			if (_matrix[src][dst]) {
				count_arc--;
				_vertices[src].outDegree--;
				_vertices[dst].inDegree--;
			}
			else {
				count_arc++;
				_vertices[src].outDegree++;
				_vertices[dst].inDegree++;
			}
		}

		void print_vertices() const {
			for (size_t i = 0; i < size(); ++i) {
				cout << "[" << i << "] " << ":";
				cout<< _vertices[i].data << endl;
			}
		}
		void print_matrix() const {
			cout << "    ";
			for(size_t i = 0; i < size(); ++i) {
				printf("%-4d ", i);
			}
			cout << endl;

			for (size_t i = 0; i < size(); ++i) {
				printf("%-4d", i);
				for (size_t j = 0; j < size(); ++j) {
					if (_matrix[i][j]) {
						cout << _matrix[i][j]->data << ' ';
					} else {
						cout << "NULL ";
					}
				}
				cout << endl;
			}
		}


	private:
		VertexTable _vertices;
		Matrix _matrix;
		size_t count_arc = 0;
	};//matrix使用指针存储边避免无向图同时存储两次的问题



	            





















	void test_graph01() {
		graph<char, int> G;
		G.add_vertex('A');
		G.add_vertex('B');
		G.add_vertex('C');
		G.add_vertex('D');
		G.add_vertex('E');

		G.add_edge(0, 1, 10);
		G.add_edge(0, 2, 20);
		G.add_edge(1, 2, 30);
		G.add_edge(1, 3, 40);
		G.add_edge(2, 4, 50);	

		G.del_arc(0, 1);
		G.del_arc(0, 2);
		G.del_arc(1, 2);
		G.del_arc(1, 3);
		G.del_arc(2, 4);

		G.del_vertex(4);
	}


	void test_graph02() {
		graph<char, int> G;

		G.add_vertex('A');
		G.add_vertex('B');
		G.add_vertex('C');
		G.add_vertex('D');

		for(size_t i = 0; i < G.size(); ++i) {
			cout << i << ':' << G(i)->data << endl;
		}

		size_t count = 0;
		for(size_t i = 0; i < G.size(); ++i) {
			for(size_t j = 0; j < G.size(); ++j) {
				G.add_arc(i, j,++count);
			}
		}	

		for(size_t i = 0; i < G.size(); ++i) {
			for(size_t j = 0; j < G.size(); ++j) {
				cout << G[i][j]->data << ' ';	
			}
			cout << endl;	
		}

		cout << "Edge count: " << G.edge_count() << endl;
	}

	void test_graph03() {
		graph<char, int> G;

		// 1. 添加顶点
		G.add_vertex('A');
		G.add_vertex('B');
		G.add_vertex('C');
		G.add_vertex('D');
		cout << "初始顶点数: " << G.vertex_count() << endl;

		// 2. 添加边和弧
		G.add_edge(0, 1, 10);
		G.add_edge(1, 2, 20);
		G.add_arc(2, 3, 30); // 有向边
		cout << "初始边数: " << G.edge_count() << endl;

		// 3. 检查 exists/is_edge_between
		cout << "0-1是否有边: " << G.exists(0, 1) << endl;
		cout << "1-0是否有边: " << G.exists(1, 0) << endl;
		cout << "2-3是否有边: " << G.exists(2, 3) << endl;
		cout << "0-2是否有边: " << G.exists(0, 2) << endl;
		cout << "0-1是否为无向边: " << G.is_edge_between(0, 1) << endl;
		cout << "2-3是否为无向边: " << G.is_edge_between(2, 3) << endl;

		// 4. 访问和修改顶点属性
		G(0)->status = DISCOVERED;
		G(1)->priority = 99;
		cout << "顶点0 status: " << G(0)->status << endl;
		cout << "顶点1 priority: " << G(1)->priority << endl;

		// 5. 删除边和弧
		G.del_edge(0, 1);
		G.del_arc(2, 3);
		cout << "删除边和弧后边数: " << G.edge_count() << endl;

		// 6. 再次添加和删除，测试多次调用
		G.add_edge(0, 2, 50);
		G.del_edge(0, 2);
		G.add_arc(1, 3, 60);
		G.del_arc(1, 3);
		cout << "多次添加删除后边数: " << G.edge_count() << endl;

		// 7. 删除顶点
		G.del_vertex(1);
		cout << "删除顶点1后顶点数: " << G.vertex_count() << endl;

		// 8. 检查 clear 和 empty
		G.clear();
		cout << "clear后是否为空: " << G.empty() << endl;

		// 9. 再次添加顶点和边，测试复用
		G.add_vertex('X');
		G.add_vertex('Y');
		G.add_edge(0, 1, 77);
		cout << "复用后顶点数: " << G.vertex_count() << ", 边数: " << G.edge_count() << endl;

		// 10. 检查 check/resize/shrink_to_fit
		cout << "check: " << G.check() << endl;
		G.shrink();

		// 11. 测试 operator[] 和 at
		auto& row = G[0];
		if (!row.empty() && row[1]) {
			cout << "G[0][1] = " << row[1]->data << endl;
		}
		auto vptr = G.vertex(0);
		cout << "vertex(0): " << vptr->data << endl;

		// 12. 测试 index_of/indices_of
		cout << "index_of('X'): " << G.index_of('X') << endl;
		auto idxs = G.indices_of('X');
		cout << "indices_of('X') size: " << idxs.size() << endl;

	
	}


	void test_graph04() {
		graph<char, int> G;

		G.add_vertex('A');
		G.add_vertex('B');
		G.add_vertex('C');
		G.add_vertex('D');

		G.add_arc(0, 1, 1024);
		
		G.show();

		size_t i = 0;
		G.BFS(i);
		cout << endl;
		G.DFS(0);
		cout << endl;
	}


	void test_graph05() {
		graph<int, int> G;

		G.add_vertex(0);
		G.add_vertex(1);
		G.add_vertex(2);
		G.add_vertex(3);
		G.add_vertex(4);
		G.add_vertex(5);
		G.add_vertex(6);

		G.add_edge(0, 1, 28);
		G.add_edge(0, 5, 10);
		G.add_edge(1, 6, 14);
		G.add_edge(1, 2, 16);
		G.add_edge(2, 3, 12);
		G.add_edge(3, 6, 18);
		G.add_edge(3, 4, 22);
		G.add_edge(4, 6, 24);
		G.add_edge(4, 5, 25);

		//G.show();	
		G.hehe();

		G.prim(2);
		cout << endl;
		G.dijkstra(2);
	}










}


