#ifndef USER_STRUCTS_H
#define USER_STRUCTS_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

class Node;
ostream& operator<<(ostream& os, const Node& n);

class Node : public std::enable_shared_from_this<Node>
{
	public:
		using node_type = Node;
		using weight_type = int;
		int vertex_id;
		using cost_type = int;
		Node(vector<vector<int>>, int, shared_ptr<Node>);
		vector<shared_ptr<Node>> expand();
		int get_element(int, int) const;
		int get_element(tuple<int,int>) const;
		void set_element(int, int, int);
		void set_element(tuple<int,int>, int);
		void switch_elements(tuple<int, int>, tuple<int, int>);
		bool is_goal_node();
		void set_cost(int);
		int get_cost() const;
		void set_parent(shared_ptr<Node> p);
		shared_ptr<Node> get_parent() const;
		bool operator==(const Node& rhs) const;
		bool operator!=(const Node& rhs) const;
		int heuristic_func() const;
		shared_ptr<Node> parent;
		int weight;
		string to_string() const;

		//int get_estimated_cost_to_end() const;
	private:
		vector<vector<int>> grid;
		tuple<int,int> get_zero_element() const;
		//int estimated_cost_to_end;
};

namespace std
{
	template <>
		struct hash<Node>
		{
			size_t operator()(const Node& n) const noexcept
			{
				return std::hash<string>()(n.to_string());
			}
		};
}
#endif
