#ifndef __MAP_NODE_HPP__
# define __MAP_NODE_HPP__

namespace ft {

	template <typename T>
	struct map_node
	{
		T           *value;
		map_node    *parent;
		map_node    *left;
		map_node    *right;
	};
	
}

#endif