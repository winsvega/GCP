#ifndef GCP_DrawH
#define GCP_DrawH
#include "GCP_Math.h"
#include "GCP_Style.h"
#include "GCP_Constants.h"
#include "SDL_ttf.h"
#include <cstring>

enum GCPE_BlendMode
{
   E_BLEND_NONE,
   E_BLEND_ADD
};

//Base Drawing Functions Class
class GCP_Draw_Base
{
   public:
      virtual void Draw_Line(const GCP_Point &A, const GCP_Point &B, const GCP_Color &color, short bold) const = 0;
      virtual void Draw_Line(int x, int y, int x2, int y2, const GCP_Color &color, short bold = 1)const = 0;
      virtual void Draw_Round(int x, int y, int width, int height, short scale, const GCP_Color &color) const = 0;
      virtual void Draw_Round(const GCP_Rect &rect, short scale, const GCP_Color &color) const = 0;
      virtual void Draw_FillRound(int x, int y, int width, int height, int scale, const GCP_Color &color) const = 0;
      virtual void Draw_FillRound(const GCP_Rect &rect, int scale, const GCP_Color &color)const  = 0;
      virtual void Draw_Rect(int x, int y, int width, int height, const GCP_Color &color) const = 0;
      virtual void Draw_Rect(const GCP_Rect &rect, const GCP_Color &color)const = 0;
      virtual void Draw_FillRect(int x, int y, int width, int height, const GCP_Color &color)const = 0;
      virtual void Draw_FillRect(const GCP_Rect &rect, const GCP_Color &color) const = 0;
      virtual void Draw_FillEllipse(int x0, int y0, int Xradius, int Yradius, const GCP_Color &color)const = 0;
      virtual void Draw_Ellipse(int x0, int y0, int Xradius, int Yradius, const GCP_Color &color)const = 0;
      virtual void Draw_Graphic(int* data, int data_size, int x, int y, int width, int height)const = 0;
      virtual void Draw_Image(const string &path, int x, int y)const = 0;
      virtual void Draw_Text(const string &text, int x, int y, const gcp_spStyle &style, GCP_DrawData* buffer = NULL) const  = 0;
      virtual void Draw_Text(const string &text, const GCP_Rect &position, const gcp_spStyle &style, GCP_DrawData* buffer = NULL) const  = 0;
      virtual void GetTextSize(const string &text, int &width, int &height, const gcp_spStyle &style) const  = 0;
      virtual void SetBlendMode(GCPE_BlendMode mode) = 0;

#define DECL_GCP_DRAW_BASE\
      void Draw_Line(const GCP_Point &A, const GCP_Point &B, const GCP_Color &color, short bold) const;\
      void Draw_Line(int x, int y, int x2, int y2, const GCP_Color &color, short bold = 1) const;\
      void Draw_Round(int x, int y, int width, int height, short scale, const GCP_Color &color) const;\
      void Draw_Round(const GCP_Rect &rect, short scale, const GCP_Color &color) const; \
      void Draw_FillRound(int x, int y, int width, int height, int scale, const GCP_Color &color) const;\
      void Draw_FillRound(const GCP_Rect &rect, int scale, const GCP_Color &color) const;\
      void Draw_Rect(int x, int y, int width, int height, const GCP_Color &color) const;\
      void Draw_Rect(const GCP_Rect &rect, const GCP_Color &color) const; \
      void Draw_FillRect(int x, int y, int width, int height, const GCP_Color &color) const;\
      void Draw_FillRect(const GCP_Rect &rect, const GCP_Color &color) const;\
      void Draw_FillEllipse(int x0, int y0, int Xradius, int Yradius, const GCP_Color &color) const;\
      void Draw_Ellipse(int x0, int y0, int Xradius, int Yradius,const GCP_Color &color) const;\
      void Draw_Image(const string &path, int x, int y) const;\
      void Draw_Text(const string &text, int x, int y, const gcp_spStyle &style, GCP_DrawData* buffer = NULL) const;\
      void Draw_Text(const string &text, const GCP_Rect &position, const gcp_spStyle &style, GCP_DrawData* buffer = NULL) const;\
      void Draw_Graphic(int* data, int data_size, int x, int y, int width, int height) const;\
      void GetTextSize(const string &text, int &width, int &height, const gcp_spStyle &style) const;\
      void SetBlendMode(GCPE_BlendMode mode);
};

//SDL Realisation of Drawing
class GCP_Draw_SDL2 : public GCP_Draw_Base
{
   private:
      SDL_Renderer* _screen;
      SDL_Color toSDLColor(Uint32 int_color);
      void drawRect(GCP_Point pointTopLeft, GCP_Point pointBottomRight, const GCP_Color &color, int bold) const;
      void drawLine(GCP_Point pointA, GCP_Point pointB, const GCP_Color &color, int bold) const;
      void applySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend) const;
      SDL_Texture* renderText(GCP_DrawData* drawdata, std::string &message, const gcp_spStyle &style) const;

   public:
      DECL_GCP_DRAW_BASE
      GCP_Draw_SDL2(SDL_Renderer* sdlRenderer) :_screen(sdlRenderer){}
};


//Static Interface for GCP Module
class GCP_Draw
{
   private:
      static GCP_Draw_Base* _drawbase;
      static string _sDefaultFontPath;
	public:
      static void initConstants();
      static void InitSDL2(SDL_Renderer *render)
      {
          _drawbase = new GCP_Draw_SDL2(render);
          TTF_Init();
          GCP_Draw::initConstants();	//дело в том что константы вне функкций почему то не объ€вл€ютс€ на некоторых компил€торах	
      }

      static void DeInit()
      {         
         if (_drawbase)
            delete _drawbase;
         TTF_Quit();
      }

      static GCP_Draw_Base* Render()
      {
         return _drawbase;
      }

      static void setFontPath(GCPE_FontType EFType, string path)
      {
         //Implement GCP_Map here
         _sDefaultFontPath = path;        
      }
      static string getFontPath(GCPE_FontType EFType)
      {
         return _sDefaultFontPath;
      }
};

extern gcp_spStyle GCP_DefaultStyle;
extern gcp_spStyle GCP_ButtonBlackStyle;
extern gcp_spStyle GCP_ButtonWhiteStyle;
extern gcp_spStyle GCP_PanelBlackStyle;
#endif