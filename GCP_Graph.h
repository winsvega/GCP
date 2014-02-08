#ifndef GCP_GraphH
#define GCP_GraphH
#include "GCP_FormComponent.h"
#include "GCP_Vector.h"

struct gcp_graphdata
{
	double X,Y;
};

class GCP_Graph: public GCP_FormComponent
{
	public:
		GCP_Vector<gcp_graphdata*> *values;
		GCP_Graph();
		void OnDraw(SDL_Renderer* screen,int w, int h, int formx, int formy, int formw, int formh);
};

#endif




