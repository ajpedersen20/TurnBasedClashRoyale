#include "Card.h"

using namespace std;

#ifndef SQUARE
#define SQUARE

class Square{

    private:
        // open = 0, barrier = 1, occupied = 2, player1base = 3
        // player2base = 4, player1placement = 5, player2placement = 6
        int type;
        Card card;

    public:
        Square();
        Square(Card c);
        Square(int t);
        int getType() const;
        Card getCard() const;
        void setType(int t);
        void setCard(Card c);

};

#endif