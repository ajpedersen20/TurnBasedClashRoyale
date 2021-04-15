#include "Square.h"
#include "Map.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"
#include "Main.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

int main(){

    srand(time(0));

    Main main;
    main.readFiles(); // loads maps and cards
    int mainMenuSelection;
    string mMS;
    do{

        // print menu
        mainMenuSelection = 0; 
        cout << "====Main Menu====" << endl;
        cout << "1. Player vs Player" << endl;
        // cout << "2. Single Player" << endl;
        cout << "2. Reset Saved Data" << endl;
        cout << "3. Quit Game" << endl;
        cout << "4. Instructions" << endl;
        cout << "Enter a selection:" << endl;
        getline(cin, mMS);
        if(main.isNumber(mMS)){
            mainMenuSelection = stoi(mMS);

            switch(mainMenuSelection){

                case 1:{
                    int pvpMenuSelection;
                    string pvpMS;
                    Game game;
                    // checks are for knowing if able to start game when 'start game' is selected
                    bool checks[4]; // 0 = map, 1 = p1 cards all placed, 2 = p2 cards all placed
                    checks[0] = false;
                    checks[1] = false;
                    checks[2] = false;
                    checks[3] = false;
                    int mapIndex = -1;

                    do{
                        pvpMenuSelection = 0;
                        cout << "====Player vs Player Menu====" << endl;
                        cout << "1. Preview Map" << endl;
                        cout << "2. Choose Map" << endl;
                        cout << "3. Create New Card" << endl;
                        cout << "4. Build Player 1's Deck" << endl;
                        cout << "5. Build Player 2's Deck" << endl;
                        cout << "6. Place Cards on Map" << endl;
                        cout << "7. Start Game" << endl;
                        cout << "8. Quit to Main Menu" << endl;
                        cout << "Enter a selection:" << endl;
                        getline(cin, pvpMS);
                        if(main.isNumber(pvpMS)){
                            pvpMenuSelection = stoi(pvpMS);

                            switch(pvpMenuSelection){

                                case 1:{
                                    
                                    int choice = -1;
                                    int exception;
                                    string _choice;
                                    main.printMapDescriptions(1); // prints names and descriptions of the maps
                                    cout << "Enter the number of the map you want to preview:" << endl;
                                    getline(cin, _choice);
                                    if(main.isNumber(_choice)){
                                        choice = stoi(_choice);
                                        // previewMap prints the map with placement tiles
                                        exception = main.previewMap(1, main.getPVPMap(choice - 1));
                                        if(exception == -2)
                                            cout << "The number you entered is invalid" << endl;
                                    }else
                                        cout << "The number you entered is invalid" << endl;
                                    
                                    break;
                                }
                                case 2:{
                                    
                                    int choice = -1;
                                    string _choice;
                                    main.printMapDescriptions(1); // prints names and descriptions of the maps
                                    cout << "Enter the number of the map you want to play on:" << endl;
                                    getline(cin, _choice);
                                    if(main.isNumber(_choice)){
                                        choice = stoi(_choice);
                                        if(choice < 1 || choice > main.getNumPVPMaps())
                                            cout << "The number you entered is invalid" << endl;
                                        else{
                                            mapIndex = choice - 1; // prints numbers starting at 1, so actual index is choice - 1
                                            game.setMap(main.getPVPMap(choice - 1));
                                            checks[0] = true; // tells program that a map has been selected
                                            cout << "The map has been successfully set" << endl;
                                        }
                                    }else
                                        cout << "The number you entered is invalid" << endl;
                                    
                                    break;
                                }
                                case 3:
                                    main.createCard(); // able to create and play with your own card
                                    break;
                                case 4:{
                                    int buildDeckSelection;
                                    string bDS;
                                    do{
                                        Player player1 = game.getP1();
                                        buildDeckSelection = 0;
                                        Deck d = player1.getDeck();
                                        d.setDeckType(1);
                                        player1.setDeck(d);
                                        // prints number of cards and current cost along with the cards in deck and build deck menu
                                        cout << "Player 1's Deck:" << endl;
                                        cout << d.getNumCards() << " of " << d.getMaxCards() << " cards used. " << d.getCost()
                                        << " of " << d.getMaxCost() << " cost used." << endl;
                                        player1.printDeck();
                                        cout << "====Building Player 1's Deck====" << endl;
                                        cout << "1. Add Card" << endl;
                                        cout << "2. Remove Card" << endl;
                                        cout << "3. Quit to Player vs Player Menu" << endl;
                                        cout << "Enter a selection:" << endl;
                                        getline(cin, bDS);
                                        if(main.isNumber(bDS)){
                                            buildDeckSelection = stoi(bDS);

                                            switch(buildDeckSelection){
                                                case 1:{
                                                    int choice = -1;
                                                    string _choice;
                                                    if(d.getNumCards() >= d.getMaxCards())
                                                        cout << "You have reached the max number of cards in your deck" << endl;
                                                    else{
                                                        main.printCards();
                                                        cout << "Enter the number of the card you want to add to your deck:" << endl;
                                                        getline(cin, _choice);
                                                        if(main.isNumber(_choice)){
                                                            choice = stoi(_choice);
                                                            if(choice < 1 || choice > main.getNumCards())
                                                                cout << "The number you entered is invalid" << endl;
                                                            else{
                                                                Card c = main.getCard(choice - 1); // get card from card library
                                                                c.setPlayer(1); // set the player stat so program knows who's card it is
                                                                int check = player1.addCard(c); // add the card to player's deck
                                                                if(check == 1)
                                                                    cout << "The card has been added" << endl;
                                                                else
                                                                    cout << "Because of either cost or number of cards, the card couldn't be added" << endl;
                                                            }
                                                        }
                                                        else
                                                            cout << "The number you entered is invalid" << endl;
                                                    game.setP1(player1); // save any changes
                                                    }
                                                    if(game.getP1().getDeck().getNumCards() >= 6)
                                                        checks[1] = true; // if full deck, store true
                                                    else
                                                        checks[1] = false;
                                                    break;
                                                }
                                                case 2:{
                                                    int choice = -1;
                                                    string _choice;
                                                    cout << "Enter the number of the card you want to remove from your deck" << endl;
                                                    getline(cin, _choice);
                                                    if(main.isNumber(_choice)){
                                                        choice = stoi(_choice);
                                                        if(choice < 1 || choice > d.getNumCards())
                                                            cout << "The number you entered is invalid" << endl;
                                                        else{
                                                            int check = player1.removeCard(choice - 1); // remove selected card
                                                            if(check == -1)
                                                                cout << "There are no cards in your deck" << endl;
                                                            else
                                                                cout << "The card has been removed" << endl;
                                                        }
                                                    }
                                                    else
                                                        cout << "The number you entered is invalid" << endl;
                                                    game.setP1(player1); // save any changes
                                                    // update check for player 1 deck
                                                    if(game.getP1().getDeck().getNumCards() >= 6)
                                                        checks[1] = true;
                                                    else
                                                        checks[1] = false;
                                                    break;
                                                }
                                                case 3:
                                                    break;
                                                default:
                                                    cout << "Please enter a valid selection" << endl;
                                            }
                                        }else
                                            cout << "Invalid choice" << endl;
                                    }while(buildDeckSelection != 3);
                                    break;
                                }
                                case 5:{

                                    // same as case 4: except for player 2

                                    int buildDeckSelection;
                                    string bDS;
                                    do{
                                        Player player2 = game.getP2();
                                        buildDeckSelection = 0;
                                        Deck d = player2.getDeck();
                                        d.setDeckType(1);
                                        player2.setDeck(d);
                                        cout << "Player 2's Deck:" << endl;
                                        cout << d.getNumCards() << " of " << d.getMaxCards() << " cards used. " << d.getCost()
                                        << " of " << d.getMaxCost() << " cost used." << endl;
                                        player2.printDeck();
                                        cout << "====Building Player 2's Deck====" << endl;
                                        cout << "1. Add Card" << endl;
                                        cout << "2. Remove Card" << endl;
                                        cout << "3. Quit to Player vs Player Menu" << endl;
                                        cout << "Enter a selection:" << endl;
                                        getline(cin, bDS);
                                        if(main.isNumber(bDS)){
                                            buildDeckSelection = stoi(bDS);

                                            switch(buildDeckSelection){
                                                case 1:{
                                                    int choice = -1;
                                                    string _choice;
                                                    if(d.getNumCards() >= d.getMaxCards())
                                                        cout << "You have reached the max number of cards in your deck" << endl;
                                                    else{
                                                        main.printCards();
                                                        cout << "Enter the number of the card you want to add to your deck:" << endl;
                                                        getline(cin, _choice);
                                                        if(main.isNumber(_choice)){
                                                            choice = stoi(_choice);
                                                            if(choice < 1 || choice > main.getNumCards())
                                                                cout << "The number you entered is invalid" << endl;
                                                            else{
                                                                Card c = main.getCard(choice - 1);
                                                                c.setPlayer(2);
                                                                int check = player2.addCard(c);
                                                                if(check == 1)
                                                                    cout << "The card has been added" << endl;
                                                                else
                                                                    cout << "Because of either cost or number of cards, the card couldn't be added" << endl;
                                                            }
                                                        }
                                                        else
                                                            cout << "The number you entered is invalid" << endl;
                                                    }
                                                    game.setP2(player2);
                                                    if(game.getP2().getDeck().getNumCards() >= 6)
                                                        checks[2] = true;
                                                    else
                                                        checks[2] = false;
                                                    break;
                                                }
                                                case 2:{
                                                    int choice = -1;
                                                    string _choice;
                                                    cout << "Enter the number of the card you want to remove from your deck" << endl;
                                                    getline(cin, _choice);
                                                    if(main.isNumber(_choice)){
                                                        choice = stoi(_choice);
                                                        if(choice < 1 || choice > d.getNumCards())
                                                            cout << "The number you entered is invalid" << endl;
                                                        else{
                                                            int check = player2.removeCard(choice - 1);
                                                            if(check == -1)
                                                                cout << "There are no cards in your deck" << endl;
                                                            else
                                                                cout << "The card has been removed" << endl;
                                                        }
                                                    }
                                                    else
                                                        cout << "The number you entered is invalid" << endl;
                                                    game.setP2(player2);
                                                    if(game.getP2().getDeck().getNumCards() >= 6)
                                                        checks[2] = true;
                                                    else
                                                        checks[2] = false;
                                                    break;
                                                }
                                                case 3:
                                                    break;
                                                default:
                                                    cout << "Please enter a valid selection" << endl;
                                            }
                                        }else
                                            cout << "Invalid choice" << endl;
                                    }while(buildDeckSelection != 3);
                                    break;
                                }
                                case 6:{ // placing cards

                                    // check to make sure a map has been selected and each player's deck is full
                                    if(!checks[0] || !checks[1] || !checks[2])
                                        cout << "You haven't chosen a map or built your decks yet" << endl;
                                    else{
                                        main.setGame(game); // update the big object with everything in it
                                        int numPlaced1 = 0; // counters for each player to know when every card has been placed
                                        int numPlaced2 = 0;
                                        Map map = main.getPVPMap(mapIndex);
                                        Player p1 = main.getGame().getP1();
                                        Player p2 = main.getGame().getP2();
                                        bool p1Placed[6] = {false, false, false, false, false, false}; // checks to make sure a card is not placed twice
                                        bool p2Placed[6] = {false, false, false, false, false, false};
                                        while(numPlaced1 < 6 || numPlaced2 < 6){ // while there are cards yet to be placed
                                            main.previewMap(1, map); // show the map with placement tiles
                                            if(numPlaced1 < 6){
                                                int cardI = -1;
                                                string cIndex;
                                                p1.printDeck(); // print deck
                                                cout << "Player 1: Enter the number of the card you want to place" << endl;
                                                getline(cin, cIndex);
                                                if(main.isNumber(cIndex)){
                                                    cardI = stoi(cIndex);
                                                    if(cardI < 1 || cardI > p1.getDeck().getMaxCards())
                                                        cout << "Not a valid number" << endl;
                                                    else{
                                                        if(!p1Placed[cardI - 1]){
                                                            cout << "Enter the position of where you want to place the card (ex. C4)" << endl;
                                                            string pos;
                                                            getline(cin, pos);
                                                            if(pos == "")
                                                                cout << "Not a valid position" << endl;
                                                            else{
                                                                int posX = game.toXPos(pos);
                                                                int posY = game.toYPos(pos);
                                                                Square s = map.getSquareAt(posX, posY);
                                                                if(s.getType() != 5)
                                                                    cout << "Not a valid position" << endl;
                                                                else{
                                                                    Card c = p1.getDeck().getCardAt(cardI - 1);
                                                                    c.setX(posX); // set x and y coords for the card
                                                                    c.setY(posY);
                                                                    Deck d = p1.getDeck();
                                                                    d.setCardAt(c, cardI - 1); // update deck with the card
                                                                    // update rest of objects with the new info
                                                                    p1.setDeck(d);
                                                                    game.setP1(p1);
                                                                    main.setGame(game);

                                                                    // checks for exception handling
                                                                    ++numPlaced1;
                                                                    p1Placed[cardI - 1] = true;
                                                                }
                                                            }
                                                        }else
                                                            cout << "That card has already been placed" << endl;
                                                    }
                                                }else{
                                                    cout << "Not a valid number" << endl;
                                                }
                                            }

                                            // this is a copy of what player 1 was asked

                                            if(numPlaced2 < 6){
                                                int cardI = -1;
                                                string cIndex;
                                                p2.printDeck();
                                                cout << "Player 2: Enter the number of the card you want to place" << endl;
                                                getline(cin, cIndex);
                                                if(main.isNumber(cIndex)){
                                                    cardI = stoi(cIndex);
                                                    if(cardI < 1 || cardI > p2.getDeck().getMaxCards())
                                                        cout << "Not a valid number" << endl;
                                                    else{
                                                        if(!p2Placed[cardI - 1]){
                                                            cout << "Enter the position of where you want to place the card (ex. C4)" << endl;
                                                            string pos;
                                                            getline(cin, pos);
                                                            if(pos == "")
                                                                cout << "Not a valid position" << endl;
                                                            else{
                                                                int posX = game.toXPos(pos);
                                                                int posY = game.toYPos(pos);
                                                                Square s = map.getSquareAt(posX, posY);
                                                                if(s.getType() != 6)
                                                                    cout << "Not a valid position" << endl;
                                                                else{
                                                                    Card c = p2.getDeck().getCardAt(cardI - 1);
                                                                    c.setX(posX);
                                                                    c.setY(posY);
                                                                    Deck d = p2.getDeck();
                                                                    d.setCardAt(c, cardI - 1);
                                                                    p2.setDeck(d);
                                                                    game.setP2(p2);
                                                                    main.setGame(game);
                                                                    ++numPlaced2;
                                                                    p2Placed[cardI - 1] = true;
                                                                }
                                                            }
                                                        }else
                                                            cout << "That card has already been placed" << endl;
                                                    }
                                                }else{
                                                    cout << "Not a valid number" << endl;
                                                }
                                            }
                                        }
                                        checks[3] = true;
                                        cout << "All cards have been placed. To prevent breaking the game, please select 7 to start game or 8 to quit to main menu" << endl;
                                    }
                                    break;
                                }
                                case 7:{ // time the start the game

                                    // make sure everything has been set
                                    if(!checks[0] || !checks[1] || !checks[2] || !checks[3])
                                        cout << "You haven't chosen a map or finished building a deck" << endl;
                                    else{

                                        // set objects for changing stuff, determine who goes first with RNG
                                        main.setGame(game);
                                        int playerTurn = (rand() % 2) + 1;
                                        cout << "Player " << playerTurn << " won the coin toss" << endl;
                                        int inGameChoice;
                                        string iGC;
                                        Player p1 = main.getGame().getP1();
                                        Player p2 = main.getGame().getP2();
                                        p1.setMoves(3);
                                        p2.setMoves(3);
                                        bool change = false; // for changing turns
                                        game = main.getGame();
                                        game.setP1(p1);
                                        game.setP2(p2);
                                        main.setGame(game);
                                        do{
                                            game = main.getGame();
                                            p1 = game.getP1();
                                            p2 = game.getP2();
                                            Player currentPlayer;
                                            Player oppoPlayer;
                                            Map map = game.getMap();
                                            map = main.fillMap(map); // possible cause of invincibility bug. hopefully you didn't encounter it
                                            game.printMap(); // print the map
                                            inGameChoice = -1;

                                            // set current and opponent Players, so I don't have to write all the steps twice for each player
                                            if(playerTurn == 1){
                                                if(change)
                                                    p1.setMoves(3);
                                                currentPlayer = p1;
                                                oppoPlayer = p2;
                                                cout << "Player 1 has " << currentPlayer.getMoves() << " actions left" << endl;
                                            }
                                            else{
                                                if(change)
                                                    p2.setMoves(3);
                                                currentPlayer = p2;
                                                oppoPlayer = p1;
                                                cout << "Player 2 has " << currentPlayer.getMoves() << " actions left" << endl;
                                            }
                                            change = false;
                                            Deck d = currentPlayer.getDeck();
                                            Deck oppoDeck = oppoPlayer.getDeck();

                                            // print the possible actions
                                            cout << "====P" << playerTurn << " Actions====" << endl;
                                            cout << "1. Move" << endl;
                                            cout << "2. Attack" << endl;
                                            cout << "3. End Turn" << endl;
                                            cout << "4. Quit Game" << endl;
                                            cout << "Enter the number of an action:" << endl;
                                            getline(cin, iGC);
                                            if(main.isNumber(iGC)){
                                                inGameChoice = stoi(iGC);
                                                switch(inGameChoice){
                                                    case 1:{// move
                                                        if(currentPlayer.getMoves() > 0){

                                                            // get positions for which card to move and where to move the card
                                                            string pos1, pos2;
                                                            cout << "Enter the position of the card you want to move:" << endl;
                                                            getline(cin, pos1);
                                                            cout << "Enter the position of the tile you want to move to:" << endl;
                                                            getline(cin, pos2);
                                                            if(pos1 != "" && pos2 != ""){
                                                                int xStart = game.toXPos(pos1);
                                                                int yStart = game.toYPos(pos1);
                                                                int xTarget = game.toXPos(pos2);
                                                                int yTarget = game.toYPos(pos2);
                                                                if(xStart == -1 || xTarget == -1)
                                                                    cout << "One or more of the positions was invalid";
                                                                else{
                                                                    Square s1 = map.getSquareAt(xStart, yStart);
                                                                    Square s2 = map.getSquareAt(xTarget, yTarget);
                                                                    Card c = s1.getCard();
                                                                    if(s1.getType() != 2 || s1.getCard().getPlayer() != playerTurn)
                                                                        cout << "The starting tile you entered was invalid" << endl;
                                                                    else{
                                                                        bool validMove = game.validMove(xStart, yStart, xTarget, yTarget, c.getSpeed());
                                                                        if(validMove){

                                                                            // if valid move, change the corresponding info for the card and map
                                                                            currentPlayer.setMoves(currentPlayer.getMoves() - 1);
                                                                            int index = -1;
                                                                            for(int i = 0; i < d.getNumCards(); ++i){
                                                                                Card temp = d.getCardAt(i);
                                                                                if(temp.getX() == xStart && temp.getY() == yStart)
                                                                                    index = i;
                                                                            }
                                                                            c.setX(xTarget);
                                                                            c.setY(yTarget);
                                                                            map.setSquareAt(Card(c), xTarget, yTarget);
                                                                            map.setSquareAt(Square(), xStart, yStart);
                                                                            d.setCardAt(c, index);
                                                                        }else
                                                                            cout << "That is not a valid move" << endl;
                                                                    }
                                                                }
                                                            }else
                                                                cout << "One or more of the positions was blank" << endl;
                                                        }else
                                                            cout << "You have no moves left" << endl;
                                                        break;
                                                    }
                                                    case 2:{// attack
                                                        if(currentPlayer.getMoves() > 0){

                                                            // get positions of attacking card and target card / base
                                                            string pos1, pos2;
                                                            cout << "Enter the position of the attacking card" << endl;
                                                            getline(cin, pos1);
                                                            cout << "Enter the position of the target card" << endl;
                                                            getline(cin, pos2);
                                                            if(pos1 != "" && pos2 != ""){
                                                                int xStart = game.toXPos(pos1);
                                                                int yStart =  game.toYPos(pos1);
                                                                int xTarget = game.toXPos(pos2);
                                                                int yTarget = game.toYPos(pos2);
                                                                if(xStart == -1 || xTarget == -1)
                                                                    cout << "One or more of the positions was invalid" << endl;
                                                                else{
                                                                    Square s1 = map.getSquareAt(xStart, yStart);
                                                                    Square s2 = map.getSquareAt(xTarget, yTarget);
                                                                    Card attacker = s1.getCard(); // card that is attacking
                                                                    if(s1.getType() != 2 || s1.getCard().getPlayer() != playerTurn || !(s2.getType() == 3 || s2.getType() == 4 || s2.getType() == 2))
                                                                        cout << "One of the tiles you entered was invalid" << endl;
                                                                    else{
                                                                        bool validAttack = game.validAttack(xStart, yStart, xTarget, yTarget, attacker.getRange());
                                                                        if(validAttack){

                                                                            // if valid attack, update the info on the map and in the opponents card that got attacked
                                                                            currentPlayer.setMoves(currentPlayer.getMoves() - 1);
                                                                            if(s2.getType() == 2){
                                                                                int index = -1;
                                                                                Card target;
                                                                                for(int i = 0; i < oppoDeck.getNumCards(); ++i){
                                                                                    target = oppoDeck.getCardAt(i);
                                                                                    if(target.getX() == xTarget && target.getY() == yTarget)
                                                                                        index = i;
                                                                                }
                                                                                target = oppoDeck.getCardAt(index);
                                                                                int health = target.getHealth() - attacker.getDamage();
                                                                                if(health < 0)
                                                                                    health = 0;
                                                                                target.setHealth(health);
                                                                                oppoDeck.setCardAt(target, index);

                                                                                // this is to remove a card from the board if it's health hits or dips below zero
                                                                                if(health == 0){
                                                                                    map.setSquareAt(Square(), xTarget, yTarget);
                                                                                    oppoPlayer.removeCard(index);
                                                                                    oppoDeck = oppoPlayer.getDeck();
                                                                                }else{
                                                                                    map.setSquareAt(Square(target), xTarget, yTarget);
                                                                                }

                                                                            // if the attack is on a base
                                                                            }else if(s2.getType() == 3 || s2.getType() == 4){
                                                                                int health;
                                                                                if(playerTurn == 1){
                                                                                    if(s2.getType() == 3)
                                                                                        cout << "Invalid attack" << endl;
                                                                                    else{
                                                                                        health = map.getPlayer2Health() - attacker.getDamage();
                                                                                        if(health < 0) health = 0;
                                                                                        map.setPlayer2Health(health);
                                                                                    }
                                                                                }else{
                                                                                    if(s2.getType() == 4)
                                                                                        cout << "Invalid attack" << endl;
                                                                                    else{
                                                                                        health = map.getPlayer1Health() - attacker.getDamage();
                                                                                        if(health < 0) health = 0;
                                                                                        map.setPlayer1Health(health);
                                                                                    }
                                                                                }
                                                                            }
                                                                        }else
                                                                            cout << "Not a valid attack" << endl;
                                                                    }
                                                                }
                                                            }else
                                                                cout << "One or more of the positions was blank" << endl;
                                                        }else
                                                            cout << "You have no moves left" << endl;
                                                        break;
                                                    }
                                                    case 3:
                                                    change = true;
                                                        break;
                                                    case 4:
                                                        break;
                                                    default:
                                                        cout << "The number you entered is invalid" << endl;
                                                }
                                            }else
                                                cout << "Invalid choice" << endl;

                                            // update the main object with all of the changes smaller objects

                                            currentPlayer.setDeck(d);
                                            oppoPlayer.setDeck(oppoDeck);
                                            if(playerTurn == 1){
                                                p1 = currentPlayer;
                                                p2 = oppoPlayer;
                                            }
                                            else{
                                                p2 = currentPlayer;
                                                p1 = oppoPlayer;
                                            }
                                            game.setMap(map);
                                            game.setP1(p1);
                                            game.setP2(p2);
                                            main.setGame(game);

                                            // if applicable, switch who's turn it is
                                            if(change){
                                                if(playerTurn == 1)
                                                    ++playerTurn;
                                                else
                                                    --playerTurn;
                                            }
                                        }while(main.getGame().getMap().getPlayer1Health() > 0 && main.getGame().getMap().getPlayer2Health() > 0
                                            && inGameChoice != 4);
                                    }
                                    for(int i = 0; i < 4; ++i){
                                        checks[i] = false;
                                    }

                                    // reset everything when the game ends
                                    game = Game();
                                    main.setGame(game);
                                    break;
                                }
                                case 8:
                                    break;
                                default:
                                    cout << "Please enter a valid selection" << endl;

                            }
                        }else
                            cout << "Invalid choice" << endl;
                    }while(pvpMenuSelection != 8);
                    break;

                }
                /*
                case 2:{
                    cout << "I could not for the life of me figure out what was causing all the bugs in single player, so I've commented off this option unfortunately :(" << endl;
                    
                    int selection;
                    string s;
                    Game game;
                    int mapIndex;
                    bool checks[3] = {false, false, false}; // 0 = map, 1 = deck, 2 = placed
                    
                    do{
                        Player player;
                        Player bot;
                        cout << "====Single Player Menu====" << endl;
                        cout << "1. Preview Map" << endl;
                        cout << "2. Choose Map" << endl;
                        cout << "3. Create Card" << endl;
                        cout << "4. Build Deck" << endl;
                        cout << "5. Place Cards" << endl;
                        cout << "6. Start Game" << endl;
                        cout << "7. Quit to Main Menu" << endl;
                        cout << "Enter a selection:" << endl;
                        getline(cin, s);
                        if(main.isNumber(s)){

                            selection = stoi(s);
                            switch(selection){
                                case 1:{
                                    int choice = -1;
                                    string ch;
                                    main.printMapDescriptions(2);
                                    cout << "Enter the number of the map you want to preview:" << endl;
                                    getline(cin, ch);
                                    if(main.isNumber(ch)){
                                        choice = stoi(ch);
                                        int exception = main.previewMap(2, main.getPVEMap(choice - 1));
                                        if(exception == -2)
                                            cout << "Invalid number" << endl;
                                    }else
                                        cout << "Invalid number" << endl;
                                    break;
                                }
                                case 2:{
                                    int choice = -1;
                                    string _choice;
                                    main.printMapDescriptions(2);
                                    cout << "Enter the number of the map you want to play on:" << endl;
                                    getline(cin, _choice);
                                    if(main.isNumber(_choice)){
                                        choice = stoi(_choice);
                                        if(choice < 1 || choice > main.getNumPVPMaps())
                                            cout << "The number you entered is invalid" << endl;
                                        else{
                                            mapIndex = choice - 1;
                                            Map map = main.getPVEMap(choice - 1);
                                            if(main.getSaveData(mapIndex, 0) == 1){
                                                vector<Card> cards = map.getSavedCards();
                                                for(int i = 0; i < cards.size(); ++i){
                                                    Card c = cards[i];
                                                    if(c.getPlayer() == 1)
                                                        player.addCard(c);
                                                    else
                                                        bot.addCard(c);
                                                }
                                                game.setP1(player);
                                                game.setP2(bot);
                                                checks[1] = true;
                                                checks[2] = true;
                                                cout << "To prevent breaking the game, please select 6 to start the game or 7 to quit to main menu" << endl;
                                                ////////////////////////////////////////////////////////////////////////////////////////
                                            }else{
                                                vector<Card> cards = map.getSavedCards();
                                                for(int i = 0; i < cards.size(); ++i){
                                                    cout << bot.addCard(cards[i]) << endl;//////
                                                    cout << bot.getDeck().getCardAt(i).getName() << endl;
                                                    /////////////////////////////////////////////////////////////
                                                }
                                                bot.printDeck(); ///////
                                                game.setP2(bot);
                                                bot.printDeck();/////
                                                game.getP2().printDeck();//////
                                            }
                                            game.setMap(map);
                                            checks[0] = true;
                                            cout << "The map has been successfully set" << endl;
                                        }
                                    }else
                                        cout << "The number you entered is invalid" << endl;
                                    break;
                                }
                                case 3:{
                                    main.createCard();
                                    break;
                                }
                                case 4:{
                                    int buildDeckSelection;
                                    string bDS;
                                    do{
                                        Player player1 = game.getP1();
                                        buildDeckSelection = 0;
                                        Deck d = player1.getDeck();
                                        d.setDeckType(1);
                                        player1.setDeck(d);
                                        cout << "Player's Deck:" << endl;
                                        cout << d.getNumCards() << " of " << d.getMaxCards() << " cards used. " << d.getCost()
                                        << " of " << d.getMaxCost() << " cost used." << endl;
                                        player1.printDeck();
                                        cout << "====Building Player's Deck====" << endl;
                                        cout << "1. Add Card" << endl;
                                        cout << "2. Remove Card" << endl;
                                        cout << "3. Quit to Single Player Menu" << endl;
                                        cout << "Enter a selection:" << endl;
                                        getline(cin, bDS);
                                        if(main.isNumber(bDS)){
                                            buildDeckSelection = stoi(bDS);

                                            switch(buildDeckSelection){
                                                case 1:{
                                                    int choice = -1;
                                                    string _choice;
                                                    if(d.getNumCards() >= d.getMaxCards())
                                                        cout << "You have reached the max number of cards in your deck" << endl;
                                                    else{
                                                        main.printCards();
                                                        cout << "Enter the number of the card you want to add to your deck:" << endl;
                                                        getline(cin, _choice);
                                                        if(main.isNumber(_choice)){
                                                            choice = stoi(_choice);
                                                            if(choice < 1 || choice > main.getNumCards())
                                                                cout << "The number you entered is invalid" << endl;
                                                            else{
                                                                Card c = main.getCard(choice - 1);
                                                                c.setPlayer(1);
                                                                int check = player1.addCard(c);
                                                                if(check == 1)
                                                                    cout << "The card has been added" << endl;
                                                                else
                                                                    cout << "Because of either cost or number of cards, the card couldn't be added" << endl;
                                                            }
                                                        }
                                                        else
                                                            cout << "The number you entered is invalid" << endl;
                                                    game.setP1(player1);
                                                    }
                                                    if(game.getP1().getDeck().getNumCards() >= 6)
                                                        checks[1] = true;
                                                    else
                                                        checks[1] = false;
                                                    break;
                                                }
                                                case 2:{
                                                    int choice = -1;
                                                    string _choice;
                                                    cout << "Enter the number of the card you want to remove from your deck" << endl;
                                                    getline(cin, _choice);
                                                    if(main.isNumber(_choice)){
                                                        choice = stoi(_choice);
                                                        if(choice < 1 || choice > d.getNumCards())
                                                            cout << "The number you entered is invalid" << endl;
                                                        else{
                                                            int check = player1.removeCard(choice - 1);
                                                            if(check == -1)
                                                                cout << "There are no cards in your deck" << endl;
                                                            else
                                                                cout << "The card has been removed" << endl;
                                                        }
                                                    }
                                                    else
                                                        cout << "The number you entered is invalid" << endl;
                                                    game.setP1(player1);
                                                    if(game.getP1().getDeck().getNumCards() >= 6)
                                                        checks[1] = true;
                                                    else
                                                        checks[1] = false;
                                                    break;
                                                }
                                                case 3:
                                                    break;
                                                default:
                                                    cout << "Please enter a valid selection" << endl;
                                            }
                                        }else
                                            cout << "Invalid choice" << endl;
                                    }while(buildDeckSelection != 3);
                                    break;
                                }

                                case 5:{

                                    if(!checks[0] || !checks[1])
                                        cout << "You haven't chosen a map or built your decks yet" << endl;
                                    else{
                                        main.setGame(game);
                                        int numPlaced = 0;
                                        Map map = main.getPVEMap(mapIndex);
                                        Player p1 = main.getGame().getP1();
                                        bool p1Placed[6] = {false, false, false, false, false, false};
                                        while(numPlaced < 6){
                                            main.previewMap(1, map);
                                            if(numPlaced < 6){
                                                int cardI = -1;
                                                string cIndex;
                                                p1.printDeck();
                                                cout << "Player: Enter the number of the card you want to place" << endl;
                                                getline(cin, cIndex);
                                                if(main.isNumber(cIndex)){
                                                    cardI = stoi(cIndex);
                                                    if(cardI < 1 || cardI > p1.getDeck().getMaxCards())
                                                        cout << "Not a valid number" << endl;
                                                    else{
                                                        if(!p1Placed[cardI - 1]){
                                                            cout << "Enter the position of where you want to place the card (ex. C4)" << endl;
                                                            string pos;
                                                            getline(cin, pos);
                                                            if(pos == "")
                                                                cout << "Not a valid position" << endl;
                                                            else{
                                                                int posX = game.toXPos(pos);
                                                                int posY = game.toYPos(pos);
                                                                Square s = map.getSquareAt(posX, posY);
                                                                if(s.getType() != 5)
                                                                    cout << "Not a valid position" << endl;
                                                                else{
                                                                    Card c = p1.getDeck().getCardAt(cardI - 1);
                                                                    c.setX(posX);
                                                                    c.setY(posY);
                                                                    Deck d = p1.getDeck();
                                                                    d.setCardAt(c, cardI - 1);
                                                                    p1.setDeck(d);
                                                                    game.setP1(p1);
                                                                    main.setGame(game);
                                                                    ++numPlaced;
                                                                    p1Placed[cardI - 1] = true;
                                                                }
                                                            }
                                                        }else
                                                            cout << "That card has already been placed" << endl;
                                                    }
                                                }else{
                                                    cout << "Not a valid number" << endl;
                                                }
                                            }
                                        }
                                        checks[2] = true;
                                    }
                                    break;
                                }
                                case 6:{
                                    if(!checks[0] || !checks[1] || !checks[2])
                                        cout << "You haven't chosen a map or finished building a deck" << endl;

                                    else{
                                        int playerTurn = 1;
                                        bool change = false;
                                        main.setGame(game);
                                        int inGameChoice;
                                        string iGC;
                                        Player p1 = main.getGame().getP1();
                                        Player p2 = main.getGame().getP2();
                                        p1.setMoves(3);
                                        p2.setMoves(3);
                                        game = main.getGame();
                                        game.setP1(p1);
                                        game.setP2(p2);
                                        main.setGame(game);

                                        do{
                                            
                                            main.getGame().getP2().printDeck();////////////////

                                            game = main.getGame();
                                            p1 = game.getP1();
                                            p2 = game.getP2();
                                            Player currentPlayer;
                                            Player oppoPlayer;
                                            Map map = game.getMap();
                                            map = main.fillMap(map); // possible cause of invincibility bug
                                            game.printMap();
                                            inGameChoice = -1;
                                            if(playerTurn == 1){
                                                if(change)
                                                    p1.setMoves(3);
                                                currentPlayer = p1;
                                                oppoPlayer = p2;
                                                cout << "You have " << currentPlayer.getMoves() << " moves left" << endl;
                                            }
                                            else{
                                                if(change)
                                                    p2.setMoves(3);
                                                currentPlayer = p2;
                                                oppoPlayer = p1;
                                                cout << "Bot has " << currentPlayer.getMoves() << " moves left" << endl;
                                            }
                                            change = false;
                                            Deck d = currentPlayer.getDeck();
                                            Deck oppoDeck = oppoPlayer.getDeck();
                                            if(playerTurn == 1){
                                                cout << "====P" << playerTurn << " Actions====" << endl;
                                                cout << "1. Move" << endl;
                                                cout << "2. Attack" << endl;
                                                cout << "3. End Turn" << endl;
                                                cout << "4. Quit Game" << endl;
                                                cout << "Enter the number of an action:" << endl;
                                                getline(cin, iGC);
                                                if(main.isNumber(iGC)){
                                                    inGameChoice = stoi(iGC);
                                                    switch(inGameChoice){
                                                        case 1:{
                                                            if(currentPlayer.getMoves() > 0){
                                                                string pos1, pos2;
                                                                cout << "Enter the position of the card you want to move:" << endl;
                                                                getline(cin, pos1);
                                                                cout << "Enter the position of the tile you want to move to:" << endl;
                                                                getline(cin, pos2);
                                                                if(pos1 != "" && pos2 != ""){
                                                                    int xStart = game.toXPos(pos1);
                                                                    int yStart = game.toYPos(pos1);
                                                                    int xTarget = game.toXPos(pos2);
                                                                    int yTarget = game.toYPos(pos2);
                                                                    if(xStart == -1 || xTarget == -1)
                                                                        cout << "One or more of the positions was invalid";
                                                                    else{
                                                                        Square s1 = map.getSquareAt(xStart, yStart);
                                                                        Square s2 = map.getSquareAt(xTarget, yTarget);
                                                                        Card c = s1.getCard();
                                                                        if(s1.getType() != 2 || s1.getCard().getPlayer() != playerTurn)
                                                                            cout << "The starting tile you entered was invalid" << endl;
                                                                        else{
                                                                            bool validMove = game.validMove(xStart, yStart, xTarget, yTarget, c.getSpeed());
                                                                            if(validMove){
                                                                                currentPlayer.setMoves(currentPlayer.getMoves() - 1);
                                                                                int index = -1;
                                                                                for(int i = 0; i < d.getNumCards(); ++i){
                                                                                    Card temp = d.getCardAt(i);
                                                                                    if(temp.getX() == xStart && temp.getY() == yStart)
                                                                                        index = i;
                                                                                }
                                                                                c.setX(xTarget);
                                                                                c.setY(yTarget);
                                                                                map.setSquareAt(Card(c), xTarget, yTarget);
                                                                                map.setSquareAt(Square(), xStart, yStart);
                                                                                d.setCardAt(c, index);
                                                                            }else
                                                                                cout << "That is not a valid move" << endl;
                                                                        }
                                                                    }
                                                                }else
                                                                    cout << "One or more of the positions was blank" << endl;
                                                            }else
                                                                cout << "You have no moves left" << endl;
                                                            break;
                                                        }
                                                        case 2:{/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                            if(currentPlayer.getMoves() > 0){
                                                                string pos1, pos2;
                                                                cout << "Enter the position of the attacking card" << endl;
                                                                getline(cin, pos1);
                                                                cout << "Enter the position of the target card" << endl;
                                                                getline(cin, pos2);
                                                                if(pos1 != "" && pos2 != ""){
                                                                    int xStart = game.toXPos(pos1);
                                                                    int yStart =  game.toYPos(pos1);
                                                                    int xTarget = game.toXPos(pos2);
                                                                    int yTarget = game.toYPos(pos2);
                                                                    if(xStart == -1 || xTarget == -1)
                                                                        cout << "One or more of the positions was invalid" << endl;
                                                                    else{
                                                                        Square s1 = map.getSquareAt(xStart, yStart);
                                                                        Square s2 = map.getSquareAt(xTarget, yTarget);
                                                                        Card attacker = s1.getCard(); // card that is attacking
                                                                        if(s1.getType() != 2 || s1.getCard().getPlayer() != playerTurn || !(s2.getType() == 3 || s2.getType() == 4 || s2.getType() == 2))
                                                                            cout << "One of the tiles you entered was invalid" << endl;
                                                                        else{
                                                                            bool validAttack = game.validAttack(xStart, yStart, xTarget, yTarget, attacker.getRange());
                                                                            if(validAttack){
                                                                                currentPlayer.setMoves(currentPlayer.getMoves() - 1);
                                                                                if(s2.getType() == 2){
                                                                                    int index = -1;
                                                                                    Card target;
                                                                                    for(int i = 0; i < oppoDeck.getNumCards(); ++i){
                                                                                        target = oppoDeck.getCardAt(i);
                                                                                        if(target.getX() == xTarget && target.getY() == yTarget)
                                                                                            index = i;
                                                                                    }
                                                                                    target = oppoDeck.getCardAt(index);
                                                                                    cout << target.getHealth() << " " << attacker.getDamage() << endl;/////////////
                                                                                    int health = target.getHealth() - attacker.getDamage();
                                                                                    cout << health << endl; ///////////////
                                                                                    if(health < 0)
                                                                                        health = 0;
                                                                                    target.setHealth(health);
                                                                                    oppoDeck.setCardAt(target, index);
                                                                                    if(health == 0){
                                                                                        map.setSquareAt(Square(), xTarget, yTarget);
                                                                                        cout << "if" << endl; ////////////
                                                                                        oppoPlayer.removeCard(index);
                                                                                        oppoDeck = oppoPlayer.getDeck();
                                                                                    }else{
                                                                                        cout << "else" << endl; ///////////
                                                                                        map.setSquareAt(Square(target), xTarget, yTarget);
                                                                                    }
                                                                                }else if(s2.getType() == 3 || s2.getType() == 4){
                                                                                    int health;
                                                                                    if(playerTurn == 1){
                                                                                        if(s2.getType() == 3)
                                                                                            cout << "Invalid attack" << endl;
                                                                                        else{
                                                                                            health = map.getPlayer2Health() - attacker.getDamage();
                                                                                            if(health < 0) health = 0;
                                                                                            map.setPlayer2Health(health);
                                                                                        }
                                                                                    }else{
                                                                                        if(s2.getType() == 4)
                                                                                            cout << "Invalid attack" << endl;
                                                                                        else{
                                                                                            health = map.getPlayer1Health() - attacker.getDamage();
                                                                                            if(health < 0) health = 0;
                                                                                            map.setPlayer1Health(health);
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }else
                                                                                cout << "Not a valid attack" << endl;
                                                                        }
                                                                    }
                                                                }else
                                                                    cout << "One or more of the positions was blank" << endl;
                                                            }else
                                                                cout << "You have no moves left" << endl;
                                                            break;
                                                        }
                                                        case 3:
                                                        change = true;
                                                            break;
                                                        case 4:
                                                            break;
                                                        default:
                                                            cout << "The number you entered is invalid" << endl;
                                                    }
                                                }else
                                                    cout << "Invalid choice" << endl;
                                                currentPlayer.setDeck(d);
                                                oppoPlayer.setDeck(oppoDeck);
                                                if(playerTurn == 1){
                                                    p1 = currentPlayer;
                                                    p2 = oppoPlayer;
                                                }
                                                else{
                                                    p2 = currentPlayer;
                                                    p1 = oppoPlayer;
                                                }
                                                game.setMap(map);
                                                game.setP1(p1);
                                                game.setP2(p2);
                                                main.setGame(game);
                                                if(change){
                                                    if(playerTurn == 1)
                                                        ++playerTurn;
                                                    else
                                                        --playerTurn;
                                                }

                                            }else{

                                                for(int i = 0; i < 3; ++i){
                                                    // executeBestMove
                                                        // should set everything back to game before ending
                                                }

                                            }

                                        }while(inGameChoice != 4);


                                    }

                                    game = Game();
                                    main.setGame(game);
                                    break;
                                }
                                
                                case 7:
                                    break;
                                default:
                                    cout << "Invalid selection" << endl;
                            }

                        }else
                            cout << "Invalid selection" << endl;
                        
                    }while(selection != 7);
                    
                    break;
                    
                }
                */

                case 2:{

                    // deletes the gameData.txt file which has all of the saved cards and maps on it
                    int check = remove("gameData.txt");
                    main.readFiles();
                    if(check == 0)
                        cout << "The saved data was successfully erased" << endl;
                    else
                        cout << "There was no saved data" << endl;
                    break;
                }
                case 3:
                    cout << "All created cards have been saved. Any progress made in Single Player has been saved" << endl;
                    cout << "Thank you for playing!" << endl;
                    break;
                case 4:// instructions for players
                    
                    cout << "When you select player vs player, you should choose a map. You can preview any of the maps first." << endl;
                    cout << "Then, each of you should build your deck. Your deck must be comprised of six cards and cannot go over the cost cap." << endl;
                    cout << "Each card has:" << endl;
                    cout << "   h = health, d = damage(how much damage the card does), r = range(how many squares away the card can attack)," << endl;
                    cout << "   s = speed(the max number of tiles a card can move), c = cost(individual cost of the card)" << endl;
                    cout << "After building your decks, you can now place the cards on your chosen map" << endl;
                    cout << "When prompted, enter positions by typing the letter followed by the number (ex. 'c4' or 'C4')" << endl;
                    cout << "After placing cards, select the start game option" << endl;
                    cout << "The starting player is determined randomly" << endl;
                    cout << "Follow the in-game prompts to play" << endl;
                    cout << "Remember, speed and range are measures of distance and are determined by adding the differences in x and y positions" << endl;
                    cout << "For example, a card with 3 range can attack a card that is 1 tile up and 2 tiles over (1 + 2 <= 3)" << endl;
                    cout << "A card who's health drops to or below 0 will be removed from the board" << endl;
                    cout << "Win by attacking and destroying the opponent's base" << endl;
                    cout << "When a base is destroyed, you will be returned to the main menu" << endl;
                    cout << "Lastly, resetting save data will delete and cards you have created in the card creator" << endl;

                    break;
                case 5:
                    cout << "YOU SHALL NOT PASS!..................An easter egg because every game has one. IDK how to do easter eggs tho" << endl;
                    break;
                default:
                    cout << "Please enter a valid selection" << endl;
            }
        }else
            cout << "Invalid choice" << endl;

    }while(mainMenuSelection != 3);

    return 0;
}