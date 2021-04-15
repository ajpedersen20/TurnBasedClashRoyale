#include "Card.h"
#include <iostream>

using namespace std;

int main(){

    Card knight("Knight", 10, 3, 1, 1, 3, 3, 4, 1);
    Card archer;
    archer.setName("Archer");
    archer.setHealth(4);
    archer.setDamage(4);
    archer.setRange(3);
    archer.setSpeed(3);
    archer.setCost(3);
    archer.setX(5);
    archer.setY(1);
    archer.setPlayer(2);

    const int size = 2;
    Card cards[size] = {knight, archer};

    for(int i = 0; i < size; ++i){
        Card c = cards[i];
        cout << c.getName() << " " << c.getHealth() << " " << c.getDamage() << " "
        << c.getRange() << " " << c.getSpeed() << " " << c.getCost() << " " <<
        c.getX() << " " << c.getY() << " " << c.getPlayer() << endl;
    }

    return 0;
}