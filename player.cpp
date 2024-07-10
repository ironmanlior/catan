#include "player.hpp"

using namespace std;
namespace ariel{
	Player::Player(string name){
		this->name = name;
		this->points = 0;
		this->resources = vector<int>(5, 0);
		this->cards = vector<int>(5, 0);
	}

	string Player::get_name() {
		return this->name;
	}
	
	int Player::get_card(int type){
		return this->cards[type];
        
	}
	void Player::printPoints(){
		cout << this->points << endl;
	}

	void Player::addPoints(int points){
		if (points >= this->points * (-1)) 
			this->points += points;
		else this->points = 0;
	}

	void Player::setPoints(int points){
		this->points = points;
	}
	int Player::getPoints(){
		return this->points;
	}

	string Player::to_string(){
		string s = "\n***********************************************************\n";
		s += this->name + ": " + std::to_string(this->points) + "\nResources:\n";
        s += "\twood: " + std::to_string(this->resources[0]) + "\n";
		s += "\tbrick: " + std::to_string(this->resources[1]) + "\n";
		s += "\twool: " + std::to_string(this->resources[2]) + "\n";
		s += "\tgrain: " + std::to_string(this->resources[3]) + "\n";
		s += "\tore: " + std::to_string(this->resources[4]) + "\n";
        s += "\nCards: ";
        s += "\tmonopoly: " + std::to_string(this->cards[0]) + "\n";
		s += "\tbuilding: " + std::to_string(this->cards[1]) + "\n";
		s += "\tyear of plenty: " + std::to_string(this->cards[2]) + "\n";
		s += "\tknight: " + std::to_string(this->cards[3]) + "\n";
		s += "\tvictory: " + std::to_string(this->cards[4]) + "\n";
		s += "\n***********************************************************\n";
	}

	bool Player::addResource(int type, int quantity){
		if (this->resources[type] + quantity > 0) {
			this->resources[type] += quantity;
			return true;
		}
		else this->resources[type] = 0;
		return false;
	}

	int Player::get_resource(int type){
		return this->resources[type];
	}

	void Player::addCard(int type, int quantity){
		if (this->resources[type] + quantity > 0) 
			this->resources[type] += quantity;
		else this->resources[type] = 0;
	}

	bool Player::valid_resource(int type, int quantity){
		return this->resources[type] >= quantity;
	}

	
}