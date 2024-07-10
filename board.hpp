#ifndef BOARD
#define BOARD

#include <vector>
#include <random> 
#include <iostream>
#include <algorithm> 
#include "place.hpp"
#include "edge.hpp"

using namespace std;


namespace ariel{
	class Place;
	class Board{
		private:
			vector<Place*> places;
			void assignNumbers();
			void init_places();
			void shuffle_places(vector<string>& places);
		public:
		    Board();
			vector<Place*>& getPlaces() ;
			void printBoard();
	};
}


#endif