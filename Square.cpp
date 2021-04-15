#include "Square.h"
#include "Card.h"

using namespace std;

Square::Square(){
    type = 0;
    card = Card();
}
Square::Square(Card c){
    type = 2;
    card = c;
}
Square::Square(int t){
    type = t;
    card = Card();
}
int Square::getType() const{
    return type;
}
Card Square::getCard() const{
    return card;
}
void Square::setType(int t){
    type = t;
}
void Square::setCard(Card c){
    card = c;
}