#include "main_menu.h"

/**
* MainMenu
* This is where the actual MainMenu elements and properties are stored
*/
struct MainMenu {
	Polygon Container;
    std::map< std::string, UIButton > Buttons;
    UIButton* LastButton;
} MainMenu;

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

	UIButton* btnptr 
		= &MainMenu.Buttons[ "BTN_ID_" + std::to_string( btnindex ) ];

	std::vector<int>& vtx 
		= (*btnptr).actorVertices[0];

	if (vtx[1] > mpos[1])
		return FindButton( mpos, imin, 
		                         (btnindex - 1) );

	else if (vtx[1] < mpos[1])
	{
		if (VectorInQuad(mpos, (*btnptr).actorVertices ))
			return btnptr;

		return FindButton( mpos, (btnindex + 1), imax );
	}
		
	return btnptr;
}

/**
* 
* Mouseclick on button state change
* accepts string with button key in map
*/
void ButtonEvent_MouseClick_Left( UIButton& Button )
{	
	if (Button.State.Pushed == false)
		Button.State.Pushed = true;
	else
		Button.State.Pushed = false;
}

/**
* Mouse motion on button state change
* accepts string with button key in map
*/
void ButtonEvent_MouseMotion( UIButton& Button )
{
	UIButton*& LastButton = MainMenu.LastButton;
	
	if (LastButton)
		(*LastButton).State.Hover = false;

	Button.State.Hover = true;

	LastButton = &Button;
}

/**
* handles mouse events on
* accepts mouse position and event to handle
*/
int MainMenu_ButtonEventHandler_Mouse( const int& mx, 
									   const int& my, 
									   const MouseEvent& event )
{
    std::vector<int> vec(2);
	
    vec[0] = mx;
    vec[1] = my;
    
	if (MainMenu.LastButton != nullptr)
		(*MainMenu.LastButton).State.Hover = false;

    if (!VectorInQuad(vec, MainMenu.Container.vertices))
		return 1;
	
	UIButton* btnptr 
		= FindButton( vec, 0, (MainMenu.Buttons.size() - 1) );
	
	if (btnptr == nullptr) 
		return 2;
	
	UIButton& Button 
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
	
	return 0;
}

/**
* Draws buttons and containers
*/
void MainMenu_Draw()
{
	MainMenu.Container.Draw();
	
	std::map< std::string, UIButton >::iterator i;

	for (i = MainMenu.Buttons.begin(); i != MainMenu.Buttons.end(); i++)
	{
		UIButton& Button = i->second;

		if (Button.State.Hover)
			Button.Draw_Hover();

		else if (Button.State.Pushed)
			Button.Draw_Pushed();

		else
			Button.Draw();
	}
}

/**
* calculates all vertices in box polygon
* accepts integer coordinates of first vextex(x,y), integer width, integer height, integer vertice number
* returns int vect for each vertice of actor
*/
std::vector<int> CalculateQuadVertex( int x, int y, 
									  int w, int h, 
									  int vtxnum )
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

/**
* Initiates MainMenu objects
* accepts integers starting button x,y coordinates
* returns 0
*/
int MainMenu_Init()
{	
	UIButton Button;
	std::vector<int> vtx(2);

	int x = 110; 
	int y = 85;

	MainMenu.Container.renderer = renderer;
	
	for (int vc = 1; vc <= 4; vc++)
	{
		vtx = CalculateQuadVertex( 54, 54, 
			                       330, (9 * 80), 
								   vc );

		MainMenu.Container.vertices.push_back( vtx );
	}
	
	MainMenu.LastButton = nullptr;

	Button.w = 235;
	Button.h = 43;
	Button.State.Hover = false;
	Button.State.Pushed = false;
	Button.renderer = renderer;

	for (int i = 0; i <= 9; i++)
	{
		Button.x = x;
		Button.y = y;

		Button.vertices.clear();

		for(int vc = 1; vc <= 4; vc++)
		{
			vtx = CalculateQuadVertex( Button.x, Button.y,
			                           Button.w, Button.h, 
									   vc );

			Button.vertices.push_back( vtx );
		}

		Button.actorVertices = Button.vertices;
		
		MainMenu.Buttons[ "BTN_ID_" + std::to_string(i) ] = Button;
		
		y += (Button.h + 15);
	}

	return 0;
}



