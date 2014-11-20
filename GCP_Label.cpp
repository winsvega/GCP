#include "GCP_FormComponent.h"
#include "GCP_Label.h"


GCP_Label::GCP_Label()	{
	
}

void GCP_Label::OnDraw(const GCP_Event &event)
{
	//isVisible = false;
	if(!isVisible())
		return;						
	
   const GCP_Rect pos = getPosition();
   GCP_Draw::Render()->Draw_Text(text, pos.x(), pos.y(), getStyle(), &drawdata);
	
	basicOnDraw(event);

}