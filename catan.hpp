#ifndef CATAN
#define CATAN

#include <iostream>
#include <string>
#include <vector>
#include "board.hpp"
#include "player.hpp"

using namespace std;


namespace ariel{
	class Catan{
		private:
			int turn;
			Board* board;
			vector<Player*> players;
			vector<edge*> citys;
			vector<Road*> roads;
			vector<int> deck; // deck of cards
			bool choise();
			int random_card();
			bool players_turn();
			void start();
		public:
		    Catan(vector<string> players);

			void play();

			vector<Player*>& get_players();
			Board& get_board();

			void printWinner();
			void trade(Player* other, int send, int recv, int num1, int num2);
			int rollDice();
			void buy_card();
			void use_card(int type);
			void placeSettelemnt(int place, int edge, bool admin);
			void placeCity(int place, int edge);
			void placeRoad(pair<int, int> e1, pair<int, int> e2);
			void end_turn();

	};
}


#endif