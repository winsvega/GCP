#ifndef GCP_MessageBoxH
#define GCP_MessageBoxH
#include "GCP_ContextMenu.h"
#include "GCP_Edit.h"
#include "GCP_Label.h"
#include "GCP_Form.h"

class GCP_MessageBox: public GCP_Form
{

	private:
	GCP_Button *buttonOk;
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


		cBackColor = c_white;
		colorHeadMenuBackground = c_black;
		colorHeadMenuFade = c_grey;
		colorButtonBackground = c_white;
		
		
		formTopRightButtons = new GCP_ContextMenu();
		formTopRightButtons->setPosition(xPos+width-20,yPos+5);
		formTopRightButtons->iType = GCP_MENU_MHORIZONTAL;
		formTopRightButtons->isContextMenuBlocking = false;
		formTopRightButtons->setColor(c_white, c_black,c_aquadark,c_white);


		xbutton = new GCP_Button();			
		xbutton->setCaption("X");
		xbutton->setWidthHeight(15,20);	
		xbutton->setOnMouseLeftClick(this,&GCP_MessageBox::toggleBoxVisibility);
		xbutton->options.draw_order = -1000;
		formTopRightButtons->addButton(xbutton);
		addComponent(formTopRightButtons);

		xpanel = new GCP_Button();
		xpanel->setWidthHeight(width,30);			
		xpanel->setPosition(xPos,yPos);		
		xpanel->options.draw_order = -999;
		xpanel->cBackColor = c_black;
		xpanel->cBackColorHover = c_black;
		addComponent(xpanel);

		buttonOk = new GCP_Button();
		buttonOk->setCaption("OK");
		buttonOk->setPosition(width/2-15,height-50);
		buttonOk->setWidthHeight(30,25);
		buttonOk->setColor(c_black,c_white,c_aquadark,c_black);
		buttonOk->setOnMouseLeftClick(this, &GCP_MessageBox::toggleBoxVisibility);
		addComponent(buttonOk);

		messagelabel = new GCP_Label();
		messagelabel->setPosition(25,50);
		messagelabel->cTextColor = c_black;
		addComponent(messagelabel);

		messagebox = NULL;
	}

	void toggleBoxVisibility(void* obj)
	{
			isVisible = !isVisible;
	}

	void setFont(string dir)			{	
	sFontDir = dir; 
	xbutton->setFont(sFontDir);	
	xpanel->setFont(sFontDir);
	buttonOk->setFont(sFontDir);
	messagelabel->setFont(sFontDir);
}

};
#endif