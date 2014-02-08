#include "SDL_ttf.h"
#include "GCP_Math.h"
#include "GCP_Draw.h"

void GCP_Draw::Draw_Line(SDL_Renderer* screen,int x,int y,int x2,int y2,GCP_Color color, int bold)
{
	Uint8 r,g,b,a;
	SDL_GetRenderDrawColor(screen,&r,&g,&b,&a);		
	SDL_SetRenderDrawColor(screen,color.r,color.g,color.b,color.a);	
	switch(bold)
	{
		case 2:
			SDL_RenderDrawLine(screen,x,y,x2,y2);
			SDL_RenderDrawLine(screen,x+1,y,x2+1,y2);
			SDL_RenderDrawLine(screen,x-1,y,x2-1,y2);
			SDL_RenderDrawLine(screen,x,y+1,x2,y2+1);
			SDL_RenderDrawLine(screen,x,y-1,x2,y2-1);
			break;
		default:
			SDL_RenderDrawLine(screen,x,y,x2,y2);
	}
	
	SDL_SetRenderDrawColor(screen,r,g,b,a);
}

void GCP_Draw::Draw_Round(SDL_Renderer* screen,Sint16 x,Sint16 y,Sint16 width,Sint16 height,Sint16 scale, GCP_Color color)
{
	//!!! scale не учитываеся!!!
	Uint8 r,g,b,a;
	SDL_GetRenderDrawColor(screen,&r,&g,&b,&a);		
	SDL_SetRenderDrawColor(screen,color.r,color.g,color.b,color.a);
	SDL_Rect recta = {x,y,width,height};
	SDL_RenderDrawRect(screen,&recta);
	SDL_SetRenderDrawColor(screen,r,g,b,a);
}

void GCP_Draw::Draw_FillRound(SDL_Renderer* screen,Sint16 x,Sint16 y,Sint16 width,Sint16 height,Sint16 scale, GCP_Color color)
{
	//!!! scale не учитываеся!!!
	Uint8 r,g,b,a;
	SDL_GetRenderDrawColor(screen,&r,&g,&b,&a);		
	SDL_SetRenderDrawColor(screen,color.r,color.g,color.b,color.a);
	SDL_Rect recta = {x,y,width,height};
	SDL_RenderFillRect(screen,&recta);
	SDL_SetRenderDrawColor(screen,r,g,b,a);
}

void GCP_Draw::Draw_Rect(SDL_Renderer* screen,Sint16 x ,Sint16 y ,Sint16 width,Sint16 height,GCP_Color color)
{		
	Uint8 r,g,b,a;
	SDL_GetRenderDrawColor(screen,&r,&g,&b,&a);		
	SDL_SetRenderDrawColor(screen,color.r,color.g,color.b,color.a);
	SDL_Rect recta = {x,y,width,height};
	SDL_RenderDrawRect(screen,&recta);
	SDL_SetRenderDrawColor(screen,r,g,b,a);
}
	
void GCP_Draw::Draw_FillRect(SDL_Renderer* screen,Sint16 x ,Sint16 y ,Sint16 width,Sint16 height,GCP_Color color)
{		
	Uint8 r,g,b,a;
	SDL_GetRenderDrawColor(screen,&r,&g,&b,&a);		
	SDL_SetRenderDrawColor(screen,color.r,color.g,color.b,color.a);
	SDL_Rect recta = {x,y,width,height};
	SDL_RenderFillRect(screen,&recta);
	SDL_SetRenderDrawColor(screen,r,g,b,a);
}
void GCP_Draw::Draw_FillEllipse(SDL_Renderer* screen,Sint16 x0,Sint16 y0,Sint16 Xradius,Sint16 Yradius,GCP_Color color)
{
	//Рисуем еллипс по точкам
	//Оригинальный код взят из SDL_draw-1.2.13

	Uint8 r,g,b,a;
	SDL_GetRenderDrawColor(screen,&r,&g,&b,&a);
	SDL_SetRenderDrawColor(screen,color.r,color.g,color.b,color.a);

	Sint32 x, y;
	Sint32 Xchange, Ychange;
	Sint32 EllipseError;
	Sint32 TwoASquare, TwoBSquare;
	Sint32 StoppingX, StoppingY;
	
	TwoASquare = 2*Xradius*Xradius;
	TwoBSquare = 2*Yradius*Yradius;

	/*1st set of points*/
	x = Xradius-1;  /*radius zero == draw nothing*/
	y = 0;

	Xchange = Yradius*Yradius*(1-2*Xradius);
	Ychange = Xradius*Xradius;

	EllipseError = 0;

	StoppingX = TwoBSquare*Xradius;
	StoppingY = 0;

	/*Plot four ellipse points by iteration*/
	while (StoppingX > StoppingY) {

		SDL_RenderDrawLine(screen,x0+x,y0+y,x0+x,y0-y);
		SDL_RenderDrawLine(screen,x0-x,y0+y,x0-x,y0-y);

		++y;
		StoppingY    += TwoASquare;
		EllipseError += Ychange;
		Ychange      += TwoASquare;
		if (( 2*EllipseError + Xchange) > 0) {
		  --x;
		  StoppingX    -= TwoBSquare;
		  EllipseError += Xchange;
		  Xchange      += TwoBSquare;
		}
	  }/*while*/

	  /*2nd set of points*/
	  x = 0;
	  y = Yradius-1;  /*radius zero == draw nothing*/
	  Xchange = Yradius*Yradius;
	  Ychange = Xradius*Xradius*(1-2*Yradius);
	  EllipseError = 0;
	  StoppingX = 0;
	  StoppingY = TwoASquare*Yradius;

	  /*Plot four ellipse points by iteration*/
	  while (StoppingX < StoppingY) {

		SDL_RenderDrawLine(screen,x0+x,y0+y,x0+x,y0-y);
		SDL_RenderDrawLine(screen,x0-x,y0+y,x0-x,y0-y);

		++x;
		StoppingX    += TwoBSquare;
		EllipseError += Xchange;
		Xchange      += TwoBSquare;
		if ((2*EllipseError + Ychange) > 0) {
		  --y;
		  StoppingY    -= TwoASquare;
		  EllipseError += Ychange;
		  Ychange      += TwoASquare;
		}
	  }	  
	  
	  SDL_SetRenderDrawColor(screen,r,g,b,a);
	/*Draw_Ellipse*/
}

void GCP_Draw::Draw_Ellipse(SDL_Renderer* screen,Sint16 x0,Sint16 y0,Sint16 Xradius,Sint16 Yradius,GCP_Color color)
{
	//Рисуем еллипс по точкам
	//Оригинальный код взят из SDL_draw-1.2.13
	Uint8 r,g,b,a;
	SDL_GetRenderDrawColor(screen,&r,&g,&b,&a);
	SDL_SetRenderDrawColor(screen,color.r,color.g,color.b,color.a);

	Sint32 x, y;
	Sint32 Xchange, Ychange;
	Sint32 EllipseError;
	Sint32 TwoASquare, TwoBSquare;
	Sint32 StoppingX, StoppingY;
	
	TwoASquare = 2*Xradius*Xradius;
	TwoBSquare = 2*Yradius*Yradius;

	/*1st set of points*/
	x = Xradius-1;  /*radius zero == draw nothing*/
	y = 0;

	Xchange = Yradius*Yradius*(1-2*Xradius);
	Ychange = Xradius*Xradius;

	EllipseError = 0;

	StoppingX = TwoBSquare*Xradius;
	StoppingY = 0;

	/*Plot four ellipse points by iteration*/
	while (StoppingX > StoppingY) {

		SDL_RenderDrawPoint(screen,x0+x,y0+y);
		SDL_RenderDrawPoint(screen,x0+x,y0-y);
		SDL_RenderDrawPoint(screen,x0-x,y0+y);
		SDL_RenderDrawPoint(screen,x0-x,y0-y);

		++y;
		StoppingY    += TwoASquare;
		EllipseError += Ychange;
		Ychange      += TwoASquare;
		if (( 2*EllipseError + Xchange) > 0) {
		  --x;
		  StoppingX    -= TwoBSquare;
		  EllipseError += Xchange;
		  Xchange      += TwoBSquare;
		}
	  }/*while*/

	  /*2nd set of points*/
	  x = 0;
	  y = Yradius-1;  /*radius zero == draw nothing*/
	  Xchange = Yradius*Yradius;
	  Ychange = Xradius*Xradius*(1-2*Yradius);
	  EllipseError = 0;
	  StoppingX = 0;
	  StoppingY = TwoASquare*Yradius;

	  /*Plot four ellipse points by iteration*/
	  while (StoppingX < StoppingY) {

		SDL_RenderDrawPoint(screen,x0+x,y0+y);
		SDL_RenderDrawPoint(screen,x0+x,y0-y);
		SDL_RenderDrawPoint(screen,x0-x,y0+y);
		SDL_RenderDrawPoint(screen,x0-x,y0-y);

		++x;
		StoppingX    += TwoBSquare;
		EllipseError += Xchange;
		Xchange      += TwoBSquare;
		if ((2*EllipseError + Ychange) > 0) {
		  --y;
		  StoppingY    -= TwoASquare;
		  EllipseError += Ychange;
		  Ychange      += TwoASquare;
		}
	  }	  
	  
	  SDL_SetRenderDrawColor(screen,r,g,b,a);
	/*Draw_Ellipse*/
}
/////////////////////////////////////////////////////////////////////////
///////////////////////DRAW Graphic
/////////////////////////////////////////////////////////////////////////
void GCP_Draw::drawGraph(SDL_Renderer* screen,int w, int h, int* data, int data_size, int x, int y, int width, int height)
{
//int data_size = sizeof(&data)/sizeof(int);
//Рисуем !!!корявый!!! график.  
//d - массив значений. 
//x , y - левый верхний угол			
x+=1; y+=1; width  -= 2; height -=2;  //Отсутп для рамочки
GCP_Color color = c_red;	

int it;
double i , _x, _y, _x2, _y2,percent;

double distance = 4;									//Минимальное расстояние между точками
int drawing_points = (int)(width/distance);				//количество точек которые мы нарисуем
int iteration = 1;										//итерация с которой мы перебираем массив	
int tmp_data_size = data_size;							//Нарасчиваем итерацию если массив не помещается
while(tmp_data_size>drawing_points)	{					//Ухудшаем информативность графика
	tmp_data_size/=2;
	iteration *=2;
}

tmp_data_size -=1;										//Сдвиг для расчета ячеек
distance = (double)width/(tmp_data_size);				//Расчитываем новое минимальное расстояние
double insert = (distance- floor(distance));		//Кореляция
distance = floor(distance);

int max = abs(data[0]);							//екстремальное значение графика
for(it = 0; it<data_size; it+=iteration)	{
	if (abs(data[it]) > max)
		max = abs(data[it]);
}
if(max==0) max = 1;

int draw_point;
double insert_sum=0;

for(it = iteration, i = x+distance, draw_point=0;  draw_point < tmp_data_size; 
	i+=distance, it+=iteration, insert_sum +=insert, draw_point++)
{	
		_x = i-distance;								//икс отрисовки
		_y = data[(int)(it-iteration)];					//игрек значение из графика
		percent = (double)(_y*100);
		percent /= max;									//расчитываем его процент относительно екстремального значения (со знаком)
		_y = y + height/2 - percent*(height-20)/200;			//игрек отрисовки. начинаем рисовать от середины прямоугольника
														//и прибавляем процент от высоты всего прямоугольника (высота пополам)
		_x2 = i;
		_y2 = data[it];
		percent = (double)(_y2*100);
		percent /= max;
		_y2 = y + height/2 - percent*(height-20)/200;				

		GCP_Draw::drawLine(screen,w, h, GCP_Point(_x,_y),GCP_Point(_x2,_y2),c_red,0);

		if(insert_sum > 1)		{
			insert_sum = insert_sum-1;
			i+=1;
		}
}	

/*std::string stringstd;
MyMath::StringToStd(Convert::ToString(data_size),stringstd);		
SDL_Main::RenderTextToSurface(stringstd,x+width-50,y+height-20,screen,c_black,c_white);
MyMath::StringToStd(Convert::ToString(max),stringstd);	
SDL_Main::RenderTextToSurface(stringstd,x+5,y+5,screen,c_black,c_white);
SDL_Main::DrawRect(screen,PointD(x,y),PointD(x+width,y+height),c_black,1);
SDL_Main::DrawLine(screen,PointD(x,y+height/2),PointD(x+width,y+height/2),c_black,0);*/
}
/////////////////////////////////////////////////////////////////////////
///////////////////////DRAW RECTANGLE
/////////////////////////////////////////////////////////////////////////
void GCP_Draw::drawRect(SDL_Renderer* screen, int w, int h,  GCP_Point pointTopLeft, GCP_Point pointBottomRight, GCP_Color color, int bold)
{
	GCP_Draw::drawLine(screen, w, h, pointTopLeft, GCP_Point(pointBottomRight.X,pointTopLeft.Y),color,bold); 
	GCP_Draw::drawLine(screen, w, h, pointTopLeft, GCP_Point(pointTopLeft.X,pointBottomRight.Y),color,bold);
	GCP_Draw::drawLine(screen, w, h, pointBottomRight, GCP_Point(pointBottomRight.X,pointTopLeft.Y),color,bold);
	GCP_Draw::drawLine(screen, w, h, pointBottomRight, GCP_Point(pointTopLeft.X,pointBottomRight.Y),color,bold);
}
/////////////////////////////////////////////////////////////////////////
////////////////////////DRAW LINE
/////////////////////////////////////////////////////////////////////////
void GCP_Draw::drawLine(SDL_Renderer* screen, int w, int h, GCP_Point pointA, GCP_Point pointB, GCP_Color color, int bold)
{
	/////////////////////////////////////ЗАКОММЕНТИРОВАНА ПРОВЕРКА ВЫХОДА ЛИНИИ ЗА БУФЕР
	/////////////////////////////////////(НЕ ТРЕБУЕТСЯ В SDL2.0)
	////Отступ от границы экрана
	//int bs = 4; 
	//GCP_Point pointA_norm,pointB_norm;

	//pointA_norm = pointA;// = PointD(639,470);//pointA;  //557.178  565.636
	//pointB_norm = pointB;// = PointD(595.648,564.464);//pointB;  //559.089  -437.361

	//
	//bool isPointAinRect = GCP_Math::isInRect(pointA.X,pointA.Y,bs,bs,w,h);
	//bool isPointBinRect = GCP_Math::isInRect(pointB.X,pointB.Y,bs,bs,w,h);
	//
	//GCP_Vector<GCP_Point> R;
	////Если хоть одна точка выходит за границу поверхности
	//if ( !isPointAinRect || !isPointBinRect)	{
	//	//Найти все пересечения линии из точки А в точку Б с границами поверхности (*именно линии, а не луча)
	//	
	//	GCP_Math::lineRectIntersection(GCP_Point (bs,bs),GCP_Point (w-bs,bs),GCP_Point (bs,h-bs), GCP_Point (w-bs,h-bs),
	//								   GCP_Line(pointA,pointB),&R);

	//	switch(R.size())
	//	{
	//		case 0:
	//			//Видимо обе точки расположены вне поверхности. Рисовать нечего
	//			return;
	//			break;
	//		case 1:
	//			if(isPointAinRect)		{
	//				pointA_norm = pointA;
	//				pointB_norm = R[0];
	//			}
	//			else					{
	//				pointA_norm = R[0];
	//				pointB_norm = pointB;
	//			}
	//			break;
	//		case 2:
	//		case 3:	//В углах может найти две точки пересечения
	//			pointA_norm = R[0];
	//			pointB_norm = R[1];
	//			break;
	//	}
	//}

	////На все оставшиеся исключения
	//pointA_norm = GCP_Math::normalizePointInRect(pointA_norm,GCP_Point(bs,bs),GCP_Point(w-bs,h-bs));
	//pointB_norm = GCP_Math::normalizePointInRect(pointB_norm,GCP_Point(bs,bs),GCP_Point(w-bs,h-bs));
	



	//SLD2 автоматически обрабатывает исключение если мы рисуем линию за пределами буфера
	GCP_Point pointA_norm,pointB_norm;
	pointA_norm = pointA;
	pointB_norm = pointB;
	switch(bold)
	{
		case 0: 
			Draw_Line(screen,(int)pointA_norm.X,(int)pointA_norm.Y,(int)pointB_norm.X,(int)pointB_norm.Y,color); break;
		case 1: 			
			Draw_Line(screen,(int)pointA_norm.X,(int)pointA_norm.Y,(int)pointB_norm.X,(int)pointB_norm.Y,color); 
			Draw_Line(screen,(int)pointA_norm.X+1,(int)pointA_norm.Y,(int)pointB_norm.X+1,(int)pointB_norm.Y,color); 
			Draw_Line(screen,(int)pointA_norm.X-1,(int)pointA_norm.Y,(int)pointB_norm.X-1,(int)pointB_norm.Y,color); 
			Draw_Line(screen,(int)pointA_norm.X,(int)pointA_norm.Y+1,(int)pointB_norm.X,(int)pointB_norm.Y+1,color); 
			Draw_Line(screen,(int)pointA_norm.X,(int)pointA_norm.Y-1,(int)pointB_norm.X,(int)pointB_norm.Y-1,color); 
			break;
	}	 
}
/////////////////////////////////////////////////////////////////////////
////////////////////////RENDER TEXT TO SURFACE
/////////////////////////////////////////////////////////////////////////
void GCP_Draw::applySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend){
	//First we must create an SDL_Rect for the position of the image, as SDL
	//won't accept raw coordinates as the image's position
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	//We also need to query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(rend, tex, NULL, &pos);
}

SDL_Texture* GCP_Draw::_renderText(SDL_Renderer *renderer,GCP_DrawData* drawdata, std::string message, std::string fontFile, SDL_Color color, int fontSize){

	//!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!
	//НУЖНО РАЗОБРАТЬСЯ С ВЫВОДОМ ТЕКСТА
	//СДЛ ПЛОХО РИСУЕТ ТЕКСТ
	//ВОЗМОЖНО СТОИТ ПОИСКАТЬ ДРУГИЕ РЕШЕНИЯ НА OPENGL например в GLEW/GLUT
	//!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!

	SDL_Texture* texture;
	TTF_Font *font = NULL;
	font = TTF_OpenFont(fontFile.c_str(), fontSize);
	
	if (font == NULL)
		return texture;
		//throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());

	/*const std::string input = message;							// null-call to get the size
	size_t needed = ::mbstowcs(NULL,&input[0],input.length());	// allocate
	std::wstring output;
	output.resize(needed);										// real call
	::mbstowcs(&output[0],&input[0],input.length());			// You asked for a pointer
	const wchar_t *pout = output.c_str();
				
	//TTF_RenderUNICODE_Solid
	//TTF_RenderUTF8_Blended
	SDL_Surface *surf = TTF_RenderUNICODE_Solid(font,(Uint16*)pout,  color);	
	*/

	

	SDL_Surface *surf = TTF_RenderUTF8_Blended(font,message.c_str(),  color);
	/*texture = SDL_CreateTexture(renderer,
                                            SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            surf->w, surf->h);*/
	//SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);


		////Создадим прототип экрана	
		////Заполним его белым цветом  !! надо сделать прозрачн!
		//SDL_Surface* surf2 = SDL_CreateRGBSurface(0,surf->w, surf->h,32,0,0,0,0);
		//SDL_FillRect(surf2, &surf->clip_rect, SDL_MapRGBA(surf->format,255,255,255,0));

		//////Прозрачность НЕРАБОТАЕТ"!
		////Uint32 white = SDL_MapRGBA(drawdata->tscreen->format, 255, 255, 255,0);
		////SDL_SetColorKey(drawdata->tscreen, true, white);

		//////Нарисуем текст на прототип экрана
		//SDL_BlitSurface(surf,NULL,surf2,NULL);

		////Обновим текстуру для рендерера
		//SDL_UpdateTexture(texture, NULL, surf->pixels, surf->pitch);
		
		//SDL_UpdateTexture(texture, &surf->clip_rect, surf->pixels, surf->pitch);
		//texture = SDL_CreateTextureFromSurface(renderer, surf); //LOW PERFOMANCE USE UPDATE TEXTURE
		
		//Clean up unneeded stuff
		//SDL_FreeSurface(screen1);

	
		texture = SDL_CreateTextureFromSurface(renderer, surf); //LOW PERFOMANCE USE UPDATE TEXTURE		
		SDL_FreeSurface(surf);
		TTF_CloseFont(font);
		return texture;

	
}
void GCP_Draw::renderText(std::string Text, int x, int y, SDL_Renderer *renderer, GCP_DrawData* drawdata, GCP_Color text_color, string font_path, int font_size/*, bool isRussian=false*/)
{
	SDL_Color color = {text_color.r,text_color.g,text_color.b,text_color.a};
	SDL_Texture *image = NULL;
	GCP_Vector<std::string> *strings = GCP_Math::strToLines(Text);
		
	//Если текста было до этого выведено больше. Уменьшим размер кеша.
	if(drawdata != NULL)	{
			while(drawdata->text.size()>strings->size())
			{
				drawdata->text.pop_back();
				drawdata->theight.pop_back();
				drawdata->twidth.pop_back();
				drawdata->color.pop_back();
				SDL_DestroyTexture(drawdata->texture.pop_back());
			}
	}

	for(unsigned int j=0; j<strings->size(); j++)
	{

		if(drawdata == NULL)
		{
			//Если рисуем без кеширования то просто рендерим текст на екран
			image = _renderText(renderer, drawdata,strings->at(j), font_path, color, font_size);//20 should be defined by font size				
			applySurface(x, y+20*j, image, renderer);
			SDL_DestroyTexture(image);
		}else
		{
			//Иначе если используем кеширование
		if(drawdata->text.size()>j)			//Если у нас есть ячейка в кеше
		{
			if(drawdata->text[j] != strings->at(j) || drawdata->color[j] != text_color) //Если строки в ней разнятся
			{
				//Рисуем новый текст и выводим его на екран
				image = _renderText(renderer, drawdata,strings->at(j), font_path, color, font_size);//20 should be defined by font size
				applySurface(x, y+20*j, image, renderer);

				//Запоминаем какой теперь текст нарисован
				drawdata->text[j]=strings->at(j);				

				//Запоминаем его характеристики
				drawdata->twidth[j]=x;
				drawdata->theight[j]=y+20*j;
				drawdata->color[j]=text_color;

				//Очищаем прошлую память и заменяем ее новой
				SDL_DestroyTexture(drawdata->texture[j]);
				drawdata->texture[j]=image;
			}
			else
			{
				//Строки не разнятся рисуем прошлую память
				//Но сначала проверим не изменились ли координаты текста
				if(drawdata->twidth[j] != x)
					drawdata->twidth[j] = x;

				if(drawdata->theight[j] != y+20*j)
					drawdata->theight[j] = y+20*j;

				applySurface(drawdata->twidth[j], drawdata->theight[j], drawdata->texture[j], renderer);
			}
		}else
		{
			//Ячейки нет. надо ее создать
			image = _renderText(renderer, drawdata,strings->at(j), font_path, color, font_size);//20 should be defined by font size
			applySurface(x, y+20*j, image, renderer);

			drawdata->text.push_back(	strings->at(j));
			drawdata->texture.push_back( image);
			drawdata->twidth.push_back(x);
			drawdata->theight.push_back(y+20*j);
			drawdata->color.push_back(text_color);
		}
		}
	}

	delete strings;

}
/////////////////////////////////////////////////////////////////////////
/////////////////////////COLORS
/////////////////////////////////////////////////////////////////////////
void GCP_Draw::initConstants()
{
	//Константы не объявляются в некоторых компиляторах если находятся вне функций. пришлось сделать их прееменными
	c_white = GCP_Color(255, 255, 255);
	c_black = GCP_Color( 0, 0, 0);
	c_aquadark = GCP_Color( 121, 188, 255);
	c_yellow = GCP_Color( 255, 255, 128);
	c_red = GCP_Color( 255, 23, 23);
	c_blue = GCP_Color( 29, 23, 255);
	c_lime = GCP_Color( 60, 240, 50); 
	c_green =  GCP_Color( 10, 135, 3);
	c_aqua = GCP_Color( 64, 244, 231); 
	c_orange = GCP_Color( 255, 130, 5);
	c_grey = GCP_Color( 107, 107, 107);
}

//does not work when entry point defined
GCP_Color c_white = GCP_Color(255, 255, 255);
GCP_Color c_black = GCP_Color( 0, 0, 0);
GCP_Color c_aquadark = GCP_Color( 121, 188, 255);
GCP_Color c_yellow = GCP_Color( 255, 255, 128);
GCP_Color c_red = GCP_Color( 255, 23, 23);
GCP_Color c_blue = GCP_Color( 29, 23, 255);
GCP_Color c_lime = GCP_Color( 60, 240, 50); 
GCP_Color c_green =  GCP_Color( 10, 135, 3);
GCP_Color c_aqua = GCP_Color( 64, 244, 231); 
GCP_Color c_orange = GCP_Color( 255, 130, 5);
GCP_Color c_grey = GCP_Color( 107, 107, 107);
		
////////////////////////////////////////////////////////////////
////////////////////////TO SDL COLOR
////////////////////////////////////////////////////////////////
SDL_Color GCP_Draw::toSDLColor(Uint32 int_color)                                 
{
	//Change from an "int color" to an SDL_Color
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		SDL_Color color={(int_color & 0x00ff0000)/0x10000,(int_color &0x0000ff00)/0x100,(int_color & 0x000000ff),0};
	#else
		SDL_Color color={(int_color & 0x000000ff),(int_color &0x0000ff00)/0x100,(int_color & 0x00ff0000)/0x10000,0};    
	#endif
	return color;
}
////////////////////////////////////////////////////////////////
////////////////////////PRINT STRINGS
////////////////////////////////////////////////////////////////
SDL_Surface* GCP_Draw::printStrings(SDL_Surface *dest, TTF_Font *font,
							 std::string str, SDL_Rect &rc, SDL_Color clrFg,
							 SDL_Color clrBg, int flags ) 
{	
	
	//Старый код из SDL-Draw
	///* This function prints "str" with font "font" and color "clrFg"
	// * onto a rectangle of color "clrBg".
	// * It does not pad the text.
	// * If CREATE_SURFACE is NOT passed, the function returns NULL,
	// *otherwise, it returns an SDL_Renderer * pointer.
	// */

 // // If there's nothing to draw, return NULL:
	//if( str.length() == 0 || font == NULL ) {
	//return( NULL );
 // }

 // // This is the surface that everything is printed to.
 // SDL_Renderer *sText = NULL;
 // int lineSkip = TTF_FontLineSkip( font );
 // int width = 10, height = 10;
 // std::vector<std::string> vLines;
 // 
 // // Break the String into its lines:
 // int n = 0;
 // while( n != -1 ) {
	//// Get until either "\n" or "\0":
	//std::string strSub;

	//n = str.find('\\',0);  //replace \n text occurancies
	//if (n != -1 && str[n+1] == 'n')
	//{
	//	strSub = str.substr( 0,n );
	//	n = n+1;
	//}
	//else
	//{
	//	n = str.find( '\n', 0 );
	//	strSub = str.substr( 0,n );
	//}

	//if( n != -1 ) {
	//  str = str.substr( n+1, -1 );
	//}
	//vLines.push_back(strSub);
 //   
	//int w = 0;
	//// Get the size of the rendered text.
	//TTF_SizeText( font, strSub.c_str(), &w,&height );
	//if( w > width ) {  width = w;  }
 // }
 // 
 // // vLines.size() == Number of Lines.
 // // we assume that height is the same for all lines.
 // height = (vLines.size()-1) * lineSkip + height;
 // 
 // // dest CAN'T be NULL if you're creating the surface!
 // if( dest != NULL && (flags&PS_CREATE_SURFACE) ) {
	//printf("dest != NULL with PS_CREATE_SURFACE!\n");
	//return(NULL);
 // }
 // if( dest == NULL ) {
	//if( flags&PS_CREATE_SURFACE ) {
	//  // Create a "dest" to which to print:
	//  dest = SDL_CreateRGBSurface( SDL_SWSURFACE, width,height, 1, 0,0,0,0 );
	//} else {
	//  printf("There was no surface.\n(Exiting function...)\n");
	//  return(NULL);
	//}
 // }
 // 
 // sText = SDL_CreateRGBSurface( SDL_SWSURFACE, width,height,
	//dest->format->BitsPerPixel, dest->format->Rmask,dest->format->Gmask,
	//dest->format->Bmask,dest->format->Amask );

 // // Color in the rectangle on the destination:
 // if( flags &PS_TRANSPARENT_BG ) {
	//// If the fg & bg colors are the same, we need to fix it:
	///*if( clrFg == clrBg ) {
	//  if( clrFg == BLACK ) {
	//	clrBg = WHITE;
	//  } else {
	//	clrBg = BLACK;
	//  }
	//}*/
	//  
	//  /*
	//SDL_FillRect( sText,NULL,
	//  SDL_MapRGB(sText->format,clrBg.r,clrBg.g,clrBg.b) );
	//	SDL_SetColorKey( sText, SDL_SRCCOLORKEY|SDL_RLEACCEL,
	//	 SDL_MapRGB(sText->format,clrBg.r,clrBg.g,clrBg.b) );*/

	//  SDL_FillRect( sText,NULL, SDL_MapRGB(sText->format,clrBg.r,clrBg.g,clrBg.b) );

 // } else {
	//SDL_FillRect( sText,NULL, SDL_MapRGB(sText->format,clrBg.r,clrBg.g,clrBg.b) );
 // }
 // 
 // 
 // // Actually render the text:
 // SDL_Renderer *sTemp = NULL;
 // for( unsigned int i = 0; i < vLines.size(); i++ ) {
	//// The rendered text:
	//if( flags & PS_BLENDED ) {
	//  sTemp = TTF_RenderText_Blended( font, vLines[i].c_str(), clrFg );
	//} else {
	//  sTemp = TTF_RenderText_Solid ( font, vLines[i].c_str(), clrFg );
	//}
 //   
	//
	//// Put it on the surface:
	//if( (flags&PS_ALIGN_LEFT) ||
	//	 !(flags&PS_ALIGN_CENTER ||
	//	 flags&PS_ALIGN_RIGHT) ) {
	//  // If it's specifically LEFT or none of the others:
	//  SDL_Rect rect = {0,i*lineSkip,0,0};
	//  SDL_BlitSurface( sTemp,NULL, sText,
	//	  &(SDL_Rect) rect );
	//}
	//if( flags & PS_ALIGN_CENTER ) {
	//  int w = 0, h = 0; TTF_SizeText( font, vLines[i].c_str(), &w,&h );
	//  SDL_Rect rect = {width/2-w/2,i*lineSkip,0,0};
	//  SDL_BlitSurface( sTemp,NULL, sText,
	//	  &(SDL_Rect) rect );
	//}
	//if( flags & PS_ALIGN_RIGHT ) {
	//  printf("ERROR: PrintStrings()::PS_ALIGN_RIGHT:"
	//	  "Oops, this hasn't been implemented yet\n");
	//}
	//// Clean up:
	//SDL_FreeSurface( sTemp );
 // }
 // 
 // if( flags & PS_CREATE_SURFACE ) {
	//SDL_FreeSurface( dest );
	//return( sText );
 // }
 // 
 // // Draw the text on top of that:

	////Transparent
 //  //SDL_SetAlpha( sText, SDL_SRCALPHA, SDL_ALPHA_OPAQUE ); 
	////apply_surface( 0, 0, back, screen ); 
	////apply_surface( 0, 0, front, screen );*/

 // SDL_BlitSurface( sText,NULL, dest,&rc );
 // SDL_FreeSurface( sText );
  return(NULL);
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////




