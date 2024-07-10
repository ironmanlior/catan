#include "board.hpp"


using namespace std;

namespace ariel {

    Board::Board() {
        
		init_places();
        assignNumbers();
    }
    void Board::init_places() {
        
        vector<string> placeTypes = {
                "FOREST", "FOREST", "FOREST", "FOREST",
                "HILL", "HILL", "HILL",
                "PASTURE", "PASTURE", "PASTURE", "PASTURE",
                "FIELD", "FIELD", "FIELD", "FIELD",
                "MOUNTAIN", "MOUNTAIN", "MOUNTAIN",
                "DESERT"
        };
        
        // Shuffle the placeTypes vector
		this->shuffle_places(placeTypes);
        
        // Clear the existing places
        this->places.clear();
        

        // Create a place for each type in placeTypes and add it to the places vector
        for (int i = 0; i < placeTypes.size(); ++i) {
			Place* place = new Place(placeTypes[i], i + 1);
            this->places.push_back(place);
        }
		// Connect the places
		this->places[3]->connect(this->places[0], 1);
		this->places[4]->connect(this->places[0], 0);
		this->places[5]->connect(this->places[1], 0);
		this->places[6]->connect(this->places[2], 0);
		this->places[7]->connect(this->places[3], 1);
		this->places[8]->connect(this->places[3], 0);
		this->places[9]->connect(this->places[4], 0);
		this->places[10]->connect(this->places[5], 0);
		this->places[11]->connect(this->places[6], 0);
		this->places[12]->connect(this->places[7], 0);
		this->places[13]->connect(this->places[8], 0);
		this->places[14]->connect(this->places[9], 0);
		this->places[15]->connect(this->places[10], 0);
		this->places[16]->connect(this->places[12], 0);
		this->places[17]->connect(this->places[13], 0);
		this->places[18]->connect(this->places[14], 0);
		
        for (int i = 0; i < this->places.size(); i++){
            this->places[i]->connect_edges();
        }
        
    }

    void Board::assignNumbers() {
        vector<string> n = {"2", "3", "3", "4", "4", "5", "5", "6", "6", "8", "8", "9", "9", "10", "10", "11", "11", "12"};
        this->shuffle_places(n);
		vector<int> numbers;
		for (int i = 0; i < n.size(); i++){
			numbers.push_back(stoi(n[i]));
		}
		auto it = numbers.begin();

        for (auto place: this->places) {
            if (place->getType() != "DESERT") {
                if (it != numbers.end()) {
                    place->setNumber(*it);
                    ++it;
                } else {
                    place->setNumber(0);
                }
            }
        }
    }

     

    void Board::printBoard() {
        cout << "**************** CATAN BOARD ****************" << endl;
        cout << "sae        "<< this->places[2]->to_string()<<"  "<< this->places[1]->to_string()<<"  "<< this->places[0]->to_string()<<"      sea"<<endl;
        cout << "sae   "<< this->places[6]->to_string()<<"  "<< this->places[5]->to_string()<<"  "<< this->places[4]->to_string()<<"  "<< this->places[3]->to_string()<<"  sea"<<endl;
        cout << "sae   "<< this->places[11]->to_string()<<"  "<< this->places[10]->to_string()<<"  "<< this->places[9]->to_string()<<"  "<< this->places[8]->to_string()<<"  "<< this->places[7]->to_string()<<"  sea"<<endl;
        cout << "sae   "<< this->places[15]->to_string()<<"  "<< this->places[14]->to_string()<<"  "<< this->places[13]->to_string()<<"  "<< this->places[12]->to_string()<<"  sea"<<endl;
        cout << "sae        "<< this->places[18]->to_string()<<"  "<< this->places[17]->to_string()<<"  "<< this->places[16]->to_string()<<"      sea"<<endl;
        cout << "**********************************************" << endl;
    }
    

	void Board::shuffle_places(vector<string>& vec) {
        random_device rd; 
		mt19937 g(rd()); 
	
		// Shuffle the vector 
		shuffle(vec.begin(), vec.end(), g); 
    }

	vector<Place*>& Board::getPlaces() {
		return this->places;
	}
}