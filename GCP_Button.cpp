#include "GCP_FormComponent.h"
#include "GCP_Button.h"

GCP_Button::GCP_Button(){
	iType = GCP_BUTTON_SHARPRECT;		//праметр - какие у кнопки углы
	checked = false;					//состояние кнопки если нажата
}

void GCP_Button::OnDraw(SDL_Renderer* screen,int w, int h, int formx, int formy, int formw, int formh)
{
	if(!isVisible)
		return;

	GCP_Color cTColor=cTextColor, cBColor=cBackColor;

	//Цвета тоже надо в структуру сделать
	if(_isMouseOver){
			cBColor = cBackColorHover;
			cTColor = cTextColorHover;					
		}

	if(checked)
		cBColor = cBackColorHover;

	//Если кнопке присвоен файлик с иконкой 
	if(icon != "")			{
		//Рисуем контур
		if(iType==GCP_BUTTON_ROUNDRECT)
			GCP_Draw::Draw_FillRound(screen,xPos,yPos,width,height,iRoundCff,cBColor);
		if(iType==GCP_BUTTON_SHARPRECT)
			GCP_Draw::Draw_FillRect(screen,xPos,yPos,width,height,cBColor);

		SDL_Surface *bmp = SDL_LoadBMP(icon.c_str());	
		if(bmp != NULL){
			//SDL_Rect recta = {(Sint16)xPos+2,(Sint16)yPos+2,width,height}; 
			//SDL_BlitSurface( hello, NULL, screen, &recta );
			//грузим картинку в текстуру и выводим ее на буфер
			SDL_Texture *tex = SDL_CreateTextureFromSurface(screen, bmp);
			GCP_Draw::applySurface(xPos+2,yPos+2,tex,screen);
			SDL_FreeSurface( bmp );
			SDL_DestroyTexture(tex); //Create texture should be once !!!!!!!!! not dynamic!!!!!
			//!!!!!!!  создание текстуры и загрузка картинки каждый раз это затратно
			//!!!!!!!  надо делать это один раз, а потом просто выводить текстуру на буффер
		}
		else
		{
			//Картинка не загрузилась
		}
	}
	else			{
		//Просто выводим надпись
		string sCaption = getCaption();
		if(iType==GCP_BUTTON_ROUNDRECT)
			GCP_Draw::Draw_FillRound(screen,xPos,yPos,width,height,iRoundCff,cBColor);
		if(iType==GCP_BUTTON_SHARPRECT)
			GCP_Draw::Draw_FillRect(screen,xPos,yPos,width,height,cBColor);			
		GCP_Draw::renderText(sCaption,xPos+3,yPos+3,screen,&drawdata,cTColor,getFont(),14);
		//TTF_CloseFont(font);
	}

	//Базовый метод он драв для всех компоннт
	basicOnDraw(screen, formx, formy, formw, formh);
}	

