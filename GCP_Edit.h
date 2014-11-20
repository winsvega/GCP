#ifndef GCP_EditH
#define GCP_EditH
#include "GCP_FormComponent.h"

const int GCP_EDIT_DIGITONLY = 0;
const int GCP_EDIT_TEXTONLY = 1;
const int GCP_EDIT_DOUBLEDIGIT = 2;
const int GCP_EDIT_ALL = 3;
class GCP_Edit: public GCP_FormComponent
{
	private:
		bool _isEditingText;
		int _iDrawDash;
      string _sTextInputDraw, _sTextInput;
		int _iTextDrawIndex;
		void corelateText();
	public:
		SDL_Rect textRect, markedRect;		
		//static enum GCP_InputType_Enum{ DIGITONLY, TEXTONLY, DOUBLEDIGIT, ALL};
		int inputType;


		GCP_Edit();
		void setCaption(std::string str);
		string getCaption();
      void OnDraw(const GCP_Event &event);
      bool OnMouseLeftClick(const GCP_Event &event);
      gcp_formEvent OnMouseGlobalLeftClick(const GCP_Event &event);
      void OnKeyDown(const GCP_Event &event);
      bool OnTextInput(const GCP_Event &event);
      bool OnTextEdit(const GCP_Event &event);
		gcp_formEvent OnEvent(const GCP_Event &event);
		
};

#endif
