#include "Card.h"
#include "Square.h"
#include <iostream>

using namespace std;

int main(){

    Card knight("Knight", 10, 3, 1, 2, 3, 1, 1, 1);

    Square one;
    Square two(1);
    Square three(knight);

    one.setCard(knight);
    one.setType(2);

    Square squares[] = {one, two, three};

    for(int i = 0; i < 3; ++i){
        Square s = squares[i];
        cout << "Square " << i+1 << ": " << s.getType() << " " << s.getCard().getName() << endl;
    }

    return 0;
}