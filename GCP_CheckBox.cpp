#include "GCP_FormComponent.h"
#include "GCP_Checkbox.h"


GCP_CheckBox::GCP_CheckBox()	{
	isChecked = false;
	_isVisible = true;
}

void GCP_CheckBox::OnDraw(const GCP_Event &event)
{
	if(!isVisible())
		return;						
	

	GCP_Point pointA,pointB;

	
	GCP_Draw::Render()->Draw_Rect(_position.x() , _position.y() , 15,15,c_black);
	if(isChecked)
      GCP_Draw::Render()->Draw_FillEllipse(_position.x() + 7, _position.y() + 7, 4, 4, c_black);

	//надпись у чекбокса
   GCP_Draw::Render()->Draw_Text(text, _position.x() + 18, _position.y(), getStyle(), &drawdata);
	
	basicOnDraw(event);

}
gcp_formEvent GCP_CheckBox::OnEvent(const GCP_Event &event)
{
	//обработка события

	gcp_formEvent evt;						//по умолчанию все флаги обнулим. они все равно не нужны
	evt.isEventInsideForm = false;
	evt.isEventOnFormHead = false;
	evt.isFormDragged = false;
	if(!isVisible())
		return evt;	

   if (event.eventType == GCP_ON_LEFT_CLICK)		//чекбокс случает только левую кнопку (локально)
		isChecked = !isChecked;

	basicOnEvent(event);
	return evt;
}

/*bool GCP_CheckBox::OnMouseLeftClick(SDL_MouseButtonEvent mousebutton)
{
	isChecked = !isChecked;
	basicOnMouseLeftClick(mousebutton);
	return true;
}*/