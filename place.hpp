#ifndef PLACE_H
#define PLACE_H

#include "edge.hpp"
#include <vector>
#include <iostream>

namespace ariel {
    class Place {
        private:
            string type;
            int number;
            int id;
            vector<Place*> neighbors;
            vector<bool> is_neighbors;
            vector<edge*> edges;

        public:
            Place(string type, int id);
            
            string getType();
            int getId();
            bool has_neighbor(int id);
            Place* get_neighbor(int id);
            int getNumber();
            void setNumber(int number);

            int getResource();
            
            string to_string();
            pair<edge*,edge*> get_vertex(int id);

            void connect(Place* other, int vertex);
            void connect_edges();
    };

}

#endif // PLACE_H