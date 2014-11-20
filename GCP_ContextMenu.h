#ifndef GCP_ContextMenuH
#define GCP_ContextMenuH
#include "GCP_Button.h"
#include "GCP_Vector.h"
class GCP_ContextMenu;
typedef GCP_SPointer<GCP_ContextMenu> gcp_spContextMenu;
class GCP_ContextMenu: public GCP_FormComponent
{
	private:
		bool _isLocked;
		GCP_Vector<unsigned int> _iSeparators;
	public:
        GCP_Vector<gcp_spButton> menu;
		int iType;
		bool isContextMenuBlocking;

		GCP_ContextMenu();
		~GCP_ContextMenu();
		void setLock(bool flag);
		void addButton(GCP_SPointer<GCP_Button> &button);
		void addButton(string type);
		void open(int x, int y);
		void initTexture(SDL_Renderer *screen);
		void close(void* obj);
		gcp_formEvent OnMouseGlobalMotion(SDL_MouseMotionEvent motion);
		bool OnMouseGlobalLeftHoldMotion(SDL_MouseMotionEvent motion, int fx, int fy, int fw, int fh);
		gcp_formEvent OnMouseGlobalLeftClick(SDL_MouseButtonEvent mousebutton);
		bool OnMouseGlobalRightClick(SDL_MouseButtonEvent mousebutton);
      gcp_formEvent OnEvent(const GCP_Event &event);
      void OnDraw(const GCP_Event &event);
};
#endif
