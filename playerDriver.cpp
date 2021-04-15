#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include <iostream>

using namespace std;

int main(){

    Card knight("Knight", 6, 3, 1, 2, 3, 1, 1, 1);
    Card archer("Archer", 3, 3, 3, 3, 3, 1, 1, 1);
    Card skeleton("Skeleton", 1, 1, 1, 1, 1, 1, 1, 1);
    Card mortar("Mortar", 7, 4, 4, 0, 6, 1, 1, 1);
    Card cards1[] = {knight, archer, skeleton};
    Card cards2[] = {mortar, skeleton, archer, knight};
    Deck deck1(cards1, 3, 1);
    Deck deck2(cards2, 4, 1);

    Player player1(deck1, 3);
    Player player2;

    player2.setDeck(deck2);
    player2.setMoves(1);

    Card architect("Architect", 4, 5, 7, 2, 5, 1, 1, 1);
    Card brawler("Brawler", 5, 2, 1, 2, 3, 1, 1, 1);
    Card test("Test",1,1,1,1,1,1,1,1);

    cout << player1.addCard(architect) << endl;
    cout << player2.removeCard("Mortar") << endl;

    Card cards4[] = {knight, archer, skeleton, mortar, architect, brawler, test};
    Deck deck4(cards4, 7, 2);

    Player player3;
    Player player4(deck4, 3);

    cout << player3.removeCard("Test") << endl;
    cout << player4.addCard(test) << endl;
    cout << player4.removeCard("IDK") << endl;

    Player players[] = {player1, player2, player3, player4};

    for(int i = 0; i < 4; ++i){
        Player p = players[i];
        Deck d = p.getDeck();
        cout << "Player " << i+1 << ": " << " " << p.getMoves() << endl;
        cout << "Deck: " << d.getNumCards() << " " << d.getCost() << endl;
        p.printDeck();
    }

    return 0;
}