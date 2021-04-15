#include "Square.h"
#include "Map.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"
#include <vector>
#include <iostream>

using namespace std;

int main(){
    
    Card archer("Archer",3,2,2,3,3,1,2,1);
    Card knight("Knight",5,3,1,1,4,2,1,1);
    Card mortar("Mortar",5,5,5,1,5,0,0,1);
    Card cards[] = {archer, knight, mortar};
    Deck deck(cards, 3, 1);

    Square a1(5);
    Square a2(5);
    Square a3(0);
    Square a4(1);
    Square a5(6);
    Square a6(6);
    Square b1(3);
    Square b2(5);
    Square b3(5);
    Square b4(6);
    Square b5(6);
    Square b6(4);
    Square c1(5);
    Square c2(5);
    Square c3(1);
    Square c4(0);
    Square c5(6);
    Square c6(6);

    vector<vector<Square>> _map{
        {a1, a2, a3, a4, a5, a6},
        {b1, b2, b3, b4, b5, b6},
        {c1, c2, c3, c4, c5, c6}
    };

    Deck testDeck1(cards, 3, 1);
    Deck testDeck2;

    Player player1(testDeck1, 3);
    Player player2(testDeck2, 0);

    Map map(_map, "Test", "Testing print map", 1, 20, 25);

    Game game;
    game.setP1(player1);
    game.setP2(player2);
    game.setMap(map);

    cout << game.getMap().getName() << endl;
    cout << "P1: BH = " << game.getMap().getPlayer1Health() << " M = " << game.getP1().getMoves() << endl;
    cout << "P2: BH = " << game.getMap().getPlayer2Health() << " M = " << game.getP2().getMoves() << endl;
    cout << endl;
    cout << game.printMap() << endl << endl;

    // d1, d2, c2, c3
    
    string pos1 = "D1", pos2 = "D2", pos3 = "C2", pos4 = "C3";
    cout << game.validMove(archer.getX(), archer.getY(), game.toXPos(pos1), game.toYPos(pos1), archer.getSpeed()) << endl;
    cout << game.validMove(archer.getX(), archer.getY(), game.toXPos(pos2), game.toYPos(pos2), archer.getSpeed()) << endl;
    cout << game.validMove(archer.getX(), archer.getY(), game.toXPos(pos3), game.toYPos(pos3), archer.getSpeed()) << endl;
    cout << game.validMove(archer.getX(), archer.getY(), game.toXPos(pos4), game.toYPos(pos4), archer.getSpeed()) << endl;

    // c1, a2, f2

    string p1 = "C1", p2 = "A2", p3 = "F2";
    cout << game.validAttack(archer.getX(), archer.getY(), game.toXPos(p1), game.toYPos(p1), archer.getRange()) << endl;
    cout << game.validAttack(archer.getX(), archer.getY(), game.toXPos(p2), game.toYPos(p2), archer.getRange()) << endl;
    cout << game.validAttack(archer.getX(), archer.getY(), game.toXPos(p3), game.toYPos(p3), archer.getRange()) << endl;

    return 0;
}