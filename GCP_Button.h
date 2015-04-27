#ifndef GCP_ButtonH
#define GCP_ButtonH
#include "GCP_FormComponent.h"

namespace gcp
{
	class GCP_Button;
	typedef GCP_SPointer<GCP_Button> gcp_spButton;
	class GCP_Button : public GCP_FormComponent
	{
	private:
		string _sCaption;
		string _sIconPath;
		int _iType;
		bool _bChecked;

	public:
		GCP_Button();
		gcp_formEvent OnEvent(const GCP_Event &event);
		void OnDraw(const GCP_Event &event);		

		void setCaption(const std::string& text)	{	_sCaption = text;	}
		const std::string& getCaption() const		{	return _sCaption;	}
		void setIcon(const std::string& path)		{	_sIconPath = path;	}
		void setButtonType(int type)				{	_iType = type;		}
		int getButtonType()							{	return _iType;		}
		bool isChecked()							{	return _bChecked;	}
		void isChecked(bool checked)				{	_bChecked = checked;	}
	};
}

#endif
