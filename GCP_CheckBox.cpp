#include "GCP_FormComponent.h"
#include "GCP_Checkbox.h"


GCP_CheckBox::GCP_CheckBox()	{
	isChecked = false;
	isVisible = true;
}

void GCP_CheckBox::OnDraw(SDL_Renderer* screen,int w, int h, int formx, int formy, int formw, int formh)
{
	if(!isVisible)
		return;						
	

	GCP_Point pointA,pointB;

	
	GCP_Draw::Draw_Rect(screen,xPos , yPos , 15,15,c_black);
	if(isChecked)
		GCP_Draw::Draw_FillEllipse(screen,xPos+7,yPos+7, 4,4 ,c_black);

	//надпись у чекбокса
	GCP_Draw::renderText(text,xPos+18,yPos,screen,&drawdata,cTextColor,getFont().c_str(),14);
	
	basicOnDraw(screen, formx, formy, formw, formh);

}
gcp_formEvent GCP_CheckBox::OnEvent( const int GCP_EVENT, sdl_events events)
{
	//обработка события

	gcp_formEvent evt;						//по умолчанию все флаги обнулим. они все равно не нужны
	evt.isEventInsideForm = false;
	evt.isEventOnFormHead = false;
	evt.isFormDragged = false;
	if(!isVisible)
		return evt;	

	if(GCP_EVENT == GCP_ON_LEFT_CLICK)		//чекбокс случает только левую кнопку (локально)
		isChecked = !isChecked;

	basicOnEvent(GCP_EVENT,events);
	return evt;
}

/*bool GCP_CheckBox::OnMouseLeftClick(SDL_MouseButtonEvent mousebutton)
{
	isChecked = !isChecked;
	basicOnMouseLeftClick(mousebutton);
	return true;
}*/