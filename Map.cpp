#include "Square.h"
#include "Map.h"
#include <vector>

using namespace std;

Map::Map(){
    vector<vector<Square>> map;
    name = "";
    description = "";
    type = -1;
    vector<Card> savedCards;
    player1Health = 0;
    player2Health = 0;
}
Map::Map(vector<vector<Square>> m, string n, string d, int t, int p1h, int p2h){
    map = m;
    name = n;
    description = d;
    type = t;
    vector<Card> savedCards;
    player1Health = p1h;
    player2Health = p2h;
}
Map::Map(vector<vector<Square>> m, string n, string d, int t, vector<Card> sCards, int p1h, int p2h){
    map = m;
    name = n;
    description = d;
    type = t;
    savedCards = sCards;
    player1Health = p1h;
    player2Health = p2h;
}
vector<vector<Square>> Map::getMap() const{
    return map;
}
Square Map::getSquareAt(int x, int y) const{
    if(map.size() == 0 || x >= map[0].size() || y >= map.size() || x < 0 || y < 0)
        return Square(-1);
    return map[y][x];
}
string Map::getName() const{
    return name;
}
string Map::getDescription() const{
    return description;
}
int Map::getType() const{
    return type;
}
vector<Card> Map::getSavedCards() const{
    return savedCards;
}
int Map::getPlayer1Health() const{
    return player1Health;
}
int Map::getPlayer2Health() const{
    return player2Health;
}
void Map::setMap(vector<vector<Square>> m){
    map = m;
}
int Map::setSquareAt(Square s, int x, int y){
    if(map.size() == 0 || x >= map[0].size() || y >= map.size() || x < 0 || y < 0)
        return -1;
    map[y][x] = s;
    return 1;
}
void Map::setName(string n){
    name = n;
}
void Map::setDescription(string d){
    description = d;
}
void Map::setType(int t){
    type = t;
}
void Map::setSavedCards(vector<Card> sCards){
    savedCards = sCards;
}
void Map::setPlayer1Health(int h){
    player1Health = h;
}
void Map::setPlayer2Health(int h){
    player2Health = h;
}

// helper functions

int Map::getWidth() const{
    if(map.size() == 0)
        return 0;
    return map[0].size();
}
int Map::getHeight() const{
    return map.size();
}