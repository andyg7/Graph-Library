#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include "user_structs.h"
#include "../src/graph_lib.h"

using namespace std;
vector<int> get_unique_elems(int n);

int main(int argc, const char *argv[]) 
{
	vector<vector<int>> v(3);
	int num_cols = 3;
	vector<int> unique_elems = get_unique_elems(10);
	for (int i = 0; i < num_cols; i++) {
		for (int j = 0; j < num_cols; j++) {
			int curr_index = (j * 3) + i;
			v[i].push_back(unique_elems[curr_index]);
		}
	}
	shared_ptr<Node> n = make_shared<Node>(v, 0, nullptr);
	n->set_element(0,0,4);
	n->set_element(1,0,0);
	n->set_element(2,0,3);
	n->set_element(0,1,7);
	n->set_element(1,1,1);
	n->set_element(2,1,5);
	n->set_element(0,2,8);
	n->set_element(1,2,2);
	n->set_element(2,2,6);
	shared_ptr<Node> goal_state = make_shared<Node>(v, 0, nullptr);
	goal_state->set_element(0,0,0);
	goal_state->set_element(1,0,1);
	goal_state->set_element(2,0,2);
	goal_state->set_element(0,1,3);
	goal_state->set_element(1,1,4);
	goal_state->set_element(2,1,5);
	goal_state->set_element(0,2,6);
	goal_state->set_element(1,2,7);
	goal_state->set_element(2,2,8);
	if (!path_exists(n, goal_state)) {
		cout << "No path ! \n";
		return 0;
	}
	shared_ptr<struct path_data<Node, int>> path_d = find_path_ast(n, goal_state);
	vector<Node> path = path_d->path_v;
	cout << "ast path\n";
	for (int i = 0; i < path.size(); i++) {
		auto v = path[i];
		cout << v << '\n';
	}
	path_d = find_path_dfs(n, goal_state);
	path_d = find_path_bfs(n, goal_state);
	path_d = find_path_ucs(n, goal_state);
	return 0;
}


vector<int> get_unique_elems(int n)
{
	uniform_int_distribution<> dist {0, 9};
	default_random_engine re {};

	set<int> picked_nums;
	vector<int> numbers;
	for (int i = 0; i < n; i++) {
		bool is_unique = false;
		do {
			int num = dist(re);
			if (picked_nums.find(num) == picked_nums.end()) {
				is_unique = true;
				picked_nums.insert(num);
				numbers.push_back(num);
			}

		} while (is_unique == false);
	}
	return numbers;
}
