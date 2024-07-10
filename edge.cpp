#include "edge.hpp"
#include <iostream>
#include <vector>
#include <string>



namespace ariel {

    edge::edge() {
        this->type = 0;
        this->player_id = -1;
    }

	void edge::evolve(){
		// none -> settlement -> city
		this->type++;
	}

    void edge::add_neighbor(edge* e) {
		if (count(this->neighbors.begin(), this->neighbors.end(), e) == 0){
        	this->neighbors.push_back(e);
			e->add_neighbor(this);
		}
    }

	void edge::add_neighbors(vector<edge*> e){
		for (int i = 0; i < e.size(); i++) {
			this->add_neighbor(e[i]);
		}
	}

	

    void edge::set_player_id(int id) {
        this->player_id = id;
    }
    
}