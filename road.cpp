#include "road.hpp"

namespace ariel {
	Road::Road(edge* e1, edge* e2, int name){
		this->edges.first = e1;
        this->edges.second = e2;
        this->player_id = name;
	}

	int Road::get_name(){
		return this->player_id;
	}

	bool Road::is_edge_connected(edge* e){
		if (addressof(*this->edges.first) == addressof(*e)){
			return true;
		}
		if (addressof(*this->edges.second) == addressof(*e)){
			return true;
		}
		return false;
	}

	edge* Road::get_other_edge(edge* e){
		if (addressof(*this->edges.first) == addressof(*e)){
			return this->edges.second;
		}
		if (addressof(*this->edges.second) == addressof(*e)){
			return this->edges.first;
		}
		return nullptr;
	}
}