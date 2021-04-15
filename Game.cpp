#include "Square.h"
#include "Map.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

Game::Game(){
    map = Map();
    player1 = Player();
    player2 = Player();
}
Game::Game(Map m, Player p1, Player p2){
    map = m;
    player1 = p1;
    player2 = p2;
}
Map Game::getMap() const{
    return map;
}
Player Game::getP1() const{
    return player1;
}
Player Game::getP2() const{
    return player2;
}
void Game::setMap(Map m){
    map = m;
}
void Game::setP1(Player p1){
    player1 = p1;
}
void Game::setP2(Player p2){
    player2 = p2;
}

// helper functions


// prints the in-game map. Each tile is made up of three different lines. Including a literal "********" line, there are four types of lines
// i % 4 checks the type of line. i / 4 (int division) gets the y coord of the tile
//in a switch statement, you'll print the info according to the type of square it is currently on
int Game::printMap(){
    if(map.getHeight() == 0)
        return -1;

    // card types:
    // open = 0, barrier = 1, occupied = 2
    // p1base = 3, p2base = 4, p1placement = 5, p2placement = 6

    Deck d = player1.getDeck();
    for(int i = 0; i < d.getNumCards(); ++i){
        Card c = d.getCardAt(i);
        if(c.getHealth() > 0)
            map.setSquareAt(Square(c), c.getX(), c.getY());
    }
    d = player2.getDeck();
    for(int i = 0; i < d.getNumCards(); ++i){
        Card c = d.getCardAt(i);
        if(c.getHealth() > 0);
            map.setSquareAt(Square(c), c.getX(), c.getY());
    }

    int numLines = 5 + ((map.getHeight() - 1) * 4);
    for(int i = 0; i < numLines; ++i){
        Square s;
        int type;
        switch(i % 4){
            case 0:{
                cout << "  *";
                for(int n = 0; n < map.getWidth(); ++n){
                    cout << "***********";
                }
                break;
            }
            case 1:{
                cout << "  *";
                for(int n = 0; n < map.getWidth(); ++n){
                    s = map.getSquareAt(n, i / 4);
                    type = s.getType();
                    if(type == 5 || type == 6)
                        type = 0;
                    switch(type){
                        case 0:
                            cout << "          *";
                            break;
                        case 1:
                            cout << "***********";
                            break;
                        case 2:{
                            string name, temp1, temp2;
                            int spot;
                            name = s.getCard().getName();
                            if(name.length() > 7)
                                name = name.substr(0,7);
                            spot = name.length() / 2;
                            temp1 = name.substr(0, spot);
                            temp2 = name.substr(spot);
                            cout << "P" << s.getCard().getPlayer() << " " << setw(3) << right << temp1 << setw(4) << left << temp2 << "*";
                            break;
                        }
                        case 3:
                            cout << "P1  Base  *";
                            break;
                        case 4:
                            cout << "P2  Base  *";
                            break;
                        default:
                            return -2;
                    }
                }
                break;
            }
            case 2:{
                cout << setw(2) << left << map.getHeight() - (i / 4) << "*";
                for(int n = 0; n < map.getWidth(); ++n){
                    s = map.getSquareAt(n, i / 4);
                    type = s.getType();
                    if(type == 5 || type == 6)
                        type = 0;
                    switch(type){
                        case 0:
                            cout << "          *";
                            break;
                        case 1:
                            cout << "***********";
                            break;
                        case 2:
                            cout << "H" << setw(3) << right << s.getCard().getHealth() << " D" << setw(3) << right << s.getCard().getDamage() << " *";
                            break;
                        case 3:
                            // could cause issues
                            cout << "    " << setw(4) << left << map.getPlayer1Health() << "  *";
                            break;
                        case 4:
                            // could cause issues
                            cout << "    " << setw(4) << left << map.getPlayer2Health() << "  *";
                            break;
                        default:
                            return -2;
                    }
                }
                break;
            }
            case 3:{
                cout << "  *";
                for(int n = 0; n < map.getWidth(); ++n){
                    s = map.getSquareAt(n, i / 4);
                    type = s.getType();
                    if(type == 5 || type == 6)
                        type = 0;
                    switch(type){
                        case 0:
                            cout << "          *";
                            break;
                        case 1:
                            cout << "***********";                            
                            break;
                        case 2:
                            cout << "R" << setw(3) << right << s.getCard().getRange() << " S" << setw(3) << right << s.getCard().getSpeed() << " *";
                            break;
                        case 3:
                        case 4:
                            cout << "  Health  *";
                            break;
                        default:
                            return -2;
                    }
                }
                break;
            }
            default:{
                return -2;
            }
        }
        cout << endl;
    }
    cout << "   ";
    for(int i = 0; i < map.getWidth(); ++i){
        cout << "    " << (char)(65 + i) << "      ";
    }
    cout << endl;
    return 1;
}


// these functions take a string like 'C4' and turn that into coordinates that into the x or y coord that I can actually use.
// 'c4' might return 2 for x and then 0 for y depending on which map you are playing on
int Game::toXPos(string pos) const{
    if(pos.length() != 2 || !isalpha(pos[0]) || !isdigit(pos[1]))
        return -1;
    char x = toupper(pos[0]);
    return (x - 65);
}

int Game::toYPos(string pos) const{
    if(pos.length() != 2 || !isalpha(pos[0]) || !isdigit(pos[1]))
        return -1;
    string temp = "";
    temp += pos[1];
    int y = stoi(temp);
    return (map.getHeight() - y);
}


// recursive function that makes sure cards can't jump over barriers or other cards
// call function on the tile above, below, to the right, to the left
    // then, it'll check all the tiles around the new tile
// if any of these tiles is the target, returns true and the whole function then returns true
bool Game::validMove(int startingX, int startingY, int targetX, int targetY, int speed, bool firstCall) const{
    if(startingX < 0 || startingX >= map.getWidth() || startingY < 0 || startingY >= map.getHeight())
        return false;
    int type = map.getSquareAt(startingX, startingY).getType();
    if(type == 1 || type == 3 || type == 4)
        return false;
    if(!firstCall && type == 2)
        return false;
    if(startingX == targetX && startingY == targetY)
        return true;
    if(speed == 0)
        return false;
    return (validMove(startingX+1, startingY, targetX, targetY, speed-1, false) ||
        validMove(startingX-1, startingY, targetX, targetY, speed-1, false) ||
        validMove(startingX, startingY+1, targetX, targetY, speed-1, false) ||
        validMove(startingX, startingY-1, targetX, targetY, speed-1, false));
}


// checks if the target is within range
// checks if the target is a tile that can be attacked
bool Game::validAttack(int startingX, int startingY, int targetX, int targetY, int range) const{
    int distance = abs(startingX - targetX) + abs(startingY - targetY);
    if(distance > range)
        return false;
    int type = map.getSquareAt(targetX, targetY).getType();
    if(type == 0 || type == 1 || type == 5 || type == 6)
        return false;
    return true;
}

