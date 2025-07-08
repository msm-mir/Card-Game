#include <iostream>
#include "player.h"

Player::Player() {
    this->name = "";
    this->score = 0;
}

string Player::getName() {
    return this->name;
}

[[nodiscard]] int Player::getScore() const {
    return this->score;
}

Card Player::getHandCards(int idx) {
    return this->cardsInHand[idx];
}

Card Player::getGalleryCards(int idx) {
    return this->cardsInGallery[idx];
}

void Player::setName(string s) {
    this->name = std::move(s);
}

void Player::setScore(int i) {
    this->score = i;
}

void Player::setHandCards(Card newCard, int idx) {
    this->cardsInHand[idx] = newCard;
}

void Player::setGalleryCards(Card newCard, int idx) {
    this->cardsInGallery[idx] = newCard;
}

void Player::setPlayerName(int numOfPlayers) {
    cout << "Please enter names of the players:" << endl;
    string playerName;

    for (int i = 0; i < numOfPlayers; i++) {
        cin >> playerName;
        this[i].setName(playerName);
    }
}

void Player::printHandCards(int playerIdx) {
    for (int i = 0; i < 3; i++) {
        if (this[playerIdx].getHandCards(i).getType() == CardType::KaleKado) {
            SetConsoleTextAttribute(h, 6);
            cout << i+1 << ". " << "KaleKado" << "(" << this[playerIdx].getHandCards(i).getScore() << ")     ";
            SetConsoleTextAttribute(h, 7);
        }
        else if (this[playerIdx].getHandCards(i).getType() == CardType::GorBeGor) {
            SetConsoleTextAttribute(h, 2);
            cout << i+1 << ". " << "GorBeGor" << "(" << this[playerIdx].getHandCards(i).getScore() << ")     ";
            SetConsoleTextAttribute(h, 7);
        }
        else if (this[playerIdx].getHandCards(i).getType() == CardType::KohnePich) {
            SetConsoleTextAttribute(h, 15);
            cout << i+1 << ". " << "KohnePich" << "(" << this[playerIdx].getHandCards(i).getScore() << ")     ";
            SetConsoleTextAttribute(h, 7);
        }
    }

    cout << "\n\n";
}

void Player::printOneGalleryCards(int playerIdx, const string& playerName) {
    cout << playerName << " deads gallery cards:" << endl;
    for (int i = 0; i < 6; i++) {
        if (this[playerIdx].getGalleryCards(i).getType() == CardType::KaleKado) {
            SetConsoleTextAttribute(h, 6);
            cout << i+1 << ". " << "KaleKado" << "(" << this[playerIdx].getGalleryCards(i).getScore() << ")     ";
            SetConsoleTextAttribute(h, 7);
        }
        else if (this[playerIdx].getGalleryCards(i).getType() == CardType::GorBeGor) {
            SetConsoleTextAttribute(h, 2);
            cout << i+1 << ". " << "GorBeGor" << "(" << this[playerIdx].getGalleryCards(i).getScore() << ")     ";
            SetConsoleTextAttribute(h, 7);
        }
        else if (this[playerIdx].getGalleryCards(i).getType() == CardType::KohnePich) {
            SetConsoleTextAttribute(h, 15);
            cout << i+1 << ". " << "KohnePich" << "(" << this[playerIdx].getGalleryCards(i).getScore() << ")     ";
            SetConsoleTextAttribute(h, 7);
        }
        else {
            cout << i+1 << ". \t";
        }
    }

    cout << "\n\n\n";
}

void Player::printOtherGalleryCards(int playerIdx, int numOfPlayers) {
    for (int i = 0; i < numOfPlayers; i++) {
        if (i != playerIdx) {
            cout << i+1 << ") " << this[i].getName() << "'s deads gallery's cards:" << endl;

            for (int j = 0; j < 6; j++) {
                if (this[i].getGalleryCards(j).getType() == CardType::KaleKado) {
                    SetConsoleTextAttribute(h, 6);
                    cout << j+1 << ". " << "KaleKado" << "(" << this[i].getGalleryCards(j).getScore() << ")     ";
                    SetConsoleTextAttribute(h, 7);
                }
                else if (this[i].getGalleryCards(j).getType() == CardType::GorBeGor) {
                    SetConsoleTextAttribute(h, 2);
                    cout << j+1 << ". " << "GorBeGor" << "(" << this[i].getGalleryCards(j).getScore() << ")     ";
                    SetConsoleTextAttribute(h, 7);
                }
                else if (this[i].getGalleryCards(j).getType() == CardType::KohnePich) {
                    SetConsoleTextAttribute(h, 15);
                    cout << j+1 << ". " << "KohnePich" << "(" << this[i].getGalleryCards(j).getScore() << ")     ";
                    SetConsoleTextAttribute(h, 7);
                }
                else {
                    cout << j+1 << ". \t";
                }
            }
            cout << "\n\n";
        }
    }
}

void Player::printSelecting(int &selCard, int &selPlayer, int &selPosition, int playerIdx) {
    cout << "Please select your card: ";
    cin >> selCard;
    selCard--;

    cout << "Please select the player: ";
    cin >> selPlayer;
    selPlayer--;

    do {
        cout << "Please select the card's position: ";
        cin >> selPosition;
        selPosition--;
    } while (!this->checkSelPosition(selCard, selPlayer, selPosition, playerIdx));
}

bool Player::checkSelPosition(int selCard, int selPlayer, int selPosition, int playerIdx) {
    if (this[selPlayer].getGalleryCards(selPosition).getType() == CardType::None ||
        this[selPlayer].getGalleryCards(selPosition).getType() == this[playerIdx].getHandCards(selCard).getType()) {
        return true;
    }
    return false;
}

bool Player::mergeColumn(int playerIdx, int selPosition) {
    bool mergeCheck = false;
    Card cards;
    cards.setType(CardType::None);
    cards.setScore(0);

    for (int i = 0; i < 6; i++) {
        if (selPosition != i)
            if (this[playerIdx].getGalleryCards(selPosition).getType() == this[playerIdx].getGalleryCards(i).getType() &&
                this[playerIdx].getGalleryCards(selPosition).getScore() == this[playerIdx].getGalleryCards(i).getScore()) {
                this[playerIdx].setGalleryCards(cards, selPosition);
                this[playerIdx].setGalleryCards(cards, selPosition);

                mergeCheck = true;
                break;
            }
    }
    return mergeCheck;
}

bool Player::check6Column(int playerIdx) {
    for (int i = 0; i < 6; i++) {
        if (this[playerIdx].getGalleryCards(i).getType() == CardType::None)
            return false;
    }
    return true;
}

bool Player::check3Type(int playerIdx) {
    bool KaleKadoBool = false;
    bool GorBeGorBool = false;
    bool KohnePichBool = false;

    for (int i = 0; i < 6; i++) {
        if (this[playerIdx].getGalleryCards(i).getType() == CardType::KaleKado)
            KaleKadoBool = true;
        else if (this[playerIdx].getGalleryCards(i).getType() == CardType::GorBeGor)
            GorBeGorBool = true;
        else if (this[playerIdx].getGalleryCards(i).getType() == CardType::KohnePich)
            KohnePichBool = true;
    }

    if (KaleKadoBool && GorBeGorBool && KohnePichBool)
        return true;
    else
        return false;
}

void Player::calScores(int playerIdx) {
    int cardScore = 0;

    for (int i = 0; i < 6; i++) {
        cardScore += this[playerIdx].getGalleryCards(i).getScore();
    }

    this[playerIdx].setScore(cardScore);
}

bool Player::endOfRound(int numOfPlayers, int gameType, int maxScore) {
    cout << "\n\n" << "This round ends!" << endl;
    Sleep(5000);

    int max = INT_MIN;
    for (int i = 0; i < numOfPlayers; i++) {
        if (this->check3Type(i)) {
            this->calScores(i);

            if (this[i].getScore() >= max) {
                max = this[i].getScore();
            }
        }
    }

    if (gameType == 2) {
        for (int i = 0; i < numOfPlayers; i++) {
            if (this[i].getScore() != max) {
                this[i].setScore(0);
            }
        }
    }

    if (max >= maxScore) {
        this->endOfGame(numOfPlayers);
        return false;
    }

    return true;
}

void Player::delGalleryCards(int numOfPlayers) {
    Card cards;
    cards.setType(CardType::None);
    cards.setScore(0);

    for (int i = 0; i < numOfPlayers; i++) {
        for (int j = 0; j < 6; j++)
            this[i].setGalleryCards(cards, j);
    }
}

void Player::endOfGame(int numOfPlayers) {
    cout << "The game ends!" << endl;

    for (int i = 0; i < numOfPlayers - 1; i++) {
        for (int j = 0; j < numOfPlayers - 1 - i; j++) {
            if (this[j].getScore() < this[j + 1].getScore()) {
                swap(this[j], this[j + 1]);
            }
        }
    }

    this->printScoreBoard(numOfPlayers);
}

void Player::printScoreBoard(int numOfPlayers) {
    system("cls");

    SetConsoleTextAttribute(h, 7);
    printf("%-2s", "rank");
    printf(" | ");
    SetConsoleTextAttribute(h, 3);
    printf("%-15s", "name");
    SetConsoleTextAttribute(h, 7);
    printf(" | ");
    SetConsoleTextAttribute(h, 12);
    printf("%-3s\n", "score");
    SetConsoleTextAttribute(h, 7);

    for (int i = 0; i < 30; ++i) {
        printf("%s", "-");
    }
    printf("\n");

    for (int i = 0; i < numOfPlayers; ++i) {
        SetConsoleTextAttribute(h, 7);
        printf("%-2s     ", to_string(i+1).c_str());
        SetConsoleTextAttribute(h, 3);
        printf("%-15s   ", this[i].getName().c_str());
        SetConsoleTextAttribute(h, 12);
        printf("%-3s\n", to_string(this[i].getScore()).c_str());
    }

    SetConsoleTextAttribute(h, 7);

    cout << "\n\n\n\n\n";
}
