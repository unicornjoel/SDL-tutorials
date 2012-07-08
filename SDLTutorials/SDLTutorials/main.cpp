//Include the SDL functions and datatypes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>

//Attributes for the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The button states in the sprite sheet
const int CLIP_MOUSEOVER = 0;
const int CLIP_MOUSEOUT = 1;
const int CLIP_MOUSEDOWN = 2;
const int CLIP_MOUSEUP = 3;

//The surfaces
SDL_Surface *buttonSheet = NULL;
SDL_Surface *screen = NULL;

//The rectangle that stores the clipping information
SDL_Rect clips[4];

//the Button class
//The event structure that will be used
SDL_Event sevent;

//The font that's going to be used
TTF_Font *font = NULL;

//The colour of the font
SDL_Color textColour = {225, 225, 225 };

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
class Button
{
private:
	//The attributes of the button
	SDL_Rect box;

	//The part of the button sprite sheet that will be shown
	SDL_Rect* clip;

public:
	//Initialize the variables
	Button( int x, int y, int w, int h);

	//Handles events and set the button's sprite region
	void handle_events();

	//Shows the button on screen
	void show();
};
void set_clips()
{
	//Clip the sprite sheet
	clips[ CLIP_MOUSEOVER ].x = 0;
	clips[ CLIP_MOUSEOVER ].y = 0;
	clips[ CLIP_MOUSEOVER ].w = 320;
	clips[ CLIP_MOUSEOVER ].h = 240;

	clips[ CLIP_MOUSEOUT ].x = 320;
	clips[ CLIP_MOUSEOUT ].y = 0;
	clips[ CLIP_MOUSEOUT ].w = 320;
	clips[ CLIP_MOUSEOUT ].h = 240;

	clips[ CLIP_MOUSEDOWN ].x = 0;
	clips[ CLIP_MOUSEDOWN ].y = 240;
	clips[ CLIP_MOUSEDOWN ].w = 320;
	clips[ CLIP_MOUSEDOWN ].h = 240;

	clips[ CLIP_MOUSEUP ].x = 320;
	clips[ CLIP_MOUSEUP ].y = 240;
	clips[ CLIP_MOUSEUP ].w = 320;
	clips[ CLIP_MOUSEUP ].h = 240;
}
Button::Button(int x, int y, int w, int h)
{
	//Set the button's attributes
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;

	//Set the default sprite
	clip = &clips[ CLIP_MOUSEOUT ];
}
void Button::handle_events()
{
	//The mouse offsets
	int x = 0;
	int y = 0;

	//If the mouse moved
	if (sevent.type == SDL_MOUSEMOTION)
	{
		//Get the mouse offsets
		x = sevent.motion.x;
		y = sevent.motion.y;

		//If the mouse is over the button
		if( ( x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h) )
		{
			//Set the button sprite
			clip = &clips[ CLIP_MOUSEOVER ];
		}
		else
		{
			//Set the button sprite
			clip = &clips[ CLIP_MOUSEOUT ];
		}
	}
	//If a mouse button was pressed
	if(sevent.type == SDL_MOUSEBUTTONDOWN )
	{
		//If the mouse left button was pressed
		if(sevent.button.button == SDL_BUTTON_LEFT)
		{
			//Get the mouse offsets
			x=sevent.button.x;
			y=sevent.button.y;

			//If the mouse is over the button
			if( ( x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h) )
			{
				//Set the button sprite
				clip = &clips[ CLIP_MOUSEDOWN ];
			}
		}
	}
	//If a mouse button was released
	if(sevent.type == SDL_MOUSEBUTTONUP)
	{
		//If the mouse left button was released
		if(sevent.button.button == SDL_BUTTON_LEFT)
		{
			//Get the mouse offsets
			x=sevent.button.x;
			y=sevent.button.y;

			//If the mouse is over the button
			if( ( x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h) )
			{
				//Set the button sprite
				clip = &clips[ CLIP_MOUSEUP ];
			}
		}
	}
}
void Button::show()
{
	//Show the button
	apply_surface(box.x, box.y, buttonSheet, screen, clip);
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
	buttonSheet = load_image( "button.png" );

	//If there was an error loading the files
	if( buttonSheet == NULL )
	{
		return false;
	}

	//If everything loaded fine
	return true;
}
void clean_up()
{
	//Free the image
	SDL_FreeSurface( buttonSheet );

	//Quit SDL
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Clip the sprite sheet
	set_clips();

	//Make the button
	Button myButton(170, 120, 320, 240);

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

	//Update screen
	if( SDL_Flip ( screen ) == -1 )
	{
		return 3;
	}

	//While the user hasn't quit
	while( quit == false )
	{
		//While there's an event to handle
		if( SDL_PollEvent( &sevent ) )
		{
			//Handle button events
			myButton.handle_events();

			//If the user has Xed out the window
			if( sevent.type == SDL_QUIT )
			{
				//Quit the program
				quit = true;
			}
		}
		
		//Fill the screen white
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF) );

		//Show the button
		myButton.show();

		if( SDL_Flip ( screen ) == -1 )
		{
			return 4;
		}
	}

	//Free the surface and quit SDL
	clean_up();

	return 0;
}