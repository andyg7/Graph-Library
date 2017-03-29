#ifndef FUNCTION_OBJS
#define FUNCTION_OBJS

template<typename V>
struct GreaterThanCost
{
	bool operator()(const V v1, const V v2) const
	{
		return v1->cost > v2->cost;
	}
};

template<typename V>
struct HeuristicGreaterThanCost
{
	bool operator()(const V v1, const V v2) const
	{
		return (v1->cost + v1->heuristic_func()) > (v2->cost + v2->heuristic_func());
	}
};

#endif
