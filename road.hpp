#ifndef ROAD_H
#define ROAD_H

#include <iostream>
#include <algorithm> 
#include <vector>
#include <string>
#include "edge.hpp"

using namespace std;

namespace ariel {
class Road {
	private:
		pair<edge*, edge*> edges;
		int player_id;
	public:
		Road(edge* e1, edge* e2, int name);

		int get_name();

		bool is_edge_connected(edge* e);

		edge* get_other_edge(edge* e);
	
};

}

#endif