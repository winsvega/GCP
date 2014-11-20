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

class GCP_Form;
typedef GCP_SPointer<GCP_Form> gcp_spForm;
class GCP_Form: public GCP_FormComponent
{
	protected:
      GCP_Vector<gcp_spForm> _subForms;
      GCP_Vector<gcp_spFormComponent> _components;
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

		GCP_Form(){/*����� ��� ������� ����*/};
		GCP_Form(int _width, int _height);
		void setBufferSize(int screenw, int screenh);
		void setFont(string dir);
		~GCP_Form();	

      void addComponent(GCP_SPointer<GCP_ContextMenu> const &component);
      void addComponent(GCP_SPointer<GCP_FormComponent> const &component);
      void removeComponent(GCP_SPointer<GCP_FormComponent> const &component);
		void setPosition(int x, int y, int width, int height);
      void setPosition(int x, int y);

		void toggleVisibility(void* obj);
		void addSubForm(GCP_SPointer<GCP_Form> &form);
		void showmessage(string text, bool block = false);
		void showmessage(int text, bool block = false);

      void OnDraw(const GCP_Event &event);
      void setCaption(const std::string& str);
      gcp_formEvent OnEvent(const GCP_Event &event);

		
      bool OnTextInput(const GCP_Event& event);
      bool OnTextEdit(const GCP_Event& event);
		gcp_formEvent OnMouseGlobalLeftHoldMotion(const GCP_Event &event);
};
#endif
