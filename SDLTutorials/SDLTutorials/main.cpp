//Include the SDL functions and datatypes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>

//Attributes for the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The event structure that is going to be used
SDL_Event sevent;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;

TTF_Font *font = NULL;

//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be played
Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;

SDL_Color textColour = { 0, 0, 0 };

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
bool init()
{
	//Initializes all SDL subsystems
	if( SDL_Init ( SDL_INIT_EVERYTHING ) == -1 )
	{
		return false;
	}

	//Initialize SDL_TTF
	if( TTF_Init() == -1 )
	{
		return false;
	}

	//Initialize SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1 )
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

	//Set window caption
	SDL_WM_SetCaption( "Monitor Music", NULL );

	//If everything initialized fine
	return true;
}
bool load_files()
{
	//Load the images
	background = load_image( "background.png" );

	//Load the font
	font = TTF_OpenFont("lazy.ttf", 30);

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

	//Load the music
	music = Mix_LoadMUS("beat.wav");

	//If there was a problem loading the music
	if( music == NULL)
	{
	return false;
	}

	//Load the sound effects
	scratch = Mix_LoadWAV( "scratch.wav" );
	high = Mix_LoadWAV( "high.wav" );
	med = Mix_LoadWAV( "medium.wav" );
	low = Mix_LoadWAV( "low.wav" );

	if( ( scratch == NULL ) || ( high == NULL ) || ( med == NULL ) || ( low == NULL ) )
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

	//Free the sound effects
	Mix_FreeChunk( scratch );
	Mix_FreeChunk( high );
	Mix_FreeChunk( med );
	Mix_FreeChunk( low );

	//Free the music
	Mix_FreeMusic( music );

	//Quit SDL_mixer
	Mix_CloseAudio();

	//Close the font
	TTF_CloseFont( font );

	//Quit SDL_ttf
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


    //Apply the background
    apply_surface( 0, 0, background, screen );

    //Render the text
    message = TTF_RenderText_Solid( font, "Press 1, 2, 3, or 4 to play a sound effect\nPress 9 to play or pause the music\nPress 0 to stop the music", textColour );

    //If there was an error in rendering the text
    if( message == NULL )
    {
        return 1;
    }

    //Show the message on the screen
    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 100, message, screen );

    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
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

			//If a key was pressed
			if( sevent.type == SDL_KEYDOWN )
			{
				//If 1 was pressed
				if( sevent.key.keysym.sym == SDLK_1 )
				{
					//Play the scratch effect
					if( Mix_PlayChannel(-1,scratch,0) == -1)
					{
						return 1;
					}
				}
				else if( sevent.key.keysym.sym == SDLK_2 )
				{
					//Play the scratch effect
					if( Mix_PlayChannel(-1,high,0) == -1)
					{
						return 1;
					}
				}
				else if( sevent.key.keysym.sym == SDLK_3 )
				{
					//Play the scratch effect
					if( Mix_PlayChannel(-1,med,0) == -1)
					{
						return 1;
					}
				}
				else if( sevent.key.keysym.sym == SDLK_4 )
				{
					//Play the scratch effect
					if( Mix_PlayChannel(-1,low,0) == -1)
					{
						return 1;
					}
				}
				else if( sevent.key.keysym.sym == SDLK_9 )
				{
					//Play the scratch effect
					if( Mix_PlayingMusic() == 0)
					{
						//Play the music
						if( Mix_PlayMusic( music, -1 ) == -1)
						{
							return 1;
						}
					}
					else
					{
						//If the music is paused
						if( Mix_PausedMusic() == 1 )
						{
							//Resume music
							Mix_ResumeMusic();
						}
						//If the music is playing
						else
						{
							Mix_PauseMusic();
						}
					}
				}
				//If 0 was pressed
				else if( sevent.key.keysym.sym == SDLK_0 )
				{
					//Stop the music
					Mix_HaltMusic();
				}
			}
		}
	}

	//Free the surface and quit SDL
	clean_up();

	return 0;
}