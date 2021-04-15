#include "Card.h"

using namespace std;

Card::Card(){
    name = "";
    health = 0;
    damage = 0;
    range = 0;
    speed = 0;
    cost = 0;
    x = -1;
    y = -1;
    player = -1;
}
Card::Card(string n, int h, int d, int r, int s, int c, int _x, int _y, int p){
    name = n;
    health = h;
    damage = d;
    range = r;
    speed = s;
    cost = c;
    x = _x;
    y = _y;
    player = p;
}
string Card::getName() const{
    return name;
}
int Card::getHealth() const{
    return health;
}
int Card::getDamage() const{
    return damage;
}
int Card::getRange() const{
    return range;
}
int Card::getSpeed() const{
    return speed;
}
int Card::getCost() const{
    return cost;
}
int Card::getX() const{
    return x;
}
int Card::getY() const{
    return y;
}
int Card::getPlayer() const{
    return player;
}
void Card::setName(string n){
    name = n;
}
void Card::setHealth(int h){
    health = h;
}
void Card::setDamage(int d){
    damage = d;
}
void Card::setRange(int r){
    range = r;
}
void Card::setSpeed(int s){
    speed = s;
}
void Card::setCost(int c){
    cost = c;
}
void Card::setX(int _x){
    x = _x;
}
void Card::setY(int _y){
    y = _y;
}
void Card::setPlayer(int p){
    player = p;
}