#include "main_menu.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>

/**
* Performs desired functionality for a Main Menu Button, Mouse Left Click Event
* @param button The button that triggered the event
*/
void ButtonEvent_MouseClick_Left( UIButton &Button );

/**
* Performs desired functionality for a Main Menu Button, Mouse Move Event
* @param button The button that triggered the event
*/
void ButtonEvent_MouseMotion( UIButton &Button );

/**
* Creates the Main Menu Buttons
* @param x The x to draw relative to
* @param y The y to draw relative to
*/
void CreateButtons( int &x, int &y, int &yspacing );

/**
* Creates the Container to hold the Buttons
* @param x The x to draw relative to
* @param y The y to draw relative to
*/
void CreateContainer( int &x, int &y, int &yspacing );

/**
* Finds a Button that triggered an event, by searching Buttons close to the Mouse Cursor
* @param mpos The position of the mouse when a Button Event was triggered
* @param imin The lower bounds of the button index to check
* @param imax The upper bounds of the button index to check
* @return button* A Pointer to the found Button
*/
UIButton* FindButton( std::vector<int> mpos, 
				      int imin, int imax );

/**
* Checks if a Vector is within the Vertices of Quad
* @param vec The vector to check is within the vertices
* @param vtcs The vertices to check vector is within
* @return True or False if the vector is within the vertices
*/
bool VectorInQuad( std::vector<int> vec, 
				   std::vector< std::vector<int> > vtcs );

/**
* Calculates the vector of a Quads' vertex
* @param x The X position to calc from
* @param y The Y position to calc from
* @param w The W to calc from X;
* @param h The H to calc from Y;
* @param vtxnum The number of vertices of the poly (Max 4)
* @return The resulting vertex Vector position to draw at
*/
std::vector<int> CalculateQuadVertex( const int &x, const int &y, 
									  const int &w, const int &h, 
									  const int &vtxnum );

/** The MainMenu and all it's elements and properties */
struct MainMenu {
	Polygon Container;
    std::map< std::string, UIButton > Buttons;
    UIButton* LastButton;
} MainMenu;

/** Creates MainMenu objects, Buttons, etc */
void MainMenu_Init()
{	
	int x = 110; 
	int y = 85;
	int yspacing = 15;

	CreateButtons(x, y, yspacing);
	CreateContainer(x, y, yspacing);

	MainMenu.LastButton = nullptr;
}

/** Draws the MainMenu and all its elements to the screen */
void MainMenu_Draw()
{
	// ///////////////////////////////////////////////////
	MainMenu.Container.renderer = renderer;
	MainMenu.Container.Colors.Line.r = 168;
	MainMenu.Container.Colors.Line.g = 168;
	MainMenu.Container.Colors.Line.b = 168;
	MainMenu.Container.Colors.Line.a = 255;
	MainMenu.Container.Draw();
	// ///////////////////////////////////////////////////

	std::map< std::string, UIButton >::iterator i;

	for (i = MainMenu.Buttons.begin(); i != MainMenu.Buttons.end(); i++)
	{
		UIButton &Button = i->second;

		if (Button.State.Hover)
			Button.Draw_Hover();

		else if (Button.State.Pushed)
			Button.Draw_Pushed();

		else
			Button.Draw();
	}
}

/** Handles all events that occur on a MainMenu Button */
void MainMenu_ButtonEventHandler_Mouse( const int &mx, 
									    const int &my, 
									    const MouseEvent &event )
{
    std::vector<int> vec(2);
	
    vec[0] = mx;
    vec[1] = my;
    
	if (MainMenu.LastButton != nullptr)
		(*MainMenu.LastButton).State.Hover = false;

    if (!VectorInQuad(vec, MainMenu.Container.vertices))
		return;
	
	UIButton *btnptr 
		= FindButton( vec, 0, (MainMenu.Buttons.size() - 1) );
	
	if (btnptr == nullptr) 
		return;
	
	UIButton &Button 
		= *btnptr;

	switch (event) 
	{
		case MOUSE_CLICK_LEFT:
			ButtonEvent_MouseClick_Left( Button );
			break;
			
		case MOUSE_MOTION:
			ButtonEvent_MouseMotion( Button );
			break;

		default:
			break;
	}
}

/** Performs desired functionality for a Main Menu Button, Mouse Left Click Event */
void ButtonEvent_MouseClick_Left( UIButton &Button )
{	
	if (Button.State.Pushed == false)
		Button.State.Pushed = true;
	else
		Button.State.Pushed = false;
}

/** Performs desired functionality for a Main Menu Button, Mouse Move Event */
void ButtonEvent_MouseMotion( UIButton &Button )
{
	UIButton *&LastButton = MainMenu.LastButton;
	
	if (LastButton)
		(*LastButton).State.Hover = false;

	Button.State.Hover = true;

	LastButton = &Button;
}

/** Creates the Buttons for the MainMenu */
void CreateButtons( int &x, int &y, int &yspacing )
{	
	UIButton Button;
	std::vector<int> vtx(2);
	
	Button.x = x;
	Button.y = y;
	Button.w = 235;
	Button.h = 43;

	Button.State.Hover = false;
	Button.State.Pushed = false;
	
	Button.renderer = renderer;

	SDL_Color &Normal = Button.Colors.Normal;
	Normal.r = 255; Normal.g = 255; 
	Normal.b = 255; Normal.a = 255;

	SDL_Color &Pushed = Button.Colors.Pushed;
	Pushed.r = 0; Pushed.g = 255; 
	Pushed.b = 0; Pushed.a = 255;

	SDL_Color &Hover = Button.Colors.Hover;
	Hover.r = 0; Hover.g = 0; 
	Hover.b = 255; Hover.a = 255;

	for (int i = 0; i <= 9; i++)
	{
		Button.vertices.clear();

		for (int vc = 1; vc <= 4; vc++)
		{
			vtx = CalculateQuadVertex( Button.x, Button.y,
			                           Button.w, Button.h, 
									   vc );

			Button.vertices.push_back( vtx );
		}

		Button.actorVertices = Button.vertices;
		
		MainMenu.Buttons[ "BTN_ID_" + std::to_string(i) ] = Button;
		
		Button.y += (Button.h + yspacing);
	}
}

/** Creates the Container for the MainMenu elements */
void CreateContainer( int &x, int &y, int &yspacing )
{	
	std::map< std::string, UIButton >::iterator &i = MainMenu.Buttons.begin();

	UIButton &Button = i->second;

	const int &w = Button.w;
	const int &h = ( (MainMenu.Buttons.size() * 
		             (Button.h + yspacing)) - yspacing );
	
	std::vector<int> vtx(2);

	for (int vc = 1; vc <= 4; vc++)
	{
		vtx = CalculateQuadVertex( x, y, w, h, vc );

		MainMenu.Container.vertices.push_back( vtx );
	}
}

/**
* FindButton (Binary Search Implementation)
* Used to search for which actor the mouse position belongs to
* accepts mouse position vector, integer start to look vector index, integer end look vector index
* returns button pointer found button, nullptr if none is found
*/
UIButton* FindButton( std::vector<int> mpos, 
				      int imin, int imax )
{
	if (imax < imin) 
		return nullptr;
	
	int btnindex 
		= (imin + ((imax - imin) / 2));

	UIButton *btnptr 
		= &MainMenu.Buttons[ "BTN_ID_" + std::to_string( btnindex ) ];

	std::vector<int> &vtx 
		= (*btnptr).actorVertices[0];

	if (vtx[1] > mpos[1])
		return FindButton( mpos, imin, (btnindex - 1) );

	else if (vtx[1] < mpos[1])
	{
		if (VectorInQuad(mpos, (*btnptr).actorVertices ))
			return btnptr;

		return FindButton( mpos, (btnindex + 1), imax );
	}
		
	return btnptr;
}

/**
* VectorInQuad
* Accepts mouse position vector and button actor vertices
* return true if mouse is in actor false otherwise
*/
bool VectorInQuad( std::vector<int> vec, 
				   std::vector< std::vector<int> > vtcs )
{
	bool vtxX;
	bool vtxY;
	int vtxpc = 0;
	
	std::vector< std::vector<int> >::iterator i;
	std::vector<int> vtx(2);
	
	for (i = vtcs.begin(); i != vtcs.end(); i++)
	{
		vtx = *i;
		
		vtxX = false;
		vtxY = false;

		vec[0] = std::abs( vec[0] );
		vec[1] = std::abs( vec[1] );
			
		if (vtx[0] < 0) 
			vec[0] = -1 * vec[0];
			
		if (vtx[1] < 0) 
			vec[1] = -1 * vec[1];
			
		// test X
		if (vec[0] >= vtx[0])
			vtxX = true;

		// test Y
		if (vec[1] >= vtx[1]) 
			vtxY = true;

		if (vtxX && vtxY)
			vtxpc++;
		else
			return false;
	}

	if (vtxpc == vtcs.size())
		return true;

	return false;
}

/**
* calculates all vertices in box polygon
* accepts integer coordinates of first vextex(x,y), integer width, integer height, integer vertice number
* returns int vect for each vertice of actor
*/
std::vector<int> CalculateQuadVertex( const int &x, const int &y, 
									  const int &w, const int &h, 
									  const int &vtxnum )
{
	std::vector<int> vtx(2);
	
	switch (vtxnum)
	{
		case 1:
			vtx[0] = x;
			vtx[1] = y;
			break;

		case 2:
			vtx[0] = -(x + w);
			vtx[1] = y;
			break;

		case 3:
			vtx[0] = -(x + w);
			vtx[1] = -(y + h);
			break;
		
		case 4:
			vtx[0] = x;
			vtx[1] = -(y + h);
			break;

		default:
			break;
	}
	
	return vtx;
}


