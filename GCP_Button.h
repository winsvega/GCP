#ifndef GCP_ButtonH
#define GCP_ButtonH
#include "GCP_FormComponent.h"

class GCP_Button;
typedef GCP_SPointer<GCP_Button> gcp_spButton;
class GCP_Button: public GCP_FormComponent
{

	public:
		GCP_Button();
		void OnDraw(SDL_Renderer* screen,int w, int h, int formx, int formy, int formw, int formh);
		int iType;
		bool checked;
		
};

#endif
