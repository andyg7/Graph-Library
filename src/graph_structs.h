#ifndef GRAPH_STRUCTS_H
#define GRAPH_STRUCTS_H

#include <vector>
#include <memory>
#include <unordered_map>

using Value = std::pair<string,int>;
using namespace std;

namespace graph_std_lib 
{
	template<typename T>
	struct vertex_wrapper {
		using vertex_type = T;
		vertex_type vertex_data;
		Value value;

		vertex_wrapper(vertex_type v) {
			vertex_data = v;
		}

		bool operator==(const vertex_wrapper& rhs) const {
			return vertex_data == rhs.vertex_data;
		}
		bool operator!=(const vertex_wrapper& rhs) const  {
			return vertex_data != rhs.vertex_data;
		}
	};

	template<typename T, typename E>
	struct edge_wrapper {
		E edge;
		Value value;
	};

	template<typename T, typename E>
	struct vertex_header {
		using vertex_wrapper_type = shared_ptr<vertex_wrapper<T>>;
		using edge_wrapper_type = shared_ptr<edge_wrapper<T, E>>;
		using neighbors_type = vector<shared_ptr<vertex_wrapper<T>>>;
		using edges_type = vector<shared_ptr<edge_wrapper<T, E>>>;

		vertex_wrapper_type vertex_wrapper_data;
		vertex_header(T v) {
			vertex_wrapper_data = std::make_shared<vertex_wrapper<T>>(v);
		}

		neighbors_type neighbors;
		edges_type edges;
	};

	struct vertex {
		int vertex_id;
		bool operator==(const vertex& rhs) const {
			return vertex_id == rhs.vertex_id;
		}		
		bool operator!=(const vertex& rhs) const {
			return vertex_id != rhs.vertex_id;
		}		
		bool operator> (const vertex& rhs) const {
			return vertex_id > rhs.vertex_id;
		}
		bool operator< (const vertex& rhs) const {
			return vertex_id < rhs.vertex_id;
		}
		vertex& operator=(const vertex& rhs) {
			vertex_id = rhs.vertex_id;
			return *this;
		}
		int get_key() const {
			return vertex_id;
		}
		void set_key(int a) {
			vertex_id = a;
		}

		string to_string() {
			return std::to_string(vertex_id);
		}
	};


	struct edge {
		using vertex_type = vertex;
		using cost_type = int;
		cost_type cost;
		vertex_type v1;
		vertex_type v2;

		bool operator==(const edge& rhs) const {
			return rhs.v1 == v1 && rhs.v2 == v2;
		}		
	};

	template<typename V, typename E>
	requires Vertex<V> && Edge<E> && Matching_vertices_edges<E, V> 
	struct dg_graph {
		using graph_type = DG;
		using edge_type = E;
		using vertex_type = V;
		using vertex_header_type = vertex_header<V, E>;
		using vertex_wrapper_type = vertex_wrapper<V>;
		using underlying_data_type = vector<vertex_header<V, E>>;
		underlying_data_type underlying_data;
	};

	template<typename V, typename E>
	requires Vertex<V> && Edge<E> && Matching_vertices_edges<E, V> 
	struct matrix_graph {
		using graph_type = Matrix_graph;
		using edge_type = E;
		using vertex_type = V;
		using vertex_header_type = vertex_header<V, E>;
		using vertex_wrapper_type = vertex_wrapper<V>;
		using underlying_data_type = vector<vector<int>>;
		underlying_data_type underlying_data;
		unordered_map<int, shared_ptr<vertex_wrapper_type>> id_to_wrapper;
		unordered_map<shared_ptr<vertex_wrapper_type>, int> wrapper_to_id;
		matrix_graph(int n) 
		{
			for (int i = 0; i < n; i++) {
				underlying_data.push_back(vector<int>(n));
				auto c_v = underlying_data[i];
				for (int j = 0; j < n; j++) {
					c_v[j] = 0;
				}
			}
		}
		matrix_graph() {}
	};

	template<typename V, typename E>
	requires Vertex<V> && Edge<E> && Matching_vertices_edges<E, V> 
	struct dag_graph {
		using graph_type = DAG;
		using edge_type = E;
		using vertex_type = V;
		using vertex_wrapper_type = vertex_wrapper<V>;
		using vertex_header_type = vertex_header<V, E>;
		using underlying_data_type = vector<vertex_header<V, E>>;
		underlying_data_type underlying_data;
	};

	template<typename V, typename E>
	requires Vertex<V> && Edge<E> && Matching_vertices_edges<E, V> 
	struct dt_graph {
		using graph_type = DT;
		using edge_type = E;
		using vertex_type = V;
		using vertex_header_type = vertex_header<V, E>;
		using vertex_wrapper_type = vertex_wrapper<V>;
		using underlying_data_type = vector<vertex_header<V, E>>;
		underlying_data_type underlying_data;
	};
}

using namespace graph_std_lib;
namespace std
{
	template <>
	struct hash<vertex>
		{
			size_t operator()(const vertex& n) const noexcept
			{
				return std::hash<int>()(n.vertex_id);
			}
		};

	template <typename T>
	struct hash<vertex_wrapper<T>>
		{
			size_t operator()(const vertex_wrapper<T>& n) const noexcept
			{
				return std::hash<T>()(n.vertex_data);
			}
		};
}

#endif
