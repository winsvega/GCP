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

      void OnDraw(const GCP_Event &event);
		bool OnMouseLeftClick(SDL_MouseButtonEvent mousebutton);
      gcp_formEvent OnEvent(const GCP_Event &event);
};

#endif
