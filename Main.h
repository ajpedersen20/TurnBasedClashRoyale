#include "Square.h"
#include "Map.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"

using namespace std;

#ifndef MAIN
#define MAIN

class Main{

    private:
        static const int maxMaps = 25;
        static const int maxCards = 50;
        static const int numSavedData = 5;
        int numPVPMaps;
        int numPVEMaps;
        int numCards;
        int numInitialCards;
        Map pvpMaps[maxMaps];
        Map pveMaps[maxMaps];
        Card cards[maxCards];
        Game game;
        int saveData[maxMaps][numSavedData]; // progress, p1h, p2h, who's move, number of moves

    public:
        Main();
        Main(Map pvpm[], int numPVP, Map pvem[], int numPVE, Card _cards[], int nCards, int numIC, Game g);
        Main(Map pvpm[], int numPVP, Map pvem[], int numPVE, Card _cards[], int nCards, int numIC, Game g, int sd[maxMaps][numSavedData]);
        int getMaxMaps() const;
        int getMaxCards() const;
        int getNumPVPMaps() const;
        int getNumPVEMaps() const;
        int getNumCards() const;
        Map getPVPMap(int index) const;
        Map getPVEMap(int index) const;
        Card getCard(int index) const;
        Game getGame() const;
        int getSaveData(int first, int second) const;
        void setNumPVPMaps(int num);
        void setNumPVEMaps(int num);
        void setNumCards(int num);
        int addPVPMap(Map map);
        int addPVEMap(Map map);
        int addCard(Card card);
        void setGame(Game g);
        void setSaveData(int first, int second, int val);

        // helper functions

        int previewMap(int type, Map map) const;
        int writeCard(Card c) const;
        int writeMap() const;
        int printCards() const;
        int readFiles();
        int createCard();
        void saveGame() const;
        int printMapDescriptions(int type) const;
        bool isNumber(string s) const;
        void setProgress(int index);
        Map fillMap(Map map) const;
        int inRange(Card c, int result[3]);
        int executeBestMove();
};

#endif