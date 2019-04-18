#include "MainCharacter.h"
const int START_LOCATION = 300;

MainCharacter::MainCharacter() {

    setXLocation(START_LOCATION);
    setYLocation(START_LOCATION);
    xIndex = 5;
    yIndex = 5;
    
    mainCharacterTexture = ResourceManager::getInstance().mainCharacterTexture;

};

MainCharacter::~MainCharacter() {

};

void MainCharacter::render(SDL_Renderer *renderer, float xLocation, float yLocation) {

    SDL_Rect rect;
    rect.x = xLocation;
    rect.y = yLocation;
    rect.w = CHARACTER_WIDTH;
    rect.h = CHARACTER_HEIGHT;
    SDL_RenderCopy(renderer, mainCharacterTexture, NULL, &rect);

};

void MainCharacter::update() {

    
};

void MainCharacter::setXLocation(float newX) {
    xLocation = newX;
};

void MainCharacter::setYLocation(float newY) {
    yLocation = newY;
};

float MainCharacter::getXLocation() {
    return xLocation;
}

float MainCharacter::getYLocation() {
    return yLocation;
}


int MainCharacter::getXIndex() {
    return xIndex;
}

int MainCharacter::getYIndex() {
    return yIndex;
}

void MainCharacter::setXIndex(int newIndex) {
    xIndex = newIndex;
}

void MainCharacter::setYIndex(int newIndex) {
    yIndex = newIndex;
}

void MainCharacter::reset() {
    setXLocation(START_LOCATION);
    setYLocation(START_LOCATION);
    xIndex = 5;
    yIndex = 5;
}
