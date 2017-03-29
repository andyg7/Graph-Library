#ifndef PATH_ALGORITHMS_STRUCTS
#define PATH_ALGORITHMS_STRUCTS

namespace std
{
	template<typename T, typename C>
	class path_state;

	template<typename T, typename C>
	class path_state : public std::enable_shared_from_this<path_state<T, C>> 
	{
		public:
			using vertex_wrapper_type = typename T::vertex_wrapper_type;
			using cost_type = C;
			shared_ptr<vertex_wrapper_type> vertex_wrapper_data;
			shared_ptr<path_state<T, cost_type>> parent;
			C cost;
			T graph_data;

			path_state(shared_ptr<vertex_wrapper_type> v, C c, shared_ptr<path_state<T, cost_type>> p, T g) {
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

			vector<shared_ptr<path_state<T, C>>> expand()
			{
				vector<shared_ptr<path_state<T, C>>> children;
				auto it = graph_data.underlying_data.begin();
				auto it_end = graph_data.underlying_data.end();
				for (; it != it_end; it++) {
					if (*(it->vertex_wrapper_data) == *vertex_wrapper_data) {
						break;
					}
				}
				auto edges = it->edges;
				auto neighbors = it->neighbors;
				for (auto e : edges) {
					for (auto n : neighbors) {
						if (n->vertex_data == e->edge.v2) {
							shared_ptr<path_state<T, C>> new_helper = make_shared<path_state<T, C>>(n, cost + e->edge.cost, this->shared_from_this(), graph_data);
							children.push_back(new_helper);
						}
					}
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
				s+="|";
				s+="\n";
			}
			s+="\n";
			return s;
		}
	};

	template <typename T, typename C>
		struct hash<path_state<T, C>>
		{
			size_t operator()(const path_state<T, C>& n) const noexcept
			{
				return std::hash<typename T::vertex_type>()((n.vertex_wrapper_data)->vertex_data);
			}
		};
}

#endif
