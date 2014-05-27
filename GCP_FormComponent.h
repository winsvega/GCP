#ifndef GCP_FormComponentH
#define GCP_FormComponentH

#include "GCP_Draw.h"
#include "GCP_Delegate.h"
#include "GCP_SPointer.h"

class GCP_FormComponent;

//template<class T>
//GCP_SPointer<T>::operator GCP_SPointer<GCP_FormComponent> () 
//{
//	GCP_SPointer<GCP_FormComponent> sliced = GCP_SPointer<GCP_FormComponent>(static_cast<GCP_FormComponent>_pointee);
//	return sliced;
//}

//Информация о стиле 
struct SStyle : public GCP_SPointerBase
{
	public:
	SStyle(){}
	SStyle(GCP_Color cBackColor_,GCP_Color cTextColor_,GCP_Color cBackColorHover_,GCP_Color cTextColorHover_,
		  GCP_Color  cBorderColor_ = c_black, GCP_Color colorHeadMenuBackground_ = c_black, 
		  GCP_Color colorHeadMenuFade_ = c_grey, GCP_Color colorButtonBackground_ = c_white)		  
	{
		setColor(cBackColor_, cTextColor_, cBackColorHover_, cTextColorHover_);
		iBorderWidth = 2;
		iRoundCff = 7;
		//Афтоинициализация параметров для формы
		cBorderColor = cBorderColor_;
		colorHeadMenuBackground = colorHeadMenuBackground_;
		colorHeadMenuFade = colorHeadMenuFade_;
		colorButtonBackground = colorButtonBackground_;
	}

	void setColor(GCP_Color cBackColor_,GCP_Color cTextColor_,GCP_Color cBackColorHover_,GCP_Color cTextColorHover_)
	{
		cBackColor = cBackColor_;
		cTextColor = cTextColor_;
		cBackColorHover = cBackColorHover_;
		cTextColorHover = cTextColorHover_;
	}
	
	GCP_Color cBackColor;				//Фон
	GCP_Color cTextColor;				//Цвет текста
	GCP_Color cBackColorHover;			//Фон при наведении
	GCP_Color cTextColorHover;			//Цвет текста при наведении
	GCP_Color cBorderColor;				//Цвет рамки
	
	int iBorderWidth;					//Толщина рамки
	Uint16 iRoundCff;					//Округление углов

	int iTextSize, iMaxTextLength;		//Параметры текста в едитах
	GCP_Color cTextFieldBackColor;		//Фон поля ввода текстов

										//Параметры для форм
	GCP_Color colorHeadMenuBackground, colorHeadMenuFade, colorButtonBackground;
	
	//string sFontDir;					//Путь к шрифтам !!!REV	
	static string sFontDir;	
};

//Сделать как цветовые константы!!//REV
struct defaultStyles
{
	public:
		defaultStyles()/*:
			defaultbuttonStyle (new SStyle(c_white,c_black,c_aquadark,c_white)),
			defaultbuttonInvStyle ( new SStyle(c_black,c_white,c_aquadark,c_white)),
			defaultMenuStyle  ( new SStyle(c_white, c_black,c_aquadark,c_white)),
			defaultMenuStyleBlack  ( new SStyle(c_white, c_black,c_aquadark,c_black)),
			defaultFormHeaderStyle  ( new SStyle(c_black, c_black,c_black,c_black)),
			defaultFormStyle  (new SStyle(c_white, c_black, c_white, c_black))*/
		{
			/*defaultbuttonStyle = new SStyle(c_white,c_black,c_aquadark,c_white);
			defaultbuttonInvStyle = new SStyle(c_black,c_white,c_aquadark,c_white);
			defaultMenuStyle  = new SStyle(c_white, c_black,c_aquadark,c_white);
			defaultMenuStyleBlack  = new SStyle(c_white, c_black,c_aquadark,c_black);
			defaultFormHeaderStyle  = new SStyle(c_black, c_black,c_black,c_black);
			defaultFormStyle  =new SStyle(c_white, c_black, c_white, c_black);*/

			defaultbuttonStyle = SStyle(c_white,c_black,c_aquadark,c_white);
			defaultbuttonInvStyle =  SStyle(c_black,c_white,c_aquadark,c_white);
			defaultMenuStyle  = SStyle(c_white, c_black,c_aquadark,c_white);
			defaultMenuStyleBlack  = SStyle(c_white, c_black,c_aquadark,c_black);
			defaultFormHeaderStyle  =  SStyle(c_black, c_black,c_black,c_black);
			defaultFormStyle  =SStyle(c_white, c_black, c_white, c_black);
		}
		~defaultStyles()
		{
			//delete defaultMenuStyle, defaultMenuStyleBlack, defaultFormHeaderStyle, defaultbuttonStyle, defaultFormStyle;
			//delete defaultbuttonInvStyle;
		}
	//Make Private!!!
	SStyle defaultMenuStyle;
	SStyle defaultMenuStyleBlack;
	SStyle defaultFormHeaderStyle;
	SStyle defaultbuttonStyle, defaultbuttonInvStyle;
	SStyle defaultFormStyle;
};
extern defaultStyles defStyles;



//Информация о компоненте 
struct SPoint
{
	int x,y;
	int width,height;
	std::string icon;
};

//Структура для сортировки компонетнов
struct SComponent
{
	int draw_order;
};

//событие внутри формы. возвращает состояние самой формы
struct gcp_formEvent		
{
	bool isFormDragged;
	bool isEventInsideForm;
	bool isEventOnFormHead;
};

//Сдлные события
struct sdl_events
{
	SDL_KeyboardEvent keyboard;
	SDL_MouseButtonEvent mousebutton;
	SDL_TextEditingEvent textediting;
	SDL_TextInputEvent textinput;
	SDL_MouseWheelEvent mouswheel;
	SDL_MouseMotionEvent mousemotion;
	int mousex;
	int mousey;
	bool isPassingOnlyGlobalEvent;
};

//Константы
const int GCP_SORTBY_DRAWORDER = 1;
const int GCP_SORTBY_EVENTORDER = 2;

//event - глобальное событие event+1 - локальное событие
const int GCP_ON_GLEFT_CLICK = 1;
const int GCP_ON_LEFT_CLICK = 2;
const int GCP_ON_GRIGHT_CLICK = 3;
const int GCP_ON_RIGHT_CLICK = 4;
const int GCP_ON_WHELL_GUP = 5;
const int GCP_ON_WHELL_UP = 6;
const int GCP_ON_WHELL_GDOWN = 7;
const int GCP_ON_WHELL_DOWN = 8;
const int GCP_ON_MOUSE_GDOWN = 9;
const int GCP_ON_MOUSE_DOWN = 10;
const int GCP_ON_MOUSE_GLDOWN = 11;
const int GCP_ON_MOUSE_LDOWN = 12;
const int GCP_ON_MOUSE_GUP = 13;
const int GCP_ON_MOUSE_UP = 14;
const int GCP_ON_MOUSE_GMOTION = 15;
const int GCP_ON_MOUSE_MOTION = 16;
const int GCP_ON_GKEYDOWN = 17;
const int GCP_ON_KEYDOWN = 18;
const int GCP_ON_GDRAG = 19;
const int GCP_ON_DRAG = 20;
const int GCP_ON_MOUSE_GLHMOTION = 21;
const int GCP_ON_MOUSE_LHMOTION = 22;
const int GCP_MAX_FUNC_NUM = 23;


class GCP_FormComponent: public GCP_SPointerBase
{
	protected:
		std::string _sCaption;						//Надпись
		IContainer* FUNCTIONS[GCP_MAX_FUNC_NUM];	//Функции навешаные на события	

		bool _isMouseOver;
		bool _isMouseHold;
		bool _isDragStarted;
		string _sTextInput;
		int _timeMouseOver;							//Таймер мыши для всплывающей подсказки
		SStyle *style;

	public:		
		static void initStyles(){defStyles = defaultStyles();}
		bool compare(const GCP_FormComponent* right, int compare, int criteria = -1)
		{
			//Метод по которому сравниваются елементы в сортировке кусорт
			switch (compare)
			{
				case 1:	// <
					switch(criteria)					{
						case GCP_SORTBY_DRAWORDER:
							return (options.draw_order > right->options.draw_order);
						case GCP_SORTBY_EVENTORDER:
							return (options.draw_order < right->options.draw_order);
					}
				case 2:	// >
					switch(criteria)					{
						case GCP_SORTBY_DRAWORDER:
							return (options.draw_order < right->options.draw_order);
						case GCP_SORTBY_EVENTORDER:
							return (options.draw_order > right->options.draw_order);
					}
				case 3:	// =
					switch(criteria)					{
						case GCP_SORTBY_DRAWORDER:
						case GCP_SORTBY_EVENTORDER:
							return (options.draw_order == right->options.draw_order);
					}
			}
			return false;
		}
	

	
	
		GCP_FormComponent()
		{
			_sCaption = "";									//Надпись
			_sTextInput = "";								//Введенный текст
			style = NULL;
			//sFontDir = "data\\arial.ttf";					//Путь к шрифту (умолчание) 
			INFO = "";										//Всплывающая подсказка
			options.draw_order = 0;							//Порядок отрисовки
			_isMouseOver = false;  _isMouseHold = false;
			isLocalEventsUnderneathBlocking = true;			//Блокировать обработку локальных событий у других компонет, которые находятся по этим
			

			isDragable = false;								//Перетаскивание
			_isDragStarted = false;		

			for(int i=0; i<GCP_MAX_FUNC_NUM; i++)			//Функции надо обнулить иначе память тютю
				FUNCTIONS[i] = 0;

			collisionBox = GCP_COLLISIONBOX_RECTANGLE;		//Обработка столкновений
			isVisible = true;			
			//icon = "";										//Путь к картинке
			width = 100;
			height = 20;
			xPos = 0; 
			yPos = 0;
			xPosStart = xPos; //!
			yPosStart = yPos;
			//iRoundCff = 2;									//Округление границ
			collisionRadius = 5;							//Если рисуется круг
			_timeMouseOver = 0;
			//setColor(c_black,c_white,c_aquadark,c_white);	//Задает цвета
		}

		~GCP_FormComponent()
		{
			//Указатели надо удалить 
			for(int i=0; i<GCP_MAX_FUNC_NUM; i++)
				if(FUNCTIONS[i]!=0)
					delete FUNCTIONS[i];			
		}

		virtual void OnDraw(SDL_Renderer* screen, int screen_w, int screen_h, int fx, int fy, int fw, int fh){basicOnDraw(screen, fx, fy, fw, fh);};

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////SET AND BASIC FUNCTIONS
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////
		/////////////////////////LEFT CLICK
		////////////////////////////////////////
		//ТУТ НАВЕШИВАЮТСЯ ОБРАБОТЧИКИ НА СОБЫТИЯ
		template< class T, class U > void setOnMouseGlobalLeftClick(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_GLEFT_CLICK]!=0) delete FUNCTIONS[GCP_ON_GLEFT_CLICK];
			FUNCTIONS[GCP_ON_GLEFT_CLICK] = new Container< T, U > ( i_class, i_method);
		}
		template< class T, class U> void setOnMouseLeftClick(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_LEFT_CLICK]!=0) delete FUNCTIONS[GCP_ON_LEFT_CLICK];
			FUNCTIONS[GCP_ON_LEFT_CLICK] = new Container< T, U > ( i_class, i_method);
		}
		////////////////////////////////////////
		/////////////////////////RIGHT CLICK
		////////////////////////////////////////
		template< class T, class U > void setOnMouseGlobalRightClick(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_GRIGHT_CLICK]!=0) delete FUNCTIONS[GCP_ON_GRIGHT_CLICK];
			FUNCTIONS[GCP_ON_GRIGHT_CLICK] = new Container< T, U > ( i_class, i_method);
		}
		template< class T, class U > void setOnMouseRightClick(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_RIGHT_CLICK]!=0) delete FUNCTIONS[GCP_ON_RIGHT_CLICK];
			FUNCTIONS[GCP_ON_RIGHT_CLICK] = new Container< T, U > ( i_class, i_method);
		}
		////////////////////////////////////////
		/////////////////////////MOUSE WHELL
		////////////////////////////////////////
		template< class T, class U > void setOnMouseGlobalWheelDown(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_WHELL_GDOWN]!=0) delete FUNCTIONS[GCP_ON_WHELL_GDOWN];
			FUNCTIONS[GCP_ON_WHELL_GDOWN] = new Container< T, U > ( i_class, i_method);
		}
		template< class T, class U > void setOnMouseWheelDown(T* i_class, U i_method)		{
			if(FUNCTIONS[GCP_ON_WHELL_DOWN]!=0) delete FUNCTIONS[GCP_ON_WHELL_DOWN];
			FUNCTIONS[GCP_ON_WHELL_DOWN] = new Container< T, U > ( i_class, i_method);
		}

		template< class T, class U > void setOnMouseGlobalWheelUp(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_WHELL_GUP]!=0) delete FUNCTIONS[GCP_ON_WHELL_GUP];
			FUNCTIONS[GCP_ON_WHELL_GUP] = new Container< T, U > ( i_class, i_method);
		}
	
		template< class T, class U > void setOnMouseWheelUp(T* i_class, U i_method)		{
			if(FUNCTIONS[GCP_ON_WHELL_UP]!=0) delete FUNCTIONS[GCP_ON_WHELL_UP];
			FUNCTIONS[GCP_ON_WHELL_UP] = new Container< T, U > ( i_class, i_method);
		}
		////////////////////////////////////////
		/////////////////////////MOUSE DOWN
		////////////////////////////////////////
		template< class T, class U > void setOnMouseGlobalDown(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_MOUSE_GDOWN]!=0) delete FUNCTIONS[GCP_ON_MOUSE_GDOWN];
			FUNCTIONS[GCP_ON_MOUSE_GDOWN] = new Container< T, U > ( i_class, i_method);
		}
		template< class T, class U > void setOnMouseGlobalLeftDown(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_MOUSE_GLDOWN]!=0) delete FUNCTIONS[GCP_ON_MOUSE_GLDOWN];
			FUNCTIONS[GCP_ON_MOUSE_GLDOWN] = new Container< T, U > ( i_class, i_method);
		}
		template< class T, class U > void setOnMouseLeftDown(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_MOUSE_LDOWN]!=0) delete FUNCTIONS[GCP_ON_MOUSE_LDOWN];
			FUNCTIONS[GCP_ON_MOUSE_LDOWN] = new Container< T, U > ( i_class, i_method);
		}

		template< class T, class U > void setOnMouseGlobalLeftHoldMotion(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_MOUSE_GLHMOTION]!=0) delete FUNCTIONS[GCP_ON_MOUSE_GLHMOTION];
			FUNCTIONS[GCP_ON_MOUSE_GLHMOTION] = new Container< T, U > ( i_class, i_method);
		}
		template< class T, class U > void setOnMouseLeftHoldMotion(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_MOUSE_LHMOTION]!=0) delete FUNCTIONS[GCP_ON_MOUSE_LHMOTION];
			FUNCTIONS[GCP_ON_MOUSE_LHMOTION] = new Container< T, U > ( i_class, i_method);
		}

		////////////////////////////////////////
		/////////////////////////MOUSE UP
		////////////////////////////////////////
	
		template< class T, class U > void setOnMouseGlobalUp(T* i_class, U i_method)		{
			if(FUNCTIONS[GCP_ON_MOUSE_GUP]!=0) delete FUNCTIONS[GCP_ON_MOUSE_GUP];
			FUNCTIONS[GCP_ON_MOUSE_GUP] = new Container< T, U > ( i_class, i_method);
		}
		template< class T, class U > void setOnMouseUp(T* i_class, U i_method)		{
			if(FUNCTIONS[GCP_ON_MOUSE_UP]!=0) delete FUNCTIONS[GCP_ON_MOUSE_UP];
			FUNCTIONS[GCP_ON_MOUSE_UP] = new Container< T, U > ( i_class, i_method);
		}

		template< class T, class U > void setOnMouseMotion(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_MOUSE_MOTION]!=0) delete FUNCTIONS[GCP_ON_MOUSE_MOTION];
			FUNCTIONS[GCP_ON_MOUSE_MOTION] = new Container< T, U > ( i_class, i_method);
		}
		template< class T, class U > void setOnGlobalMouseMotion(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_MOUSE_GMOTION]!=0) delete FUNCTIONS[GCP_ON_MOUSE_GMOTION];
			FUNCTIONS[GCP_ON_MOUSE_GMOTION] = new Container< T, U > ( i_class, i_method);		}

		////////////////////////////////////////
		/////////////////////////MOUSE MOTION
		////////////////////////////////////////		
		template< class T, class U > void setOnDrag(T* i_class, U i_method )		{
			if(FUNCTIONS[GCP_ON_DRAG]!=0) delete FUNCTIONS[GCP_ON_DRAG];
				FUNCTIONS[GCP_ON_DRAG] = new Container< T, U > ( i_class, i_method);
		}		
		
		template< class T, class U > void setOnKeyDown(T* i_class, U i_method)		{
			if(FUNCTIONS[GCP_ON_GKEYDOWN]!=0) delete FUNCTIONS[GCP_ON_GKEYDOWN];
				FUNCTIONS[GCP_ON_GKEYDOWN] = new Container< T, U > ( i_class, i_method);
		}

		//РИСУЕМ ВСПЛЫВЮЩУЮ ПОДСКАЗКУ
		void OnDrawInfo(SDL_Renderer* screen, int formx, int formy, int formw, int formh) {
			//ПОКА ЧТО КРИВО НО РАБОТАЕТ
			if(INFO!="" && _isMouseOver){
				int mess_w, mess_h;
				string fonts = getFont().c_str();
				TTF_Font* font = TTF_OpenFont(getFont().c_str(), 14);

				//Вычисление ширины и высоты текста				
				GCP_Vector<string>* strings = GCP_Math::strToLines(INFO);
				int maxSize=0, maxSizeIndex=-1;
				for(int i=0; i<strings->size(); i++)
				{
					if(strings->at(i).length() > maxSize){
						maxSize = strings->at(i).length();
						maxSizeIndex = i;
					}
				}
				if(maxSizeIndex == -1)
					return;

				TTF_SizeUTF8(font, strings->at(maxSizeIndex).c_str(), &mess_w, &mess_h);	
				mess_w += 5;	mess_h += 5;
				//mess_w /= strings->size();
				mess_h *= strings->size();
				delete strings;


				TTF_CloseFont(font);
				GCP_Point normPos = GCP_Math::normalizeRectInRect(GCP_Point(formx,formy),
									GCP_Point(formx+formw,formy+formh),xPos+10,yPos+10,mess_w,mess_h,1);

				SDL_SetRenderDrawBlendMode(screen,SDL_BLENDMODE_BLEND);
				GCP_Color c_white_a(255,255,255,210);
				GCP_Draw::Draw_FillRect(screen,(Sint16)normPos.X,(Sint16)normPos.Y,mess_w,mess_h,c_white_a);
				SDL_SetRenderDrawBlendMode(screen,SDL_BLENDMODE_NONE);
				GCP_Draw::Draw_Rect(screen,(Sint16)normPos.X,(Sint16)normPos.Y,mess_w,mess_h,c_black);
				GCP_Draw::renderText(INFO,(int)normPos.X+3,(int)normPos.Y+3,screen,&drawdatainfo,c_black,getFont(),14);			
			}

		}

		void basicOnDraw(SDL_Renderer* screen, int formx, int formy, int formw, int formh) {	}
		
		void basicOnTextInput(SDL_TextInputEvent text)
		{
			_sTextInput += text.text;
		}
		void basicOnTextEdit(SDL_TextEditingEvent edit)
		{
			_sTextInput = edit.text;
		}

		void basicOnMouseLeftHoldMotion(SDL_MouseMotionEvent motion, int fx, int fy, int fw, int fh)
		{
			if(FUNCTIONS[GCP_ON_MOUSE_LHMOTION] != 0)
			FUNCTIONS[GCP_ON_MOUSE_LHMOTION]->Call((void*)this);
		}

		void basicOnDrag(SDL_MouseMotionEvent motion, int fx, int fy, int fw, int fh)
		{
			if(FUNCTIONS[GCP_ON_DRAG] != 0)
			FUNCTIONS[GCP_ON_DRAG]->Call((void*)this);
		}

		void basicOnMouseGlobalLeftHoldMotion(SDL_MouseMotionEvent motion, int fx, int fy, int fw, int fh)
		{
			if(_isDragStarted){
				xPos = motion.x;
				yPos = motion.y;
				_isMouseHold = true;

				switch(collisionBox){
					case GCP_COLLISIONBOX_RECTANGLE: 
						xPos = max(fx,min(fx+fw-width,(int)xPos));
						yPos = max(fy,min(fy+fh-height,(int)yPos));
						break;
					case GCP_COLLISIONBOX_ROUNDCIRCLE:
						xPos = max(fx+collisionRadius+10,min(fx+fw-collisionRadius-10,(int)xPos));
						yPos = max(fy+collisionRadius+10,min(fy+fh-collisionRadius-10,(int)yPos));
						break;
				}
				basicOnDrag(motion, fx, fy, fw, fh);
			}
			if(FUNCTIONS[GCP_ON_MOUSE_GLHMOTION] != 0)
			FUNCTIONS[GCP_ON_MOUSE_GLHMOTION]->Call((void*)this);
			return;

		}


		////////////////////////////////////////////////////////////////////
		
		void basicOnEvent(const int GCP_EVENT, sdl_events events)
		{
			switch(GCP_EVENT)
			{
				case GCP_ON_MOUSE_GMOTION:
					if (_isMouseHold == false) 
						_isMouseOver = false; //assume mouse is out of collision rect
				break;
				case GCP_ON_MOUSE_MOTION:
					_isMouseOver = true;
					_timeMouseOver++;
				break;
				case GCP_ON_MOUSE_GUP:
					_isMouseHold = false;
					break;
				case GCP_ON_MOUSE_GLDOWN:
					_isDragStarted = false;
					break;
				

			}

			if(FUNCTIONS[GCP_EVENT] != 0)
			FUNCTIONS[GCP_EVENT]->Call((void*)this);
		}

		virtual gcp_formEvent OnEvent(const int GCP_EVENT, sdl_events events)
		{
			basicOnEvent(GCP_EVENT, events);
			gcp_formEvent evt; evt.isEventInsideForm = false; return evt;
		}
		
		virtual bool OnTextEdit(SDL_TextEditingEvent edit){basicOnTextEdit(edit); return true;}
		virtual bool OnTextInput(SDL_TextInputEvent text){basicOnTextInput(text); return true;}
		virtual bool OnMouseGlobalLeftHoldMotion(SDL_MouseMotionEvent motion, int fx, int fy, int fw, int fh)	{	basicOnMouseGlobalLeftHoldMotion(motion, fx, fy, fw, fh);	return true;}
		virtual bool OnMouseLeftHoldMotion(SDL_MouseMotionEvent motion, int fx, int fy, int fw, int fh)	{
			if (isDragable)
				_isDragStarted = true;
			basicOnMouseLeftHoldMotion(motion,fx,fy,fw,fh);
			return true;
		}


		virtual void setIcon(std::string path)
		{
			icon = path;			
		}

		virtual void setCaption(std::string str)	{	_sCaption = str;	}
		virtual void setPosition(int x, int y)		{	xPos = x; 	yPos = y;  
			xPosStart   = x;
			yPosStart   = y;///!
		}
		virtual void setWidthHeight(int w, int h)	{	width = w; 	height = h;	}
		virtual void setVisible(bool visibility)	{	isVisible = visibility;	}
		virtual void setFont(string dir)			{	//if(style!= NULL) style->sFontDir = dir;	//!REV
													}
		virtual void setStyle(SStyle *style_)	{
			style = style_;
		}
		virtual SStyle *getStyle()				{	
			if (style!= NULL)
			return style;
			else return &defStyles.defaultbuttonStyle;
		} 

	
		virtual string getFont()			{	
													//Если есть стиль
													//Если в стиле указан шрифт, используем его
													//Иначе стиль по умолчанию
													if (style!= NULL) return style->sFontDir; //!REV													
													return SStyle::sFontDir;
		}
		
		virtual std::string getCaption()	{	return _sCaption;	}

		virtual SPoint getPosition()		{
			SPoint Position;		
			Position.x = xPos;
			Position.y = yPos;
			Position.width = width;
			Position.height = height;
			Position.icon = icon;	
			return Position;
		}

		bool checkCollisionBox(double mousex, double mousey)
		{
			SPoint compPos = getPosition();
			bool flag = false;
			switch(collisionBox){
				case GCP_COLLISIONBOX_RECTANGLE: 
					if(GCP_Math::isInRect(mousex,mousey,compPos.x,compPos.y,compPos.width,compPos.height))
						flag = true;
					break;
				case GCP_COLLISIONBOX_ROUNDCIRCLE:
					if (GCP_Math::isInRadius(compPos.x, compPos.y, mousex, mousey, collisionRadius))
						flag = true;
					break;
			}
			return flag;
		}

		virtual void initTexture(SDL_Renderer* screen)
		{
			//Эта функция вызывается только для тех елементов, которые выводят на экран текст
			//Для них нужно заранее создать текстуру и поверхность чтобы не создавать их каждый раз при рендеренге
			/*drawdata.texture = SDL_CreateTexture(screen,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,width,height);
			drawdata.tscreen = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
			drawdata.twidth = width;
			drawdata.theight = height;			*/
		}


		Sint16 width, height, collisionRadius;
		int xPos, yPos, xPosStart, yPosStart;
		int collisionBox;
		
		bool isVisible, isDragable;	
		bool isLocalEventsUnderneathBlocking;
		SComponent options;

		std::string icon;					//Путь к иконке кнопки
		std::string INFO;					//Всплывающая подсказка

		GCP_DrawData drawdata;		
		GCP_DrawData drawdatainfo;
		

};

#endif