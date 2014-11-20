#ifndef GCP_SelectH
#define GCP_SelectH
#include "GCP_FormComponent.h"
#include "GCP_Button.h"


//¬€œ¿ƒ¿ﬁŸ»… —œ»—Œ 
class GCP_Select: public GCP_FormComponent
{
	private:
		GCP_SPointer<GCP_Button> _dropdownButton;
        GCP_Vector<gcp_spButton> items;
		int _iSelectedItem;
		bool _isDrawingDropDown;
		string _sSelectedText;

	public:

		GCP_Select()
		{
			_iSelectedItem = -1;
			_isDrawingDropDown = false;
         _dropdownButton = GCP_SPointer<GCP_Button>(new GCP_Button());
			_dropdownButton->setWidthHeight(15,15);
			_dropdownButton->setCaption("\\/");
			_dropdownButton->setOnMouseLeftClick(this,&GCP_Select::OnDropDown);
		}
		~GCP_Select()
		{
			//delete _dropdownButton;
			/*for(int i=0; i<items.size(); i++)
				delete items.at(i);*/
		}

		void addItem(string s)
		{
         gcp_spButton button = GCP_SPointer<GCP_Button>(new GCP_Button());
         button->setWidthHeight(_position.width(), _position.height());
         button->setStyle(GCP_ButtonBlackStyle);
			button->setCaption(s);			
			button->setVisible(true);
			button->setOnMouseLeftClick(this, &GCP_Select::OnDroppedButtonClick);			
			items.push_back(button);
		}
      
		void selectItem(unsigned int i)
		{
			if(i<items.size() && i>=0)
			{
				_iSelectedItem = i;
				_sSelectedText = items.at(_iSelectedItem)->getCaption();
			}
		}

		const string& getSelectedItem()
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
			GCP_SPointer<GCP_Button> button  = GCP_SPointer<GCP_Button>((GCP_Button*) obj);
			if(button != 0){
				_sSelectedText = button->getCaption();
				_isDrawingDropDown = false;

				_iSelectedItem = -1;
				for(unsigned int i=0; i<items.size(); i++)
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
				for(unsigned int i=0; i<items.size(); i++)
					items.at(i)->setVisible(false);
		}

      void OnDraw(const GCP_Event &event)
		{
			if(!isVisible())
			return;

         _dropdownButton->setWidthHeight(_position.height(), _position.height());
         _dropdownButton->setPosition(_position.x() + _position.width() - _dropdownButton->getPosition().width(), _position.y());
			_dropdownButton->setStyle(GCP_ButtonBlackStyle); //!!!REV
			
			GCP_Draw::Render()->Draw_FillRound(_position, 1, getStyle()->borderColor);

         int iBorderWidth = getStyle()->borderWidth;
         GCP_Draw::Render()->Draw_FillRound(_position.x() + iBorderWidth, _position.y() + iBorderWidth, _position.width() - iBorderWidth * 2, _position.height() - iBorderWidth * 2, 1, getStyle()->backgroundColor);

			if(_isDrawingDropDown){
            GCP_Draw::Render()->Draw_FillRect(_position.x(), _position.y() + 25, _position.width(), 25 * (items.size()), getStyle()->backgroundColor);
				for(unsigned int i=0; i<items.size(); i++)
				{
               items.at(i)->setVisible(true);
               items.at(i)->setPosition(_position.x(), _position.y() + 25 * (i + 1));
					items.at(i)->OnDraw(event);
				}
			}
			else
				for(unsigned int i=0; i<items.size(); i++)
					items.at(i)->setVisible(false);



         iBorderWidth = getStyle()->borderWidth;
         GCP_Draw::Render()->Draw_Text(_sSelectedText, _position.x() + iBorderWidth * 2, _position.y() + iBorderWidth * 2, getStyle(), &drawdata);

			_dropdownButton->OnDraw(event);
			basicOnDraw(event);
		}

		gcp_formEvent OnEvent(const GCP_Event &event)
		{
			gcp_formEvent evt;
			evt.isEventInsideForm = false;
			evt.isEventOnFormHead = false;
			evt.isFormDragged = false;
			if(!isVisible())
				return evt;


         if (event.eventType% 2 != 0) //if Event is Global
			{
            _dropdownButton->OnEvent(event);
				if(!event.isPassingOnlyGlobalEvent)
				if(_dropdownButton->checkCollisionBox(event.mousex, event.mousey))
               _dropdownButton->OnEvent(MakeEventLocal(event));

				for(unsigned int i=0; i<items.size(); i++){
						items.at(i)->OnEvent(event);
						if(!event.isPassingOnlyGlobalEvent)
						if(items.at(i)->isVisible())
						if(items.at(i)->checkCollisionBox(event.mousex, event.mousey))
                  {
                     items.at(i)->OnEvent(MakeEventLocal(event));
						}
				}

            if (event.eventType == GCP_ON_MOUSE_GUP)
					_isDrawingDropDown = false;

			}

			basicOnEvent(event);
			return evt;
		}
};
#endif
