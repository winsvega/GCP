#include "GCP_FormComponent.h"
#include "GCP_Label.h"
using namespace gcp;

GCP_Label::GCP_Label()	{
}

void GCP_Label::OnDraw(const GCP_Event &event)
{
	//isVisible = false;
	if (!isVisible())
		return;

	gcp_spStyle style = getStyle();
	if (style->drawTextBorder)
		GCP_Draw::Render()->Draw_Round(_position, 1, style->borderColor);

	if (style->drawTextBackground)
	{
		gcpUint8 alphaOrig = GCP_Draw::Render()->GetAlpha();
		GCP_Draw::Render()->SetAlpha(style->drawTextBackgroundAlpha);
		if (_isMouseOver)
			GCP_Draw::Render()->Draw_FillRound(_position, 1, style->backgroundMouseHoverColor);
		else GCP_Draw::Render()->Draw_FillRound(_position, 1, style->backgroundColor);
		GCP_Draw::Render()->SetAlpha(alphaOrig);
	}


	int iBorderWidth = style->borderWidth;
	GCP_Rect<int> textPos = (style->font.align == E_CENTER) ? getPosition() : GCP_Rect<int>(_position.x() + iBorderWidth * 2, _position.y() + iBorderWidth * 1, _position.width(), _position.height());
	gcp_spStyle color = gcp_spStyle(new GCP_Style());
	if (_isMouseOver)
		color->textColor = style->textMouseHoverColor;
	else color->textColor = style->textColor;
	color->font = style->font;
	GCP_Draw::Render()->Draw_Text(text, textPos, color, &drawdata);
	
	basicOnDraw(event);

}
