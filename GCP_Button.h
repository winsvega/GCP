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

	public:
		GCP_Button();
		void OnDraw(const GCP_Event &event);
		int iType;
		bool checked;
		void setCaption(const std::string& text)
		{
			_sCaption = text;
		}
		const std::string& getCaption() const
		{
			return _sCaption;
		}
		void setIcon(const std::string& path)
		{
			_sIconPath = path;
		}
	};
}

#endif
