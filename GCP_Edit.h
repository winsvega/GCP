#ifndef GCP_EditH
#define GCP_EditH
#include "GCP_FormComponent.h"

namespace gcp
{
   class GCP_Edit : public GCP_FormComponent
   {
   private:
      bool _isEditingText;
      int _iDrawDash;
      string _sTextInputDraw, _sTextInput;
      int _iTextDrawIndex;
      void corelateText();
      bool onTextInput(const string &text);
      void onKeyDown(int keycode);
   public:
      SDL_Rect textRect, markedRect;
      GCPE_InputType inputType;


      GCP_Edit();
      void setCaption(const std::string &str);
      string getCaption();
      void OnDraw(const GCP_Event &event);
      //bool OnMouseLeftClick(const GCP_Event &event);
      //gcp_formEvent OnMouseGlobalLeftClick(const GCP_Event &event);

      //bool OnTextInput(const GCP_Event &event);
      //bool OnTextEdit(const GCP_Event &event);
      gcp_formEvent OnEvent(const GCP_Event &event);
   };
}

#endif
