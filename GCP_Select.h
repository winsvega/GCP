#ifndef GCP_SelectH
#define GCP_SelectH
#include "GCP_FormComponent.h"
#include "GCP_Button.h"


//¬€œ¿ƒ¿ﬁŸ»… —œ»—Œ 
class GCP_Select: public GCP_FormComponent
{
	private:
		GCP_Button* _dropdownButton;
		GCP_Vector<GCP_Button*> items;
		int _iSelectedItem;
		bool _isDrawingDropDown;
		string _sSelectedText;

	public:
		
		GCP_Select()
		{
			_iSelectedItem = -1;
			_isDrawingDropDown = false;
			_dropdownButton = new GCP_Button();
			_dropdownButton->setWidthHeight(15,15);
			_dropdownButton->setCaption("\\/");	
			_dropdownButton->setOnMouseLeftClick(this,&GCP_Select::OnDropDown);
		}
		~GCP_Select()
		{
			delete _dropdownButton;
			for(int i=0; i<items.size(); i++)
				delete items.at(i);
		}

		void addItem(string s)
		{
			GCP_Button *button = new GCP_Button();
			button->setWidthHeight(width,height);
			button->setColor(cBackColor,cTextColor,c_aquadark,c_white);
			button->setCaption(s);
			button->setFont(getFont());
			button->isVisible = true;
			button->setOnMouseLeftClick(this, &GCP_Select::OnDroppedButtonClick);
			items.push_back(button);
		}

		void selectItem(int i)
		{
			if(i<items.size() && i>=0)
				_iSelectedItem = i;
		}

		string getSelectedItem()
		{
			if(_iSelectedItem != -1)
				return items.at(_iSelectedItem)->getCaption();
				return "";
		}

		int getSelectedItemIndex()
		{
			return _iSelectedItem;
		}

		void OnDroppedButtonClick(void *obj)
		{
			GCP_Button *button  = (GCP_Button*) obj;
			if(button != 0){
				_sSelectedText = button->getCaption();
				_isDrawingDropDown = false;

				_iSelectedItem = -1;
				for(int i=0; i<items.size(); i++)
				{
					if(items.at(i)==button)
						_iSelectedItem = i;
				}
			}			
		}

		void OnDropDown(void* obj)
		{
			_isDrawingDropDown = !_isDrawingDropDown;
			if(!_isDrawingDropDown)			
				for(int i=0; i<items.size(); i++)
					items.at(i)->isVisible = false;
		}

		void OnDraw(SDL_Renderer* screen,int w, int h, int formx, int formy, int formw, int formh)
		{
			if(!isVisible)
			return;

			_dropdownButton->setWidthHeight(height,height);
			_dropdownButton->setPosition(xPos+width-_dropdownButton->width,yPos);
			_dropdownButton->setColor(cBorderColor,c_white,c_aquadark,c_black);
			_dropdownButton->setFont(getFont());
			GCP_Draw::Draw_FillRound(screen, xPos, yPos, width, height, 1, cBorderColor); 
			GCP_Draw::Draw_FillRound(screen, xPos+iBorderWidth, yPos+iBorderWidth, width-iBorderWidth*2, height-iBorderWidth*2, 1, cBackColor); 

			if(_isDrawingDropDown){
				GCP_Draw::Draw_FillRect(screen,xPos,yPos+25,width,25*(items.size()),cBackColor);
				for(int i=0; i<items.size(); i++)
				{
					items.at(i)->isVisible = true;
					items.at(i)->setPosition(xPos,yPos+25*(i+1));					
					items.at(i)->OnDraw(screen,w,h,formx,formy,formw,formh);
				}
			}
					

			GCP_Draw::renderText(_sSelectedText,xPos+iBorderWidth*2,yPos+iBorderWidth*2,screen,&drawdata,cTextColor,getFont().c_str(),14);
	

			_dropdownButton->OnDraw(screen,w,h,formx,formy,formw,formh);	
			basicOnDraw(screen, formx, formy, formw, formh);
				
		}

		gcp_formEvent OnEvent( const int GCP_EVENT, sdl_events events)
		{
			gcp_formEvent evt;
			evt.isEventInsideForm = false;
			evt.isEventOnFormHead = false;
			evt.isFormDragged = false;
			if(!isVisible)
				return evt;


			if(GCP_EVENT%2 !=0)
			{
				_dropdownButton->OnEvent(GCP_EVENT, events);
				if(!events.isPassingOnlyGlobalEvent)
				if(_dropdownButton->checkCollisionBox(events.mousex, events.mousey))
					_dropdownButton->OnEvent(GCP_EVENT+1, events);

				for(unsigned int i=0; i<items.size(); i++){
						items.at(i)->OnEvent(GCP_EVENT,events);
						if(!events.isPassingOnlyGlobalEvent)
						if(items.at(i)->checkCollisionBox(events.mousex, events.mousey)){
							items.at(i)->OnEvent(GCP_EVENT+1,events);
						}
				}		

				if(GCP_EVENT == GCP_ON_MOUSE_GUP)
					_isDrawingDropDown = false;

			}

			basicOnEvent(GCP_EVENT, events);
			return evt;
		}
};
#endif