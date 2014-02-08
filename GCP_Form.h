////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////GCP_Form
/////////////////////////////////////����� ����� ����������
////////////////////////////////////////////////////////////////////////////////////////////
///////
///////_subForms    
//			������ ���� ����, ������������� � ���� �����
//			��� ��������� ������� �������� ��� ����������, ����� ������������� �����
//			��� ��������� ������� ������� �������������� ��� �����, ����� ����������
//			(���� ����� �� ����������� ���������)
///////_components
//			������ ���� ��������� ������� ���������� ���������� ������� 
//			� ��� ������� ����������� ������� ���������. (���� �� ����������)
///////_contextmenus
//			������ ������ ������� ����������� ����������� ���� (���� ������ ������)
//			����� ����� ������ ����������� ����. ������� ��������� ��������� �� ��������������
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


class GCP_Form: public GCP_FormComponent
{
	protected:
		GCP_Vector<GCP_Form*> _subForms;
		GCP_Vector<GCP_FormComponent*> _components;
		GCP_Vector<GCP_ContextMenu*> _contextmenus;
		GCP_FormComponent* _componentThatWasLeftClicked;
		int _swidth, _sheight;
		bool _isLocked, _isClickedOnTopHeader, _isContextMenuOpened, _isComponentClicked;
		GCP_Button* xbutton, *xpanel;
		GCP_Form* messagebox;
		GCP_Label* messagelabel;
		GCP_ContextMenu *formTopRightButtons;
		SDL_Renderer* sdlRenderer;
		GCP_Vector<string> messages;
	public:
		GCP_Color colorHeadMenuBackground, colorHeadMenuFade, colorButtonBackground;
		bool isParentLocking;
		bool isShowTopRightButtons;
		bool isDraggingSomeComponent;
		bool isTransparent;
		bool isLocalEventsLocked;
		short int iPosition;
		int mouse_x, mouse_y;
		bool isLocked;

		GCP_Form(){/*����� ��� ������� ����*/};
		GCP_Form(SDL_Renderer* screen, int _width, int _height);
		void setBufferSize(int screenw, int screenh);
		void setFont(string dir);
		~GCP_Form();	

		void addComponent(GCP_ContextMenu* component);
		void addComponent(GCP_FormComponent* component);
		void removeComponent(GCP_FormComponent* component);
		void setPosition(int x, int y);

		void toggleVisibility(void* obj);
		void addSubForm(GCP_Form* form);
		void showmessage(string text, bool block = false);
		void showmessage(int text, bool block = false);

		bool OnDraw(SDL_Renderer* screen, int w, int h);
		gcp_formEvent OnEvent( const int GCP_EVENT, sdl_events events);

		
		bool OnTextInput(SDL_TextInputEvent text);
		bool OnTextEdit(SDL_TextEditingEvent edit);
		gcp_formEvent OnMouseGlobalLeftHoldMotion(SDL_MouseMotionEvent motion);
};
#endif