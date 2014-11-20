#ifndef GCP_ConstantsH
#define GCP_ConstantsH
#include "SDL.h"
#include "GCP_Math.h"

const int PS_ALIGN_LEFT = 1;
const int PS_ALIGN_CENTER = 2;
const int PS_ALIGN_RIGHT = 4;
const int PS_CREATE_SURFACE = 8;
const int PS_TRANSPARENT_BG = 16;
const int PS_BLENDED = 32;

const int GCP_BUTTON_ROUNDRECT = 1;
const int GCP_BUTTON_SHARPRECT = 2;
const int GCP_MENU_MVERTICAL = 3;
const int GCP_MENU_MHORIZONTAL = 4;
const int GCP_COLLISIONBOX_RECTANGLE = 5;
const int GCP_COLLISIONBOX_ROUNDCIRCLE = 6;

// онстанты
const int GCP_SORTBY_DRAWORDER = 1;
const int GCP_SORTBY_EVENTORDER = 2;

struct GCP_Color;
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


//—труктура дл€ сортировки компонетнов
struct SComponent
{
   int draw_order;
};

//событие внутри формы. возвращает состо€ние самой формы
struct gcp_formEvent
{
   gcp_formEvent() :isEventInsideForm(false), isEventOnFormHead(false), isFormDragged(false){}
   bool isFormDragged;
   bool isEventInsideForm;
   bool isEventOnFormHead;
};

//
struct GCP_DrawData
{
   GCP_Vector<SDL_Texture*> texture;
   GCP_Vector<int> twidth;
   GCP_Vector<int> theight;
   GCP_Vector<string> text;
   GCP_Vector<GCP_Color> color;
};

//—длные событи€
//event - глобальное событие event+1 - локальное событие
/*const int GCP_ON_GLEFT_CLICK = 1;
const int GCP_ON_LEFT_CLICK = 2;
const int GCP_ON_GRIGHT_CLICK = 3;
const int GCP_ON_RIGHT_CLICK = 4;
const int GCP_ON_WHELL_GUP = 5;
const int GCP_ON_WHELL_UP = 6;
const int GCP_ON_WHELL_GDOWN = 7;
const int GCP_ON_WHELL_DOWN = 8;
const int GCP_ON_MOUSE_GDOWN = 9;
const int GCP_ON_MOUSE_DOWN = 10;
const int GCP_ON_MOUSE_GLDOWN = 11;
const int GCP_ON_MOUSE_LDOWN = 12;
const int GCP_ON_MOUSE_GUP = 13;
const int GCP_ON_MOUSE_UP = 14;
const int GCP_ON_MOUSE_GMOTION = 15;
const int GCP_ON_MOUSE_MOTION = 16;
const int GCP_ON_GKEYDOWN = 17;
const int GCP_ON_KEYDOWN = 18;
const int GCP_ON_GDRAG = 19;
const int GCP_ON_DRAG = 20;
const int GCP_ON_MOUSE_GLHMOTION = 21;
const int GCP_ON_MOUSE_LHMOTION = 22;
const int GCP_MAX_FUNC_NUM = 23;*/

enum GCPE_Events
{
   GCP_EVENT_NONE,
   GCP_ON_GLEFT_CLICK,
   GCP_ON_LEFT_CLICK,
   GCP_ON_GRIGHT_CLICK,
   GCP_ON_RIGHT_CLICK,
   GCP_ON_WHELL_GUP,
   GCP_ON_WHELL_UP,
   GCP_ON_WHELL_GDOWN,
   GCP_ON_WHELL_DOWN,
   GCP_ON_MOUSE_GDOWN,
   GCP_ON_MOUSE_DOWN,
   GCP_ON_MOUSE_GLDOWN,
   GCP_ON_MOUSE_LDOWN,
   GCP_ON_MOUSE_GUP,
   GCP_ON_MOUSE_UP,
   GCP_ON_MOUSE_GMOTION,
   GCP_ON_MOUSE_MOTION,
   GCP_ON_GKEYDOWN,
   GCP_ON_KEYDOWN,
   GCP_ON_GDRAG,
   GCP_ON_DRAG,
   GCP_ON_MOUSE_GLHMOTION,
   GCP_ON_MOUSE_LHMOTION,
   GCP_ON_GDRAW,
   GCP_ON_DRAW,
   GCP_EVENT_GNONE,   
   GCP_MAX_FUNC_NUM,
};

struct GCP_Event
{
   /*SDL_KeyboardEvent keyboard;
   SDL_MouseButtonEvent mousebutton;
   SDL_TextEditingEvent textediting;
   SDL_TextInputEvent textinput;
   SDL_MouseWheelEvent mouswheel;
   SDL_MouseMotionEvent mousemotion;*/
   int eventType;

   int mousex, iMouseXRel;
   int mousey, iMouseYRel;
   bool isPassingOnlyGlobalEvent;

   GCP_Rect drawRect;
};

enum GCPE_FontType
{
   E_ARIAL
};

enum GCPE_TextAlign
{
   E_CENTER,
   E_LEFT,
   E_RIGHT
};

struct GCP_Font
{
   GCP_Font() :type(E_ARIAL), size(15), align(E_LEFT) {}
   GCPE_FontType type;
   GCPE_TextAlign align;
   short size;

};

typedef unsigned __int8 gcpUint8;
struct GCP_Color
{
   gcpUint8         r;
   gcpUint8         g;
   gcpUint8         b;
   gcpUint8         a;
   GCP_Color(gcpUint8 R, gcpUint8 G, gcpUint8 B, gcpUint8 A) :r(R), g(G), b(B), a(A) {}
   GCP_Color(gcpUint8 R, gcpUint8 G, gcpUint8 B) :r(R), g(G), b(B) { a = 255; }
   GCP_Color(int R, int G, int B) :r(R), g(G), b(B) { a = 255; }
   GCP_Color(){}
   bool operator==(const GCP_Color &X){
      if (r == X.r && g == X.g && b == X.b && a == X.a)
         return true;
      return false;
   }
   bool operator!=(const GCP_Color &X){
      if (r == X.r && g == X.g && b == X.b && a == X.a)
         return false;
      return true;
   }
};

#endif