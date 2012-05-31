//Include the SDL functions and datatypes
#include "SDL.h"
#include "SDL_image.h"
#include <string>

//Attributes for the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Surfaces to be used in the program
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

SDL_Surface *load_image( std::string filename )
{
	//Temporary storage for the string that will be loaded
	SDL_Surface *loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface *optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load( filename.c_str() );

	//If nothing went wrong
	if( loadedImage != NULL )
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );

		//Free the old surface
		SDL_FreeSurface( loadedImage );
	}

	//Return the optimized image
	return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	//Make a temporary rectancle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface( source, NULL, destination, &offset );
}


int main( int argc, char* args[] )
{

	//Initialize all SDL subsystems
    if( SDL_Init ( SDL_INIT_EVERYTHING ) == -1 )
	{
		return 1;
	}

	//Set up the screen
	screen = SDL_SetVideoMode ( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was an error in setting up the screen
	if( screen==NULL )
	{
		return 1;
	}

	//Set window caption
	SDL_WM_SetCaption( "Different image formats!", NULL );

	//Load images
	message = load_image( "look.png" );


	//Apply the message to the screen
	apply_surface( 0, 0, message, screen );

	//Update screen
	if( SDL_Flip ( screen ) == -1 )
	{
		return 1;
	}

	//Wait 2 seconds
	SDL_Delay ( 2000 );

	//Free the surfaces
	SDL_FreeSurface ( message );

    //Quit SDL
    SDL_Quit();
    
    return 0;    
}