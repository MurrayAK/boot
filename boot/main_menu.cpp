#include "main_menu.h"

/**
* MainMenu structure
*/
struct MainMenu {
	Polygon Container;
    std::map< std::string, UIButton > Buttons;
    UIButton* LastButton;

} MainMenu;

/**
* accepts mouse position vector and button actor vertices
* return true if mouse is in actor false otherwise
*/
bool VectorInBox( std::vector<int> vec, 
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
* Used to search for which actor the mouse position belongs to
* accepts mouse position vector, integer start to look vector index, integer end look vector index
* returns integer of found vector index, -1 if none is found
* binary search method
*/
int FindButtonActor( std::vector<int> mpos, 
				     int imin, int imax )
{
	if (imax < imin) 
		return 1;

	else
	{
		int imid;
		std::vector< std::vector<int> > vtcs;

		imid = (imin + ((imax - imin) / 2));
		vtcs = MainMenu.Buttons["BTN_ID_" + std::to_string(imid)].actorVertices;

		if (vtcs[0][1] > mpos[1])
			return FindButtonActor(mpos, imin, (imid - 1));

		else if (vtcs[0][1] < mpos[1])
		{
			if (VectorInBox(mpos, vtcs))
				return imid;

			return FindButtonActor(mpos, (imid + 1), imax);
		}
		
		return imid;
	}

	return -1;
}

/**
* Mouseclick on button state change
* accepts string with button key in map
* returns 0
*/
int ButtonEvent_MouseLClick( std::string id )
{
	UIButton& Button = MainMenu.Buttons[id];
	
	if (Button.State.Pressed == false)
		Button.State.Pressed = true;
	else
		Button.State.Pressed = false;

	return 0;
}

/**
* Mouse motion on button state change
* accepts string with button key in map
* returns 0
*/
int ButtonEvent_MouseMotion( std::string id )
{
	UIButton& Button = MainMenu.Buttons[id];
	UIButton*& LastButton = MainMenu.LastButton;
	
	if (LastButton)
		(*LastButton).State.Hover = false;

	Button.State.Hover = true;

	LastButton = &Button;

	return 0;
}

/**
* handles mouse events on
* accepts mouse position and event to handle
* returns 0
*/
int MainMenu_ButtonEventHandler_Mouse( int mx, int my, 
									   MouseEvent event )
{
    std::vector<int> vec(2);
	
    vec[0] = mx;
    vec[1] = my;
    
    if (!VectorInBox(vec, MainMenu.Container.vertices))
		return 1;
     
	int actorNumber;

	actorNumber = FindButtonActor( vec, 0, (MainMenu.Buttons.size() - 1) );

	if (actorNumber == -1) 
		return -1;
	
	std::string id = "BTN_ID_" + std::to_string(actorNumber);

	switch (event) 
	{
		case MOUSE_CLICK_LEFT:
			ButtonEvent_MouseLClick( id );
			break;
			
		case MOUSE_MOTION:
			ButtonEvent_MouseMotion( id );
			break;

		default:
			break;
	}
	
	//else if (MainMenu.LastButton != NULL)
	//	(*MainMenu.LastButton).State.Hover = false;
	
	return 0;
}

/**
* Draws buttons and containers
* returns 0
*/
int MainMenu_Draw()
{
	//MainMenu.Container.Draw();

	std::map< std::string, UIButton >::iterator i;

	for (i = MainMenu.Buttons.begin(); i != MainMenu.Buttons.end(); i++)
	{
		UIButton& Button = i->second;

		if (Button.State.Hover)
			Button.Draw_Hover();

		else if (Button.State.Pressed)
			Button.Draw_Pressed();

		else
			Button.Draw();
	}

	return 0;
}

/**
* calculates all vertices in box polygon
* accepts integer coordinates of first vextex(x,y), integer width, integer height, integer vertice number
* returns int vect for each vertice of actor
*/
std::vector<int> CalculateBoxVertex( int x, int y, 
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

	//MainMenu.Container.renderer = renderer;
	
	for (int v = 1; v <= 4; v++)
	{
		vtx = CalculateBoxVertex( 54, 54, 
			                      330, (9 * 80), 
								  v );

		MainMenu.Container.vertices.push_back( vtx );
	}
	
	Button.w = 235;
	Button.h = 43;
	Button.State.Hover = false;
	Button.State.Pressed = false;
	Button.renderer = renderer;

	for (int i = 0; i <= 9; i++)
	{
		Button.x = x;
		Button.y = y;

		Button.vertices.clear();

		for(int a = 1; a <= 4; a++)
		{
			vtx = CalculateBoxVertex( Button.x, Button.y,
			                          Button.w, Button.h, 
									  a );

			Button.vertices.push_back( vtx );
		}

		Button.actorVertices = Button.vertices;
		
		MainMenu.Buttons["BTN_ID_" + std::to_string(i)] = Button;
		
		y += (Button.h + 15);
	}

	return 0;
}



