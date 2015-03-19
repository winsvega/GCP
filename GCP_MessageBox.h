#ifndef GCP_MessageBoxH
#define GCP_MessageBoxH
#include "GCP_ContextMenu.h"
#include "GCP_Edit.h"
#include "GCP_Label.h"
#include "GCP_Form.h"

namespace gcp
{
	class GCP_MessageBox : public GCP_Form
	{

	private:
		GCP_SPointer<GCP_Button> buttonOk;
	public:

		GCP_MessageBox(int _width, int _height)
		{
			_componentThatWasLeftClicked = 0;
			isLocalEventsLocked = false;
			_isLocked = false;
			isLocked = false;
			_isDragStarted = false;
			isDraggingSomeComponent = false;
			isTransparent = false;
			_isDragable = true;
			iPosition = 0;

			isParentLocking = false;
			_isVisible = true;
			isShowTopRightButtons = true;
			setPosition(0, 0, _width, _height);
			_isContextMenuOpened = false;
			setStyle(GCP_DefaultStyle);

			//cBackColor = c_white;
			//colorHeadMenuBackground = c_black;
			//colorHeadMenuFade = c_grey;
			//colorButtonBackground = c_white;


			formTopRightButtons = GCP_SPointer<GCP_ContextMenu>(new GCP_ContextMenu());
			formTopRightButtons->setPosition(getPosition().x() + getPosition().width() - 20, getPosition().y() + 5);
			formTopRightButtons->iType = GCP_MENU_MHORIZONTAL;
			formTopRightButtons->isContextMenuBlocking = false;
			formTopRightButtons->setStyle(GCP_ButtonWhiteStyle);


			xbutton = GCP_SPointer<GCP_Button>(new GCP_Button());
			xbutton->setCaption("X");
			xbutton->setWidthHeight(15, 20);
			xbutton->setOnMouseLeftClick(this, &GCP_MessageBox::toggleBoxVisibility);
			xbutton->setStyle(GCP_ButtonWhiteStyle);
			xbutton->options.draw_order = -1000;
			formTopRightButtons->addButton(xbutton);
			addComponent(formTopRightButtons);

			xpanel = GCP_SPointer<GCP_Button>(new GCP_Button());
			xpanel->setPosition(_position.x(), _position.y(), _position.width(), 30);
			xpanel->options.draw_order = -999;
			xpanel->setStyle(GCP_PanelBlackStyle);
			addComponent((GCP_SPointer<GCP_FormComponent>)xpanel);

			buttonOk = GCP_SPointer<GCP_Button>(new GCP_Button());
			buttonOk->setCaption("OK");
			buttonOk->setPosition(_position.width() / 2 - 15, _position.height() - 50, 30, 25);
			buttonOk->setStyle(GCP_ButtonWhiteStyle);
			buttonOk->setOnMouseLeftClick(this, &GCP_MessageBox::toggleBoxVisibility);
			addComponent((GCP_SPointer<GCP_FormComponent>)buttonOk);

			messagelabel = GCP_SPointer<GCP_Label>(new GCP_Label());
			messagelabel->setPosition(25, 50);
			messagelabel->setStyle(GCP_DefaultStyle);
			addComponent(static_cast<gcp_spFormComponent>(messagelabel));

			messagebox = 0;
		}

		void toggleBoxVisibility(void* obj)
		{
			setVisible(!isVisible());
		}
	};
}
#endif
