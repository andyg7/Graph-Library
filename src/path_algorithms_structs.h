#ifndef PATH_ALGORITHMS_STRUCTS
#define PATH_ALGORITHMS_STRUCTS

#include "graph_lib_header_helper.h"

namespace std
{
	template<typename G, typename C>
	class path_state;

	template<typename G, typename C>
	class path_state : public std::enable_shared_from_this<path_state<G, C>> 
	{
		public:
			using vertex_type = typename G::element_type::vertex_type;
			using vertex_wrapper_type = typename G::element_type::vertex_wrapper_type;
			using cost_type = C;
			shared_ptr<vertex_wrapper_type> vertex_wrapper_data;
			shared_ptr<path_state<G, cost_type>> parent;
			C cost;
			G graph_data;

			path_state(shared_ptr<vertex_wrapper_type> v, C c, shared_ptr<path_state<G, cost_type>> p, G g) {
				vertex_wrapper_data = make_shared<vertex_wrapper_type>(*v);	
				cost = c;
				parent = p;
				graph_data = g;
			};

			bool operator==(const path_state& rhs) const {
				return *vertex_wrapper_data == *(rhs.vertex_wrapper_data);
			}
			bool operator!=(const path_state& rhs) const  {
				return *vertex_wrapper_data != *(rhs.vertex_wrapper_data);
			}
			bool operator==(nullptr_t n) const  {
				if (this == nullptr) {
					return true;
				}
				return false;
			}
			bool operator!=(nullptr_t n) const  {
				if (this == nullptr) {
					return false;
				}
				return true;
			}

			string to_string() {
				string s = (vertex_wrapper_data->vertex_data).to_string();
				return s;
			}

			C heuristic_func() 
			{
				return (vertex_wrapper_data->vertex_data).heuristic_func();
			}

			vector<shared_ptr<path_state<G, C>>> expand()
			{
				vector<shared_ptr<path_state<G, C>>> children;
				shared_ptr<typename G::element_type::vertex_type> tmp_v = make_shared<typename G::element_type::vertex_type>(vertex_wrapper_data->vertex_data);
				auto edges = get_edges_for_vertex(graph_data, tmp_v);
				for (auto e : edges) {
					shared_ptr<vertex_type> t_p = make_shared<vertex_type>(e.v2);
					auto v_w = get_vertex_wrapper(graph_data, t_p);
					shared_ptr<path_state<G, C>> new_helper = make_shared<path_state<G, C>>(v_w, cost + e.cost, this->shared_from_this(), graph_data);
					children.push_back(new_helper);
				}
				return children;
			}

	};

	template<typename V, typename C>
	struct path_data {
		C cost;
		vector<V> path_v;
		vector<string> path_v_stringified;
		string to_string() {
			string s;
			for (auto p : path_v_stringified) {
				s+=p;
				s+="\n";
				s+="|";
			}
			s+="\n";
			return s;
		}
	};

	template <typename G, typename C>
		struct hash<path_state<G, C>>
		{
			size_t operator()(const path_state<G, C>& n) const noexcept
			{
				return std::hash<typename G::element_type::vertex_type>()((n.vertex_wrapper_data)->vertex_data);
			}
		};
}

#endif
