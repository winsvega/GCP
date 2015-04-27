#include "GCP_FormComponent.h"
#include "GCP_Button.h"
using namespace gcp;

GCP_Button::GCP_Button()
{
	_iType = GCP_BUTTON_SHARPRECT;		//праметр - какие у кнопки углы
	_bChecked = false;					//состояние кнопки если нажата
	setStyle(GCP_ButtonWhiteStyle);
}


gcp_formEvent GCP_Button::OnEvent(const GCP_Event &event)
{
	basicOnEvent(event);

	if (event.eventType == GCP_ON_GLEFT_CLICK || event.eventType == GCP_ON_LEFT_CLICK)
		_isMouseOver = false;

	gcp_formEvent evt;
	evt.isEventInsideForm = false;
	return evt;
}



void GCP_Button::OnDraw(const GCP_Event &event)
{
	if(!isVisible())
		return;

	gcp_spStyle ptrStyle = getStyle();
	GCP_Color cTColor = ptrStyle->textColor;
	GCP_Color cBColor = ptrStyle->backgroundColor;

	//Цвета тоже надо в структуру сделать
	if(_isMouseOver)
	{
		cBColor = ptrStyle->backgroundMouseHoverColor;
		cTColor = ptrStyle->textMouseHoverColor;
	}

	if (!_isEnabled)
	{
		cBColor = ptrStyle->backgroundDisabledColor;
		cTColor = ptrStyle->textDisabledColor;
	}


	if(_bChecked)
		cBColor = ptrStyle->backgroundMouseHoverColor;

	//Если кнопке присвоен файлик с иконкой
	if(_sIconPath != "")			{
		//Рисуем контур
		if (_iType==GCP_BUTTON_ROUNDRECT)
			GCP_Draw::Render()->Draw_FillRound(_position, ptrStyle->roundCff, cBColor);
		if (_iType==GCP_BUTTON_SHARPRECT)
			GCP_Draw::Render()->Draw_FillRect(_position, cBColor);
		//GCP_Draw::Render()->SetBlendMode(E_BLEND_ADD);
		GCP_Draw::Render()->Draw_Image(_sIconPath, _position.x() + 2, _position.y() + 2);
		//GCP_Draw::Render()->SetBlendMode(E_BLEND_NONE);
	}
	else			{
		//Просто выводим надпись
		string sCaption = getCaption();
		gcpUint8 alphaOrig = GCP_Draw::Render()->GetAlpha();

		if (_iType==GCP_BUTTON_ROUNDRECT)
		{
			GCP_Draw::Render()->SetAlpha(ptrStyle->drawTextBackgroundAlpha);
			GCP_Draw::Render()->Draw_FillRound(_position, ptrStyle->roundCff, cBColor);
			GCP_Draw::Render()->SetAlpha(alphaOrig);
			GCP_Draw::Render()->Draw_Round(_position, ptrStyle->roundCff, ptrStyle->borderColor);
		}
		if (_iType==GCP_BUTTON_SHARPRECT)
		{
			GCP_Draw::Render()->SetAlpha(ptrStyle->drawTextBackgroundAlpha);
			GCP_Draw::Render()->Draw_FillRect(_position, cBColor);
			GCP_Draw::Render()->SetAlpha(alphaOrig);
			GCP_Draw::Render()->Draw_Rect(_position, ptrStyle->borderColor);
		}

		gcp_spStyle color = gcp_spStyle(new GCP_Style());
		color->textColor = cTColor;
		color->font = ptrStyle->font;
		GCP_Draw::Render()->Draw_Text(sCaption,_position, color, &drawdata);
	}

	//Базовый метод он драв для всех компоннт
	basicOnDraw( event);
}	

