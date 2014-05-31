#include "GCP_FormComponent.h"
#include "GCP_Graph.h"


GCP_Graph::GCP_Graph()	{

}

//ÂÛÂÎÄ ÃĞÀÔÈÊÀ (ÑÅÉ×ÀÑ ĞÈÑÓÅÒ ÊĞÓÃÎÂÓŞ ÄÈÀÃĞÀÌÌÓ)
void GCP_Graph::OnDraw(SDL_Renderer* screen,int w, int h, int formx, int formy, int formw, int formh)
{
	if(!isVisible)
		return;


	double maxY=0;
	for(unsigned int i=0; i< values->size(); i++)
		if(values->at(i)->Y > maxY)
			maxY=values->at(i)->Y;


	GCP_Point pointA  = GCP_Point(xPos+width/2,yPos+height/2);
	for(unsigned int i=0; i< values->size(); i++)
	{
		double yRadius = (values->at(i)->Y*100)/maxY;
		yRadius *= width/2/100;
		GCP_Point pointB  = GCP_Point(pointA.X+GCP_Math::ccos(values->at(i)->X)*yRadius,
									  pointA.Y-GCP_Math::ssin(values->at(i)->X)*yRadius
							);

		GCP_Draw::drawLine(screen,w,h,pointA,pointB,c_red,0);
	}
	GCP_Draw::Draw_Ellipse(screen,pointA.X,pointA.Y,width/2,height/2,c_black);
	basicOnDraw(screen, formx, formy, formw, formh);

}
