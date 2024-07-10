#ifndef PLAYER
#define PLAYER

#include <iostream>
#include <string>
#include <vector>
#include "board.hpp"
#include "road.hpp"

using namespace std;


namespace ariel{
	class Player{
		private:
		    int points;
			string name;
			vector<int> resources;
			vector<int> cards;

			
		public:
		    Player(string name);

			int get_card(int type);
			void addCard(int type, int quantity);

			string get_name();
			
			void printPoints();
			void addPoints(int points);
			void setPoints(int points);
			int getPoints();
			
			string to_string();
			bool addResource(int type, int quantity);
			int get_resource(int type);
			bool valid_resource(int type, int quantity);

	};
}


#endif