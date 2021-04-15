#include "Square.h"
#include "Card.h"
#include <vector>

using namespace std;

#ifndef MAP
#define MAP

class Map{

    private:
        vector<vector<Square>> map;
        string name;
        string description;
        int type; // 1v1 = 1, 1vBot = 2
        vector<Card> savedCards;
        int player1Health;
        int player2Health;

    public:
        Map();
        Map(vector<vector<Square>> m, string n, string d, int t, int p1h, int p2h);
        Map(vector<vector<Square>> m, string n, string d, int t, vector<Card> sCards, int p1h, int p2h);
        vector<vector<Square>> getMap() const;
        Square getSquareAt(int x, int y) const;
        string getName() const;
        string getDescription() const;
        int getType() const;
        vector<Card> getSavedCards() const;
        int getPlayer1Health() const;
        int getPlayer2Health() const;
        void setMap(vector<vector<Square>> m);
        int setSquareAt(Square s, int x, int y);
        void setName(string n);
        void setDescription(string d);
        void setType(int t);
        void setSavedCards(vector<Card> sCards);
        void setPlayer1Health(int h);
        void setPlayer2Health(int h);

        // helper functions

        int getWidth() const;
        int getHeight() const;

};

#endif