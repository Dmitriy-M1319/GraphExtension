#include <iostream>

#include "graph.h"


int main() {
	using graphs::node_t;
	node_t<int> node{4, 5};
	node_t<int> node2 = node;
	std::cout << "Id: " << node.id() << " Data: " << node.item() << std::endl;
	std::cout << "Id: " << node2.id() << " Data: " << node2.item() << std::endl;

	std::vector<int> nodes = {1, 4, 5};
	std::vector<std::pair<int, int>> adjs = {
		{0, 1},
		{1, 2}
	};

	try {
		graphs::graph_t<int> g(nodes, adjs);
		unsigned int new_id = g.add_node(8);
		g.add_adjacency(new_id, 0);
		auto a = g.find_node_by_id(new_id);
		std::cout << a << std::endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
