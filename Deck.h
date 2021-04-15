#include "Card.h"

using namespace std;

#ifndef DECK
#define DECK

class Deck{

    private:
        static const int botDeckSize = 25;
        static const int maxCards = 6;
        static const int maxCost = 15;
        Card cards[botDeckSize];
        int numCards;
        int cost;
        int deckType;

    public:
        Deck();
        Deck(Card _cards[], int _numCards, int dt);
        Card getCardAt(int index) const;
        int getNumCards() const;
        int getCost() const;
        int getDeckType() const;
        int getBotDeckSize() const;
        int getMaxCards() const;
        int getMaxCost() const;
        int setCardAt(Card card, int index);
        void setNumCards(int num);
        void setCost(int c);
        void setDeckType(int dt);

        // helper functions

};

#endif