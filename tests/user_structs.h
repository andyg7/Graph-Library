#ifndef USER_STRUCTS_H
#define USER_STRUCTS_H

#include "../src/graph_lib.h"
#include <string>

using namespace graph_std_lib;

struct my_vertex {
	int vertex_id;
	bool operator==(const my_vertex& rhs) const {
		return vertex_id == rhs.vertex_id;
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

namespace std
{
	template <>
		struct hash<my_vertex>
		{
			size_t operator()(const my_vertex& n) const noexcept
			{
				return std::hash<int>()(n.vertex_id);
			}
		};
}

struct my_edge {
	using vertex_type = my_vertex;
	using cost_type = int;
	int cost;
	vertex_type v1;
	vertex_type v2;
	bool operator==(const my_edge& rhs) const {
		return v1 == rhs.v1 && v2 == rhs.v2;
	}
};

struct user_vertex_1 {
	int vertex_id;
	bool operator==(const user_vertex_1& rhs) const {
		return vertex_id == rhs.vertex_id;
	}
	bool operator!=(const user_vertex_1& rhs) const {
		return vertex_id != rhs.vertex_id;
	}
	bool operator< (const user_vertex_1& rhs) const {
		return vertex_id < rhs.vertex_id;
	}
	bool operator> (const user_vertex_1& rhs) const {
		return vertex_id > rhs.vertex_id;
	}

	int get_key() const {
		return vertex_id;
	}
	void set_key(int a) {
		vertex_id = a;
	}
	string name;

	string to_string() {
		return std::to_string(vertex_id);
	}
};

namespace std
{
	template <>
		struct hash<user_vertex_1>
		{
			size_t operator()(const user_vertex_1& n) const noexcept
			{
				return std::hash<int>()(n.vertex_id);
			}
		};
}
struct user_edge_1 {
	using vertex_type = user_vertex_1;
	using cost_type = int;
	int cost;
	vertex_type v1;
	vertex_type v2;
	bool operator==(const user_edge_1& rhs) const {
		return v1 == rhs.v1 && v2 == rhs.v2;
	}
};

struct user_vertex_2 {
	int vertex_id;
	using cost_type = int;
	bool operator==(const user_vertex_2& rhs) const {
		return vertex_id == rhs.vertex_id;
	}
	bool operator!=(const user_vertex_2& rhs) const {
		return vertex_id != rhs.vertex_id;
	}
	bool operator< (const user_vertex_2& rhs) const {
		return vertex_id < rhs.vertex_id;
	}
	bool operator> (const user_vertex_2& rhs) const {
		return vertex_id > rhs.vertex_id;
	}

	int get_key() const {
		return vertex_id;
	}
	void set_key(int a) {
		vertex_id = a;
	}
	string name;
	string city;
	string counter;
	int population;
	string to_string() {
		return std::to_string(vertex_id);
	}
};

namespace std
{
		template <>
		struct hash<user_vertex_2>
		{
			size_t operator()(const user_vertex_2& n) const noexcept
			{
				return std::hash<int>()(n.vertex_id);
			}
		};
}

struct user_edge_2 {
	using vertex_type = user_vertex_2;
	using cost_type = int;
	int cost;
	vertex_type v1;
	vertex_type v2;
	bool operator==(const user_edge_2& rhs) const {
		return v1 == rhs.v1 && v2 == rhs.v2;
	}
};

#endif
