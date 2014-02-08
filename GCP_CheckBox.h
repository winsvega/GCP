#ifndef GCP_CheckboxH
#define GCP_CheckboxH
#include "GCP_FormComponent.h"

class GCP_CheckBox: public GCP_FormComponent
{
	public:
		int iTextSize, iMaxTextLength;
		bool isChecked;
		string text;

		GCP_CheckBox();

		void OnDraw(SDL_Renderer* screen,int w, int h, int formx, int formy, int formw, int formh);
		bool OnMouseLeftClick(SDL_MouseButtonEvent mousebutton);
		gcp_formEvent OnEvent( const int GCP_EVENT, sdl_events events);
};

#endif
