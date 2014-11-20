//#ifndef GCP_FontH
//#define GCP_FontH
//
//#include "GCP_SPointer.h"
//#include "SDL_ttf.h"
//
//class GCP_Font;
//typedef GCP_SPointer<GCP_Font> gcp_spFont;
//
//enum GCPE_FontType
//{
//   E_ARIAL
//};
//
//
//class GCP_Font : public GCP_SPointerBase
//{
//   private:
//      TTF_Font* _font;
//      static string _sDefaultFontPath;
//
//	public:
//      explicit GCP_Font(GCPE_FontType EFontType)
//      {
//         _font = NULL;
//         Reinit();
//      }
//
//      TTF_Font* Font()
//      {
//         return _font;
//      }
//
//      ~GCP_Font()
//      {
//         if (_font)
//            TTF_CloseFont(_font);      //Кто то закрыл фонт без нашего ведома!!!
//         
//         _font = NULL;
//      }
//
//      void Reinit()
//      {
//         if (_font)
//            TTF_CloseFont(_font);
//
//         _font = TTF_OpenFont(GCP_Font::getFontPath(E_ARIAL).c_str(), 14);
//      }
//      
//      static void setFontPath(GCPE_FontType EFType, string path)
//      {
//         //Implement GCP_Map here
//         _sDefaultFontPath = path;        
//      }
//      static string getFontPath(GCPE_FontType EFType)
//      {
//         return _sDefaultFontPath;
//      }
//};
//
//
//#endif
