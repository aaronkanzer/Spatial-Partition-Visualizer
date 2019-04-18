#ifndef Opponent_h
#define Opponent_h
#include "SDL2/SDL.h"
#include "Vector2D.h"
const float OPPONENT_SIZE = 15;

//!  This class represents what would be the opponents or other characters in a game
class Opponent {

    public:
        /* Methods */
        Opponent();
        ~Opponent();
        //! Renders each opponent in a given x-coordinate and y-coordinate location
        void render(SDL_Renderer *renderer, float xLocation, float yLocation);
        //! Updates all information (location, status, etc.) associated wit the opponent
        void update();
        //! Sets the x-coordinate location for the opponent
        void setXLocation(float newX);
        //! Sets the y-coordinate location for the opponent
        void setYLocation(float newY);
        //! Gets the x-coordinate location for the opponent
        float getXLocation();
        //! Gets the y-coordinate location for the opponent
        float getYLocation();
        //! Gets the speed that opponent should move per frame
        float getOpponentSpeed();
        //! Sets the speed that opponent should move per frame
        void setOpponentSpeed(float newSpeed);
        //! Determines if the x-coordinate location could indicate a collision with the main character
        void checkXCollision();
        //! Determines if the y-coordinate location could indicate a collision with the main character
        void checkYCollision();
        //! Determines if the location of the opponent has come in contact with the bounds of the SDL window
        void checkCeilingCollision();
        //! Gets the X-index of the opponent in the 2D-grid dependent on its x-coordinate location
        int getXIndex();
        //! Gets the Y-index of the opponent in the 2D-grid dependent on its y-coordinate location
        int getYIndex();
        //! Sets the X-index of the opponent in the 2D-grid
        void setXIndex(int newIndex);
        //! Sets the Y-index of the opponent in the 2D-grid
        void setYIndex(int newIndex);
        //! Gets the x-coordinate location that the opponent started at
        float getOriginalX();
        //! Gets the y-coordinate location that the opponent started at
        float getOriginalY();
        //! Sets the x-coordinate location that the opponent should start at
        void setOriginalX(float x);
        //! Sets the y-coordinate location that the opponent should start at
        void setOriginalY(float y);

        /* Fields */
        //! Vector2D class associated with the opponent
        Vector2D opponentVector;

    private:

        float xLocationStart;
        float yLocationStart;
        float xLocation;
        float yLocation;
        SDL_Texture *opponentTexture;
        float opponentSpeed;
        Vector2D direction;
        int xIndex;
        int yIndex;

};

#endif