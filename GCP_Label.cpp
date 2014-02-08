#include "GCP_FormComponent.h"
#include "GCP_Label.h"


GCP_Label::GCP_Label()	{
	
}

void GCP_Label::OnDraw(SDL_Renderer* screen,int w, int h, int formx, int formy, int formw, int formh)
{
	//isVisible = false;
	if(!isVisible)
		return;						
	

	GCP_Draw::renderText(text,xPos,yPos,screen,&drawdata,cTextColor,getFont().c_str(),14);
	
	basicOnDraw(screen, formx, formy, formw, formh);

}