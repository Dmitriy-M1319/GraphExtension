#ifndef GRAPH_H
#define GRAPH_H

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>

namespace graphs {

template <typename T> class Vertex {
public:
	Vertex(unsigned id, std::string label, const T& item): id_{id}, label_{label}, item_{new T(item)} {}
    Vertex(Vertex&& node): id_{std::move(node.id_)}, label_{std::move(node.label_)}, item_{std::move(node.item_)} {}
	
	Vertex& operator=(const Vertex& node) {
		Vertex tmp{node};
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
    std::unique_ptr<T> item_;
    std::string label_;
	unsigned id_;
};




class Edge {
public:
    Edge(uint32_t fst, uint32_t snd, std::string label = ""):
        from_{fst}, to_{snd}, label_{label} {}

    uint32_t from() const noexcept {
        return from_;
    }

    uint32_t to() const noexcept {
        return to_;
    }

    const std::string& label() const noexcept {
        return label_;
    }

    void setLabel(const std::string& label) {
        label_ = label;
    }

    void setLabel(std::string&& label) {
        label_ = std::move(label);
    }
    
    void setBidirectional(bool direction) {
        is_bidirectional_ = direction;
    }

    void reverseDirection() {
        std::swap(from_, to_);
    }

    bool equals(const Edge& e) const noexcept {
        return e.from() == from_ && e.to() == to_ && e.label() == label_;
    }

private:
    bool is_bidirectional_ = false;
    uint32_t from_;
    uint32_t to_;
    std::string label_;
};






template <typename T>
class Graph {
public:
    using neighbours_lst = std::vector<Vertex<T>>;
    using graph_itt = typename std::vector<T>::iterator;
    using adj_index_list = std::vector<std::pair<int, int>>;

public:
	Graph(): nodes_{}, list_adj_{} {}

	Graph(std::vector<T> nodes) {
		for(const T& val: nodes) {
			Vertex node(curr_id_, val);
			nodes_.push_back(node);
			++curr_id_;
		}
	}

	explicit Graph(std::vector<T> nodes,
			const std::vector<std::pair<int, int>>& adjs): Graph(nodes) {

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
		Vertex node(curr_id_, value);
		nodes_.push_back(node);
		++curr_id_;
		list_adj_.push_back({});
		return node.id();
	}

	void add_adjacency(unsigned int first_node, unsigned int second_node) {
		auto n1 = std::find_if(nodes_.begin(), nodes_.end(), 
				[&](Vertex<T> &node){ return node.id() == first_node; });
		if(n1 == nodes_.end())
			return;
		auto n2 = std::find_if(nodes_.begin(), nodes_.end(), 
				[&](Vertex<T> &node){ return node.id() == second_node; });
		if(n2 == nodes_.end())
			return;

		list_adj_.at(nodes_.begin() - n1).push_back(&(*n2));
	}

	const T& find_node_by_id(unsigned int id) const {
		auto n_iter = std::find_if(nodes_.begin(), nodes_.end(), 
				[&](const Vertex<T> &node){ return node.id() == id; });
		if(n_iter == nodes_.end())
			throw std::out_of_range("No such id in graph");
		else
			return (*n_iter).item();
	}

private:
	std::vector<Vertex<T>> nodes_;
	std::vector<neighbours_lst> list_adj_;
	unsigned curr_id_ = 1;
};

};

#endif // graph.h
