#include <iostream>
#include <string>
#include "Tool.h"
#include "ResourceManager.h"
#include "MainCharacter.h"
#include "Opponent.h"
#include <string>
#include <stdlib.h>

const float GAME_SPEED = 12;
const float OFFSET = 43;
const float RENDER_BOX_SIZE = 100;
float GAME_OPPONENT_COUNT = 20;
const float GAME_CONSTANT = 3;

//! Tool Constructor
Tool::Tool()
{
    isGameMode = false;
    isEditor = false;
    isSpatialVisual = false;
    framesRendered = 0;
    framesPerSecondInt = 0;
    lag = 0.0;
    previous = SDL_GetTicks();
}

//! Tool Deconstructor
Tool::~Tool()
{

}

// Initializes Tool -- SDL_Image, Window Creation, Renderer Creation
void Tool::init(const char *title, int xCoord, int yCoord, int width, int height, bool fullScreen)
{

    TTF_Init();

    for (int i = 0; i < NUMBER_OF_ROWS; i++) {
        for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
            gridCount[i][j] = 0;
        }
    }
    
    int flags = 0;
    if (fullScreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_Log("Subsystems Initialized....");
        window = SDL_CreateWindow(title, xCoord, yCoord, width, height, flags);
        if (window)
        {
            SDL_Log("Window created!");
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_Log("Renderer successfully created!");
        isRunning = true;
    }

    else
    {
        isRunning = false;
    }

    // Loading resources
    ResourceManager::getInstance().startUp();
    ResourceManager::getInstance().createTextures(renderer);
    font = ResourceManager::getInstance().font;
    backgroundMusic = ResourceManager::getInstance().backgroundMusic;
    highScoreSound = Mix_LoadWAV("../Assets/sfx/highscore.wav");
    collisionSound = Mix_LoadWAV("../Assets/sfx/astroidCollision.wav");
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(backgroundMusic, -1);
    }

    // Setup - Objects
    mainCharacter = new MainCharacter();
    int xTemp = mainCharacter->getXIndex();
    int yTemp = mainCharacter->getYIndex();

    for(int j = 0; j < POOL_SIZE; j++) {
        opponents[j] = 0;
    }

    for(int x = 0; x < GAME_OPPONENT_COUNT; x++) {
        if(opponents[x] == 0) {
            opponents[x] = new Opponent();
        }
    }


}

void Tool::clean() {
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    Mix_FreeChunk(highScoreSound);
    Mix_FreeChunk(collisionSound);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    Mix_Quit();
    for(int i  = 0; i < GAME_OPPONENT_COUNT; i++) {
        opponents[i]->~Opponent();
    }
    mainCharacter->~MainCharacter();
    SDL_Log("Game Cleaned!");
    return;
}

void Tool::handleEvents() {

    int x = 0;
    int y = 0;

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        // Editor mode -- mouse logic
        if(isEditor) {

            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                    SDL_GetMouseState( &x, &y );

                    currentAsteroid = checkAsteroidClick(x,y);

                    if(currentAsteroid != - 1) {
                        opponents[currentAsteroid]->setOriginalX(float(x));
                        opponents[currentAsteroid]->setOriginalY(float(y));
                    }

                    if (e.type == SDL_MOUSEBUTTONDOWN) {

                        editingAsteroid = true;

                    }

                    if (e.type == SDL_MOUSEMOTION && currentAsteroid != - 1) {
                        opponents[currentAsteroid]->setOriginalX(float(x));
                        opponents[currentAsteroid]->setOriginalY(float(y));
                    }

                    break;
            }

            if(e.type == SDL_MOUSEBUTTONUP)
            {
                    SDL_GetMouseState( &x, &y );

                    if (currentAsteroid != - 1) {
                        opponents[currentAsteroid]->setOriginalX(float(x));
                        opponents[currentAsteroid]->setOriginalY(float(y));
                        editingAsteroid = false;
                    }

                    break;
            }

        }

        //User presses a key
        if (e.type == SDL_KEYDOWN)
        {
            //Select surfaces based on key press
            switch (e.key.keysym.sym)
            {

            // Move main character
            case SDLK_LEFT:
                if(mainCharacter->getXLocation() > 0) {
                    mainCharacter->setXLocation(mainCharacter->getXLocation() - GAME_SPEED);
                }
                break;
            case SDLK_RIGHT:
                if(mainCharacter->getXLocation() < (SCREEN_WIDTH - 20)) {
                    mainCharacter->setXLocation(mainCharacter->getXLocation() + GAME_SPEED);
                }
                break;
            case SDLK_UP:
                if(mainCharacter->getYLocation() > 0) {
                    mainCharacter->setYLocation(mainCharacter->getYLocation() - GAME_SPEED);
                }
                break;
            case SDLK_DOWN:
                if(mainCharacter->getYLocation() < (SCREEN_HEIGHT - 20)) {
                    mainCharacter->setYLocation(mainCharacter->getYLocation() + GAME_SPEED);
                }
                break;

            // Play game
            case SDLK_p:
                gridCount[mainCharacter->getXIndex()][mainCharacter->getYIndex()] = 0;
                startTime = time(0);
                for(int x = 0; x < GAME_OPPONENT_COUNT; x++) {
                    opponents[x]->setOpponentSpeed(1.2);
                    opponents[x]->setXLocation(opponents[x]->getOriginalX());
                    opponents[x]->setYLocation(opponents[x]->getOriginalY());
                }
                mainCharacter->reset();
                isGameMode = true;
                isMainMenu = false;
                break;

            // Back to main menu
            case SDLK_b:
                gridCount[mainCharacter->getXIndex()][mainCharacter->getYIndex()] = 0;
                if(isHighScore) {
                    highScore = score;
                    isHighScore = false;
                }
                isEditor = false;
                isGameMode = false;
                isSpatialVisual = false;
                isGameOver = false;
                isMainMenu = true;
                hasGOSoundPlayed = false;
                for (int i = 0; i < NUMBER_OF_ROWS; i++) {
                    for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
                        gridCount[i][j] = 0;
                    }
                }
                score = 0;
                break;

            // Demo mode
            case SDLK_d:
                gridCount[mainCharacter->getXIndex()][mainCharacter->getYIndex()] = 0;
                for(int x = 0; x < GAME_OPPONENT_COUNT; x++) {
                    opponents[x]->setOpponentSpeed(0.5);
                }
                calibrateGrid();
                isSpatialVisual = true;
                isMainMenu = false;
                break;
            
            // Editor mode
            case SDLK_e:
                
                isEditor = true;
                isMainMenu = false;
                isGameMode = false;
                isSpatialVisual = false;
                isGameOver = false;
                break;

            // quit
            case SDLK_q:
                isRunning = false;
                break;
            default:
                break;
            }
        }
    }

}


void Tool::update() {

    for(int i = 0; i < POOL_SIZE; i++) {
        if(opponents[i] != NULL) {    
            opponents[i]->update();
        }
    }

    if(isGameMode) {
        updateGameState();
    }

}

void Tool::updateGameState() {

    double seconds_since_start = difftime(time(0), startTime);
    score = (int)seconds_since_start;    

    if(score > highScore) {
        highScore = score;
        isHighScore = true;
    }

}

void Tool::render() {

    if(isMainMenu) {

        renderMainMenu();

    }

    if(isGameMode) {
        SDL_RenderClear(renderer);
        renderOpponents();
        renderGameStats();
        bool collisionOccured = false;
        for(int i = 0; i < GAME_OPPONENT_COUNT; i++) {
            collisionOccured = checkAsteroidCollision(opponents[i]->getXLocation(), opponents[i]->getYLocation());
            if(collisionOccured) {
                isMainMenu = false;
                isGameMode = false;
                isGameOver = true;
                break;
            }
            collisionOccured = false;
        }
        mainCharacter->render(renderer,mainCharacter->getXLocation(),mainCharacter->getYLocation());
        SDL_RenderPresent(renderer);
    }

    if(isSpatialVisual) {

        SDL_RenderClear(renderer);
        renderGrid();
        renderBox();
        renderOpponents();
        mainCharacter->render(renderer,mainCharacter->getXLocation(),mainCharacter->getYLocation());
        SDL_RenderPresent(renderer);
        
    }

    if(isGameOver) {
        renderGameSummary();
    }

    if(isEditor) {

        SDL_RenderClear(renderer);
        renderGrid();
        renderEditor();
        SDL_RenderPresent(renderer);

    }

}

void Tool::renderGameSummary() {

    SDL_RenderClear(renderer);
    SDL_Color White = {255, 255, 255};
    SDL_Color Green = {57, 255, 20};

    if(!hasGOSoundPlayed) {
        Mix_PlayChannel(-1,collisionSound, 0);
        hasGOSoundPlayed = true;
    }

    // Game Over Message
    SDL_Surface *gameOverMessage = TTF_RenderText_Solid(font, "Game Over!", White);
    SDL_Texture *gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverMessage);
    SDL_Rect goRect;
    goRect.x = 150;
    goRect.y = 250;
    goRect.w = 300;
    goRect.h = 70;

    // Press B to Return Home
    SDL_Surface *bMessage = TTF_RenderText_Solid(font, "Press B to Return to Main Menu", White);
    SDL_Texture *bTexture = SDL_CreateTextureFromSurface(renderer, bMessage);
    SDL_Rect bRect;
    bRect.x = 100;
    bRect.y = 400;
    bRect.w = 400;
    bRect.h = 60;

    
    // High Score
    SDL_Surface *hsMessage = TTF_RenderText_Solid(font, "NEW HIGH SCORE! CONGRATS!", Green);
    SDL_Texture *hsTexture = SDL_CreateTextureFromSurface(renderer, hsMessage);
    SDL_Rect hsRect;
    hsRect.x = 100;
    hsRect.y = 100;
    hsRect.w = 400;
    hsRect.h = 80;

    // Render
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &goRect);
    SDL_RenderCopy(renderer, bTexture, NULL, &bRect);

    if(isHighScore) {
        SDL_RenderCopy(renderer, hsTexture, NULL, &hsRect);
        Mix_PlayChannel(-1, highScoreSound, 0);
        SDL_FreeSurface(hsMessage);
        SDL_DestroyTexture(hsTexture);
    }

    // Clean
    SDL_FreeSurface(gameOverMessage);
    SDL_DestroyTexture(gameOverTexture);

    SDL_FreeSurface(bMessage);
    SDL_DestroyTexture(bTexture);

    SDL_RenderPresent(renderer);

}

void Tool::renderMainMenu() {

    SDL_RenderClear(renderer);
    SDL_Color White = {255, 255, 255};

    // Title Message
    SDL_Surface *spatialMessage = TTF_RenderText_Solid(font, "Spatial Partitioning with Asteroids!", White);
    SDL_Texture *spatialTexture = SDL_CreateTextureFromSurface(renderer, spatialMessage);
    SDL_Rect titleRect;
    titleRect.x = 70;
    titleRect.y = 100;
    titleRect.w = 450;
    titleRect.h = 54;

    // Press P for Play Asteroids
    SDL_Surface *playMessage = TTF_RenderText_Solid(font, "Press P to Play Asteroids", White);
    SDL_Texture *playTexture = SDL_CreateTextureFromSurface(renderer, playMessage);
    SDL_Rect pRect;
    pRect.x = 160;
    pRect.y = 250;
    pRect.w = 280;
    pRect.h = 45;

    // Press D for Demo
    SDL_Surface *dMessage = TTF_RenderText_Solid(font, "Press D for Demo", White);
    SDL_Texture *dTexture = SDL_CreateTextureFromSurface(renderer, dMessage);
    SDL_Rect dRect;
    dRect.x = 160;
    dRect.y = 320;
    dRect.w = 200;
    dRect.h = 45;

    // Press E for Editor
    SDL_Surface *eMessage = TTF_RenderText_Solid(font, "Press E for Editor", White);
    SDL_Texture *eTexture = SDL_CreateTextureFromSurface(renderer, eMessage);
    SDL_Rect editorRect;
    editorRect.x = 160;
    editorRect.y = 390;
    editorRect.w = 200;
    editorRect.h = 45;

    // Background Image
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT;
    SDL_RenderCopy(renderer, ResourceManager::getInstance().hubbleTexture, NULL, &rect);

    // Render
    SDL_RenderCopy(renderer, spatialTexture, NULL, &titleRect);
    SDL_RenderCopy(renderer, playTexture, NULL, &pRect);
    SDL_RenderCopy(renderer, dTexture, NULL, &dRect);
    SDL_RenderCopy(renderer, eTexture, NULL, &editorRect);

    // Clean
    SDL_FreeSurface(spatialMessage);
    SDL_DestroyTexture(spatialTexture);

    SDL_FreeSurface(playMessage);
    SDL_DestroyTexture(playTexture);

    SDL_FreeSurface(dMessage);
    SDL_DestroyTexture(dTexture);

    SDL_FreeSurface(eMessage);
    SDL_DestroyTexture(eTexture);

    SDL_RenderPresent(renderer);

}

void Tool::calibrateGrid() {

    int x = ((int)mainCharacter->getYLocation() / 60);
    int y = ((int)mainCharacter->getXLocation() / 60);
    int priorMainX = mainCharacter->getXIndex();
    int priorMainY = mainCharacter->getYIndex();

    if(priorMainX != x && priorMainY != y) {
        gridCount[x][y] += 1;
        gridCount[priorMainX][y] -= 1;
        mainCharacter->setXIndex(x);
        gridCount[x][priorMainY] -= 1;
        mainCharacter->setYIndex(y);
    }    
    
    else if(priorMainX != x) {
        gridCount[x][y] += 1;
        gridCount[priorMainX][y] -= 1;
        mainCharacter->setXIndex(x);
    }

    else if(priorMainY != y) {
        gridCount[x][y] += 1;
        gridCount[x][priorMainY] -= 1;
        mainCharacter->setYIndex(y);
    }

    for(int i = 0; i < GAME_OPPONENT_COUNT; i++) {

        int a = ((int)opponents[i]->getYLocation() / 60);
        int b = ((int)opponents[i]->getXLocation() / 60);
        int priorOppX = opponents[i]->getXIndex();
        int priorOppY = opponents[i]->getYIndex();

        if((priorOppX != a) && (priorOppY != b)) {
            gridCount[a][b] += 1;
            gridCount[priorOppX][b] -= 1;
            opponents[i]->setXIndex(a);
            gridCount[a][priorOppY] -= 1;
            opponents[i]->setYIndex(b);
        }
        else if(priorOppX != a) {
            gridCount[a][b] += 1;
            gridCount[priorOppX][b] -= 1;
            opponents[i]->setXIndex(a);
        }
        else if(priorOppY != b) {
            gridCount[a][b] += 1;
            gridCount[a][priorOppY] -= 1;
            opponents[i]->setYIndex(b);
        }

    }

    return;

}

void Tool::renderGrid() {

    SDL_Color Grey = {80, 105, 105};
    SDL_Surface *numberMessage;
    SDL_Texture *numberTexture;
    std::string numberToRender;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT;
    SDL_RenderCopy(renderer, ResourceManager::getInstance().gridTexture, NULL, &rect);

        calibrateGrid();
        if(isSpatialVisual) {
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 10; j++) {
                    if(gridCount[i][j] < 0) {
                        gridCount[i][j] = 0;
                    }
                    numberToRender = std::to_string(gridCount[i][j]);
                    numberMessage = TTF_RenderText_Solid(font, numberToRender.c_str(), Grey);
                    numberTexture = SDL_CreateTextureFromSurface(renderer, numberMessage);
                    SDL_Rect numberRect;
                    numberRect.x = (60 * j) + 20;
                    numberRect.y = (60 * i) + 10;
                    numberRect.w = 25;
                    numberRect.h = 40;
                    SDL_RenderCopy(renderer, numberTexture, NULL, &numberRect);
                    SDL_FreeSurface(numberMessage);
                    SDL_DestroyTexture(numberTexture);
            }
        }
    }
    
}

void Tool::renderBox() {

    SDL_Rect rect;
    rect.x = mainCharacter->getXLocation() - OFFSET;
    rect.y = mainCharacter->getYLocation() - OFFSET;
    rect.w = RENDER_BOX_SIZE;
    rect.h = RENDER_BOX_SIZE;
    SDL_RenderCopy(renderer, ResourceManager::getInstance().renderBoxTexture, NULL, &rect);

}

void Tool::renderOpponents() {

    for(int i = 0; i < POOL_SIZE; i++) {
        if(opponents[i] != NULL) {
            SDL_Rect rect;
            rect.x = opponents[i]->getXLocation();
            rect.y = opponents[i]->getYLocation();
            rect.w = OPPONENT_SIZE;
            rect.h = OPPONENT_SIZE;
            SDL_RenderCopy(renderer, ResourceManager::getInstance().opponentTexture, NULL, &rect);
        }
    }

}

void Tool::renderGameStats() {

    SDL_Color White = {255, 255, 255};

    std::string numberToRender = std::to_string(score);
    std::string scoreString = "Score:    ";
    scoreString += numberToRender;
    const char *finalString = scoreString.c_str();

    std::string highScoreToRender = std::to_string(highScore);
    std::string highScoreString = "High Score:    ";
    highScoreString += highScoreToRender;
    const char *finalHighString = highScoreString.c_str();

    // High Score
    SDL_Surface *hScoreMessage = TTF_RenderText_Solid(font, finalHighString, White);
    SDL_Texture *hScoreTexture = SDL_CreateTextureFromSurface(renderer, hScoreMessage);
    SDL_Rect hScoreRect;
    hScoreRect.x = 150;
    hScoreRect.y = 10;
    hScoreRect.w = 130;
    hScoreRect.h = 50;

    // Score
    SDL_Surface *scoreMessage = TTF_RenderText_Solid(font, finalString, White);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreMessage);
    SDL_Rect scoreRect;
    scoreRect.x = 20;
    scoreRect.y = 10;
    scoreRect.w = 100;
    scoreRect.h = 50;

    // Render
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_RenderCopy(renderer, hScoreTexture, NULL, &hScoreRect);

}

void Tool::renderEditor() {

    for (int i = 0; i < GAME_OPPONENT_COUNT; i++) {

        SDL_Rect rect;
        rect.x = opponents[i]->getOriginalX();
        rect.y = opponents[i]->getOriginalY();
        rect.w = OPPONENT_SIZE;
        rect.h = OPPONENT_SIZE;
        SDL_RenderCopy(renderer, ResourceManager::getInstance().opponentTexture, NULL, &rect);

    }

    SDL_Color White = {255, 255, 255};
    SDL_Surface *directionMessage = TTF_RenderText_Solid(font, "Click On Any Asteroid and Drag", White);
    SDL_Texture *directionTexture = SDL_CreateTextureFromSurface(renderer, directionMessage);
    SDL_Rect pRect;
    pRect.x = 100;
    pRect.y = 10;
    pRect.w = 400;
    pRect.h = 40;

    SDL_Surface *backMessage = TTF_RenderText_Solid(font, "Press B to Return to Main Menu", White);
    SDL_Texture *backTexture = SDL_CreateTextureFromSurface(renderer, backMessage);
    SDL_Rect bRect;
    bRect.x = 100;
    bRect.y = 550;
    bRect.w = 400;
    bRect.h = 40;

    SDL_RenderCopy(renderer, backTexture, NULL, &bRect);
    SDL_RenderCopy(renderer, directionTexture, NULL, &pRect);


}

bool Tool::checkAsteroidCollision(float oppX, float oppY) {

    if ((mainCharacter->getXLocation() > oppX - OPPONENT_SIZE && mainCharacter->getXLocation()< oppX + OPPONENT_SIZE) &&
        (mainCharacter->getYLocation() > oppY - OPPONENT_SIZE && mainCharacter->getYLocation()< oppY + OPPONENT_SIZE))
    {
        return true;
    }

    return false;

}

int Tool::checkAsteroidClick(int clickX, int clickY) {

    float xF = (float)clickX;
    float yF = (float)clickY;

    for(int i = 0; i < GAME_OPPONENT_COUNT; i++) {
        if ((opponents[i]->getOriginalX() > xF - OPPONENT_SIZE && opponents[i]->getOriginalX()< xF + OPPONENT_SIZE) &&
        (opponents[i]->getOriginalY() > yF - OPPONENT_SIZE && opponents[i]->getOriginalY()< yF + OPPONENT_SIZE))
        {
        return i;
        }
    }

    return -1;


}


