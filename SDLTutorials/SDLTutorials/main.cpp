//Include the SDL functions and datatypes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>

//Attributes for the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Surfaces to be used in the program
SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

//The event structure that will be used
SDL_Event sevent;

//The font that's going to be used
TTF_Font *font = NULL;

//The colour of the font
SDL_Color textColour = {225, 225, 225 };

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

	//If the image was optimized with no problems
	if( optimizedImage != NULL )
	{
		//Map the colour key
		Uint32 colourkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );

		//Set all pixels of that colour to be transparent
		SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colourkey );
	}

	//Return the optimized image
	return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	//Make a temporary rectancle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
	//Initializes all SDL subsystems
	if( SDL_Init ( SDL_INIT_EVERYTHING ) == -1 )
	{
		return false;
	}

	//Set up the screen
	screen = SDL_SetVideoMode ( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was an error in setting up the screen
	if( screen==NULL )
	{
		return false;
	}

	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		return false;
	}

	//Set window caption
	SDL_WM_SetCaption( "TTF test", NULL );

	//If everything initialized fine
	return true;
}

bool load_files()
{
	//Load the images
	background = load_image( "background.png" );

	//Open the font
	font = TTF_OpenFont( "lazy.ttf", 28 );

	//If there was an error loading the files
	if( background == NULL )
	{
		return false;
	}

	//If there was an error loading the files
	if( font == NULL )
	{
		return false;
	}

	//If everything loaded fine
	return true;
}

void clean_up()
{
	//Free the image
	SDL_FreeSurface( background );
	SDL_FreeSurface( message );

	//Close the font that was used
	TTF_CloseFont(font);

	//Quit TTF
	TTF_Quit();

	//Quit SDL
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Make sure the program waits for a quit
	bool quit = false;

	//Initialize
	if( init() == false )
	{
		return 1;
	}

	//Load the files
	if( load_files() == false )
	{
		return 2;
	}

	//Render the text
	message = TTF_RenderText_Solid( font, "The quick brown fox jumps over the lazy dog", textColour );

	//If there was an error in rendering the text
	if( message == NULL )
	{
		return 1;
	}

	//Apply the images to the screen
	apply_surface( 0, 0, background, screen);
	apply_surface( 0, 150, message, screen);

	//Update screen
	if( SDL_Flip ( screen ) == -1 )
	{
		return 3;
	}

	//While the user hasn't quit
	while( quit == false )
	{
		//While there's an event to handle
		while( SDL_PollEvent( &sevent ) )
		{
			//If the user has Xed out the window
			if( sevent.type == SDL_QUIT )
			{
				//Quit the program
				quit = true;
			}
		}
	}

	//Free the surface and quit SDL
	clean_up();

	return 0;
}