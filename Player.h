#include "Deck.h"

using namespace std;

#ifndef PLAYER
#define PLAYER

class Player{

    private:
        Deck deck;
        int moves;

    public:
        Player();
        Player(Deck d, int m);
        Deck getDeck() const;
        int getMoves() const;
        void setDeck(Deck d);
        void setMoves(int m);

        // helper functions

        int addCard(Card c);
        int removeCard(int index);
        int printDeck() const;

};

#endif