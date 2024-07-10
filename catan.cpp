#include "catan.hpp"

using namespace std;
namespace ariel{
//vector<string> players
//string p1, string p2, string p3
Catan::Catan(vector<string> players){
	//vector<string> players{p1, p2, p3};
	this->board = new Board();
	this->deck.push_back(2);
	this->deck.push_back(2);
	this->deck.push_back(2);
	this->deck.push_back(9);
	this->deck.push_back(4);
	for (int i = 0; i < (int)players.size(); i++){
		this->players.push_back(new Player(players[i]));
	}
	this->turn = 0;
}

void Catan::play(){
	this->start();
	bool winner = false;
	while (!winner){
		winner = this->players_turn();
	}
	this->printWinner();
}

vector<Player*>& Catan::get_players(){
	return this->players;
}
Board& Catan::get_board(){
	return *this->board;
}

void Catan::start(){
	this->board->printBoard();
	for (int i = 0; i < this->players.size(); i++){
		this->players[i]->addResource(0, 2);
		this->players[i]->addResource(1, 2);
		this->players[i]->addResource(2, 1);
		this->players[i]->addResource(3, 1);
        this->players[i]->setPoints(2);
		cout << endl << "choose coordinates:" << endl;
		pair<int, int> pos;
		cin >> pos.first;
		cin >> pos.second;
		this->placeSettelemnt(pos.first, pos.second, true);

		cout << endl << "choose coordinates:" << endl;
		cin >> pos.first;
		cin >> pos.second;
		this->placeSettelemnt(pos.first, pos.second, true);

		cout << endl << "choose coordinates:" << endl;
		pair<int, int> pos1;
		cin >> pos1.first;
		cin >> pos1.second;
		cout << endl << "choose coordinates:" << endl;
		pair<int, int> pos2;
		cin >> pos2.first;
		cin >> pos2.second;
		this->placeRoad(pos1, pos2);

		cout << endl << "choose coordinates:" << endl;
		cin >> pos1.first;
		cin >> pos1.second;
		cout << endl << "choose coordinates:" << endl;
		cin >> pos2.first;
		cin >> pos2.second;
		this->placeRoad(pos1, pos2);

		this->end_turn();
	}
}

void Catan::printWinner(){
	for (int i = 0; i < this->players.size(); i++){
		if (this->players[i]->getPoints() >= 10)
		    cout << this->players[i]->to_string();
	}
}

void Catan::trade(Player* other, int send, int recv, int num1, int num2){
	Player* me = this->players[this->turn];
	bool me_has = me->valid_resource(send, num1);
	bool other_has = other->valid_resource(recv, num2);
	if (!me_has || !other_has) {
		std::cout << "Trade failed due to insufficient resources." << std::endl;
		return;
	}
	me->addResource(send, (-1) * num1);
	other->addResource(send, num1);

	other->addResource(recv, (-1) * num2);
	me->addResource(recv, num2);
	std::cout << "Trade completed." << std::endl;
}

int Catan::rollDice(){
	srand(time(NULL));
	return rand() % 11 + 2;
}

void Catan::buy_card(){
	Player* me = this->players[this->turn];
	bool has_wool = me->valid_resource(2, 1);
	bool has_grain = me->valid_resource(3, 1);
	bool has_ore = me->valid_resource(4, 1);
	if (!has_wool || !has_grain || !has_ore) {
		std::cout << "Not enough resources to buy a development card." << std::endl;
		return;
	}

	int card_type = this->random_card();
	if (card_type == -1) {
		std::cout << "No more development cards left in the deck." << std::endl;
		return;
	}

	this->deck[card_type]--;
	me->addCard(card_type, 1);

	if (card_type == 4) 
		me->addPoints(1);
	
	if (card_type == 3) {
		if (me->get_card(3) == 3){
			me->addPoints(2);
		}
	}

	me->addResource(2, -1);
	me->addResource(3, -1);
	me->addResource(4, -1);

	std::cout << "Trade completed." << std::endl;
}

void Catan::use_card(int type){
	Player* me = this->players[this->turn];
	if (me->get_card(type) < 1) {
		cout << "Not enough development cards to use this card." << endl;
        return;
	}
	me->addCard(type, -1);
	switch (type) {
		
        case 0:
			cout << "whitch resource do you want to take from the other player?" << endl;
			cout << "1. wood" << endl;
			cout << "2. brick" << endl;
			cout << "3. wool" << endl;
			cout << "4. grain" << endl;
			cout << "5. ore" << endl;
			int resource;
			cin >> resource;
			resource--;

			for (Player *p: players) {
				if (me->get_name() != p->get_name()) {
					me->addResource(resource, p->get_resource(resource));
					p->addResource(resource, (-1) * p->get_resource(resource));
				}
			}
            break;
        case 1:
			for(int i = 0; i < 2; i++) {
				me->addResource(0, 1);
				me->addResource(1, 1);
				int place1, edge1, place2, edge2;
				cout << "place 1: ";
                cin >> place1;
				cout << "edge 1: ";
                cin >> edge1;
				cout << "place 2: ";
                cin >> place2;
				cout << "edge 2: ";
                cin >> edge2;
				pair<int, int> e1(place1, edge1);
				pair<int, int> e2(place2, edge2);
				this->placeRoad(e1, e2);
			}
			
            break;
		case 2:
			for (int i = 0; i < 2; i++) {
				cout << "whitch resource do you want to take?" << endl;
				cout << "1. wood" << endl;
				cout << "2. brick" << endl;
				cout << "3. wool" << endl;
				cout << "4. grain" << endl;
				cout << "5. ore" << endl;
				int resource;
				cin >> resource;
				resource--;
				me->addResource(resource, 1);
			}
            break;
		case 3:
			cout << "the knight card can't be used" << endl;
            break;
        case 4:
		    cout << "the victory point card can't be used" << endl;
            break;
        default:
            std::cout << "Invalid card type." << std::endl;
            return;
	}



	
	
}

void Catan::placeSettelemnt(int place, int edge1, bool admin){
	Player* me = this->players[this->turn];
	bool has_wood = me->valid_resource(0, 1);
	bool has_brick = me->valid_resource(1, 1);
	bool has_wool = me->valid_resource(2, 1);
	bool has_grain = me->valid_resource(3, 1);
	if (!has_wood || !has_brick || !has_wool || !has_grain) {
		cout << "Not enough resources to build a road." << endl;
        return;
	}
	edge* e = this->board->getPlaces()[place]->get_vertex(edge1).first;

	for (int i = 0; i < this->citys.size(); i++) {
		if (addressof(*this->citys[i]) == addressof(*e)) {
			cout << "Cannot build settlemnt here." << endl;
            return;
		}
	}

	if (e->get_type() > 0) {
		cout << "settlemnt already exists." << endl;
		return;
	}
	if (!admin){
		bool con = false;

		for (int i = 0; i < this->roads.size(); i++){
			con |= this->roads[i]->is_edge_connected(e);
		}

		if (!con) {
			cout << "road not connected." << endl;
			return;
		}
	}

	e->evolve();
	e->set_player_id(this->turn);
	this->citys.push_back(e);

	me->addPoints(1);

	me->addResource(0, -1);
	me->addResource(1, -1);
	me->addResource(2, -1);
	me->addResource(3, -1);
}

void Catan::placeCity(int place, int edge1){
	Player* me = this->players[this->turn];
	bool has_ore = me->valid_resource(4, 3);
	bool has_grain = me->valid_resource(3, 2);
	if (!has_ore || !has_grain) {
		cout << "Not enough resources to build a road." << endl;
        return;
	}
	edge* e = this->board->getPlaces()[place]->get_vertex(edge1).first;

	if (e->get_type() != 1) {
		cout << "settlemnt not exists." << endl;
		return;
	}
	e->evolve();
	me->addPoints(1);

	me->addResource(3, -2);
	me->addResource(4, -3);
}

void Catan::placeRoad(pair<int, int> e1, pair<int, int> e2){
	Player* me = this->players[this->turn];
	bool has_wood = me->valid_resource(0, 1);
	bool has_brick = me->valid_resource(1, 1);
	if (!has_wood || !has_brick) {
		cout << "Not enough resources to build a road." << endl;
        return;
	}
	edge* edge1 = this->board->getPlaces()[e1.first]->get_vertex(e1.second).first;
	edge* edge2 = this->board->getPlaces()[e2.first]->get_vertex(e2.second).first;

	vector<edge*> v = edge1->get_neighbors();
	if (count(v.begin(), v.end(), edge2) == 0){
		std::cout << "Cannot build road here." << std::endl;
        return;
	}


	Road* road = new Road(edge1, edge2, this->turn);

	bool con = false;
	con |= edge1->get_type() > 0;
	con |= edge2->get_type() > 0;
	if (!con){
		for (int i = 0; i < this->roads.size(); i++) {
			if (addressof(*this->roads[i]->get_other_edge(edge1)) == addressof(*edge2)) {
				cout << "Road already exists" << endl;
				return;
			}
			bool con1 = this->roads[i]->is_edge_connected(edge1);
			con |= con1;
			bool con2 = this->roads[i]->is_edge_connected(edge2);
			con |= con2;
		}
	}
	if (!con){
		cout << "road not connected to anther road or Settelemnt" << endl;
		return;
	}
	this->roads.push_back(road);

	me->addResource(0, -1);
	me->addResource(1, -1);
}


void Catan::end_turn(){
	this->turn = (this->turn + 1) % this->players.size();
}

bool Catan::choise(){
	Player* me = this->players[this->turn];
    int choice;
    cout << "Player " << me->get_name() << ", choose an action:" << endl;
    cout << "1. Trade" << endl;
    cout << "2. Build settlement" << endl;
	cout << "3. Build city" << endl;
    cout << "4. Build road" << endl;
	cout << "5. Buy card" << endl;
	cout << "6. Use card" << endl;
    cout << "7. End turn" << endl;
    cin >> choice;
    if (choice == 1){
		cout << endl << "choose player to trade:" << endl;
		for (int i = 0; i < this->players.size(); i++){
			cout << (i + 1) << ". " << this->players[i]->get_name() << endl;
		}
		int player_num;
		cin >> player_num;
		player_num--;

		cout << endl << "choose resource and amount to send:" << endl;
		cout << "1. wood" << endl;
		cout << "2. brick" << endl;
		cout << "3. wool" << endl;
		cout << "4. grain" << endl;
		cout << "5. ore" << endl;
		pair<int, int> send;
		cin >> send.first;
		cin >> send.second;
		send.first--;

		cout << endl << "choose resource and amount to recive:" << endl;
		cout << "1. wood" << endl;
		cout << "2. brick" << endl;
		cout << "3. wool" << endl;
		cout << "4. grain" << endl;
		cout << "5. ore" << endl;
		pair<int, int> recv;
		cin >> recv.first;
		cin >> recv.second;
		recv.first--;
		this->trade(this->players[player_num], send.first, recv.first, send.second, recv.second);
	}
	else if (choice == 2){
		cout << endl << "choose coordinates:" << endl;
		pair<int, int> pos;
		cin >> pos.first;
		cin >> pos.second;
		this->placeSettelemnt(pos.first, pos.second, false);
    }
	else if (choice == 3){
		cout << endl << "choose coordinates:" << endl;
		pair<int, int> pos;
		cin >> pos.first;
		cin >> pos.second;
		this->placeCity(pos.first, pos.second);
	}
	else if (choice == 4){
			cout << endl << "choose coordinates:" << endl;
			pair<int, int> pos1;
			cin >> pos1.first;
			cin >> pos1.second;
			cout << endl << "choose coordinates:" << endl;
			pair<int, int> pos2;
			cin >> pos2.first;
			cin >> pos2.second;
            this->placeRoad(pos1, pos2);
		}
	else if (choice == 5){
		this->buy_card();
	}
	else if (choice == 6){
		cout << "choose card:" << endl;
		cout << "1. monopoly" << endl;
		cout << "2. building" << endl;
		cout << "3. year of plenty" << endl;
		cout << "4. knight" << endl;
		cout << "5. victory" << endl;
		int card;
		cin >> card;
		this->use_card(card);
		this->end_turn();
		return false;
	}
	else {
		this->end_turn();
		return false;
	}
	return true;
}

bool Catan::players_turn(){
	this->board->printBoard();
	for (int i = 0; i < this->players.size(); i++){
		cout << this->players[i]->to_string();
	}
	int dice = this->rollDice();
	for (int i = 0; i < this->board->getPlaces().size(); i++){
		Place* place = this->board->getPlaces()[i];
		if (place->getNumber() != dice) continue;
		for (int j = 0; j < 6; j++){
			edge* e = place->get_vertex(j).first;
			int id = e->get_player_id();
			if (id == -1) continue;
			Player* player = this->players[id];
			player->addResource(place->getResource(), e->get_type());
		}
	}

	while (this->choise());

	for (int i = 0; i < this->players.size(); i++){
		if (this->players[i]->getPoints() >= 10)
		    return true;
	}

	return false;

}

int Catan::random_card(){
	vector<int> temp;
	for (int i = 0; i < this->deck.size(); i++){
		for (int j = 0; j < this->deck[i]; j++){
			temp.push_back(i);
		}
	}
	if (temp.size() == 0) return -1;
	srand(time(NULL));
	return temp[rand() % temp.size()];
}

}