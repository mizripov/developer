#ifndef _HASH_H_
#define _HASH_H_

#include "DataType.h"

template<typename _T>
inline void hashCombine(size_t& seed, const _T& value)
{
	seed ^= hash<_T>()(value) + 0x9e3379b9 + (seed << 6) + (seed >> 2);
}

template<typename _T>
inline void hashValue(size_t& seed, const _T& value)
{
	hashCombine(seed, value);
}

template<typename _T, typename ... _Types>
inline void hashValue(size_t& seed, const _T& value, const _Types &...args)
{
	hashCombine(seed, value);
	hashValue(seed, args...);
}

template<typename ... _Types>
inline size_t hashValue(const _Types &...args)
{
	size_t seed = 0;
	hashValue(seed, args...);
	return seed;
}

struct Hash
{
	size_t operator()(const Edge& edge) const 
	{
		if (edge.edgeNodes.first <= edge.edgeNodes.second) 
		{
			return hashValue(edge.edgeNodes.first, edge.edgeNodes.second);
		}
		else 
		{
			return hashValue(edge.edgeNodes.second, edge.edgeNodes.first);
		}
	}
};

#endif // !_HASH_H_
