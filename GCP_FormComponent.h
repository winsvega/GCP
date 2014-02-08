#ifndef GCP_FormComponentH
#define GCP_FormComponentH

#include "GCP_Draw.h"
#include "GCP_Delegate.h"



struct point
{
	int x,y;
	int width,height;
	std::string icon;
};
struct component
{
	int draw_order;

};

struct gcp_formEvent		
{
	bool isFormDragged;
	bool isEventInsideForm;
	bool isEventOnFormHead;
};


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

const int GCP_SORTBY_DRAWORDER = 1;
const int GCP_SORTBY_EVENTORDER = 2;



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


class GCP_FormComponent
{
	protected:
		std::string _sCaption;
		IContainer* FUNCTIONS[GCP_MAX_FUNC_NUM];

		

		bool _isMouseOver;
		bool _isMouseHold;
		bool _isDragStarted;
		string _sTextInput;
		int _timeMouseOver;
		

	public:
		//GCP_FormComponent* _OnRightClickContextMenu;
		bool compare(const GCP_FormComponent* right, int compare, int criteria = -1)
		{
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
			_sCaption = "";
			_sTextInput = "";
			sFontDir = "data\\arial.ttf";
			INFO = "";
			options.draw_order = 0;
			_isMouseOver = false;  _isMouseHold = false;
			isLocalEventsUnderneathBlocking = true;
			

			isDragable = false;
			_isDragStarted = false;		

			for(int i=0; i<GCP_MAX_FUNC_NUM; i++)
				FUNCTIONS[i] = 0;

			collisionBox = GCP_COLLISIONBOX_RECTANGLE;
			isVisible = true;
			icon = "";
			width = 100;
			height = 20;
			xPos = 0; 
			yPos = 0;
			xPosStart = xPos; //!
			yPosStart = yPos;
			iRoundCff = 2;
			collisionRadius = 5;
			_timeMouseOver = 0;
			setColor(c_black,c_white,c_aquadark,c_white);
		}

		~GCP_FormComponent()
		{
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

		void OnDrawInfo(SDL_Renderer* screen, int formx, int formy, int formw, int formh) {

			if(INFO!="" && _isMouseOver){
				int mess_w, mess_h;
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


		virtual void setIcon(std::string path)		{	icon = path;	}
		virtual void setCaption(std::string str)	{	_sCaption = str;	}
		virtual void setPosition(int x, int y)		{	xPos = x; 	yPos = y;  
			xPosStart   =x;
			yPosStart   = y;///!
		}
		virtual void setWidthHeight(int w, int h)	{	width = w; 	height = h;	}
		virtual void setVisible(bool visibility)	{	isVisible = visibility;	}
		virtual void setFont(string dir)			{	sFontDir = dir;	}
		virtual string getFont()			{	return sFontDir;	}
		virtual std::string getCaption()	{	return _sCaption;	}

		virtual point getPosition()		{
			point Position;
		
			Position.x = xPos;
			Position.y = yPos;
			Position.width = width;
			Position.height = height;
			Position.icon = icon;
			return Position;
		}

		virtual void setColor(GCP_Color _cBackColor,GCP_Color _cTextColor,GCP_Color _cBackColorHover,GCP_Color _cTextColorHover)
		{
			cBackColor = _cBackColor;
			cTextColor = _cTextColor;
			cBackColorHover = _cBackColorHover;
			cTextColorHover = _cTextColorHover;
		}

		bool checkCollisionBox(double mousex, double mousey)
		{
			point compPos = getPosition();
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

		GCP_Color cBackColor, cTextColor, cBackColorHover, cTextColorHover;
		GCP_Color cBorderColor;
		int iBorderWidth;

		Uint16 iRoundCff;
		string sFontDir;
		Sint16 width, height, collisionRadius;
		int xPos, yPos, xPosStart, yPosStart;
		int collisionBox;
		std::string icon;
		bool isVisible, isDragable;	
		bool isLocalEventsUnderneathBlocking;
		component options;
		

		GCP_DrawData drawdata;
		std::string INFO;
		GCP_DrawData drawdatainfo;

};

#endif