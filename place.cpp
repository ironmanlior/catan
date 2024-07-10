#include "place.hpp"
namespace ariel {

Place::Place(string type, int id){
	this->type = type;
	this->number = 0;
    this->id = id;
	this->is_neighbors = vector<bool>(6, false);
	this->neighbors = vector<Place*>(6, nullptr);
	for (int i = 0; i < 6; i++) {
		this->edges.push_back(new edge());
	}
	
}



string Place::getType(){ return this->type; }
int Place::getId(){ return this->id; }
int Place::getNumber(){ return this->number; }
void Place::setNumber(int number){ this->number = number; }

int Place::getResource(){
	if (this->type == "FOREST") return 0;
	else if (this->type == "HILL") return 1;
	else if (this->type == "PASTURE") return 2;
	else if (this->type == "FIELD") return 3;
	else if (this->type == "MOUNTAIN") return 4;
	else return -1;
}



pair<edge*,edge*> Place::get_vertex(int id){
	pair<edge*,edge*> p;
	p.first = this->edges[id % 6];
	p.second = this->edges[(id + 1) % 6];
	return p;
}

bool Place::has_neighbor(int id){
	return this->is_neighbors[id];
}
Place* Place::get_neighbor(int id){
	return this->neighbors[id];
}

void Place::connect(Place* other, int vertex){
	if (this->is_neighbors[vertex]) return;
	this->is_neighbors[vertex] = true;
	this->neighbors[vertex] = other;
	
	pair<edge*,edge*> p = other->get_vertex((vertex + 3) % 6);
	this->edges[vertex % 6] = p.second;
	this->edges[(id + 1) % 6] = p.first;

	if (other->has_neighbor((vertex + 2) % 6)){
		this->connect(other->get_neighbor((vertex + 2) % 6), (vertex + 1) % 6);
	}
	if (other->has_neighbor((vertex + 4) % 6)){
		this->connect(other->get_neighbor((vertex + 4) % 6), (vertex + 5) % 6);
	}

	other->connect(this, (vertex + 3) % 6);
}

void Place::connect_edges(){
	for (int i = 0; i < 5; i++){
        this->edges[i]->add_neighbor(this->edges[(i + 1) % 6]);
    }
}

string Place::to_string(){
	string s = this->type;
	if (s=="DESERT")
		return s;
	s = s + std::to_string(this->number);
	return s;
}

}