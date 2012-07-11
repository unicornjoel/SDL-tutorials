//Include the SDL functions and datatypes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
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
SDL_Surface *keyboard = NULL;

SDL_Rect keyclips[41];

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int Q = 4;
const int W = 5;
const int E = 6;
const int R = 7;
const int T = 8;
const int Y = 9;
const int U = 10;
const int I = 11;
const int O = 12;
const int P = 13;
const int LBRACE = 14;
const int RBRACE = 15;
const int HACK = 16;
const int A = 17;
const int S = 18;
const int D = 19;
const int F = 20;
const int G = 21;
const int H = 22;
const int J = 23;
const int K = 24;
const int L = 25;
const int COLON = 26;
const int QUOTE = 27;
const int RETURN = 28;
const int Z = 29;
const int X = 30;
const int C = 31;
const int V = 32;
const int B = 33;
const int N = 34;
const int M = 35;
const int COMMA = 36;
const int PERIOD = 37;
const int QMARK = 38;
const int RSHIFT = 39;
const int SPACE = 40;

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

	//Set up the screen
	screen = SDL_SetVideoMode ( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was an error in setting up the screen
	if( screen==NULL )
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
	keyboard = load_image( "keyboard.png" );

	//If there was an error loading the files
	if( background == NULL )
	{
		return false;
	}

	//If there was an error loading the files
	if( keyboard == NULL )
	{
		return false;
	}

	//Set the keyboard clips up
	SDL_Rect temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 168;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	temprect.w = 10;
	temprect.h = 10;
	keyclips[UP] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 168;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 58;
	keyclips[DOWN] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 157;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 58;
	keyclips[LEFT] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 181;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 58;
	keyclips[RIGHT] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 30;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[Q] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 41;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[W] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 52;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[E] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 63;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[R] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 74;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[T] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 85;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[Y] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 96;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[U] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 107;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[I] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 118;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[O] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 129;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[P] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 140;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[LBRACE] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 151;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 25;
	keyclips[RBRACE] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 33;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	keyclips[A] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 44;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	keyclips[S] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 55;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	keyclips[D] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 66;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	keyclips[F] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 77;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	keyclips[G] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 88;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	keyclips[H] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 99;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	keyclips[J] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 110;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	keyclips[K] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 121;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	keyclips[L] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 132;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	keyclips[COLON] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 143;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	keyclips[QUOTE] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 154;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 36;
	temprect.w = 24;
	keyclips[RETURN] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 36;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	temprect.w = 10;
	keyclips[Z] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 47;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	keyclips[X] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 58;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	keyclips[C] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 69;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	keyclips[V] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 80;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	keyclips[B] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 91;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	keyclips[N] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 102;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	keyclips[M] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 113;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	keyclips[COMMA] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 124;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	keyclips[PERIOD] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 135;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	keyclips[QMARK] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 146;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 47;
	temprect.w = 21;
	keyclips[RSHIFT] = temprect;
	temprect.x = (SCREEN_WIDTH - keyboard->w)/2 + 58;
	temprect.y = (SCREEN_HEIGHT - keyboard->h)/2 + 58;
	temprect.w = 54;
	keyclips[SPACE] = temprect;

	//If everything loaded fine
	return true;
}
void clean_up()
{
	//Free the image
	SDL_FreeSurface( background );
	SDL_FreeSurface( keyboard );

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
		
		//Get the keystates
		Uint8 *keystates = SDL_GetKeyState(NULL);

		//Fix the background
		apply_surface(0,0,background,screen);

		//If up is pressed
		if( keystates[ SDLK_UP ])
		{
			SDL_FillRect(screen, &keyclips[UP], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}

		//If down is pressed
		if( keystates[ SDLK_DOWN ])
		{
			SDL_FillRect(screen, &keyclips[DOWN], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}

		//If right is pressed
		if( keystates[ SDLK_RIGHT ])
		{
			SDL_FillRect(screen, &keyclips[RIGHT], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}

		//If left is pressed
		if( keystates[ SDLK_LEFT ])
		{
			SDL_FillRect(screen, &keyclips[LEFT], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}

		//If other keys are pressed
		if( keystates[ SDLK_q ])
		{
			SDL_FillRect(screen, &keyclips[Q], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_w ])
		{
			SDL_FillRect(screen, &keyclips[W], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_e ])
		{
			SDL_FillRect(screen, &keyclips[E], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_r ])
		{
			SDL_FillRect(screen, &keyclips[R], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_t ])
		{
			SDL_FillRect(screen, &keyclips[T], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_y ])
		{
			SDL_FillRect(screen, &keyclips[Y], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_u ])
		{
			SDL_FillRect(screen, &keyclips[U], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_i ])
		{
			SDL_FillRect(screen, &keyclips[I], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_o ])
		{
			SDL_FillRect(screen, &keyclips[O], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_p ])
		{
			SDL_FillRect(screen, &keyclips[P], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_LEFTBRACKET ])
		{
			SDL_FillRect(screen, &keyclips[LBRACE], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_RIGHTBRACKET ])
		{
			SDL_FillRect(screen, &keyclips[RBRACE], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_BACKSLASH ])
		{
			SDL_FillRect(screen, &keyclips[HACK], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_a ])
		{
			SDL_FillRect(screen, &keyclips[A], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_s ])
		{
			SDL_FillRect(screen, &keyclips[S], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_d ])
		{
			SDL_FillRect(screen, &keyclips[D], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_f ])
		{
			SDL_FillRect(screen, &keyclips[F], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_g ])
		{
			SDL_FillRect(screen, &keyclips[G], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_h ])
		{
			SDL_FillRect(screen, &keyclips[H], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_j ])
		{
			SDL_FillRect(screen, &keyclips[J], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_k ])
		{
			SDL_FillRect(screen, &keyclips[K], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_l ])
		{
			SDL_FillRect(screen, &keyclips[L], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_SEMICOLON ])
		{
			SDL_FillRect(screen, &keyclips[COLON], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_QUOTE ])
		{
			SDL_FillRect(screen, &keyclips[QUOTE], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_RETURN ])
		{
			SDL_FillRect(screen, &keyclips[RETURN], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_z ])
		{
			SDL_FillRect(screen, &keyclips[Z], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_x ])
		{
			SDL_FillRect(screen, &keyclips[X], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_c ])
		{
			SDL_FillRect(screen, &keyclips[C], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_v ])
		{
			SDL_FillRect(screen, &keyclips[V], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_b ])
		{
			SDL_FillRect(screen, &keyclips[B], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_n ])
		{
			SDL_FillRect(screen, &keyclips[N], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_m ])
		{
			SDL_FillRect(screen, &keyclips[M], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_COMMA ])
		{
			SDL_FillRect(screen, &keyclips[COMMA], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_PERIOD ])
		{
			SDL_FillRect(screen, &keyclips[PERIOD], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_SLASH ])
		{
			SDL_FillRect(screen, &keyclips[QMARK], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_RSHIFT ])
		{
			SDL_FillRect(screen, &keyclips[RSHIFT], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}
		if( keystates[ SDLK_SPACE ])
		{
			SDL_FillRect(screen, &keyclips[SPACE], SDL_MapRGB( screen->format, 0, 0xA0, 0xFF));
		}

		//Apply the keyboard
		apply_surface((SCREEN_WIDTH - keyboard->w)/2, (SCREEN_HEIGHT - keyboard->h)/2, keyboard, screen);

		if( SDL_Flip ( screen ) == -1 )
		{
			return 3;
		}
	}

	//Free the surface and quit SDL
	clean_up();

	return 0;
}