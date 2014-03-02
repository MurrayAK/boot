#include "main_menu.h"
#include <typeinfo>
#include <iostream>
std::map< std::string, UIButton > MainMenuButtons;
Polygon Menu_Container_box;

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

		std::cout << "vecx(" << vec[0] << ") vtxx(" << vtx[0] << ") | " 
			      << "vecy(" << vec[1] << ") vtxy(" << vtx[1] << ") >>> " << vtxX << " " << vtxY << std::endl;
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

	if(VectorInBox(vec,Menu_Container_box.vertices)){
	
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
}

int MainMenu_Draw()
{
	UIButton btn;

	std::map< std::string, UIButton >::iterator i;

	for (i = MainMenuButtons.begin(); i != MainMenuButtons.end(); i++)
	{
		btn = i->second;
		if (btn.State.Hover) {btn.Draw_Hover();std::cout<<"drawing hover"<<std::endl;}
		else { 
			if (btn.State.Pressed)
				btn.Draw_Pressed();
			else
				btn.Draw();
		}
	}
	return 0;
}

std::vector<int> Polygon_vertex_ops(int x, int y,int width,int height, int vertex_num){
	std::vector<int> vertex_coord(2);
	switch (vertex_num)
		{
	case 1:
			vertex_coord[0]=x;
			vertex_coord[1]=y;
			break;
		case 2:
			vertex_coord[0]=-((x + width) - 1);
			vertex_coord[1]=y+5;
			break;
		case 3:
			vertex_coord[0]=-((x + width) - 1);
			vertex_coord[1]=-((y + height) - 1)+2;
			break;
		default:
			vertex_coord[0]=x;
			vertex_coord[1]=-((y + height) - 1);
			break;
	}
	//std::cout << typeid(vertex_coord).name() << " " << "type on vertex_ops"<<std::endl;

return vertex_coord;
}



int MainMenu_Init( int x, int y )
{	
	UIButton btn;
	//std::vector<int> vec(2);
	for(int v=1;v<=4;v++){
		Menu_Container_box.vertices.push_back(Polygon_vertex_ops(54,54,330,9*65,v));
	}
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
		for(int a=1;a<=4;a++){
			btn.vertices.push_back( Polygon_vertex_ops(btn.x,btn.y,btn.w,btn.h,a));
		}
		btn.actorVertices = btn.vertices;
		MainMenuButtons["BTN_ID_" + std::to_string(i)] = btn;

		y += (btn.h + 15);
	}

	return 0;
}



