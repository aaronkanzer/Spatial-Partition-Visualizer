#ifndef Tool_h
#define Tool_h
#include <string>
#include "SDL2/SDL.h"
#include "MainCharacter.h"
#include "Opponent.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <time.h>
#define MS_PER_UPDATE 16

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int POOL_SIZE = 100; 
const int NUMBER_OF_COLUMNS = 10;
const int NUMBER_OF_ROWS = 10;

//!  This class represents the tool and all of its states
class Tool
{
  public:
    /* Methods */
    Tool();
    ~Tool();
    //! Initializes the game, creating a window and all other necessary pieces
    void init(const char *title, int xCoord, int yCoord, int width, int height, bool fullScreen);
    //! Handles user input
    /*!
      LeftArrowKey - move character left \n
      RightArrowKey - move character right \n
      UpArrowKey - move character Up \n
      DownArrowKey - move character down \n
      Q - quit out of the game \n
      Click-Down - start to edit a specific asteroid's location\n
      Click-Up - finish editing a specific asteroid's location\n
      B - return to main menu from any screen\n
      D - enter demo mode\n
      E - enter editor mode\n
    */
    void handleEvents();
    //! Updates the game by updating the ball, bricks, and paddle
    void update();
    //! Renders the game by rendering the ball, bricks, and paddle if unpaused or the correct menu while paused
    void render();
    //! Handles cleaning up the game after quitting
    void clean();
    //! Check if the game is running or paused
    bool isRunning;
    //! Check if the tool is in the demo
    bool isSpatialVisual;
    //! Check if the tool is in the editor
    bool isEditor;
    //! Check if the tool is in the main menu
    bool isMainMenu = true;
    //! Check if the tool is in game mode
    bool isGameMode;
    //! Check if the game has acheived a new high score
    bool isHighScore = false;
    //! Renders the grid background
    void renderGrid();
    //! Renders the renderBox
    void renderBox();
    //! Renders the opponents
    void renderOpponents();
    //! Renders the editor mode
    void renderEditor();
    //! Renders the main menu
    void renderMainMenu();
    //! Updates all elements of the game state
    void updateGameState();
    //! Renders the stats associated with the game at its current state
    void renderGameStats();
    //! Renders the game summary after Game Over has occurred
    void renderGameSummary();
    //! Checks if the main character has collided with an asteroid at a given position
    bool checkAsteroidCollision(float oppX, float oppY);
    //! Checks if an astroid has been clicked on in the editor
    int checkAsteroidClick(int clickX, int clickY);
    
    /* Fields */
    //! 2D int array that determines how many objects an in each index
    int gridCount[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];
    //! Object pool of Opponents for the duration of the Tool
    Opponent* opponents[POOL_SIZE];
    //! Determines if the Game Over sound has played after the game ends
    bool hasGOSoundPlayed = false;
    //! Determines if the game is over
    bool isGameOver = false;
    //! Determines if an asteroid's location is being edited
    bool editingAsteroid = false;
    //! The index of the current asteroid being edited -- -1 if no asteroid is being edited
    int currentAsteroid = -1;
    //! Number of frames rendereed
    int framesRendered;
    //! Number of frames rendered per second
    int framesPerSecondInt;
    //! Lag that is needed to maintain 60 fps
    double lag;
    //! Temp variable to assist with FPS Timer
    double previous;
    //! Current score of the game session
    int score = 0;
    //! Current high score of the game session
    int highScore = 0;
    //! Seconds timer to determine score for game
    time_t startTime;
    //! Temp variable to assist with score during game
    double seconds_since_start;

  private:

    void setupLevel();
    void renderGame();
    void renderText();
    void renderEnd();
    void calibrateGrid();

    Mix_Music *backgroundMusic;
    Mix_Chunk *highScoreSound;
    Mix_Chunk *collisionSound;

    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    MainCharacter* mainCharacter;

};

#endif