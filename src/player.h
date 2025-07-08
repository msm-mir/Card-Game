#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include <string>
#include <windows.h>

using namespace std;

extern HANDLE h;

class Player
{
private:
    string name;
    int score;
    Card cardsInHand[3];
    Card cardsInGallery[6];

public:
    Player();
    string getName();
    [[nodiscard]] int getScore() const;
    Card getHandCards(int);
    Card getGalleryCards(int);
    void setName(string);
    void setScore(int);
    void setHandCards(Card, int);
    void setGalleryCards(Card, int);
    void setPlayerName(int);
    void printHandCards(int);
    void printOneGalleryCards(int, const string&);
    void printOtherGalleryCards(int, int);
    void printSelecting(int&, int&, int&, int);
    bool checkSelPosition(int, int, int, int);
    bool mergeColumn(int, int);
    bool check6Column(int);
    bool check3Type(int);
    void calScores(int);
    bool endOfRound(int, int, int);
    void delGalleryCards(int);
    void endOfGame(int);
    void printScoreBoard(int);
};

#endif // PLAYER_H
