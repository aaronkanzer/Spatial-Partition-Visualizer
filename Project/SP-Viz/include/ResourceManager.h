#ifndef ResourceManager_h
#define ResourceManager_h

#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <map>
#include <iterator>
#include <string>

//!  This class stores all resources that must be loaded and holds them for other classes to use
class ResourceManager
{
  public:
    /* Methods */
    //! This gets the instance of the ResourceManager or creates it if it doesn't exist, there can only be one ResourceManager instance
    static ResourceManager &getInstance(); // 'equivalent' to our constructor
    //! This sets up the basic resources the tool needs to run
    int startUp(); // 'equivalent' to our destructor
    //! This cleans up the resources loaded by the ResourceManager after the tool has been quit out of
    int shutDown(); // ... // Perhaps other public functions..
    //! This creates textures from loaded surfaces, this is separate so the tool can pass its renderer
    void createTextures(SDL_Renderer *ren);

    /* Fields */
    //! The image used for the mainCharacter
    SDL_Surface *mainCharacterSurface;
    //! This is the texture created from mainCharacter after given the tool's renderer
    SDL_Texture *mainCharacterTexture;
    //! The image used for the Grid
    SDL_Surface *gridSurface;
    //! This is the texture created from grid after given the tool's renderer
    SDL_Texture *gridTexture;
    //! This is the image used for the renderBox
    SDL_Surface *renderBoxSurface;
    //! This is the texture created from renderBox after given the tool's renderer
    SDL_Texture *renderBoxTexture;
    //! This is the image used for the hubble image
    SDL_Surface *hubbleSurface;
    //! This is the texture created from hubble after given the tool's renderer
    SDL_Texture *hubbleTexture;
    //! This is the image used for the opponent object image
    SDL_Surface *opponentSurface;
    //! This is the texture created from opponent object after given the tool's renderer
    SDL_Texture *opponentTexture;
    //! The font used for all text in the tool
    TTF_Font *font;
    //! The music played during the tool
    Mix_Music *backgroundMusic;

  private:
    ResourceManager();                        // Private Singleton
    ~ResourceManager();                       // Deconstructor
    ResourceManager(ResourceManager const &); // Avoid copy constructor
    void operator=(ResourceManager const &);  // Don't allow assignment.
    
};

#endif
