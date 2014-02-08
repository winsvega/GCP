#ifndef GCP_LabelH
#define GCP_LabelH
#include "GCP_FormComponent.h"

class GCP_Label: public GCP_FormComponent
{
	public:
		int iTextSize, iMaxTextLength;
		string text;

		GCP_Label();

		void OnDraw(SDL_Renderer* screen,int w, int h, int formx, int formy, int formw, int formh);
};

#endif




