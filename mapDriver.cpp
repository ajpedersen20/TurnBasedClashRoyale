#include "Map.h"
#include "Card.h"
#include "Square.h"
#include <iostream>

using namespace std;

int main(){

    Card archer("Archer",3,3,2,3,3, 0, 0, 2);
    Card knight("Knight",5,2,1,2,3, 1, 1, 1);
    vector<Card> cards = {archer, knight};

    Square a1(0);
    Square a2(0);
    Square a3(0);
    Square b1(3);
    Square b2(4);
    Square b3(5);
    Square replacement(1);

    vector<vector<Square>> squares = {
        {a1, a2, a3},
        {b1, b2, b3}
    };

    Map map1(squares, "test", "this is a test", 1, 20, 20);
    Map map2(squares, "test2", "another test", 2, cards, 20, 20);
    Map map3;

    map3.setMap(squares);
    map3.setSquareAt(replacement, 0, 0);
    map3.setName("OnceEmpty");
    map3.setDescription("This map used to be empty");
    map3.setType(2);
    map3.setSavedCards(cards);
    map3.setPlayer1Health(20);
    map3.setPlayer2Health(20);

    Map maps[] = {map1, map2, map3};

    for(int i = 0; i < 3; ++i){
        Map m = maps[i];
        cout << "Map " << i+1 << ": " << m.getType() << " " << m.getName() << " " << 
        m.getDescription() << endl;
        cout << "P1 Health = " << m.getPlayer1Health() << " P2 Health = " << m.getPlayer2Health() << endl;
        cout << "H: " << m.getHeight() << " " << "W: " << m.getWidth() << endl;
        for(int n = 0; n < m.getHeight(); ++n){
            for(int x = 0; x < m.getWidth(); ++x){
                cout << m.getSquareAt(x, n).getType() << ",";
            }
            cout << endl;
        }
        vector<Card> c = m.getSavedCards();
        for(int n = 0; n < c.size(); ++n){
            cout << c[n].getName() << ",";
        }
        cout << endl;
    }

    return 0;
}