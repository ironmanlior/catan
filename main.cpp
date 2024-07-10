#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "catan.hpp"


using namespace std;
using namespace ariel;

int main() {
	cout << "1" << endl;
	ariel::Catan* game = new ariel::Catan({"p1", "p2", "p3"});
	cout << "1" << endl;
	game->play();
	return 0;
}
