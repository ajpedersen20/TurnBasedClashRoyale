#include "Card.h"
#include "Deck.h"
#include <iostream>

using namespace std;

Deck::Deck(){
    for(int i = 0; i < botDeckSize; ++i){
        cards[i] = Card();
    }
    numCards = 0;
    cost = 0;
    deckType = 0;
}
Deck::Deck(Card _cards[], int _numCards, int dt){
    deckType = dt;
    int spacer;

    // check if it's a bot deck because the sizes of a player deck and bot deck are different
    // fill the deck accordingly and fill any empty spots with empty cards
    if(deckType == 1){    
        spacer = maxCards;
        if(_numCards < spacer)
            spacer = _numCards;
        for(int i = 0; i < spacer; ++i){
            cards[i] = _cards[i];
        }
    }else{
        spacer = botDeckSize;
        if(_numCards < botDeckSize)
            spacer = _numCards;
        for(int i = 0; i < spacer; ++i){
            cards[i] = _cards[i];
        }
    }
    for(int i = spacer; i < botDeckSize; ++i){
        cards[i] = Card();
    }
    numCards = spacer;
    cost = 0;
    for(int i = 0; i < numCards; ++i){
        cost += cards[i].getCost();
    }
}
Card Deck::getCardAt(int index) const{

    // exception handling
    if(deckType == 1 && index >= 0 && index < numCards)
        return cards[index];
    if(deckType == 2 && index >= 0 && index < botDeckSize)
        return cards[index];
    return Card();
}
int Deck::getNumCards() const{
    return numCards;
}
int Deck::getCost() const{
    return cost;
}
int Deck::getDeckType() const{
    return deckType;
}
int Deck::getBotDeckSize() const{
    return botDeckSize;
}
int Deck::getMaxCards() const{
    return maxCards;
}
int Deck::getMaxCost() const{
    return maxCost;
}
int Deck::setCardAt(Card card, int index){

    // exception handling
    if(deckType == 1 && (index < 0 || index >= maxCards))
        return -1;
    if(deckType == 2 && (index < 0 || index >= botDeckSize))
        return -1;
    if(index >= numCards)
        ++numCards;
    cost -= cards[index].getCost();
    cards[index] = card;
    cost += cards[index].getCost();
    return 1;
}
void Deck::setNumCards(int num){
    numCards = num;
}
void Deck::setCost(int c){
    cost = c;
}
void Deck::setDeckType(int dt){
    deckType = dt;
}

// helper functions