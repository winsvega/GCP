#ifndef GCP_CheckboxH
#define GCP_CheckboxH
#include "GCP_FormComponent.h"

namespace gcp
{
	class GCP_CheckBox;
	typedef GCP_SPointer<GCP_CheckBox> gcp_spCheckbox;
	class GCP_CheckBox : public GCP_FormComponent
	{
		private:
			bool _isChecked;
			int _iTextSize, _iMaxTextLength;
			string _text;
		public:
			GCP_CheckBox();
			void OnDraw(const GCP_Event &event);			
			gcp_formEvent OnEvent(const GCP_Event &event);

			///
			void setChecked(bool checked)
			{
				_isChecked = checked;
			}

			///
			bool isChecked()
			{
				return _isChecked;
			}

			///
			void setCaption(const std::string& text)
			{
				_text = text;
			}

			//
			const std::string& getCaption() const
			{
				return _text;
			}
	};
}

#endif
