#ifndef PATH_ALGORITHMS_STRUCTS
#define PATH_ALGORITHMS_STRUCTS

namespace std
{
	template<typename G, typename N, typename C>
	class path_state : public std::enable_shared_from_this<path_state<G, N, C>> 
	{
		public:
			/*
			   G is a pointer to underlying graph
			   N is the current node aka Node
			   C is current weight
			 */
			using weight_type = C;
			using node_type = N;
			G graph_data;
			N node;
			shared_ptr<path_state<G, N, C>> parent;
			C weight;
			path_state(N n, C c, shared_ptr<path_state<G, N, C>> p, G g) 
			{
				node = n;
				weight = c;
				parent = p;
				graph_data = g;
			}

			bool operator==(const path_state& rhs) const {
				return node->get_id() == rhs.node->get_id();
			}

			bool operator!=(const path_state& rhs) const {
				return node->get_id() != rhs.node->get_id();
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

			vector<shared_ptr<path_state<G, N, C>>> expand() 
			{
				using path_state_type = path_state<G, N, C>;
				vector<shared_ptr<path_state_type>> children;
				auto edges = graph_data->edges_of_node(node);
				for (auto edge : edges) {
					C curr_weight = edge->get_weight(); 	
					N neighbour = edge->get_dst();
					shared_ptr<path_state_type> new_state = make_shared<path_state_type>(neighbour, weight + curr_weight, this->shared_from_this(), graph_data);
					children.push_back(new_state);
				}
				return children;
			}
	};

	template<typename V, typename C>
	struct path_data {
		C weight;
		vector<V> path_v;
		vector<string> path_v_stringified;
		string to_string() {
			string s;
			for (auto p : path_v) {
				s+=(p->get_id());
				s+="\n";
				s+="|";
			}
			s+="\n";
			return s;
		}
	};

	template <typename G, typename N, typename C>
		struct hash<path_state<G, N, C>>
		{
			size_t operator()(const path_state<G, N, C>& p) const noexcept
			{
				return std::hash<int>()(p.node->get_id());
			}
		};
}

#endif
