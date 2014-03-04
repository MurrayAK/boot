#include "main_menu.h"
#include <typeinfo>
#include <iostream>
std::map< std::string, UIButton > MainMenuButtons;
Polygon Menu_Container_box;
std::vector<int> ActorColecctiony;

struct MainMenu {
    int ContainerID;
    std::map< std::string, UIButton >* Buttons;
    UIButton* LastHoverID;} 
MainMenu;

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

	//std::cout << std::endl;

	if (vtxpc == vtcs.size())
		return true;

	return false;
}

int Binary_search(std::vector<int> mousePosition,std::vector<int> UiButoonYPosition,int imin, int imax){
	//std::cout << imax << " " << imin << std::endl;
	if ( imax < imin) return -1;
	
	else{
		int imid = imin + ( ( imax - imin ) / 2 );
		//std::cout << imid << " the middle point!!! "<<std::endl;
		if (ActorColecctiony[imid]>mousePosition[1]){
			return Binary_search(mousePosition,UiButoonYPosition,imin,imid-1);
		}
		else if(ActorColecctiony[imid]<mousePosition[1]){
				if (VectorInBox(mousePosition,MainMenuButtons["BTN_ID_" + std::to_string(imid)].actorVertices)){return imid;}
				return Binary_search(mousePosition,UiButoonYPosition,imid+1,imax);

		}
		else{
			if(VectorInBox(mousePosition,MainMenuButtons["BTN_ID_" + std::to_string(imid)].actorVertices)){return imid;}
			}
	}
	return -1;
}

int MainMenu_ButtonEvent_MouseClickLeft( std::string button_id )
{
	if (MainMenuButtons[button_id].State.Pressed == false)
		MainMenuButtons[button_id].State.Pressed = true;
	else
		MainMenuButtons[button_id].State.Pressed = false;
	
	return 0;
}

int MainMenu_ButtonEvent( int mx, int my,MouseEvent event )
    {
    std::map< std::string, UIButton >::iterator i;
    std::vector< std::vector<int> > vtcs;
    std::vector<int> vec(2);
     
    vec[0] = mx;
    vec[1] = my;
    
	int actorNumber=Binary_search(vec,ActorColecctiony,0,MainMenuButtons.size()-1);

    if (!VectorInBox(vec, Menu_Container_box.vertices)) return 1;
     
    //std::cout << "test";

	if(actorNumber!=-1){
		//std::cout<<" actor found"<<std::endl;
		switch(event){
			case MOUSE_CLICK_LEFT:
				MainMenu_ButtonEvent_MouseClickLeft( "BTN_ID_" + std::to_string(actorNumber) );
				break;
     
			case MOUSE_MOTION:
				if( MainMenu.LastHoverID == NULL ){
					MainMenu.LastHoverID = &MainMenuButtons["BTN_ID_" + std::to_string(actorNumber)];
				}
				if( MainMenu.LastHoverID!=&MainMenuButtons["BTN_ID_" + std::to_string(actorNumber)] ){
					(*MainMenu.LastHoverID).State.Hover = false;
					MainMenuButtons["BTN_ID_" + std::to_string(actorNumber)].State.Hover = true;
					MainMenu.LastHoverID=&MainMenuButtons["BTN_ID_" + std::to_string(actorNumber)];
				}
				break;
		}
	}
	
	return 0;
}

     

int MainMenu_Draw()
{
	UIButton btn;
	Menu_Container_box.Draw();
	std::map< std::string, UIButton >::iterator i;

	for (i = MainMenuButtons.begin(); i != MainMenuButtons.end(); i++)
	{
		btn = i->second;
		if (btn.State.Hover) {btn.Draw_Hover();/*std::cout<<"drawing hover"<<std::endl;*/}
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
	MainMenu.ContainerID=1;
	//std::vector<int> vec(2);
	for(int v=1;v<=4;v++){
		Menu_Container_box.vertices.push_back(Polygon_vertex_ops(54,54,330,9*80,v));
	}
	Menu_Container_box.renderer=renderer;
	btn.renderer = renderer;
	btn.w = 235;
	btn.h = 43;
	btn.State.Pressed = false;
	btn.State.Hover = false;
	
	for (int i = 0; i <= 9; i++)
	{
		btn.x = x;
		btn.y = y;
		ActorColecctiony.push_back(y);
		btn.vertices.clear();
		for(int a=1;a<=4;a++){
			btn.vertices.push_back( Polygon_vertex_ops(btn.x,btn.y,btn.w,btn.h,a));
		}
		btn.actorVertices = btn.vertices;
		MainMenuButtons["BTN_ID_" + std::to_string(i)] = btn;

		y += (btn.h + 15);
	}
	MainMenu.Buttons=&MainMenuButtons;

	return 0;
}



