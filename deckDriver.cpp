#include "Card.h"
#include "Deck.h"
#include <iostream>

using namespace std;

int main(){

    Card knight("Knight", 10, 3, 1, 1, 3, 1, 1, 1);
    Card archer("Archer", 4, 4, 3, 3, 3, 1, 1, 1);
    Card mortar("Mortar", 8, 5, 5, 0, 5, 1, 1, 1);
    Card skeleton("Skeleton", 1, 1, 1, 1, 1, 1, 1, 1);
    Card god("God", 10, 10, 10, 10, 10, 1, 1, 1);
    Card dragon("Dragon", 9, 6, 2, 6, 7, 1, 1, 1);
    Card chief("Chief", 5, 4, 1, 3, 5, 1, 1, 1);

    Card incompleteCards[] = {knight, archer, mortar};
    Card overfilledCards[] = {knight, archer, mortar, skeleton, god, dragon, chief};
    Card completeCards[] = {knight, archer, mortar, skeleton, god, dragon};

    Deck incompleteDeck(incompleteCards, 3, 1);
    incompleteDeck.setCardAt(skeleton, 3);
    incompleteDeck.setCardAt(chief, 0);
    Deck overfilledDeck(overfilledCards, 7, 1);
    Deck completeDeck(completeCards, 6, 1);
    Deck emptyDeck;

    Deck botDeck(overfilledCards, 7, 2);

    Deck deck[] = {incompleteDeck, overfilledDeck, completeDeck, emptyDeck, botDeck};

    cout << emptyDeck.getMaxCards() << " " << emptyDeck.getMaxCost() << " "
    << botDeck.getBotDeckSize() << endl;

    for(int i = 0; i < 5; ++i){
        Deck d = deck[i];
        cout << i+1 << " " << d.getNumCards() << " " << d.getCost() << endl;
        for(int n = 0; n < d.getNumCards(); ++n){
            Card c = d.getCardAt(n);
            cout << c.getName() << " " << c.getCost() << endl;
        }
    }

    return 0;
}