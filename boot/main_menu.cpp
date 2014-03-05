#include "main_menu.h"
#include <typeinfo>
#include <iostream>


Polygon Menu_Container_box;


//MainMenu structure
struct MainMenu {
    int ContainerID;
    std::map< std::string, UIButton > Buttons;
    UIButton* LastHoverID;} 
MainMenu;


//accepts mouse position vector and button actor vertices
//return true if mouse is in actor false otherwise


bool VectorInBox( std::vector<int> vec, 
				  std::vector< std::vector<int> > vtcs )
{
	std::vector< std::vector<int> >::iterator i;
	std::vector<int> vtx(2);
	bool vtxX;
	bool vtxY;
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
	}

	if (vtxpc == vtcs.size())
		return true;

	return false;
}

//Used to search for which actor the mouse position belongs to
//accepts mouse position vector, integer start to look vector index ,integer end look vector index
//returns integer of found vector index, -1 if none is found

int Binary_search(std::vector<int> mousePosition,int imin, int imax){
	if ( imax < imin) return -1;
	
	else{
		int imid = imin + ( ( imax - imin ) / 2 );
		if ( MainMenu.Buttons["BTN_ID_"+std::to_string(imid)].actorVertices[0][1]>mousePosition[1] ){
			return Binary_search( mousePosition,imin,imid-1 );
		}
		else if( MainMenu.Buttons["BTN_ID_"+std::to_string(imid)].actorVertices[0][1] < mousePosition[1]){
				if (VectorInBox(mousePosition, MainMenu.Buttons["BTN_ID_"+std::to_string ( imid )].actorVertices )){ return imid; }
				return Binary_search( mousePosition, imid+1, imax);
		}
		else{
			return imid;
			}
	}
	return -1;
}

//Mouseclick on button state change
//accepts string with button key in map
//returns 0

int MainMenu_ButtonEvent_MouseClickLeft( std::string button_id )
{
	if (MainMenu.Buttons[button_id].State.Pressed == false)
		MainMenu.Buttons[button_id].State.Pressed = true;
	else
		MainMenu.Buttons[button_id].State.Pressed = false;
	
	return 0;
}

//Handles mouse events on
//accepts mouse position and event to handle
//returns 0

int MainMenu_ButtonEvent( int mx, int my,MouseEvent event )
    {
    std::vector<int> vec(2);
     
    vec[0] = mx;
    vec[1] = my;
    
	int actorNumber=Binary_search(vec,0,MainMenu.Buttons.size()-1);

    if (!VectorInBox(vec, Menu_Container_box.vertices)) return 1;
     
  

	if(actorNumber!=-1){

		switch ( event ) {
			case MOUSE_CLICK_LEFT:
				MainMenu_ButtonEvent_MouseClickLeft( "BTN_ID_" + std::to_string( actorNumber) );
				break;
     
			case MOUSE_MOTION:
				if( MainMenu.LastHoverID == NULL ){
					MainMenu.Buttons["BTN_ID_" + std::to_string ( actorNumber )].State.Hover=true;
					MainMenu.LastHoverID = &MainMenu.Buttons["BTN_ID_" + std::to_string ( actorNumber )];
				}
				if( MainMenu.LastHoverID!=&MainMenu.Buttons["BTN_ID_" + std::to_string ( actorNumber )] ){
					(*MainMenu.LastHoverID).State.Hover = false;
					MainMenu.Buttons["BTN_ID_" + std::to_string ( actorNumber )].State.Hover = true;
					MainMenu.LastHoverID=&MainMenu.Buttons["BTN_ID_" + std::to_string ( actorNumber )];
				}
				break;
		}
	}
	
	return 0;
}

//Draws buttons and containers
//returns 0

int MainMenu_Draw()
{
	UIButton btn;
	Menu_Container_box.Draw();
	std::map< std::string, UIButton >::iterator i;

	for (i = MainMenu.Buttons.begin(); i != MainMenu.Buttons.end(); i++)
	{
		btn = i->second;
		if ( btn.State.Hover ) { btn.Draw_Hover();}
		else { 
			if ( btn.State.Pressed )
				btn.Draw_Pressed();
			else
				btn.Draw();
		}
	}
	return 0;
}

//calculates all vertices in polygon
//accepts integers coordinates of first vextex(x,y),integer width,integer height, integer vertice number
//returns int vect for each vertice of actor

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
return vertex_coord;
}

//initiates MainMenu objects
//accepts integers starting button x,y coordinates
//returns 0

int MainMenu_Init( int x, int y )
{	
	UIButton btn;
	MainMenu.ContainerID=1;
	Menu_Container_box.renderer=renderer;
	for(int v=1;v<=4;v++){
		Menu_Container_box.vertices.push_back(Polygon_vertex_ops(54,54,330,9*80,v));
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
			btn.vertices.push_back( Polygon_vertex_ops( btn.x,btn.y,btn.w,btn.h,a ) );
		}
		btn.actorVertices = btn.vertices;
		MainMenu.Buttons["BTN_ID_" + std::to_string(i)] = btn;
		y += (btn.h + 15);
	}

	return 0;
}



