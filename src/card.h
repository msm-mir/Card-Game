#ifndef CARD_H
#define CARD_H
#include "cardtype.h"

class Card
{
private:
    CardType type;
    int score;

public:
    Card();
    CardType getType();
    [[nodiscard]] int getScore() const;
    void setType(CardType);
    void setScore(int);
    void setGameCards();
};

#endif // CARD_H
