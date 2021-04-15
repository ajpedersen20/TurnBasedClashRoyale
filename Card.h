#include <string>

using namespace std;

#ifndef CARD
#define CARD

class Card{

    private:
        static const int numStats = 6;
        string name;
        int health;
        int damage;
        int range;
        int speed;
        int cost;
        int x;
        int y;
        int player;

    public:
        Card();
        Card(string n, int h, int d, int r, int s, int c, int _x, int _y, int p);
        string getName() const;
        int getHealth() const;
        int getDamage() const;
        int getRange() const;
        int getSpeed() const;
        int getCost() const;
        int getX() const;
        int getY() const;
        int getPlayer() const;
        void setName(string n);
        void setHealth(int h);
        void setDamage(int d);
        void setRange(int r);
        void setSpeed(int s);
        void setCost(int c);
        void setX(int _x);
        void setY(int _y);
        void setPlayer(int p);

};

#endif