#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <vector>

namespace graphs {

// TODO: придумать решение через умные указатели
template <typename T> class node_t {
public:
	explicit node_t(unsigned id, const T& item): id_{id}, item_{new T(item)} {}
	node_t(const node_t<T>& node) {
		std::cout << "ctor" << std::endl;
		T* new_item = new T(node.item());
		item_ = new_item;
		id_ = node.id();
	}

	~node_t() {
		// Здесь должна быть сериализация на диск (возможно)
		delete item_;
	}

	node_t& operator=(const node_t& node) {
		node_t tmp{node};
		std::swap(*this, tmp);
		return *this;
	}


	const T& item() const noexcept {
	    return *item_;
    }


	unsigned int id() const noexcept{
	    return id_;
    }

private:
	T* item_;
	unsigned id_;
};

template <typename T>
class graph_t {
public:
    using neighbours_lst = std::vector<node_t<T>*>;
    using graph_itt = typename std::vector<T>::iterator;
    using adj_index_list = std::vector<std::pair<int, int>>;

public:
	graph_t(): nodes_{}, list_adj_{} {}

	graph_t(std::vector<T> nodes) {
		for(const T& val: nodes) {
			node_t node(curr_id_, val);
			nodes_.push_back(node);
			++curr_id_;
		}
	}

	explicit graph_t(std::vector<T> nodes,
			const std::vector<std::pair<int, int>>& adjs): graph_t(nodes) {

		std::vector<neighbours_lst> tmp(nodes.size());
		for(const std::pair<int, int>& adj: adjs) {
			int first_node_index = std::get<0>(adj), second_node_index = std::get<1>(adj);
			// вызов необходим чисто чтобы в плохой момент бросить исключение out_of_range
			nodes_.at(first_node_index);
			auto n2 = nodes_.at(std::get<1>(adj));
			tmp.at(first_node_index).push_back(&n2);
		}
		std::swap(list_adj_, tmp);
	}

	graph_itt begin() const {
		return nodes_.begin();
	}
		
	graph_itt end() const {
		return nodes_.end();
	}

	

	unsigned int add_node(const T& value) {
		node_t node(curr_id_, value);
		nodes_.push_back(node);
		++curr_id_;
		list_adj_.push_back({});
		return node.id();
	}

	void add_adjacency(unsigned int first_node, unsigned int second_node) {
		auto n1 = std::find_if(nodes_.begin(), nodes_.end(), 
				[&](node_t<T> &node){ return node.id() == first_node; });
		if(n1 == nodes_.end())
			return;
		auto n2 = std::find_if(nodes_.begin(), nodes_.end(), 
				[&](node_t<T> &node){ return node.id() == second_node; });
		if(n2 == nodes_.end())
			return;

		list_adj_.at(nodes_.begin() - n1).push_back(&(*n2));
	}

	const T& find_node_by_id(unsigned int id) const {
		auto n_iter = std::find_if(nodes_.begin(), nodes_.end(), 
				[&](const node_t<T> &node){ return node.id() == id; });
		if(n_iter == nodes_.end())
			throw std::out_of_range("No such id in graph");
		else
			return (*n_iter).item();
	}

private:
	std::vector<node_t<T>> nodes_;
	std::vector<neighbours_lst> list_adj_;
	unsigned curr_id_ = 1;
};

};

#endif // graph.h
