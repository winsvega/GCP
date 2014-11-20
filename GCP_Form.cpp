#include "GCP_ContextMenu.h"
#include "GCP_Edit.h"
#include "GCP_Label.h"
#include "GCP_CheckBox.h"
#include "GCP_Form.h"
#include "GCP_MessageBox.h"

GCP_Form::GCP_Form(int _width, int _height)
{
	_componentThatWasLeftClicked = 0;			//код указателя на компонент по которому мы кликнули
	_isLocked = false;							//заблокирована форма?
	_isDragStarted = false;						//начали перетаскивать компонент?
	isLocalEventsLocked = false;				//заблокировать обработку локальных событий на форме?
	isDraggingSomeComponent = false;			//перетаскивается ли компонент в данный момент?
	isTransparent = false;						//Рисовать форму прозрачно поверх других?
	_isDragable = true;							//Можно ли таскать форму по буферу или другой форме?
	iPosition = 0;

	isParentLocking = false;					//Блокировать родительскую форму если работает эта форма
	_isVisible = true;							//Можно вообще форму не рисовать
	isShowTopRightButtons = true;				//Показывать крестики нолики в правом верхнем углу
   setPosition(0, 0, _width, _height);
	_swidth = _width;							   //Ширина буфера на котором рисуем
	_sheight = _height;							//Высота буфера на котором рисуем
	//_sdlPixelFormat = screen->format;
	_isContextMenuOpened = false;				//Открыто ли контекстное меню  на форме?
	isLocked = false;							//Можно заблокировать обработку компонент на форме
	setStyle(GCP_DefaultStyle);

	//cBackColor = c_white;						//Цвет задника
	//colorHeadMenuBackground = c_black;			//Фон верхней полоски
	//colorHeadMenuFade = c_grey;					//Фон верхней полоски если форма не активна
	//colorButtonBackground = c_white;			//Фон кнопок????


	//Крестики нолики
	formTopRightButtons = GCP_SPointer<GCP_ContextMenu>(new GCP_ContextMenu());
   formTopRightButtons->setPosition(_position.x() + _position.width() - 20, _position.y() + 5);
	formTopRightButtons->iType = GCP_MENU_MHORIZONTAL;
	formTopRightButtons->isContextMenuBlocking = false;			//Меню не блокирует другие компоненты на форме
	formTopRightButtons->setStyle(GCP_ButtonWhiteStyle);
	formTopRightButtons->setVisible(true);


	xbutton = GCP_SPointer<GCP_Button> (new GCP_Button());
	xbutton->setCaption("X");
	xbutton->setWidthHeight(15,20);
	xbutton->setStyle(GCP_ButtonWhiteStyle);
	xbutton->setOnMouseLeftClick(this,&GCP_Form::toggleVisibility);
	xbutton->options.draw_order = -1000;
	formTopRightButtons->addButton(xbutton);
	addComponent(formTopRightButtons);

	//Верхняя полоска на форме (для обработки драгендроп)
	xpanel = GCP_SPointer<GCP_Button> (new GCP_Button());
   xpanel->setWidthHeight(_position.width(), 30);
   xpanel->setPosition(_position.x(), _position.y());
	xpanel->options.draw_order = -999;
   xpanel->setStyle(GCP_PanelBlackStyle);
 	addComponent((GCP_SPointer<GCP_FormComponent>)xpanel);

	//Сообщение с алармом
	messagebox = GCP_SPointer<GCP_Form>(new GCP_MessageBox(450,150));
	messagebox->isParentLocking = true;
	messagebox->setVisible(false);
	messagebox->setDragable(false);
	messagebox->options.draw_order = -100;
   messagebox->setPosition(_position.width() / 2 - messagebox->_position.width() / 2, _position.height() / 2 - messagebox->_position.height() / 2);
	const char *caprion = "УВЕДОМЛЕНИЕ";
	messagebox->setCaption(GCP_Math::RUSCP1251_TO_WCHAR(caprion));   
	addSubForm(messagebox);

}

void GCP_Form::showmessage(string text, bool block)
{
	messages.push_back(text);
}

void GCP_Form::showmessage(int text, bool block)
{
	messages.push_back(GCP_Math::intToString(text));
}
void GCP_Form::setBufferSize(int screenw, int screenh)
{
	_swidth = screenw;
	_sheight = screenh;
	//if(width > screenw || width < 0 || height > screenh || height < 0 )
	//	throw "Form size doesn't match screen size";

}

void GCP_Form::setFont(string dir)			{
	//!!! передаем шрифт своим компонентам
	/*getStyle()->sFontDir = dir;
	xbutton->setFont(getStyle()->sFontDir);
	xpanel->setFont(getStyle()->sFontDir);
	messagebox->setFont(getStyle()->sFontDir);*/
}

GCP_Form::~GCP_Form()	{
	//!!!Удаляем указатели из памяти по уничтожению формы!!!!!
	/*for(int i=0; i<_subForms.size(); i++)
		delete _subForms.at(i);

	for(int i=0; i<_components.size(); i++)
		delete _components.at(i);

	for(int i=0; i<_contextmenus.size(); i++)
		delete _contextmenus.at(i);*/

}

void GCP_Form::addComponent(GCP_SPointer<GCP_ContextMenu> const &component)
{
	_contextmenus.push_back(component);
}

void GCP_Form::addComponent(GCP_SPointer<GCP_FormComponent> const &component)
{
	for(unsigned int i=0; i<_components.size(); i++)
		if(component == _components.at(i))			//Два раза одно и тоже не принимаем
			return;

	//Координаты компонента идут оносительно левого верхнего угла формы
   const GCP_Rect formPos = _position;
   const GCP_Rect compPos = component->getPosition();

   component->setPosition(formPos.x() + compPos.x(), formPos.y() + compPos.y());
	//component->setFont(getFont());
	_components.push_back(component);
    GCP_Math::quickSort<gcp_spFormComponent>(&_components,0,_components.size()-1, GCP_SORTBY_DRAWORDER);
}

void GCP_Form::removeComponent(GCP_SPointer<GCP_FormComponent> const &component)
{
	for(unsigned int i=0; i<_components.size(); i++)
		if(_components.at(i) == component){
			_components.erase(i);
			break;
		}
}

void GCP_Form::toggleVisibility(void* obj)
{
	setVisible(!isVisible());
}

void GCP_Form::addSubForm(GCP_SPointer<GCP_Form> &form)
{
	//!!! Шрифт передаем!!!
	//form->setFont(getFont());
	form->setBufferSize(_swidth,_sheight);
	_subForms.push_back(form);
    GCP_Math::quickSort<gcp_spForm>(&_subForms,0,_subForms.size()-1, GCP_SORTBY_DRAWORDER);
}

void GCP_Form::setPosition(int x, int y, int width, int height)
{
   _position.bottomRight.X = width;
   _position.bottomRight.Y = height;
   setPosition(x, y);
}

void GCP_Form::setPosition(int x, int y)
{
   int deltaX = x - _position.x();
   int deltaY = y - _position.y();
   _position.topLeft.X = x;
   _position.topLeft.Y = y;
   for (unsigned int i = 0; i<_components.size(); i++)
      _components.at(i)->setPosition(_components.at(i)->getPosition().x() + deltaX, _components.at(i)->getPosition().y() + deltaY);
   for (unsigned int i = 0; i<_contextmenus.size(); i++)
      _contextmenus.at(i)->setPosition(_contextmenus.at(i)->getPosition().x() + deltaX, _contextmenus.at(i)->getPosition().y() + deltaY);

}

void GCP_Form::setCaption(const std::string& str)
{
   xpanel->setCaption(str);
   xpanel->setWidthHeight(getPosition().width(), 30);
}

void GCP_Form::OnDraw(const GCP_Event &event)
{
	if(!isVisible())
		return;

	if(!isShowTopRightButtons)
		xbutton->setVisible(false);

   GCP_Event drawEvent = event;
   drawEvent.drawRect = _position;

	if(!isTransparent)
      GCP_Draw::Render()->Draw_FillRound(_position, 1, getStyle()->backgroundColor);
   GCP_Draw::Render()->Draw_Round(_position, 1, getStyle()->headBackground);


	//!!! Сортировку тоже надо один раз сообразить
	//GCP_Math::quickSort<GCP_FormComponent*>(&_components,0,_components.size()-1, GCP_SORTBY_DRAWORDER);
	for(unsigned int i=0; i<_components.size(); i++)
      _components.at(i)->OnDraw(drawEvent);

	//Всплывающие подсказки рисуются поверх компонент
	for(unsigned int i=0; i<_components.size(); i++)
      _components.at(i)->OnDrawInfo(drawEvent);

	//Загаловок формы
   //GCP_Draw::Render()->Draw_Text(_sCaption, xPos + width / 2 - 65, yPos + xpanel->height / 5, getStyle(), &drawdata);

	//Рисуем Контекстные меню
	_isContextMenuOpened = false;
	for(unsigned int i=0; i<_contextmenus.size(); i++){
		_contextmenus.at(i)->setLock(_isContextMenuOpened);
      _contextmenus.at(i)->OnDraw(drawEvent);
		if(_contextmenus.at(i)->isVisible() && _contextmenus.at(i)->isContextMenuBlocking)
			_isContextMenuOpened = true;	//будем блокировать компоненты пока открыто это меню
	}

   basicOnDraw(drawEvent);

	//Сообщения можно сделать с потоками. тогда они могут блокировать всю программу пока не нажмешь кнопку ОК
	//Но тогда надо отделять интерфейс от главного потока обработки событий SDL
	if(messages.size())
		if(messagebox->isVisible() == false){
			messagebox->messagelabel->text = messages.pop_first();
			messagebox->setVisible(true);
		}

	//!!! Сортировку тоже надо один раз сообразить
    GCP_Math::quickSort<gcp_spForm>(&_subForms,0,_subForms.size()-1, GCP_SORTBY_DRAWORDER);
	bool isHavingSubformsThatLocking = false;
	for(unsigned int i=0; i<_subForms.size(); i++){
      _subForms.at(i)->OnDraw(drawEvent);
		if(_subForms.at(i)->isParentLocking && _subForms.at(i)->isVisible())
			isHavingSubformsThatLocking = true;
	}

	//По хорошему месадж бокс должен блокировать другие формы с
	//следовательно рисоваться и обрабатываться он должен отдельно
	//messagebox->OnDraw(screen, width, height);

	_isLocked = false;
	if(isHavingSubformsThatLocking||isLocked)
		_isLocked = true;

	return;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////KEY EVENTS
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////OnKeyDown
////////////////////////////////////////////////////////////////////////////////////////////
bool GCP_Form::OnTextInput(const GCP_Event& event)
{
	if(!_isVisible)
		return false;

	for(unsigned int i=0; i<_subForms.size(); i++){
		_subForms.at(i)->OnTextInput(event);
	}

	if(_isLocked)
		return false;

	if(!_isContextMenuOpened)
		for(unsigned int i=0; i<_components.size(); i++)
         _components.at(i)->OnTextInput(event);

   basicOnTextInput(event);

	return true;
}

bool GCP_Form::OnTextEdit(const GCP_Event& event)
{
	if(!_isVisible)
		return false;

	for(unsigned int i=0; i<_subForms.size(); i++){
		_subForms.at(i)->OnTextEdit(event);
	}

	if(_isLocked)
		return false;

	if(!_isContextMenuOpened)
		for(unsigned int i=0; i<_components.size(); i++)
			_components.at(i)->OnTextEdit(event);

	basicOnTextEdit(event);
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////OnEvent
////////////////////////////////////////////////////////////////////////////////////////////
   gcp_formEvent GCP_Form::OnEvent(const GCP_Event &cevent)
		{
			//Будем возвращать где находился курсор когда произошло событие
			gcp_formEvent evt, other_evt;
			evt.isEventInsideForm = cevent.isPassingOnlyGlobalEvent;
			evt.isEventOnFormHead = false;

         GCP_Event event = cevent;  //Чуть подправим событие.

			if(!_isVisible)
				return evt;

			//WHY?  EVENTORDER = DRAWORDER^-1
            GCP_Math::quickSort<gcp_spForm>(&_subForms,0,_subForms.size()-1, GCP_SORTBY_EVENTORDER);
			//Передаем всем дочерним формам глобальное событие
			for(unsigned int i=0; i<_subForms.size(); i++){
				other_evt = _subForms.at(i)->OnEvent(event);
				//Запоминаем если это событие произошло внутри хоть одной из активных форм
				evt.isEventInsideForm = evt.isEventInsideForm || other_evt.isEventInsideForm;
				//Все остальные формы получат только глобальные события если хоть на одной мы обработаем локальные
				event.isPassingOnlyGlobalEvent = event.isPassingOnlyGlobalEvent || evt.isEventInsideForm;
			}

			if(_isLocked){
				evt.isEventInsideForm = false;
				evt.isEventOnFormHead = false;
				return evt;
			}

         if (event.eventType == GCP_ON_MOUSE_GUP){
				_isDragStarted = false;
				isDraggingSomeComponent = false;
			}

			//ОПТИМИЗИРОВАТЬ КАК ТО ОБРАБОТКУ БОЛЬШОГО ЧИСЛА КОМПОНЕНТ? ВРОДЕ ДО 1000-2000 работает нормально
			//РАСЧЕТ НА ТО ЧТО КОМПОНЕНТ БУДЕТ МНОГО > 400
			///СОРТИРОВКА КОМПОНЕНТ И НА ВЫХОДЕ СПИСОК ТОЛЬКО ТЕХ У КОТОРЫХ КЛЮЧЕНА ПРОСЛУШКА
			///GCP_EVENT или GCP_EVENT+1
			///НАДО ЛИ?


			//Предположим мы не обрабатываем никакое локальное событие у компонент
			bool isMouseOverSomeComponent = false;
			if(!_isContextMenuOpened && !isDraggingSomeComponent){
				for(unsigned int i=0; i<_components.size(); i++){
					_components.at(i)->OnEvent(event);		//Вызываем глобальное событие у наших компонент

					//Если глобальное событие произошло над дочерней формой, локальные события для наших компонент не обрабатываем
					if(!isLocalEventsLocked)
					if(!isMouseOverSomeComponent && !evt.isEventInsideForm)	{
						if(_components.at(i)->checkCollisionBox(event.mousex, event.mousey)){
							_components.at(i)->OnEvent(MakeEventLocal(event));
							if(event.eventType == GCP_ON_MOUSE_GLDOWN)
								_componentThatWasLeftClicked = _components.at(i);

                     if (_components.at(i)->isEventUnderneathBloacking())
								isMouseOverSomeComponent = true;
							//Передали локальное событие компоненту по этим координатам.
							//Далее локальные события более не передаем
						}
					}
				}
			}

			event.isPassingOnlyGlobalEvent = evt.isEventInsideForm;
			if(!isLocalEventsLocked)
			for(unsigned int i=0; i<_contextmenus.size(); i++)
				_contextmenus.at(i)->OnEvent(event);

			if(event.eventType == GCP_ON_MOUSE_GUP)
				_componentThatWasLeftClicked = 0;
         if (event.eventType == GCP_ON_MOUSE_GLDOWN)
				_isClickedOnTopHeader = false;

			//Обрабатываем глобальное и локальные события для формы
			basicOnEvent(event);
			if (!event.isPassingOnlyGlobalEvent)
			if (checkCollisionBox(event.mousex, event.mousey)){
				mouse_x = event.mousex;
				mouse_y =  event.mousey;
				evt.isEventInsideForm = true;
				basicOnEvent(MakeEventLocal(event));
				if(event.mousey<_position.y()+xpanel->getPosition().height()){
					if(event.eventType == GCP_ON_MOUSE_GLDOWN)
						_isClickedOnTopHeader = true;
					evt.isEventOnFormHead = true;
				}
			}
			return evt;
		}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////OnMouseGlobalLeftHoldMotion
////////////////////////////////////////////////////////////////////////////////////////////
 gcp_formEvent GCP_Form::OnMouseGlobalLeftHoldMotion(const GCP_Event& cevent)
 {
	gcp_formEvent evt;
	evt.isEventInsideForm = false;
	evt.isFormDragged = false;
	if(!_isVisible)
		return evt;

   GCP_Event event = cevent;
   event.drawRect = GCP_Rect(_position.x(), _position.y(), _position.width(), _position.height());

	//WHY?  EVENTORDER = DRAWORDER^-1
    GCP_Math::quickSort<gcp_spForm>(&_subForms,0,_subForms.size()-1, GCP_SORTBY_EVENTORDER);
	bool isDragged = false;
	bool isEventInsideChildForm = false;
	if(!_isDragStarted || _isLocked){
	for(unsigned int i=0; i<_subForms.size(); i++){
		evt = _subForms.at(i)->OnMouseGlobalLeftHoldMotion(event);
		isDragged = evt.isFormDragged; //If child form is dragged
		isEventInsideChildForm = evt.isEventInsideForm;

		if(isDragged) {
			isDraggingSomeComponent = true; //Consider sub form as dragging component
			break;
		}
	}}

	if(_isLocked){
		evt.isEventInsideForm = false;
		evt.isFormDragged = false;
		return evt;
	}

	if(!_isContextMenuOpened){
		if (!isDragged && isDragable()){
			if (_isClickedOnTopHeader || _isDragStarted){
					int xPosStart = _position.x(), yPosStart = _position.y();
               _position.topLeft.X += event.iMouseXRel;
					_position.topLeft.Y += event.iMouseYRel;
               _position.topLeft.X = (int)std::fmax(0, std::fmin(_swidth - _position.width(), _position.x()));
               _position.topLeft.Y = (int)std::fmax(0, std::fmin(_sheight - _position.height(), _position.y()));

					int deltaX = _position.x() - xPosStart;
               int deltaY = _position.y() - yPosStart;
					for(unsigned int i=0; i<_components.size(); i++)
               {
						GCP_Rect previousPos = _components.at(i)->getPosition();
						_components.at(i)->setPosition(previousPos.x()+deltaX,previousPos.y()+deltaY);
					}

					for(unsigned int i=0; i<_contextmenus.size(); i++)
               {
						if(!_contextmenus.at(i)->isContextMenuBlocking)		
                  {
                     GCP_Rect previousPos = _contextmenus.at(i)->getPosition();
						   _contextmenus.at(i)->setPosition(previousPos.x()+deltaX,previousPos.y()+deltaY);
						}
					}
					_isDragStarted = true;

					evt.isEventInsideForm = false;
					evt.isFormDragged = _isDragStarted;
					return evt;
			}
		}

		bool isComponentClicked = false;
		if(!_isDragStarted){
			for(unsigned int i=0; i<_components.size(); i++){
				_components.at(i)->OnMouseGlobalLeftHoldMotion(event);
				/*if(!isComponentClicked && !isDraggingSomeComponent)
				if(_components.at(i)==_componentThatWasLeftClicked){
					_components.at(i)->OnMouseLeftHoldMotion(motion,_position.x() yPos+xpanel->height,width,height-xpanel->height);
					isComponentClicked = true;
					isDraggingSomeComponent = true;
				}*/
			}

			///REFACTOR THIS!!!!
			if(_componentThatWasLeftClicked)
				if(_componentThatWasLeftClicked->isDragable()&& !isComponentClicked && !isDraggingSomeComponent)
            {               
               event.drawRect = GCP_Rect(_position.x(), _position.y() + xpanel->getPosition().height(), _position.width(), _position.height() - xpanel->getPosition().height());
               _componentThatWasLeftClicked->OnMouseLeftHoldMotion(event);
					isComponentClicked = true;
					isDraggingSomeComponent = true;
				}

		}


	}

	if (checkCollisionBox(event.drawRect.x(),event.drawRect.y())&&!isEventInsideChildForm){
		evt.isEventInsideForm = true;
		basicOnMouseLeftHoldMotion(event);
	}

	basicOnMouseGlobalLeftHoldMotion(event);

	evt.isFormDragged = _isDragStarted;
	return evt;
}


