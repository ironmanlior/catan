#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <algorithm> 
#include <vector>
#include <string>

using namespace std;

namespace ariel {
class edge {
	private:
		vector<edge*> neighbors;
		vector<int> places;
		int player_id;
		int type;
	public:
		edge();

		int get_type() { return this->type; }
		void add_neighbor(edge* e);
		void add_neighbors(vector<edge*> e);
		vector<edge*>& get_neighbors()  { return neighbors; }
		void set_player_id(int id);
		int get_player_id() { return this->player_id; }
		void evolve();
		
	
};

}

#endif