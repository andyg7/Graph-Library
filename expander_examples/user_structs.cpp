#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "user_structs.h"

Node::Node(vector<vector<int>> g, int c, shared_ptr<Node> p)
{
	grid.resize(3);
	for (int i = 0; i < g.size(); i++) {
		vector<int> col = g[i];
		for (int j = 0; j < col.size(); j++) {
			grid[i].push_back(col[j]);
		}
	}
	cost = c;
	parent = p;
}

vector<shared_ptr<Node>> Node::expand() 
{
	vector<shared_ptr<Node>> children;
	vector<tuple<int, int>> tuples;
	tuple<int, int> zero_pos = get_zero_element();
	tuple<int, int> up = make_tuple(std::get<0>(zero_pos), std::get<1>(zero_pos) - 1);
	tuple<int, int> down = make_tuple(std::get<0>(zero_pos), std::get<1>(zero_pos) + 1);
	tuple<int, int> left = make_tuple(std::get<0>(zero_pos) - 1, std::get<1>(zero_pos));
	tuple<int, int> right = make_tuple(std::get<0>(zero_pos) + 1, std::get<1>(zero_pos));

	tuples.push_back(right);
	tuples.push_back(left);
	tuples.push_back(down);
	tuples.push_back(up);
	for (auto tup : tuples) {
		if (std::get<0>(tup) < 0) {
			continue;
		}
		if (std::get<0>(tup) > 2) {
			continue;
		}
		if (std::get<1>(tup) < 0) {
			continue;
		}
		if (std::get<1>(tup) > 2) {
			continue;
		}
		shared_ptr<Node> n = make_shared<Node>(grid, cost + 1, shared_from_this());
		n->switch_elements(zero_pos, tup);
		children.push_back(n);
	}

	return children;
}

int Node::get_element(int col, int row) const
{
	return grid[col][row];
}

int Node::get_element(tuple<int, int> t) const
{
	int col = std::get<0>(t);
	int row = std::get<1>(t);
	return grid[col][row];
}

void Node::set_element(int col, int row, int v)
{
	grid[col][row] = v;
}

void Node::set_element(tuple<int,int> t, int v)
{
	int col = std::get<0>(t);
	int row = std::get<1>(t);
	grid[col][row] = v;
}
tuple<int,int> Node::get_zero_element() const
{
	for (int col = 0; col < grid.size(); col++) {
		vector<int> column = grid[col];
		for (int row = 0; row < column.size(); row++) {
			if (grid[col][row] == 0) {
				return make_tuple(col, row);
			}
		}
	}
	throw std::runtime_error("Din't find 0 element");
}

void Node::switch_elements(tuple<int, int> t1, tuple<int, int> t2)
{
	int t1_val = get_element(t1);
	int t2_val = get_element(t2);
	set_element(t1, t2_val);
	set_element(t2, t1_val);

}

bool Node::is_goal_node()
{
	for (int col = 0; col < grid.size(); col++) {
		vector<int> column = grid[col];
		for (int row = 0; row < column.size(); row++) {
			int curr_val = get_element(col, row);
			int expected_val = (row * 3) + col;
			if (curr_val != expected_val) {
				return false;	
			}
		}
	}
	return true;
}

ostream& operator<<(ostream& os, const Node& n)
{
	return os << n.to_string();
}

void Node::set_cost(int c)
{
	cost = c;;
}

int Node::get_cost() const
{
	return cost;
}

/*
   int Node::get_estimated_cost_to_end() const
   {
   return estimated_cost_to_end;
   }
 */

void Node::set_parent(shared_ptr<Node> p)
{
	parent = p;
}

shared_ptr<Node> Node::get_parent() const
{
	return parent;
}

bool Node::operator==(const Node& rhs) const
{
	for (int i = 0; i < grid.size(); i++) {
		vector<int> col = grid[i];
		for (int j = 0; j < col.size(); j++) {
			if (grid[i][j] != rhs.get_element(i, j)) {
				return false;
			}
		}
	}
	return true;
}

bool Node::operator!=(const Node& rhs) const
{
	for (int i = 0; i < grid.size(); i++) {
		vector<int> col = grid[i];
		for (int j = 0; j < col.size(); j++) {
			if (grid[i][j] != rhs.get_element(i, j)) {
				return true;
			}
		}
	}
	return false;
}

int Node::heuristic_func() const
{
	int estimated_cost = 0;
	for (int col = 0; col < grid.size(); col++) {
		vector<int> col_data = grid[col];
		for (int j = 0; j < col_data.size(); j++) {
			int curr_elem = get_element(col, j);
			int finish_pos_x = curr_elem % 3; 
			int finish_pos_y = curr_elem / 3; 
			estimated_cost+= abs(finish_pos_x - col) + abs(finish_pos_y - j);
		}
	}
	return estimated_cost;
}

string Node::to_string() const
{
	string s;
	for (int row = 0; row < grid.size(); row++) {
		for (int col = 0; col < grid.size(); col++) {
			vector<int> col_data = grid[col];
			int curr_elem = grid[col][row]; 
			s+=std::to_string(curr_elem);
			s+=" ";
		}
		s+="\n";
	}
	return s;
}

