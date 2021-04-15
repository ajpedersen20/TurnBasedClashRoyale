#include "Square.h"
#include "Map.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"
#include "Main.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

Main::Main(){
    numPVPMaps = 0;
    numPVEMaps = 0;
    numCards = 0;
    for(int i = 0; i < maxMaps; ++i){
        pvpMaps[i] = Map();
    }
    for(int i = 0; i < maxMaps; ++i){
        pveMaps[i] = Map();
    }
    for(int i = 0; i < maxCards; ++i){
        cards[i] = Card();
    }
    game = Game();
    for(int i = 0; i < maxMaps; ++i){
        for(int n = 0; n < numSavedData; ++n){
            saveData[i][n] = -1;
        }
    }
}

// sets the cards, pve maps, and pvp maps, and then fills rest of arrays with blank maps / cards
Main::Main(Map pvpm[], int numPVP, Map pvem[], int numPVE, Card _cards[], int nCards, int numIC, Game g){
    numPVPMaps = numPVP;
    numPVEMaps = numPVE;
    numCards = nCards;
    numInitialCards = numIC;
    int spacer = maxMaps;
    if(numPVP < spacer)
        spacer = numPVP;
    for(int i = 0; i < spacer; ++i){
        pvpMaps[i] = pvpm[i];
    }
    for(int i = spacer; i < maxMaps; ++i){
        pvpMaps[i] = Map();
    }
    spacer = maxMaps;
    if(numPVE < spacer)
        spacer = numPVE;
    for(int i = 0; i < spacer; ++i){
        pveMaps[i] = pvem[i];
    }
    for(int i = spacer; i < maxMaps; ++i){
        pveMaps[i] = Map();
    }
    spacer = maxCards;
    if(nCards < spacer)
        spacer = nCards;
    for(int i = 0; i < spacer; ++i){
        cards[i] = _cards[i];
    }
    for(int i = spacer; i < maxCards; ++i){
        cards[i] = Card();
    }
    for(int i = 0; i < maxMaps; ++i){
        for(int n = 0; n < numSavedData; ++n){
            saveData[i][n] = -1;
        }
    }
}

// differs from previous contructor in that it includes saveData in case there is stuff in the gameData.txt file
Main::Main(Map pvpm[], int numPVP, Map pvem[], int numPVE, Card _cards[], int nCards, int numIC, Game g, int sd[maxMaps][numSavedData]){
    numPVPMaps = numPVP;
    numPVEMaps = numPVE;
    numCards = nCards;
    numInitialCards = numIC;
    int spacer = maxMaps;
    if(numPVP < spacer)
        spacer = numPVP;
    for(int i = 0; i < spacer; ++i){
        pvpMaps[i] = pvpm[i];
    }
    for(int i = spacer; i < maxMaps; ++i){
        pvpMaps[i] = Map();
    }
    spacer = maxMaps;
    if(numPVE < spacer)
        spacer = numPVE;
    for(int i = 0; i < spacer; ++i){
        pveMaps[i] = pvem[i];
    }
    for(int i = spacer; i < maxMaps; ++i){
        pveMaps[i] = Map();
    }
    spacer = maxCards;
    if(nCards < spacer)
        spacer = nCards;
    for(int i = 0; i < spacer; ++i){
        cards[i] = _cards[i];
    }
    for(int i = spacer; i < maxCards; ++i){
        cards[i] = Card();
    }
    for(int i = 0; i < numPVEMaps; ++i){
        for(int n = 0; n < numSavedData; ++n){
            saveData[i][n] = sd[i][n];
        }
    }
    for(int i = numPVEMaps; i < maxMaps; ++i){
        for(int n = 0; n < numSavedData; ++n){
            saveData[i][n] = -1;
        }
    }
}
int Main::getMaxMaps() const{
    return maxMaps;
}
int Main::getMaxCards() const{
    return maxCards;
}
int Main::getNumPVPMaps() const{
    return numPVPMaps;
}
int Main::getNumPVEMaps() const{
    return numPVEMaps;
}
int Main::getNumCards() const{
    return numCards;
}
Map Main::getPVPMap(int index) const{
    if(index < 0 || index >= numPVPMaps)
        return Map();
    return pvpMaps[index];
}
Map Main::getPVEMap(int index) const{
    if(index < 0 || index >= numPVEMaps)
        return Map();
    return pveMaps[index];
}
Card Main::getCard(int index) const{
    if(index < 0 || index >= numCards)
        return Card();
    return cards[index];
}
Game Main::getGame() const{
    return game;
}
int Main::getSaveData(int first, int second) const{
    return saveData[first][second];
}
void Main::setNumPVPMaps(int num){
    numPVPMaps = num;
}
void Main::setNumPVEMaps(int num){
    numPVEMaps = num;
}
void Main::setNumCards(int num){
    numCards = num;
}
int Main::addCard(Card card){
    if(numCards >= maxCards)
        return -1;
    cards[numCards] = card;
    ++numCards;
    return 1;
}
int Main::addPVPMap(Map map){
    if(numPVPMaps >= maxMaps)
        return -1;
    pvpMaps[numPVPMaps] = map;
    ++numPVPMaps;
    return 1;
}
int Main::addPVEMap(Map map){
    if(numPVEMaps >= maxMaps)
        return -1;
    pveMaps[numPVEMaps] = map;
    ++numPVEMaps;
    return 1;
}
void Main::setGame(Game g){
    game = g;
}
void Main::setSaveData(int first, int second, int val){
    saveData[first][second] = val;
}

// helper functions


// from other homeworks. splits line into pieces based on a delimiter
int split(string str, char separator, string arr[], int size){
    if(str.length() == 0) // check for empty string
        return 0;
    int spot = 0, arrIndex = 0; // initialize variables
    for(int i = 0; i < str.length(); ++i){ // iterate char by char through string
        if(str[i] == separator){
            arr[arrIndex] = str.substr(spot, i - spot); // store everything before separator in array
            ++arrIndex; // next spot
            spot = i + 1; // update where next substr will start
        }
    }
    arr[arrIndex] = str.substr(spot); // add final piece to array
    ++arrIndex;
    if(arrIndex > size) // exception if more pieces that size
        return -1;
    return arrIndex;
}

// basically the exact same as the printMap function in the Game class. I probably should have combined the two into one function
int Main::previewMap(int type, Map map) const{
    int index = -1;
    if(map.getType() == 2){
        for(int i = 0; i < numPVEMaps; ++i){
            Map temp = pveMaps[i];
            if(map.getName() == temp.getName())
                index = i;
        }
    }
    
    if(map.getHeight() == 0)
        return -3;
    cout << map.getName() << endl << map.getDescription() << endl;

    vector<Card> cards = map.getSavedCards();
    Deck p1Deck = game.getP1().getDeck();
    Player p2 = game.getP2();
    for(int i = 0; i < cards.size(); ++i){
        p2.addCard(cards[i]);
    }
    Deck p2Deck = p2.getDeck();

    for(int i = 0; i < p1Deck.getNumCards(); ++i){
        Card c = p1Deck.getCardAt(i);
        if(c.getX() >= 0 && c.getY() >= 0){
            map.setSquareAt(Square(c), c.getX(), c.getY());
        }
    }
    for(int i = 0; i < p2Deck.getNumCards(); ++i){
        Card c = p2Deck.getCardAt(i);
        if(c.getX() >= 0 && c.getY() >= 0){
            map.setSquareAt(Square(c), c.getX(), c.getY());
        }
    }

    // card types:
    // open = 0, barrier = 1, occupied = 2
    // p1base = 3, p2base = 4, p1placement = 5, p2placement = 6

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
                    if(map.getType() == 2 && saveData[index][0] == 1 && (type == 5 || type == 6))
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
                        case 5:
                            cout << "P1  Place *";
                            break;
                        case 6:
                            cout << "P2  Place *";
                            break;
                        default:
                            return -4;
                    }
                }
                break;
            }
            case 2:{
                cout << setw(2) << left << map.getHeight() - (i / 4) << "*";
                for(int n = 0; n < map.getWidth(); ++n){
                    s = map.getSquareAt(n, i / 4);
                    type = s.getType();
                    if(map.getType() == 2 && saveData[index][0] == 1 && (type == 5 || type == 6))
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
                        case 5:
                        case 6:
                            cout << "    Card  *";
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
                    if(map.getType() == 2 && saveData[index][0] == 1 && (type == 5 || type == 6))
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
                        case 5:
                        case 6:
                            cout << "    Here  *";
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

// first stores everything from gameData.txt then prints it again to the file
// prints the card at the end of everything else
// creates the gameData.txt file if it doesn't exist
int Main::writeCard(Card c) const{
    string line;
    vector<string> lines;
    ifstream infile("gameData.txt");
    if(infile.is_open()){
        while(getline(infile, line)){
            lines.push_back(line);
        }
        infile.close();
    }
    ofstream file("gameData.txt");
    if(!file.is_open())
        return -1;
    for(int i = 0; i < lines.size(); ++i){
        file << lines[i] << endl;
    }
    file << "added card" << endl;;
    file << c.getName() << "," << c.getHealth() << "," << c.getDamage() << "," <<
        c.getRange() << "," << c.getSpeed() << "," << c.getCost() << endl;
    file.close();
    return 1;
}

// simple for loop to print card all the cards in the card library
int Main::printCards() const{
    if(numCards == 0)
        return -1;
    for(int i = 0; i < numCards; ++i){
        Card c = cards[i];
        cout << i+1 << ". " << c.getName() << ": H=" << c.getHealth() << ", D=" << c.getDamage()
        << ", R=" << c.getRange() << ", S=" << c.getSpeed() << ", C=" << c.getCost() << endl;
    }
    return 1;
}

// opens card, pve mpa, and pvp maps files.
// stores all of the maps and cards into the Main object
int Main::readFiles(){
    for(int i = 0; i < maxCards; ++i){
        cards[i] = Card();
    }
    numCards = 0;
    for(int i = 0; i < maxMaps; ++i){
        pvpMaps[i] = Map();
        pveMaps[i] = Map();
    }
    numPVPMaps = 0;
    numPVEMaps = 0;
    ifstream gameData("gameData.txt");
    ifstream pvp("pvpMaps.txt");
    ifstream pve("pveMaps.txt");
    ifstream cardFile("cardLibrary.txt");
    string line;
    if(!(pvp.is_open() && pve.is_open() && cardFile.is_open()))
        return -1;
    
    while(getline(cardFile, line) && numCards < maxCards){
        if(line != ""){
            string parts[6];
            split(line, ',', parts, 6);
            Card c(parts[0], stoi(parts[1]), stoi(parts[2]), stoi(parts[3]), stoi(parts[4]),
                stoi(parts[5]), -1, -1, -1);
            cards[numCards] = c;
            ++numCards;
            ++numInitialCards;
        }
    }

    while(getline(pvp, line) && numPVPMaps < maxMaps){
        if(line != ""){
            string parts[4];
            split(line, ',', parts, 4);
            string name = parts[0];
            string description = parts[1];
            int p1h = stoi(parts[2]);
            int p2h = stoi(parts[3]);
            vector<vector<Square>> m;
            while(getline(pvp, line) && line != "*"){
                if(line != ""){
                    vector<Square> row;
                    for(int i = 0; i < line.length(); ++i){
                        if(line[i] != ','){
                            string temp = "";
                            temp += line[i];
                            row.push_back(Square(stoi(temp)));
                        }
                    }
                    m.push_back(row);
                }
            }
            Map map(m, name, description, 1, p1h, p2h);
            pvpMaps[numPVPMaps] = map;
            ++numPVPMaps;
        }
    }

    while(getline(pve, line) && numPVEMaps < maxMaps){
        if(line != ""){
            string parts[4];
            split(line, ',', parts, 4);
            string name = parts[0];
            string description = parts[1];
            int p1h = stoi(parts[2]);
            int p2h = stoi(parts[3]);
            vector<vector<Square>> m;
            while(getline(pve, line) && line != "*"){
                if(line != ""){
                    vector<Square> row;
                    for(int i = 0; i < line.length(); ++i){
                        if(line[i] != ','){
                            string temp = "";
                            temp += line[i];
                            row.push_back(Square(stoi(temp)));
                        }
                    }
                    m.push_back(row);
                }
            }
            Map map(m, name, description, 2, p1h, p2h);
            
            vector<Card> savedCards;
            while(getline(pve, line) && line != "*"){
                string parts[9];
                split(line, ',', parts, 9);
                Card c(parts[0], stoi(parts[1]), stoi(parts[2]), stoi(parts[3]), stoi(parts[4]),
                    stoi(parts[5]), stoi(parts[6]), stoi(parts[7]), stoi(parts[8]));
                map.setSquareAt(c, c.getX(), c.getY());
                savedCards.push_back(c);
            }
            map.setSavedCards(savedCards);
            pveMaps[numPVEMaps] = map;
            ++numPVEMaps;
        }
    }

    if(gameData.is_open()){
        while(getline(gameData, line)){
            if(line.substr(0, 10) == "added card" && numCards < maxCards){
                getline(gameData, line);
                string parts[6];
                split(line, ',', parts, 6);
                Card c(parts[0], stoi(parts[1]), stoi(parts[2]), stoi(parts[3]), stoi(parts[4]),
                    stoi(parts[5]), -1, -1, -1);
                cards[numCards] = c;
                ++numCards;
            }else if(line.substr(0, 3) == "map" && numPVEMaps < maxMaps){
                int index = stoi(line.substr(4, 1));
                getline(gameData, line);
                string parts[numSavedData];
                split(line, ',', parts, numSavedData);
                for(int i = 0; i < numSavedData; ++i){
                    saveData[index][i] = stoi(parts[i]);
                }
                if(saveData[index][0] == 1){
                    Map map = pveMaps[index];
                    for(int i = 0; i < map.getHeight(); ++i){
                        for(int n = 0; n < map.getWidth(); ++n){
                            int type = map.getSquareAt(n, i).getType();
                            if(type == 2 || type == 5 || type == 6)
                                map.setSquareAt(Square(0), n, i);
                        }
                    }
                    vector<Card> savedCards;
                    while(getline(gameData, line) && line != "*"){
                        string parts[9];
                        split(line, ',', parts, 9);
                        savedCards.push_back(Card(parts[0], stoi(parts[1]), stoi(parts[2]),
                            stoi(parts[3]), stoi(parts[4]), stoi(parts[5]), stoi(parts[6]),
                            stoi(parts[7]), stoi(parts[8])));
                    }
                    map.setSavedCards(savedCards);
                    for(int i = 0; i < savedCards.size(); ++i){
                        Card c = savedCards[i];
                        map.setSquareAt(c, c.getX(), c.getY());
                    }
                    map.setPlayer1Health(saveData[index][1]);
                    map.setPlayer2Health(saveData[index][2]);
                    pveMaps[index] = map;
                }
            }
        }
    }

    gameData.close();
    pvp.close();
    pve.close();
    cardFile.close();

    return 1;
}


// in single player, (unfortunately couldn't get single player to work) if you quit game, stores positions of each card and each basehealth into the gameData.txt file
// if you won a game, stores that too.
int Main::writeMap() const{
    string line;
    vector<string> lines;
    ifstream infile("gameData.txt");
    if(infile.is_open()){
        while(getline(infile, line)){
            lines.push_back(line);
        }
        infile.close();
    }
    ofstream file("gameData.txt");
    if(!file.is_open())
        return -1;
    for(int i = 0; i < lines.size(); ++i){
        file << lines[i] << endl;
    }
    Map m = game.getMap();
    int index = -1;
    for(int i = 0; i < numPVEMaps; ++i){
        if(m.getName() == pveMaps[i].getName() && m.getDescription() == pveMaps[i].getDescription())
            index = i;
    }
    if(index == -1)
        return -2;
    file << "map " << index << endl;
    file << saveData[index][0];
    for(int i = 1; i < numSavedData; ++i){
        file << "," << saveData[index][i];
    }
    file << endl;
    if(saveData[index][0] == 1){
        for(int i = 0; i < m.getHeight(); ++i){
            for(int n = 0; n < m.getWidth(); ++n){
                if(m.getSquareAt(n, i).getType() == 2){
                    Card c = m.getSquareAt(n, i).getCard();
                    file << c.getName() << "," << c.getHealth() << "," << c.getDamage() << "," <<
                        c.getRange() << "," << c.getSpeed() << "," << c.getCost() << "," <<
                        c.getX() << "," << c.getY() << "," << c.getPlayer() << endl;
                }
            }
        }
        file << "*" << endl;
    }
    return 1;
}

// checks if the string consists only of digits
bool Main::isNumber(string s) const{
    if(s.length() == 0)
        return false;
    for(int i = 0; i < s.length(); ++i){
        if(isdigit(s[i]) == 0)
            return false;
    }
    return true;
}

// prompts the player for stats to make a new card. Stores the card
int Main::createCard(){
    if(numCards >= maxCards)
        return -1;
    bool good;
    string name = "", temp;
    int h = 0, d = -1, r = -1, s = -1, c = -1;
    while(name == ""){
        cout << "Enter the card's name:" << endl;
        getline(cin, name);
        if(name == "")
            cout << "Don't leave it blank" << endl;
    }
    while(h < 1 || h >= 100){
        good = true;
        cout << "Enter the card's health from 1 to 99:" << endl;
        getline(cin, temp);
        if(!isNumber(temp))
            cout << "The number you entered did not meet the requirements" << endl;
        else{
            h = stoi(temp);
            if(h < 1 || h >= 100)
                cout << "The number you entered did not meet the requirements" << endl;
        }
    }
    while(d < 0 || d >= 100){
        good = true;
        cout << "Enter the card's damage from 0 to 99:" << endl;
        getline(cin, temp);
        if(!isNumber(temp))
            cout << "The number you entered did not meet the requirements" << endl;
        else{
            d = stoi(temp);
            if(d < 1 || d >= 100)
                cout << "The number you entered did not meet the requirements" << endl;
        }
    }
    while(r < 0 || r >= 100){
        good = true;
        cout << "Enter the card's range from 0 to 99:" << endl;
        getline(cin, temp);
        if(!isNumber(temp))
            cout << "The number you entered did not meet the requirements" << endl;
        else{
            r = stoi(temp);
            if(r < 1 || r >= 100)
                cout << "The number you entered did not meet the requirements" << endl;
        }
    }
    while(s < 0 || s >= 100){
        good = true;
        cout << "Enter the card's speed from 0 to 99:" << endl;
        getline(cin, temp);
        if(!isNumber(temp))
            cout << "The number you entered did not meet the requirements" << endl;
        else{
            s = stoi(temp);
            if(s < 1 || s >= 100)
                cout << "The number you entered did not meet the requirements" << endl;
        }
    }
    while(c < 0 || c >= 100){
        good = true;
        cout << "Enter the card's cost from 0 to 99:" << endl;
        getline(cin, temp);
        if(!isNumber(temp))
            cout << "The number you entered did not meet the requirements" << endl;
        else{
            c = stoi(temp);
            if(c < 1 || c >= 100)
                cout << "The number you entered did not meet the requirements" << endl;
        }
    }
    Card card(name, h, d, r, s, c, -1, -1, -1);
    cards[numCards] = card;
    ++numCards;
    writeCard(card);
    return 1;
}

// prints titles and descriptions of all maps in the indicated map array
int Main::printMapDescriptions(int type) const{
    int numMaps;
    Map maps[maxMaps];
    if(type == 1){
        for(int i = 0; i < numPVPMaps; ++i){
            maps[i] = pvpMaps[i];
        }
        numMaps = numPVPMaps;
    }else if(type == 2){
        for(int i = 0; i < numPVEMaps; ++i){
            maps[i] = pveMaps[i];
        }
        numMaps = numPVEMaps;
    }else{
        return -1;
    }
    for(int i = 0; i < numMaps; ++i){
        string temp = "";
        if(saveData[i][0] == 1)
            temp = "(In Progress)";
        if(saveData[i][0] == 2)
            temp = "(Finished)";
        cout << i+1 << ". " << maps[i].getName() << " " << temp << endl;
        cout << maps[i].getDescription() << endl << endl;
    }
    return 1;
}

// I may not have actually used this function in mainDriver.cpp, but it sets all the relevant map squares with the corresponding cards
Map Main::fillMap(Map map) const{
    Deck d1 = game.getP1().getDeck();
    Deck d2 = game.getP2().getDeck();
    for(int i = 0; i < d1.getNumCards(); ++i){
        Card c = d1.getCardAt(i);
        map.setSquareAt(Square(c), c.getX(), c.getY());
    }
    for(int i = 0; i < d2.getNumCards(); ++i){
        Card c = d2.getCardAt(i);
        map.setSquareAt(Square(c), c.getX(), c.getY());
    }
    return map;
}

// checks if if a card or base is in range: int result[3] = {type of target in range, x, y}
int Main::inRange(Card c, int result[3]){
    int x = c.getX(), y = c.getY(), r = c.getRange();
    Map map = game.getMap();
    for(int i = x-r; i < x+r+1; ++i){
        for(int n = y-r; n < y+r+1; ++n){
            if(game.validAttack(x, y, n, i, r)){
                if(map.getSquareAt(n, i).getType() == 3){
                    result[0] = 3;
                    result[1] = n;
                    result[2] = i;
                    return 1;
                }else{
                    result[0] = 2;
                    result[1] = n;
                    result[2] = i;
                    return 1;
                }
            }
        }
    }
    return -1;
}

// when playing single player, determines the best move for your opponent to make
// preference list:
//      will attack base if in range of any cards
//      will attack a card if in range of any cards
//      otherwise, moves the card closest to opponents base, closer to that base
int Main::executeBestMove(){
    Player bot = game.getP2();
    Player player = game.getP1();
    Map map = game.getMap();
    Deck deck = bot.getDeck();
    Deck pDeck = player.getDeck();
    
    int baseX, baseY;
    for(int i = 0; i < map.getHeight(); ++i){
        for(int n = 0; n < map.getWidth(); ++n){
            if(map.getSquareAt(n, i).getType() == 3){
                baseX = n;
                baseY = i;
            }
        }
    }

    for(int i = 0; i < deck.getNumCards(); ++i){
        int result[3];
        Card card = deck.getCardAt(i);
        int check = inRange(card, result);
        if(check != -1){
            if(result[0] == 3){
                map.setPlayer1Health(map.getPlayer1Health() - deck.getCardAt(i).getDamage());
                game.setMap(map);
                return 1;
            }else if(result[0] == 2){
                int index = -1;
                for(int n = 0; n < pDeck.getNumCards(); ++n){
                    Card c = pDeck.getCardAt(n);
                    if(c.getX() == result[1] && c.getY() == result[2])
                        index = i;
                }
                Card temp = pDeck.getCardAt(index);
                int health = temp.getHealth() - card.getDamage();
                if(health < 0) health = 0;
                temp.setHealth(health);
                pDeck.setCardAt(temp, index);
                if(health == 0){
                    map.setSquareAt(Square(), result[1], result[2]);
                    player.setDeck(pDeck);
                    player.removeCard(index);
                    game.setP1(player);
                    game.setMap(map);
                }else{
                    map.setSquareAt(Square(temp), result[1], result[2]);
                    player.setDeck(pDeck);
                    game.setP1(player);
                    game.setMap(map);
                }
                return 1;
            }
        }
    }
    int bestX, bestY, distance = 1000, cardIndex;
    for(int i = 0; i < deck.getNumCards(); ++i){
        int result[3];
        Card card = deck.getCardAt(i);
        int x = card.getX();
        int y = card.getY();
        int s = card.getSpeed();
        int check = inRange(card, result);
        if(check == -1){
            for(int n = x-s; n < x+s+1; ++n){
                for(int z = x-s; z < x+s+1; ++z){
                    if(game.validMove(x, y, z, n, s)){
                        int d = abs(baseX - z) + abs(baseY - n);
                        if(d < distance){
                            distance = d;
                            bestX = z;
                            bestY = n;
                            cardIndex = i;
                        }
                    }
                }
            }
        }
    }
    Card c = deck.getCardAt(cardIndex);
    int x = c.getX();
    int y = c.getY();
    c.setX(bestX);
    c.setY(bestY);
    map.setSquareAt(Card(c), bestX, bestY);
    map.setSquareAt(Square(), x, y);
    deck.setCardAt(c, cardIndex);
    bot.setDeck(deck);
    game.setP2(bot);
    game.setMap(map);

    return 1;
}

