#include "main_menu.h"

std::map< std::string, UIButton > MainMenuButtons;

bool VectorInBox( std::vector<int> vec, 
				  std::vector< std::vector<int> > vtcs )
{
	std::vector< std::vector<int> >::iterator i;
	std::vector<int> vtx(2);
	bool vtxX = false;
	bool vtxY = false;
	int vtxpc = 0;
	
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

		//std::cout << "vecx(" << vec[0] << ") vtxx(" << vtx[0] << ") | " 
		//	      << "vecy(" << vec[1] << ") vtxy(" << vtx[1] << ") >>> " << vtxX << " " << vtxY << std::endl;
	}

	std::cout << std::endl;

	if (vtxpc == vtcs.size())
		return true;

	return false;
}

int MainMenu_ButtonEvent_MouseClickLeft( std::string button_id )
{
	if (MainMenuButtons[button_id].State.Pressed == false)
		MainMenuButtons[button_id].State.Pressed = true;
	else
		MainMenuButtons[button_id].State.Pressed = false;
	
	return 0;
}

int MainMenu_ButtonEvent( int mx, int my, 
						  MouseEvent event )
{
	std::map< std::string, UIButton >::iterator i;
	std::vector< std::vector<int> > vtcs;
	std::vector<int> vec(2);

	vec[0] = mx;
	vec[1] = my;
	
	for (i = MainMenuButtons.begin(); i != MainMenuButtons.end(); i++)
	{
		vtcs = i->second.actorVertices;

		if (VectorInBox(vec, vtcs))
		{			
			switch (event)
			{
				case MOUSE_CLICK_LEFT:
					MainMenu_ButtonEvent_MouseClickLeft( i->first );
					break;

				case MOUSE_MOTION:
					MainMenuButtons[i->first].State.Hover = true;
					break;
			}

			break;
		}
		else 
		{
			switch (event)
			{
				case MOUSE_MOTION:
					MainMenuButtons[i->first].State.Hover = false;
					break;
			}
		}
	}

	return 0;
}

int MainMenu_Draw()
{
	UIButton btn;
	std::map< std::string, UIButton >::iterator i;

	for (i = MainMenuButtons.begin(); i != MainMenuButtons.end(); i++)
	{
		btn = i->second;
		if (btn.State.Hover) btn.Draw_Hover();
		else { 
			if (btn.State.Pressed)
				btn.Draw_Pressed();
			else
				btn.Draw();
		}
	}
	return 0;
}

int MainMenu_Init( int x, int y )
{	
	UIButton btn;
	std::vector<int> vec(2);

	btn.renderer = renderer;
	btn.w = 235;
	btn.h = 43;
	btn.State.Pressed = false;
	btn.State.Hover = false;
	
	for (int i = 0; i <= 9; i++)
	{
		btn.x = x;
		btn.y = y;

		btn.vertices.clear();

		vec[0] = btn.x;
		vec[1] = btn.y;
		btn.vertices.push_back( vec );

		vec[0] = -((btn.x + btn.w) - 1);
		vec[1] = btn.y + 5;
		btn.vertices.push_back( vec );

		vec[0] = -((btn.x + btn.w) - 1);
		vec[1] = -((btn.y + btn.h) - 1) + 2;
		btn.vertices.push_back( vec );

		vec[0] = btn.x;
		vec[1] = -((btn.y + btn.h) - 1);
		btn.vertices.push_back( vec );

		btn.actorVertices = btn.vertices;

		MainMenuButtons["BTN_ID_" + std::to_string(i)] = btn;

		y += (btn.h + 15);
	}

	return 0;
}