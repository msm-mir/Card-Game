#include <iostream>
#include <windows.h>
#include "card.h"
#include "cardtype.h"
#include "player.h"

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void setPlayerNum(int&);
void setMaxScore(int&);
void setGameType(int&);
void give1stRandCards(int, Player*, Card*);
bool giveRandCards(int, int, Player*, Card*);
bool selectCardByPlayers(int, int, Player*, Card*);

int main() {
    int numOfPlayers = 0;
    setPlayerNum(numOfPlayers);
    auto *players = new Player[numOfPlayers];
    players->setPlayerName(numOfPlayers);

    int maxScore;
    setMaxScore(maxScore);

    int gameType;
    setGameType(gameType);

    Card *cards = new Card[90];
    cards->setGameCards();
    give1stRandCards(numOfPlayers, players, cards);

    bool EOP;
    int idx = 0;
    while (true) {

        if (!selectCardByPlayers(numOfPlayers, idx % numOfPlayers, players, cards)) {
            EOP = players->endOfRound(numOfPlayers, gameType, maxScore);
            if (!EOP)
                break;
            players->delGalleryCards(numOfPlayers);
            cards->setGameCards();
            give1stRandCards(numOfPlayers, players, cards);
        }

        /*if (!EOP)
            break;*/

        idx++;
    }

    delete [] players;
    delete [] cards;

    return 0;
}

void setPlayerNum(int &numOfPlayers) {
    cout << "Please enter the number of players: ";
    cin >> numOfPlayers;
    while (numOfPlayers < 2) {
        cout << "Number of players must above two!: ";
        cin >> numOfPlayers;
    }
}

void setMaxScore(int &maxScore) {
    cout << "Please enter maximum score: ";
    cin >> maxScore;
}

void setGameType(int &gameType) {
    cout << "Please select the type of game: " << endl << "1. Ordinary" << endl << "2. Professional" << endl;
    cin >> gameType;
}

void give1stRandCards(int numOfPlayers, Player *players, Card *cards) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < numOfPlayers; j++) {
            giveRandCards(j, i, players, cards);
        }
    }
}

bool giveRandCards(int playerIdx, int playerCardIdx, Player *players, Card *cards) {
    int randCard;
    static int lastCardIdx = 90;

    Sleep(100);
    srand(time(0));
    randCard = rand() % lastCardIdx;

    players[playerIdx].setHandCards(cards[randCard], playerCardIdx);

    cards[randCard].setType(CardType::None);
    cards[randCard].setScore(0);

    lastCardIdx--;
    if (lastCardIdx == -1)
        return false;
    swap(cards[randCard], cards[lastCardIdx]);

    return true;
}

bool selectCardByPlayers(int numOfPlayers, int playerIdx, Player *players, Card *cards) {
    system("cls");

    cout << players[playerIdx].getName() << "! It's your turn to choose your card:" << endl;
    players->printHandCards(playerIdx);
    players->printOneGalleryCards(playerIdx, "Your");
    players->printOtherGalleryCards(playerIdx, numOfPlayers);

    int selCard = 0, selPlayer = 0, selPosition = 0;
    players->printSelecting(selCard, selPlayer, selPosition, playerIdx);

    players[selPlayer].setGalleryCards(players[playerIdx].getHandCards(selCard), selPosition);

    if (players->mergeColumn(selPlayer, selPosition)) {
        cout << "\n\n";
        players->printOneGalleryCards(selPlayer, players[selPlayer].getName() + "'s new");
        Sleep(5000);
    }

    if (players->check6Column(selPlayer) || !giveRandCards(playerIdx, selCard, players, cards)) {
        return false;
    }

    return true;
}
