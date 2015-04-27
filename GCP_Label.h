#ifndef GCP_LabelH
#define GCP_LabelH
#include "GCP_FormComponent.h"

namespace gcp
{
	class GCP_Label;
	typedef GCP_SPointer<GCP_Label> gcp_spLabel;
	class GCP_Label : public GCP_FormComponent
	{
	public:
		GCP_Label();
		void setText(string _sText){	text = _sText;	}
		void setText(const char* _sText){	text = string(_sText);	}
		void OnDraw(const GCP_Event &event);

		string text;

	private:
		int iTextSize, iMaxTextLength;

	};
}
#endif




