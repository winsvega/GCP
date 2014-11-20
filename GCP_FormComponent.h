#ifndef GCP_FormComponentH
#define GCP_FormComponentH

#include "GCP_Draw.h"
#include "GCP_Delegate.h"
#include "GCP_SPointer.h"

class GCP_FormComponent;
typedef GCP_SPointer<GCP_FormComponent> gcp_spFormComponent;

class GCP_FormComponent: public GCP_SPointerBase
{
	protected:		
      bool _isLocalEventsUnderneathBlocking;
      bool _isVisible, _isDragable;
      bool _isStartPositionSet;
		bool _isMouseOver;                        //Триггер мышь над объектом
		bool _isMouseHold;                        //Триггер левая клавиша мыши зажата над объектом
		bool _isDragStarted;                      //Триггер начали перетаскивать объект		
		int _timeMouseOver;							   //Таймер для всплывающей подсказки

		gcp_spStyle pStyle;
      GCP_Rect _position;
      IContainer* FUNCTIONS[GCP_MAX_FUNC_NUM];	//Функции навешаные на события

      static const GCP_Event MakeEventLocal(const GCP_Event& event)
      {
         GCP_Event evt = event;
         evt.eventType++;
         return evt;
      }

   public:
      int collisionRadius;
      int xPosStart, yPosStart;
      int collisionBox;

      SComponent options;
      std::string icon;					//Путь к иконке кнопки
      std::string INFO;					//Всплывающая подсказка

      GCP_DrawData drawdata;
      GCP_DrawData drawdatainfo;

	public:
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
         pStyle = GCP_DefaultStyle;
			options.draw_order = 0;						      //Порядок отрисовки
			_isMouseOver = false;
         _isMouseHold = false;
         _isStartPositionSet = false;
			_isLocalEventsUnderneathBlocking = true;		//Блокировать обработку локальных событий у других компонет, которые находятся по этим         
			_isDragable = false;								   //Перетаскивание
			_isDragStarted = false;
         INFO = "";

			for(int i=0; i<GCP_MAX_FUNC_NUM; i++)			//Функции надо обнулить иначе память тютю
				FUNCTIONS[i] = 0;

			collisionBox = GCP_COLLISIONBOX_RECTANGLE;		//Обработка столкновений
			_isVisible = true;
			
         _position = GCP_Rect(0, 0, 100, 20);
			xPosStart = 0; 
			yPosStart = 0;			
			collisionRadius = 5;							//Если рисуется круг
			_timeMouseOver = 0;			
		}

		virtual ~GCP_FormComponent()
		{
			//Указатели надо удалить
			for(int i=0; i<GCP_MAX_FUNC_NUM; i++)
				if(FUNCTIONS[i]!=0)
					delete FUNCTIONS[i];
		}

      virtual void OnDraw(const GCP_Event &event)
      {
         basicOnDraw(event);
      };

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
		void OnDrawInfo(const GCP_Event &event) {
			//ПОКА ЧТО КРИВО НО РАБОТАЕТ
			if(INFO!="" && _isMouseOver){
				int mess_w, mess_h;

				//Вычисление ширины и высоты текста
				GCP_Vector<string>* strings = GCP_Math::strToLines(INFO);
				bool hasIndex = false;
				unsigned int maxSize=0, maxSizeIndex=0;
				for(unsigned int i=0; i<strings->size(); i++)
				{
					if(strings->at(i).length() > maxSize){
						maxSize = strings->at(i).length();
						maxSizeIndex = i;
						hasIndex = true;
					}
				}
				if(!hasIndex)
					return;

            GCP_Draw::Render()->GetTextSize(strings->at(maxSizeIndex), mess_w, mess_h, gcp_spStyle(pStyle));
				mess_w += 5;	mess_h += 5;
				//mess_w /= strings->size();
				mess_h *= strings->size();
				delete strings;

            GCP_Point normPos = GCP_Math::normalizeRectInRect(GCP_Point(event.drawRect.x(), event.drawRect.y()),
               GCP_Point(event.drawRect.x() + event.drawRect.width(), event.drawRect.y() + event.drawRect.height()), _position.x() + 10, _position.y() + 10, mess_w, mess_h, 1);

            GCP_Draw::Render()->SetBlendMode(E_BLEND_ADD);
				GCP_Color c_white_a(255,255,255,210);
            GCP_Draw::Render()->Draw_FillRect((Sint16)normPos.X, (Sint16)normPos.Y, mess_w, mess_h, c_white_a);
            GCP_Draw::Render()->SetBlendMode(E_BLEND_NONE);
            GCP_Draw::Render()->Draw_Rect((Sint16)normPos.X, (Sint16)normPos.Y, mess_w, mess_h, c_black);
            GCP_Draw::Render()->Draw_Text(INFO, (int)normPos.X + 3, (int)normPos.Y + 3, pStyle, &drawdatainfo);
			}

		}

      void basicOnDraw(const GCP_Event &event) {	}

      void basicOnTextInput(const GCP_Event& event)
		{

		}
      void basicOnTextEdit(const GCP_Event& event)
		{

		}

      void basicOnMouseLeftHoldMotion(const GCP_Event& event)
		{
			if(FUNCTIONS[GCP_ON_MOUSE_LHMOTION] != 0)
			FUNCTIONS[GCP_ON_MOUSE_LHMOTION]->Call((void*)this);
		}

      void basicOnDrag(const GCP_Event& event)
		{
			if(FUNCTIONS[GCP_ON_DRAG] != 0)
			FUNCTIONS[GCP_ON_DRAG]->Call((void*)this);
		}

      void basicOnMouseGlobalLeftHoldMotion(const GCP_Event& event)
		{
			if(_isDragStarted){
            _position.topLeft.X = event.mousex;
            _position.topLeft.Y = event.mousey;
				_isMouseHold = true;

            int fx = event.drawRect.x();
            int fy = event.drawRect.y();
            int fw = event.drawRect.width();
            int fh = event.drawRect.height();

				switch(collisionBox){
					case GCP_COLLISIONBOX_RECTANGLE:
                  _position.topLeft.X = (int)std::fmax(fx, std::fmin(fx + fw - _position.width(), _position.x()));
                  _position.topLeft.Y = (int)std::fmax(fy, std::fmin(fy + fh - _position.height(), _position.y()));
						break;
					case GCP_COLLISIONBOX_ROUNDCIRCLE:
                  _position.topLeft.X = (int)std::fmax(fx + collisionRadius + 10, std::fmin(fx + fw - collisionRadius - 10, _position.x()));
                  _position.topLeft.Y = (int)std::fmax(fy + collisionRadius + 10, std::fmin(fy + fh - collisionRadius - 10, _position.y()));
						break;
				}
				basicOnDrag(event);
			}
			if(FUNCTIONS[GCP_ON_MOUSE_GLHMOTION] != 0)
			FUNCTIONS[GCP_ON_MOUSE_GLHMOTION]->Call((void*)this);
			return;

		}


		////////////////////////////////////////////////////////////////////

      void basicOnEvent(const GCP_Event &event)
		{
         switch (event.eventType)
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

         if (FUNCTIONS[event.eventType] != 0)
            FUNCTIONS[event.eventType]->Call((void*)this);
		}

		virtual gcp_formEvent OnEvent(const GCP_Event &event)
		{
         basicOnEvent(event);
			gcp_formEvent evt; 
         evt.isEventInsideForm = false; 
         return evt;
		}

      virtual bool OnTextEdit(const GCP_Event& event){ basicOnTextEdit(event); return true; }
      virtual bool OnTextInput(const GCP_Event& event){ basicOnTextInput(event); return true; }
      virtual gcp_formEvent OnMouseGlobalLeftHoldMotion(const GCP_Event& event)	{ basicOnMouseGlobalLeftHoldMotion(event); return gcp_formEvent();}
      virtual bool OnMouseLeftHoldMotion(const GCP_Event& event)	{
			if (_isDragable)
				_isDragStarted = true;
			basicOnMouseLeftHoldMotion(event);
			return true;
		}
      
		virtual void setPosition(int x, int y)		
      {	
         _position.topLeft.X = x;
         _position.topLeft.Y = y;
         if (!_isStartPositionSet)
         {
            xPosStart = x;
            yPosStart = y;
            _isStartPositionSet = true;
         }
		}

      virtual void setPosition(int x, int y, int width, int height )
      {         
         _position.bottomRight.X = width;
         _position.bottomRight.Y = height;
         setPosition(x, y);
      }
      

		virtual void setWidthHeight(int w, int h)	
      {	
         _position.bottomRight.X = w;
         _position.bottomRight.Y = h;
      }

		virtual void setVisible(bool visibility) { _isVisible = visibility; }
      virtual bool isVisible() { return _isVisible; }
      virtual void setDragable(bool dragable) { _isDragable = dragable; }
      virtual bool isDragable() { return _isDragable; }
      virtual const GCP_Rect& getPosition()	const     { return _position; }
      virtual bool isEventUnderneathBloacking() const { return _isLocalEventsUnderneathBlocking; }

		virtual void setStyle(const gcp_spStyle& style_)	
      {
			pStyle = style_;
		}

      virtual const gcp_spStyle &getStyle()				
      {
         return pStyle;
		}      


	

		bool checkCollisionBox(double mousex, double mousey)
		{
			bool flag = false;
			switch(collisionBox){
				case GCP_COLLISIONBOX_RECTANGLE:
               if (GCP_Math::isInRect(mousex, mousey, _position.x(), _position.y(), _position.width(), _position.height()))
						flag = true;
					break;
				case GCP_COLLISIONBOX_ROUNDCIRCLE:
               if (GCP_Math::isInRadius(_position.x(), _position.y(), mousex, mousey, collisionRadius))
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
};

#endif
