#ifndef GCP_MessageBoxH
#define GCP_MessageBoxH
#include "GCP_ContextMenu.h"
#include "GCP_Edit.h"
#include "GCP_Label.h"
#include "GCP_Form.h"

class GCP_MessageBox: public GCP_Form
{

	private:
	GCP_SPointer<GCP_Button> buttonOk;
	public:		
	
	GCP_MessageBox(SDL_Renderer* screen, int _width, int _height)
	{
		_componentThatWasLeftClicked = NULL;
		isLocalEventsLocked = false;
		_isLocked = false;
		isLocked = false;
		_isDragStarted = false;
		isDraggingSomeComponent = false;
		isTransparent = false;
		isDragable = true;
		iPosition = 0;

		isParentLocking = false;
		isVisible = true;
		isShowTopRightButtons = true;
		xPos = 0; yPos = 0;
		width = _width; 
		height = _height;
		sdlRenderer = screen;
		_isContextMenuOpened = false;
		setStyle(&defStyles.defaultFormStyle);

		//cBackColor = c_white;
		//colorHeadMenuBackground = c_black;
		//colorHeadMenuFade = c_grey;
		//colorButtonBackground = c_white;
		
		
		formTopRightButtons = GCP_SPointer<GCP_ContextMenu>(new GCP_ContextMenu());
		formTopRightButtons->setPosition(xPos+width-20,yPos+5);
		formTopRightButtons->iType = GCP_MENU_MHORIZONTAL;
		formTopRightButtons->isContextMenuBlocking = false;
		formTopRightButtons->setStyle(&defStyles.defaultMenuStyle);
		

		xbutton = GCP_SPointer<GCP_Button> (new GCP_Button());			
		xbutton->setCaption("X");
		xbutton->setWidthHeight(15,20);	
		xbutton->setOnMouseLeftClick(this,&GCP_MessageBox::toggleBoxVisibility);
		xbutton->options.draw_order = -1000;
		formTopRightButtons->addButton(xbutton);
		addComponent(formTopRightButtons);

		xpanel = GCP_SPointer<GCP_Button> (new GCP_Button());
		xpanel->setWidthHeight(width,30);			
		xpanel->setPosition(xPos,yPos);		
		xpanel->options.draw_order = -999;
		xpanel->setStyle(&defStyles.defaultFormHeaderStyle);
		addComponent((GCP_SPointer<GCP_FormComponent>)xpanel);

		buttonOk = GCP_SPointer<GCP_Button> (new GCP_Button());
		buttonOk->setCaption("OK");
		buttonOk->setPosition(width/2-15,height-50);
		buttonOk->setWidthHeight(30,25);
		buttonOk->setStyle(&defStyles.defaultbuttonInvStyle);
		buttonOk->setOnMouseLeftClick(this, &GCP_MessageBox::toggleBoxVisibility);
		addComponent((GCP_SPointer<GCP_FormComponent>)buttonOk);

		messagelabel = GCP_SPointer<GCP_Label> (new GCP_Label());
		messagelabel->setPosition(25,50);
		messagelabel->setStyle(&defStyles.defaultFormHeaderStyle);
        addComponent(static_cast<gcp_spFormCmpnt>(messagelabel));

		messagebox = NULL;
	}

	void toggleBoxVisibility(void* obj)
	{
			isVisible = !isVisible;
	}

	void setFont(string dir)			
	{	
		/*sFontDir = dir; 
		xbutton->setFont(sFontDir);	
		xpanel->setFont(sFontDir);
		buttonOk->setFont(sFontDir);
		messagelabel->setFont(sFontDir);*/
	}

};
#endif
