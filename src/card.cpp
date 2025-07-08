#include "card.h"

Card::Card() {
    this->type = CardType::None;
    this->score = 0;
}

CardType Card::getType() {
    return this->type;
}

[[nodiscard]] int Card::getScore() const {
    return this->score;
}

void Card::setType(CardType cardType) {
    this->type = cardType;
}

void Card::setScore(int i) {
    this->score = i;
}

void Card::setGameCards() {
    int cardScore = 1;

    for (int i = 0; i < 90; i++) {
        if ((cardScore == 1) || (cardScore == 4) || (cardScore == 9) || (cardScore == 11) || (cardScore == 15)) {
            this[i].setScore(cardScore);
            this[i].setType(CardType::KaleKado);
        }

        if ((cardScore == 3) || (cardScore == 6) || (cardScore == 8) || (cardScore == 10) || (cardScore == 13)) {
            this[i].setScore(cardScore);
            this[i].setType(CardType::GorBeGor);
        }

        if ((cardScore == 2) || (cardScore == 5) || (cardScore == 7) || (cardScore == 12) || (cardScore == 14)) {
            this[i].setScore(cardScore);
            this[i].setType(CardType::KohnePich);
        }

        if (i % 6 == 5)
            cardScore++;
    }
}
