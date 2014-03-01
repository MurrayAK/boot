#include "main_menu.h"

std::map< std::string, UIButton > MainMenuButtons;

bool VectorInBox(std::vector<int> vec, std::vector< std::vector<int> > vtcs)
{
	std::vector<int> vtx;
	bool vtxX = false;
	bool vtxY = false;
	int vtxpc = 0;

	std::vector< std::vector<int> >::iterator i;
	for (i = vtcs.begin(); i != vtcs.end(); i++)
	{
		vtx = *i;

		vtxX = false;
		vtxY = false;

		vec[0] = std::abs(vec[0]);
		vec[1] = std::abs(vec[1]);
			
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

int MainMenu_ButtonEvent_MouseClickLeft(std::string button_id)
{
	if (MainMenuButtons[button_id].pushed == false)
		MainMenuButtons[button_id].pushed = true;
	else
		MainMenuButtons[button_id].pushed = false;
	
	return 0;
}

int MainMenu_ButtonEvent(int mx, int my, MouseEvent event)
{
	std::vector<int> vec(2);
	std::vector< std::vector<int> > vtcs(4);

	vec[0] = mx;
	vec[1] = my;

	std::map< std::string, UIButton >::iterator i;
	for (i = MainMenuButtons.begin(); i != MainMenuButtons.end(); i++)
	{
		vtcs = i->second.actorVertices;

		if (VectorInBox(vec, vtcs))
		{
			//std::cout << "button event! >> i->first << std::endl << std::endl;
			
			switch (event)
			{
				case MOUSE_CLICK_LEFT:
					MainMenu_ButtonEvent_MouseClickLeft( i->first );
					break;

				case MOUSE_MOTION:
					MainMenuButtons[i->first].hover = true;
					break;
			}

			break;
		}
		else 
		{
			switch (event)
			{
				case MOUSE_MOTION:
					MainMenuButtons[i->first].hover = false;
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
		btn.Draw();
	}

	return 0;
}

int MainMenu_Init(int x, int y)
{	
	UIButton btn;
	std::vector<int> vec(2);

	btn.renderer = renderer;
	btn.w = 235;
	btn.h = 43;
	btn.pushed = false;
	btn.hover = false;

	for (int i = 0; i <= 9; i++)
	{
		btn.x = x;
		btn.y = y;

		btn.actorVertices.clear();

		vec[0] = btn.x;
		vec[1] = btn.y;
		btn.actorVertices.push_back( vec );

		vec[0] = -((btn.x + btn.w) - 1);
		vec[1] = btn.y;
		btn.actorVertices.push_back( vec );

		vec[0] = -((btn.x + btn.w) - 1);
		vec[1] = -((btn.y + btn.h) - 1);
		btn.actorVertices.push_back( vec );

		vec[0] = btn.x;
		vec[1] = -((btn.y + btn.h) - 1);
		btn.actorVertices.push_back( vec );

		MainMenuButtons["BTN_ID_" + std::to_string(i)] = btn;

		y += (btn.h + 15);
	}

	return 0;
}