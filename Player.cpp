#include "Deck.h"
#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(){
    deck = Deck();
    moves = 0;
}
Player::Player(Deck d, int m){
    deck = d;
    moves = m;
}
Deck Player::getDeck() const{
    return deck;
}
int Player::getMoves() const{
    return moves;
}
void Player::setDeck(Deck d){
    deck = d;
}
void Player::setMoves(int m){
    moves = m;
}

// helper functions

int Player::addCard(Card c){

    // exception handling
    if(deck.getDeckType() == 1 && (deck.getNumCards() >= deck.getMaxCards() || deck.getCost() + c.getCost() > deck.getMaxCost()))
        return -1;
    if(deck.getDeckType() == 2 && deck.getNumCards() >= deck.getBotDeckSize())
        return -2;
    deck.setCardAt(c, deck.getNumCards());
    return 1;
}
int Player::removeCard(int index){
    if(deck.getNumCards() == 0)
        return -1;

    // at the index of the card to be removed, put the last card in the deck there
    deck.setCardAt(deck.getCardAt(deck.getNumCards() - 1), index);
    // where the last card used to be, put an empty card
    deck.setCardAt(Card(), deck.getNumCards() - 1);
    // decrement the number of cards
    deck.setNumCards(deck.getNumCards() - 1);
    return 1;
}

int Player::printDeck() const{
    if(deck.getNumCards() == 0)
        return -1;

    // for each card, print its stats
    for(int i = 0; i < deck.getNumCards(); ++i){
        Card c = deck.getCardAt(i);
        cout << i+1 << ". " << c.getName() << ": H=" << c.getHealth() << ", D=" << c.getDamage()
        << ", R=" << c.getRange() << ", S=" << c.getSpeed() << ", C=" << c.getCost() << endl;
    }
    return 1;
}