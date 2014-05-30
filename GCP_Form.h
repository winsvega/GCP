////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////GCP_Form
/////////////////////////////////////Класс формы интерфейса
////////////////////////////////////////////////////////////////////////////////////////////
///////
///////_subForms    
//			список всех форм, прикрепленных к этой форме
//			При отрисовке сначала рисуются все компоненты, затем прикрепленные формы
//			При обработке событий сначала обрабатываются все формы, затем компоненты
//			(если формы не заблокируют обработку)
///////_components
//			Список всех компонент которым передаются глобальные события 
//			и для которых вычисляются события локальные. (клик по компоненту)
///////_contextmenus
//			Список кнопок которые отображаютс контекстные меню (меню правой кнопки)
//			Когда форма рисует контекстное меню. события остальных компонент не обрабатываются
////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef GCP_FormH
#define GCP_FormH
#include "GCP_ContextMenu.h"
#include "GCP_Edit.h"
#include "GCP_Label.h"
#include "GCP_Graph.h"
#include "GCP_CheckBox.h"
#include "GCP_Select.h"

class GCP_Form;
typedef GCP_SPointer<GCP_Form> gcp_spForm;
class GCP_Form: public GCP_FormComponent
{
	protected:
        GCP_Vector<gcp_spForm> _subForms;
        GCP_Vector<gcp_spFormCmpnt> _components;
        GCP_Vector<gcp_spContextMenu> _contextmenus;
		GCP_SPointer<GCP_FormComponent> _componentThatWasLeftClicked;
		int _swidth, _sheight;
		bool _isLocked, _isClickedOnTopHeader, _isContextMenuOpened, _isComponentClicked;
		GCP_SPointer<GCP_Button> xbutton, xpanel;
		GCP_SPointer<GCP_Form> messagebox;
		GCP_SPointer<GCP_Label> messagelabel;
		GCP_SPointer<GCP_ContextMenu> formTopRightButtons;
		SDL_Renderer* sdlRenderer;
		GCP_Vector<string> messages;
	public:		
		bool isParentLocking;
		bool isShowTopRightButtons;
		bool isDraggingSomeComponent;
		bool isTransparent;
		bool isLocalEventsLocked;
		short int iPosition;
		int mouse_x, mouse_y;
		bool isLocked;

		GCP_Form(){/*НУЖЕН ДЛЯ МЕССАДЖ БОКС*/};
		GCP_Form(SDL_Renderer* screen, int _width, int _height);
		void setBufferSize(int screenw, int screenh);
		void setFont(string dir);
		~GCP_Form();	

        void addComponent(GCP_SPointer<GCP_ContextMenu> const &component);
        void addComponent(GCP_SPointer<GCP_FormComponent> const &component);
        void removeComponent(GCP_SPointer<GCP_FormComponent> const &component);
		void setPosition(int x, int y);

		void toggleVisibility(void* obj);
		void addSubForm(GCP_SPointer<GCP_Form> &form);
		void showmessage(string text, bool block = false);
		void showmessage(int text, bool block = false);

		bool OnDraw(SDL_Renderer* screen, int w, int h);
		gcp_formEvent OnEvent( const int GCP_EVENT, sdl_events events);

		
		bool OnTextInput(SDL_TextInputEvent text);
		bool OnTextEdit(SDL_TextEditingEvent edit);
		gcp_formEvent OnMouseGlobalLeftHoldMotion(SDL_MouseMotionEvent motion);
};
#endif
