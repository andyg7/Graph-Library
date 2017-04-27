#ifndef USER_STRUCTS_H
#define USER_STRUCTS_H

#include <string>
#include "../src/graph_lib.h"

using namespace graph_std_lib;

class city {
	public:
		using heuristic_function_type = int;
		city(string, int);
		city();
		string get_name() const;
		void set_name(string);
		int get_population() const;
		void set_population(int);
		int get_key() const;
		void set_key(int);
		bool operator==(const city&) const;
		bool operator!=(const city&) const;
		bool operator< (const city&) const;
		bool operator> (const city&) const;
		heuristic_function_type heuristic_func() const;
		string to_string() const;
		int vertex_id;
	private:
		string name;
		int population;
};

class road {
	public:
		using vertex_type = city;
		using cost_type = int;
		vertex_type v1;
		vertex_type v2;
		cost_type cost;
		bool operator==(const road& rhs) const {
		return v1 == rhs.v1 && v1 == rhs.v2;
	}
};

city::city() {}

string city::to_string() const 
{
	return name;
}

city::city(string s, int p) 
{
	name = s;
	population = p;
}

string city::get_name() const
{
	return name;
}

void city::set_name(string s)
{
	name = s;
}

int city::get_population() const
{
	return population;
}

void city::set_population(int a)
{
	population = a;
}

int city::get_key() const
{
	return vertex_id;
}

void city::set_key(int a)
{
	vertex_id = a;
}

bool city::operator==(const city& c) const
{
	return vertex_id == c.get_key();
}

bool city::operator!=(const city& c) const
{
	return vertex_id != c.get_key();
}

bool city::operator> (const city& c) const
{
	return vertex_id > c.get_key();
}

int city::heuristic_func() const
{
	return 10;
}

bool city::operator< (const city& c) const
{
	return vertex_id < c.get_key();
}

namespace std
{
	template <>
		struct hash<city>
		{
			size_t operator()(const city& n) const noexcept
			{
				return
					std::hash<string>()(n.get_name());
			}
		};
}

#endif
