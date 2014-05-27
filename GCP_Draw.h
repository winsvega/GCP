#ifndef GCP_DrawH
#define GCP_DrawH
#include "SDL_ttf.h"
#include "GCP_Math.h"
#include <cstring>

const int PS_ALIGN_LEFT =  1;
const int PS_ALIGN_CENTER =  2;
const int PS_ALIGN_RIGHT =  4;
const int PS_CREATE_SURFACE =  8;
const int PS_TRANSPARENT_BG =  16;
const int PS_BLENDED =    32;

const int GCP_BUTTON_ROUNDRECT = 1;
const int GCP_BUTTON_SHARPRECT = 2;
const int GCP_MENU_MVERTICAL = 3;
const int GCP_MENU_MHORIZONTAL = 4;
const int GCP_COLLISIONBOX_RECTANGLE = 5;
const int GCP_COLLISIONBOX_ROUNDCIRCLE = 6;

struct GCP_Color
{
	int         r;
    int         g;
    int         b;
    int         a;
	GCP_Color(Uint8 R, Uint8 G, Uint8 B, Uint8 A):r(R),g(G),b(B),a(A) {} 
	GCP_Color(Uint8 R, Uint8 G, Uint8 B):r(R),g(G),b(B) {a = 255;} 
	GCP_Color(int R, int G, int B):r(R),g(G),b(B) {a = 255;} 
	GCP_Color(){}
	bool operator==(const GCP_Color &X){ 
		if(r == X.r && g == X.g && b == X.b && a == X.a)
			return true;
		return false;
	}
	bool operator!=(const GCP_Color &X){ 
		if(r == X.r && g == X.g && b == X.b && a == X.a)
			return false;
		return true;
	}
};


//When entry point function is defined in linker
//global static structures does not work, WTF?
extern GCP_Color c_white;
extern GCP_Color c_black;
extern GCP_Color c_aquadark;
extern GCP_Color c_yellow;
extern GCP_Color c_red;
extern GCP_Color c_blue;
extern GCP_Color c_lime; 
extern GCP_Color c_green;
extern GCP_Color c_aqua; 
extern GCP_Color c_orange;
extern GCP_Color c_grey;

struct GCP_DrawData
{
	GCP_Vector<SDL_Texture*> texture;
	GCP_Vector<int> twidth;
	GCP_Vector<int> theight;
	GCP_Vector<string> text;
	GCP_Vector<GCP_Color> color;
};


class GCP_Draw
{
	public:
		static void Draw_Line(SDL_Renderer* screen,int x,int y,int x2,int y2,GCP_Color color, int bold = 1);
		static void Draw_Round(SDL_Renderer* screen,Sint16 x,Sint16 y,Sint16 width,Sint16 height,Sint16 scale, GCP_Color color);
		static void Draw_FillRound(SDL_Renderer* screen,Sint16 x,Sint16 y,Sint16 width,Sint16 height,Sint16 scale, GCP_Color color);
		static void Draw_Rect(SDL_Renderer* screen,Sint16 x ,Sint16 y ,Sint16 width,Sint16 height,GCP_Color color);
		static void Draw_FillRect(SDL_Renderer* screen,Sint16 x ,Sint16 y ,Sint16 width,Sint16 height,GCP_Color color);
		static void Draw_FillEllipse(SDL_Renderer* screen,Sint16 x0,Sint16 y0,Sint16 Xradius,Sint16 Yradius,GCP_Color color);
		static void Draw_Ellipse(SDL_Renderer* screen,Sint16 x0,Sint16 y0,Sint16 Xradius,Sint16 Yradius,GCP_Color color);
		static void drawGraph(SDL_Renderer* screen,int w, int h, int* data, int data_size, int x, int y, int width, int height);
		static void drawRect(SDL_Renderer* screen, int w, int h,  GCP_Point pointTopLeft, GCP_Point pointBottomRight, GCP_Color color, int bold);
		static void drawLine(SDL_Renderer* screen, int w, int h, GCP_Point pointA, GCP_Point pointB, GCP_Color color, int bold);
		static void applySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend);
		static SDL_Texture* _renderText(SDL_Renderer *renderer, GCP_DrawData* drawdata, std::string message, std::string fontFile, SDL_Color color, int fontSize);
		static void renderText(string Text, int x, int y, SDL_Renderer *renderer, GCP_DrawData* drawdata, GCP_Color text_color, string font_path, int font_size/*, bool isRussian=false*/);
		static void initConstants();
		/*static GCP_Color c_white ();
		static GCP_Color c_black ();
		static GCP_Color c_grey ();
		static GCP_Color c_aquadark ();
		static GCP_Color c_yellow ();
		static GCP_Color c_red ();
		static GCP_Color c_blue ();
		static GCP_Color c_lime ();
		static GCP_Color c_green ();
		static GCP_Color c_aqua ();
		static GCP_Color c_orange ();*/
		static SDL_Color toSDLColor(Uint32 int_color);
		static SDL_Surface* printStrings(SDL_Surface *dest, TTF_Font *font,
									 std::string str, SDL_Rect &rc, SDL_Color clrFg,
									 SDL_Color clrBg, int flags ); 
};
#endif