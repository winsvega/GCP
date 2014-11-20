#ifndef GCP_LabelH
#define GCP_LabelH
#include "GCP_FormComponent.h"

class GCP_Label: public GCP_FormComponent
{
	public:
		int iTextSize, iMaxTextLength;
		string text;

		GCP_Label();

      void OnDraw(const GCP_Event &event);
};

#endif




