#ifndef GCP_FormComponentH
#define GCP_FormComponentH

#include "GCP_Draw.h"
#include "GCP_Delegate.h"
#include "GCP_SPointer.h"

namespace gcp
{
	class GCP_FormComponent;
	typedef GCP_SPointer<GCP_FormComponent> gcp_spFormComponent;

	class GCP_FormComponent : public GCP_SPointerBase
	{
	protected:
		bool _isLocalEventsUnderneathBlocking;
		bool _isVisible, _isDragable, _isEnabled;
		bool _isStartPositionSet;
		bool _isMouseOver;                        //������� ���� ��� ��������
		bool _isMouseHold;                        //������� ����� ������� ���� ������ ��� ��������
		bool _isDragStarted;                      //������� ������ ������������� ������
		bool _isLocalEventEnabled;				  //��������� ��������� ������� / ������������
		int _timeMouseOver;						  //������ ��� ����������� ���������
		int _timeMouseOverInit;
		int _iInfoXoffset;
		int _iInfoYoffset;
		void* _memory;
		GCP_UID _ID;

		std::string _sInfo;					      //����������� ���������
		gcp_spStyle pStyle;
		GCP_Rect<int> _position;
		IContainer* FUNCTIONS[GCP_MAX_FUNC_NUM];  //������� ��������� �� �������

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
		GCP_DrawData drawdata;
		GCP_DrawData drawdatainfo;

	public:
		bool compare(const GCP_FormComponent* right, int compare, int criteria = -1)
		{
			//����� �� �������� ������������ �������� � ���������� ������
			switch (compare)
			{
			case 1:	// <
				switch (criteria)					{
				case GCP_SORTBY_DRAWORDER:
					return (options.draw_order > right->options.draw_order);
				case GCP_SORTBY_EVENTORDER:
					return (options.draw_order < right->options.draw_order);
				}
			case 2:	// >
				switch (criteria)					{
				case GCP_SORTBY_DRAWORDER:
					return (options.draw_order < right->options.draw_order);
				case GCP_SORTBY_EVENTORDER:
					return (options.draw_order > right->options.draw_order);
				}
			case 3:	// =
				switch (criteria)					{
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
			options.draw_order = 0;						    //������� ���������
			_isMouseOver = false;
			_isMouseHold = false;
			_isEnabled = true;
			_isStartPositionSet = false;
			_isLocalEventsUnderneathBlocking = true;		//����������� ��������� ��������� ������� � ������ ��������, ������� ��������� �� ����
			_isDragable = false;							//��������������
			_isDragStarted = false;
			_isLocalEventEnabled = true;
			_sInfo = "";

			for (int i = 0; i < GCP_MAX_FUNC_NUM; i++)		//������� ���� �������� ����� ������ ����
				FUNCTIONS[i] = 0;

			collisionBox = GCP_COLLISIONBOX_RECTANGLE;		//��������� ������������
			_isVisible = true;

			_position = GCP_Rect<int>(0, 0, 100, 20);
			xPosStart = yPosStart = 0;
			collisionRadius = 5;							 //���� �������� ����
			_timeMouseOver = _timeMouseOverInit = -25;
		}

		virtual ~GCP_FormComponent()
		{
			//��������� ���� �������
			for (int i = 0; i < GCP_MAX_FUNC_NUM; i++)
				if (FUNCTIONS[i] != 0)
					delete FUNCTIONS[i];
		}

		///SET AND BASIC FUNCTIONS
		////////////////////////////////////////
		/////////////////////////LEFT CLICK
		////////////////////////////////////////
		//��� ������������ ����������� �� �������
		template< class T, class U > void setOnMouseGlobalLeftClick(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_GLEFT_CLICK] != 0) delete FUNCTIONS[GCP_ON_GLEFT_CLICK];
			FUNCTIONS[GCP_ON_GLEFT_CLICK] = new Container< T, U >(i_class, i_method);
		}
		template< class T, class U> void setOnMouseLeftClick(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_LEFT_CLICK] != 0) delete FUNCTIONS[GCP_ON_LEFT_CLICK];
			FUNCTIONS[GCP_ON_LEFT_CLICK] = new Container< T, U >(i_class, i_method);
		}

		////////////////////////////////////////
		/////////////////////////RIGHT CLICK
		////////////////////////////////////////
		template< class T, class U > void setOnMouseGlobalRightClick(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_GRIGHT_CLICK] != 0) delete FUNCTIONS[GCP_ON_GRIGHT_CLICK];
			FUNCTIONS[GCP_ON_GRIGHT_CLICK] = new Container< T, U >(i_class, i_method);
		}
		template< class T, class U > void setOnMouseRightClick(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_RIGHT_CLICK] != 0) delete FUNCTIONS[GCP_ON_RIGHT_CLICK];
			FUNCTIONS[GCP_ON_RIGHT_CLICK] = new Container< T, U >(i_class, i_method);
		}

		////////////////////////////////////////
		/////////////////////////MOUSE WHELL
		////////////////////////////////////////
		template< class T, class U > void setOnMouseGlobalWheelDown(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_WHELL_GDOWN] != 0) delete FUNCTIONS[GCP_ON_WHELL_GDOWN];
			FUNCTIONS[GCP_ON_WHELL_GDOWN] = new Container< T, U >(i_class, i_method);
		}
		template< class T, class U > void setOnMouseWheelDown(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_WHELL_DOWN] != 0) delete FUNCTIONS[GCP_ON_WHELL_DOWN];
			FUNCTIONS[GCP_ON_WHELL_DOWN] = new Container< T, U >(i_class, i_method);
		}

		template< class T, class U > void setOnMouseGlobalWheelUp(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_WHELL_GUP] != 0) delete FUNCTIONS[GCP_ON_WHELL_GUP];
			FUNCTIONS[GCP_ON_WHELL_GUP] = new Container< T, U >(i_class, i_method);
		}

		template< class T, class U > void setOnMouseWheelUp(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_WHELL_UP] != 0) delete FUNCTIONS[GCP_ON_WHELL_UP];
			FUNCTIONS[GCP_ON_WHELL_UP] = new Container< T, U >(i_class, i_method);
		}

		////////////////////////////////////////
		/////////////////////////MOUSE DOWN
		////////////////////////////////////////
		template< class T, class U > void setOnMouseGlobalDown(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_MOUSE_GDOWN] != 0) delete FUNCTIONS[GCP_ON_MOUSE_GDOWN];
			FUNCTIONS[GCP_ON_MOUSE_GDOWN] = new Container< T, U >(i_class, i_method);
		}
		template< class T, class U > void setOnMouseGlobalLeftDown(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_MOUSE_GLDOWN] != 0) delete FUNCTIONS[GCP_ON_MOUSE_GLDOWN];
			FUNCTIONS[GCP_ON_MOUSE_GLDOWN] = new Container< T, U >(i_class, i_method);
		}
		template< class T, class U > void setOnMouseLeftDown(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_MOUSE_LDOWN] != 0) delete FUNCTIONS[GCP_ON_MOUSE_LDOWN];
			FUNCTIONS[GCP_ON_MOUSE_LDOWN] = new Container< T, U >(i_class, i_method);
		}

		template< class T, class U > void setOnMouseGlobalLeftHoldMotion(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_MOUSE_GLHMOTION] != 0) delete FUNCTIONS[GCP_ON_MOUSE_GLHMOTION];
			FUNCTIONS[GCP_ON_MOUSE_GLHMOTION] = new Container< T, U >(i_class, i_method);
		}
		template< class T, class U > void setOnMouseLeftHoldMotion(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_MOUSE_LHMOTION] != 0) delete FUNCTIONS[GCP_ON_MOUSE_LHMOTION];
			FUNCTIONS[GCP_ON_MOUSE_LHMOTION] = new Container< T, U >(i_class, i_method);
		}

		////////////////////////////////////////
		/////////////////////////MOUSE UP
		////////////////////////////////////////
		template< class T, class U > void setOnMouseGlobalUp(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_MOUSE_GUP] != 0) delete FUNCTIONS[GCP_ON_MOUSE_GUP];
			FUNCTIONS[GCP_ON_MOUSE_GUP] = new Container< T, U >(i_class, i_method);
		}
		template< class T, class U > void setOnMouseUp(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_MOUSE_UP] != 0) delete FUNCTIONS[GCP_ON_MOUSE_UP];
			FUNCTIONS[GCP_ON_MOUSE_UP] = new Container< T, U >(i_class, i_method);
		}

		template< class T, class U > void setOnMouseMotion(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_MOUSE_MOTION] != 0) delete FUNCTIONS[GCP_ON_MOUSE_MOTION];
			FUNCTIONS[GCP_ON_MOUSE_MOTION] = new Container< T, U >(i_class, i_method);
		}
		template< class T, class U > void setOnGlobalMouseMotion(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_MOUSE_GMOTION] != 0) delete FUNCTIONS[GCP_ON_MOUSE_GMOTION];
			FUNCTIONS[GCP_ON_MOUSE_GMOTION] = new Container< T, U >(i_class, i_method);
		}

		////////////////////////////////////////
		/////////////////////////MOUSE MOTION
		////////////////////////////////////////
		template< class T, class U > void setOnDrag(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_DRAG] != 0) delete FUNCTIONS[GCP_ON_DRAG];
			FUNCTIONS[GCP_ON_DRAG] = new Container< T, U >(i_class, i_method);
		}

		template< class T, class U > void setOnKeyDown(T* i_class, U i_method)		{
			if (FUNCTIONS[GCP_ON_GKEYDOWN] != 0) delete FUNCTIONS[GCP_ON_GKEYDOWN];
			FUNCTIONS[GCP_ON_GKEYDOWN] = new Container< T, U >(i_class, i_method);
		}

		virtual gcp_formEvent OnEvent(const GCP_Event &event)
		{
			basicOnEvent(event);			
			gcp_formEvent evt;
			evt.isEventInsideForm = false;
			return evt;
		}

		virtual const GCP_UID& ID() const {return _ID;}
		virtual void setPosition(GCP_Rect<int> const& position)
		{
			_position.setWidthHeight(position.width(), position.height());
			setPosition(position.x(), position.y());
		}

		virtual void setPosition(int x, int y, int width, int height)
		{
			_position.setWidthHeight(width, height);
			setPosition(x, y);
		}

		virtual void setPosition(int x, int y)
		{
			_position.setTopLeft(x, y);
			if (!_isStartPositionSet)
			{
				xPosStart = x;
				yPosStart = y;
				_isStartPositionSet = true;
			}
		}

		virtual void setWidthHeight(int w, int h)
		{
			_position.setWidthHeight(w, h);
		}

		virtual void setMemory (void* mem) { _memory = mem; }
		virtual void* getMemory () { return _memory; }
		virtual void setVisible(bool visibility) { _isVisible = visibility; }
		virtual bool isVisible() { return _isVisible; }
		virtual void setEnabled(bool enabled) { _isEnabled = enabled; }
		virtual bool isEnabled() { return _isEnabled; }
		virtual bool isDragStarted() {return _isDragStarted; }

		virtual void setDragable(bool dragable) { _isDragable = dragable; }
		virtual bool isDragable() { return _isDragable; }
		virtual const GCP_Rect<int>& getPosition()	const     { return _position; }
		virtual bool isEventUnderneathBlocking() const { return _isLocalEventsUnderneathBlocking; }
		virtual void setEventUnderneathBlocking(bool set){ _isLocalEventsUnderneathBlocking = set; }

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
			switch (collisionBox){
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

		virtual void OnDraw(const GCP_Event &event)
		{
			basicOnDraw(event);
		};

		//������ ���������� ���������
		void OnDrawInfo(const GCP_Event &event)
		{
			if (_sInfo != "" && _isMouseOver)
			{
				int mess_w, mess_h, mess_l;
				mess_l = GCP_Draw::Render()->GetTextSize(_sInfo, mess_w, mess_h, gcp_spStyle(pStyle));
				mess_w += 6;
				mess_h += 6 + (mess_l-1)*5;
				GCP_Rect <int> rectToDraw(_position.x() + _iInfoXoffset, _position.y() + _iInfoYoffset, mess_w, mess_h);
				GCP_Point<int> normPos = GCP_Math::normalizeRectInRect(rectToDraw, event.drawRect, 1);

				GCP_Draw::Render()->SetBlendMode(E_BLEND_ADD);
				gcpUint8 alpha = GCP_Draw::Render()->GetAlpha();
				GCP_Draw::Render()->SetAlpha(215);
				GCP_Draw::Render()->Draw_FillRect((Sint16)normPos.X, (Sint16)normPos.Y, mess_w, mess_h, c_white);
				GCP_Draw::Render()->SetAlpha(alpha);
				GCP_Draw::Render()->SetBlendMode(E_BLEND_NONE);
				GCP_Draw::Render()->Draw_Rect((Sint16)normPos.X, (Sint16)normPos.Y, mess_w, mess_h, c_black);
				GCP_Draw::Render()->Draw_Text(_sInfo, GCP_Rect<int>(normPos.X + 3 , normPos.Y + 3, 100, 20), GCP_DefaultStyle, &drawdatainfo);
			}
		}

		virtual gcp_formEvent OnMouseGlobalLeftHoldMotion(const GCP_Event& event)	{ basicOnMouseGlobalLeftHoldMotion(event); return gcp_formEvent(); }
		virtual bool OnMouseLeftHoldMotion(const GCP_Event& event)	{
			if (_isDragable)
				_isDragStarted = true;
			basicOnMouseLeftHoldMotion(event);
			return true;
		}

		virtual void setInfo(const string& info, int iXoffset = 15, int iYoffset = 10)
		{
			_sInfo = info;
			_iInfoXoffset = iXoffset;
			_iInfoYoffset = iYoffset;
		}

		virtual const string& getInfo()
		{
			return _sInfo;
		}


	protected:
		void basicOnDraw(const GCP_Event &event) {	}
		void basicOnTextInput(const GCP_Event& event)	{	}
		void basicOnTextEdit(const GCP_Event& event)	{	}

		void basicOnMouseLeftHoldMotion(const GCP_Event& event)
		{
			if (FUNCTIONS[GCP_ON_MOUSE_LHMOTION] != 0)
				FUNCTIONS[GCP_ON_MOUSE_LHMOTION]->Call((void*)this);
		}

		void basicOnDrag(const GCP_Event& event)
		{
			if (FUNCTIONS[GCP_ON_DRAG] != 0)
				FUNCTIONS[GCP_ON_DRAG]->Call((void*)this);
		}

		void basicOnMouseGlobalLeftHoldMotion(const GCP_Event& event)
		{
			if (_isDragStarted){
				_position.setTopLeft(event.mousex, event.mousey);
				_isMouseHold = true;

				int fx = event.drawRect.x();
				int fy = event.drawRect.y();
				int fw = event.drawRect.width();
				int fh = event.drawRect.height();

				switch (collisionBox)
				{
				case GCP_COLLISIONBOX_RECTANGLE:
					_position.setTopLeft((int)GCP_Math::Max(fx, GCP_Math::Min(fx + fw - _position.width(), _position.x())),
										 (int)GCP_Math::Max(fy, GCP_Math::Min(fy + fh - _position.height(), _position.y())));
					break;
				case GCP_COLLISIONBOX_ROUNDCIRCLE:
					_position.setTopLeft((int)GCP_Math::Max(fx + collisionRadius + 10, GCP_Math::Min(fx + fw - collisionRadius - 10, _position.x())),
										 (int)GCP_Math::Max(fy + collisionRadius + 10, GCP_Math::Min(fy + fh - collisionRadius - 10, _position.y())));
					break;
				}
				basicOnDrag(event);
			}
			if (FUNCTIONS[GCP_ON_MOUSE_GLHMOTION] != 0)
				FUNCTIONS[GCP_ON_MOUSE_GLHMOTION]->Call((void*)this);
			return;

		}

		///
		void basicOnEvent(const GCP_Event &event)
		{
			if (!_isEnabled)
				return;

			switch (event.eventType)
			{
			case GCP_ON_MOUSE_GMOTION:
				if (_isMouseHold == false)
					_isMouseOver = false; //assume mouse is out of collision rect
				break;
			case GCP_ON_MOUSE_MOTION:
				_isMouseOver = true;
				_timeMouseOver ++;
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

		virtual void onParentFormStartBlocking(){}
		virtual void onParentFormEndBlocking(){}
	};
}
#endif
