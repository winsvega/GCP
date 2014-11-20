#include "GCP_FormComponent.h"
#include "GCP_Graph.h"


GCP_Graph::GCP_Graph()	{

}

//ÂÛÂÎÄ ÃĞÀÔÈÊÀ (ÑÅÉ×ÀÑ ĞÈÑÓÅÒ ÊĞÓÃÎÂÓŞ ÄÈÀÃĞÀÌÌÓ)
void GCP_Graph::OnDraw(const GCP_Event& event)
{
	if(!isVisible())
		return;


	double maxY=0;
	for(unsigned int i=0; i< values->size(); i++)
		if(values->at(i)->Y > maxY)
			maxY=values->at(i)->Y;


   GCP_Point pointA = _position.center();
	for(unsigned int i=0; i< values->size(); i++)
	{
		double yRadius = (values->at(i)->Y*100)/maxY;
      yRadius *= _position.width()/ 2 / 100;
		GCP_Point pointB  = GCP_Point(pointA.X+GCP_Math::ccos(values->at(i)->X)*yRadius,
									  pointA.Y-GCP_Math::ssin(values->at(i)->X)*yRadius
							);

      GCP_Draw::Render()->Draw_Line((int)pointA.X, (int)pointA.Y, (int)pointB.X, (int)pointB.Y, c_red, 0);
	}
   GCP_Draw::Render()->Draw_Ellipse((int)pointA.X, (int)pointA.Y, _position.width() / 2, _position.height() / 2, c_black);
	basicOnDraw(event);

}
