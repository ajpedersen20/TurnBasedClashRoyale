#include "Square.h"
#include "Map.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <vector>

using namespace std;

#ifndef GAME
#define GAME

class Game{

    private:
        Map map;
        Player player1;
        Player player2;

    public:
        Game();
        Game(Map m, Player p1, Player p2);
        Map getMap() const;
        Player getP1() const;
        Player getP2() const;
        void setMap(Map m);
        void setP1(Player p1);
        void setP2(Player p2);

        // helper functions

        int printMap();
        int toXPos(string pos) const;
        int toYPos(string pos) const;
        bool validMove(int startingX, int startingY, int targetX, int targetY, int speed, bool firstCall = true) const;
        bool validAttack(int startingX, int startingY, int targetX, int targetY, int range) const;

};

#endif