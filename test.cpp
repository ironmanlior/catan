#include <sstream>
#include <cassert>
#include <iostream>
#include "Player.hpp"
#include "board.hpp"
#include "catan.hpp"
#include "place.hpp"
#include "edge.hpp"

using namespace ariel;

void testPlayer() {
	Catan game = Catan({"Player1"});
    Board board;
    Player player1("Player1");

    // Test addResource and removeResource edge cases
    player1.addResource(1, 5);
    assert(player1.get_resource(1) == 5);
    assert(player1.addResource(1, -3));
    assert(player1.get_resource(1) == 2);
    assert(!player1.addResource(1, -3)); // Remove more than available
    assert(!player1.addResource(1, -2));
    assert(player1.get_resource(1) == 0);

    // Test buildSettlement edge case
    player1.addResource(1, 1);
    player1.addResource(0, 1);
    player1.addResource(2, 1);
    player1.addResource(3, 1);
    game.placeSettelemnt(0, 0, false);  // Assuming this uses the resources added

    // Test buildCity edge case
    player1.addResource(4, 3);
    player1.addResource(3, 2);
    assert(player1.valid_resource(4, 3));
    game.placeCity(0, 0);

    // Test trade edge case
    Player player2("Player2");
    player2.addResource(1, 1);
    game.trade(&player2, 4, 1, 1, 1);

    // Test buyDevelopmentCard edge case
    std::vector<int> dev_cards = {0, 1, 0, 0, 0};
    player1.addResource(4, 1);
    player1.addResource(3, 1);
    player1.addResource(2, 1);
    game.buy_card();
    player1.addResource(1, 5);
    assert(!player1.addResource(1, -8));
    assert(player1.get_resource(1) == 0);
    player1.addResource(1, -3);
    assert(player1.get_resource(1) == 0);


}

void testGame() {
    Board board;

    Catan game({"player1", "player2", "player3"});
	Player player1 = *game.get_players()[0];

    // Redirect std::cout to a stringstream
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    player1.addResource(1, -1);
    player1.addResource(0, -1);
    game.placeRoad({0, 0}, {3, 1});
    std::cout.rdbuf(prevcoutbuf);
    std::string output = buffer.str();
    assert(output == "player Player1 does not have enough resources to build a road\n");
    std::cout<<"pass test 1 on bild road\n";

    player1.addResource(1, 1);
    player1.addResource(0, 1);
    std::stringstream buffer1;
    std::streambuf* prevcoutbuf1 = std::cout.rdbuf(buffer1.rdbuf());
    game.placeRoad({4, 0}, {3, 1});
    std::cout.rdbuf(prevcoutbuf1);
    std::string output1 = buffer1.str();
    std::string expected_output = "player Player1 which edge do you want to put? the option are:\n"
                                  "2\n"
                                  "4\n"
                                  "10\n"
                                  "17\n"
                                  "37\n"
                                  "38\n"
                                  "50\n"
                                  "55\n"
                                  "enter the edge id\n"
                                  "player Player1 build a road in edge 2\n";
    if (output1 != expected_output) {
        std::cout << "Test 2 on build road failed.\n";
        std::cout << "Expected output:\n" << expected_output << "\n";
        std::cout << "Actual output:\n" << output1 << "\n";
    } else {
        std::cout << "Pass test 2 on build road.\n";
    }
    
}

void testBoard() {
    Board board;
    board.generateBoard();
    assert(!board.getPlaces().empty());
    board.printBoard();
}

int main() {
    testPlayer();
    testGame();
    testBoard();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}