#include "ResourceManager.h"
#include <iostream>
#include <fstream>

ResourceManager &ResourceManager::getInstance()
{
    static ResourceManager *instance = new ResourceManager();
    return *instance;
}

int ResourceManager::startUp()
{
    mainCharacterSurface = IMG_Load("../Assets/images/mainCharacter.png");
    SDL_Log("Main Character loaded");

    gridSurface = IMG_Load("../Assets/images/grid.png");
    SDL_Log("Grid PNG loaded");

    renderBoxSurface = IMG_Load("../Assets/images/renderBox.png");
    SDL_Log("Render Box PNG loaded");

    opponentSurface = IMG_Load("../Assets/images/genericObject.png");
    SDL_Log("Opponent Object PNG loaded");

    hubbleSurface = IMG_Load("../Assets/images/hubblePhoto.png");
    SDL_Log("Hubble Photo PNG loaded");

    font = TTF_OpenFont("../Assets/fonts/sp-font.ttf", 12);
    SDL_Log("Font loaded");

    backgroundMusic = Mix_LoadMUS("../Assets/sfx/backgroundMusicMain.mp3");
    SDL_Log("Music loaded");

    return 1;
}

int ResourceManager::shutDown()
{

    SDL_Log("Resource Manager has initialized shut down");

    SDL_FreeSurface(mainCharacterSurface);
    mainCharacterSurface = NULL;
    SDL_DestroyTexture(mainCharacterTexture);

    SDL_FreeSurface(gridSurface);
    gridSurface = NULL;
    SDL_DestroyTexture(gridTexture);

    SDL_FreeSurface(renderBoxSurface);
    renderBoxSurface = NULL;
    SDL_DestroyTexture(renderBoxTexture);

    SDL_FreeSurface(hubbleSurface);
    renderBoxSurface = NULL;
    SDL_DestroyTexture(hubbleTexture);

    SDL_FreeSurface(opponentSurface);
    renderBoxSurface = NULL;
    SDL_DestroyTexture(opponentTexture);

    TTF_CloseFont(font);
    Mix_FreeMusic(backgroundMusic);

    SDL_Log("Resource Manager has completed shut down");

    return 1;
    
}

void ResourceManager::createTextures(SDL_Renderer *ren)
{
    mainCharacterTexture = SDL_CreateTextureFromSurface(ren, mainCharacterSurface);
    gridTexture = SDL_CreateTextureFromSurface(ren, gridSurface);
    renderBoxTexture = SDL_CreateTextureFromSurface(ren, renderBoxSurface);
    opponentTexture = SDL_CreateTextureFromSurface(ren, opponentSurface);
    hubbleTexture = SDL_CreateTextureFromSurface(ren, hubbleSurface);
    SDL_Log("Textures created from surfaces");
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}
