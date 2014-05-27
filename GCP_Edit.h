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
		string _sTextInputDraw;
		int _iTextDrawIndex;
		void corelateText();
	public:
		SDL_Rect textRect, markedRect;		
		//static enum GCP_InputType_Enum{ DIGITONLY, TEXTONLY, DOUBLEDIGIT, ALL};
		int inputType;


		GCP_Edit();
		void setCaption(std::string str);
		string getCaption();
		void OnDraw(SDL_Renderer* screen,int w, int h, int formx, int formy, int formw, int formh);
		bool OnMouseLeftClick(SDL_MouseButtonEvent mousebutton)	;
		gcp_formEvent OnMouseGlobalLeftClick(SDL_MouseButtonEvent mousebutton);
		void OnKeyDown(SDL_KeyboardEvent keybevent);		
		bool OnTextInput(SDL_TextInputEvent textevent);
		bool OnTextEdit(SDL_TextEditingEvent edit);
		gcp_formEvent OnEvent( const int GCP_EVENT, sdl_events events);
		
};

#endif
