#ifndef GCP_EditH
#define GCP_EditH
#include "GCP_FormComponent.h"

namespace gcp
{
	class GCP_Edit;
	typedef GCP_SPointer<GCP_Edit> gcp_spEdit;

	class GCP_Edit : public GCP_FormComponent
	{
	private:
		bool _isEditingText;
		int _iDrawDash;
		string _sTextInputDraw, _sTextInput;
		int _iTextDrawIndex;
		GCP_Vector<int> _inputSizeMap;
		void corelateText();
		bool onTextInput(const string &text);
		void onKeyDown(int keycode);
	public:
		SDL_Rect textRect, markedRect;
		GCPE_InputType inputType;

		GCP_Edit();
		void setText(const std::string &str, int byteperletter = 1);
		string getText();
		void OnDraw(const GCP_Event &event);
		//bool OnMouseLeftClick(const GCP_Event &event);
		//gcp_formEvent OnMouseGlobalLeftClick(const GCP_Event &event);

		//bool OnTextInput(const GCP_Event &event);
		//bool OnTextEdit(const GCP_Event &event);
		gcp_formEvent OnEvent(const GCP_Event &event);
	};
}

#endif
