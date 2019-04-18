#ifndef MainCharacter_h
#define MainCharacter_h
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_ttf.h>
#else // This works for Mac
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
    #include <SDL.h>
#endif
#include "ResourceManager.h"
#define CHARACTER_WIDTH 15
#define CHARACTER_HEIGHT 15

//!  This class represents what would be the main focal point in a game -- e.g. the main character
class MainCharacter {

    public:
        /* Methods */
        MainCharacter();
        ~MainCharacter();
        //! Renders the main character in the scene with a given x-coordinate and y-coordinate
        void render(SDL_Renderer *renderer, float xLocation, float yLocation);
        //! Renders the main character with a surrounding box meant to visualize immediate range of sight
        void renderWithBox(SDL_Renderer *renderer, float xLocation, float yLocation);
        //! Update information within the main character for each frame
        void update();
        //! Sets the x-coordinate location for the main character
        void setXLocation(float newX);
        //! Sets the y-coordinate location for the main character
        void setYLocation(float newY);
        //! Gets the x-coordinate location for the main character
        float getXLocation();
        //! Gets the y-coordinate location for the main character
        float getYLocation();
        //! Gets the x-coordinate index in the 2D Grid for the main character
        int getXIndex();
        //! Gets the y-coordinate index in the 2D Grid for the main character
        int getYIndex();
        //! Sets the x-coordinate index in the 2D Grid for the main character
        void setXIndex(int newIndex);
        //! Sets the y-coordinate index in the 2D Grid for the main character
        void setYIndex(int newIndex);
        //! Resets the location of the main character to the original starting position
        void reset();

    private:

        float xLocation;
        float yLocation;
        int xIndex;
        int yIndex;
        SDL_Texture *mainCharacterTexture;
        float mainCharacterSpeed;

};

#endif
