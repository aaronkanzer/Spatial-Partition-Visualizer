#include "Opponent.h"
#include "Tool.h"

Opponent::Opponent() {

    xLocationStart = (rand() % 600);
    yLocationStart = (rand() % 600);
    opponentVector = Vector2D(xLocationStart, yLocationStart);
    direction = Normalize(Vector2D(1, 1));
    xLocation = xLocationStart;
    yLocation = yLocationStart;
    opponentSpeed = 0.5;
    xIndex = (int)xLocationStart / 60;
    yIndex = (int)yLocationStart / 60;

};

Opponent::~Opponent() {
    
};

void Opponent::update() {

    opponentVector += (direction * getOpponentSpeed());
    checkXCollision();
    checkYCollision();
    checkCeilingCollision();

}

float Opponent::getXLocation() {

    return opponentVector.x;

};

float Opponent::getYLocation() {

    return opponentVector.y;

};

 void Opponent::setXLocation(float newX) {
     opponentVector.x = newX;
 }

 void Opponent::setYLocation(float newY) {
     opponentVector.y = newY;
 }

 float Opponent::getOpponentSpeed() {
     return opponentSpeed;
 }

 void Opponent::setOpponentSpeed(float newSpeed) {
     opponentSpeed = newSpeed;
 }

 void Opponent::checkXCollision() {
    if (opponentVector.x < 0 || opponentVector.x > SCREEN_WIDTH - 15)
    {
        direction.x = -direction.x;
    }
    else if (opponentVector.y < 0)
    {
        direction.y = abs(direction.y);
    }
    else
    {
        return;
    }
 }

 void Opponent::checkYCollision() {
    if (opponentVector.y < 0 || opponentVector.y > SCREEN_HEIGHT - 15)
    {
        direction.y = -direction.y;
    }
    else if (opponentVector.x < 0)
    {
        direction.y = abs(direction.y);
    }
    else
    {
        return;
    }
 }

 void Opponent::checkCeilingCollision()
{
    if (opponentVector.y < 0) 
    {
        direction.y = abs(direction.y);
        return;
    }
    else
    {
        return;
    }
}

int Opponent::getXIndex() {
    return xIndex;
}

int Opponent::getYIndex() {
    return yIndex;
}

void Opponent::setXIndex(int newIndex) {
    xIndex = newIndex;
}

void Opponent::setYIndex(int newIndex) {
    yIndex = newIndex;
}

float Opponent::getOriginalX() {
    return xLocationStart;
}

float Opponent::getOriginalY() {
    return yLocationStart;
}

void Opponent::setOriginalX(float x) {
     xLocationStart = x;
}

void Opponent::setOriginalY(float y) {
     yLocationStart = y;
}
