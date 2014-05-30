#include "GCP_ContextMenu.h"
#include "GCP_Edit.h"
#include "GCP_Label.h"
#include "GCP_CheckBox.h"
#include "GCP_Form.h"
#include "GCP_MessageBox.h"

GCP_Form::GCP_Form(SDL_Renderer* screen, int _width, int _height)
{
	_componentThatWasLeftClicked = 0;			//код указателя на компонент по которому мы кликнули
	_isLocked = false;							//заблокирована форма?
	_isDragStarted = false;						//начали перетаскивать компонент?
	isLocalEventsLocked = false;				//заблокировать обработку локальных событий на форме?
	isDraggingSomeComponent = false;			//перетаскивается ли компонент в данный момент?
	isTransparent = false;						//Рисовать форму прозрачно поверх других?
	isDragable = true;							//Можно ли таскать форму по буферу или другой форме?
	iPosition = 0;								

	isParentLocking = false;					//Блокировать родительскую форму если работает эта форма
	isVisible = true;							//Можно вообще форму не рисовать
	isShowTopRightButtons = true;				//Показывать крестики нолики в правом верхнем углу
	xPos = 0; yPos = 0;							//Верхний левый угол
	width = _width;								//Ширина 
	height = _height;							//Высота
	_swidth = _width;							//Ширина буфера на котором рисуем
	_sheight = _height;							//Высота буфера на котором рисуем
	sdlRenderer = screen;
	//_sdlPixelFormat = screen->format;
	_isContextMenuOpened = false;				//Открыто ли контекстное меню  на форме?
	isLocked = false;							//Можно заблокировать обработку компонент на форме
	setStyle(&defStyles.defaultFormStyle);

	//cBackColor = c_white;						//Цвет задника
	//colorHeadMenuBackground = c_black;			//Фон верхней полоски
	//colorHeadMenuFade = c_grey;					//Фон верхней полоски если форма не активна
	//colorButtonBackground = c_white;			//Фон кнопок????
	
	
	//Крестики нолики
	formTopRightButtons = GCP_SPointer<GCP_ContextMenu>(new GCP_ContextMenu());	
	formTopRightButtons->setPosition(xPos+width-20,yPos+5);
	formTopRightButtons->iType = GCP_MENU_MHORIZONTAL;
	formTopRightButtons->isContextMenuBlocking = false;			//Меню не блокирует другие компоненты на форме
	formTopRightButtons->setStyle(&defStyles.defaultMenuStyle);


	xbutton = GCP_SPointer<GCP_Button> (new GCP_Button());			
	xbutton->setCaption("X");
	xbutton->setWidthHeight(15,20);	
	xbutton->setStyle(&defStyles.defaultbuttonStyle);
	xbutton->setOnMouseLeftClick(this,&GCP_Form::toggleVisibility);
	xbutton->options.draw_order = -1000;
	formTopRightButtons->addButton(xbutton);
	addComponent(formTopRightButtons);

	//Верхняя полоска на форме (для обработки драгендроп)
	xpanel = GCP_SPointer<GCP_Button> (new GCP_Button());
	xpanel->setWidthHeight(width,30);			
	xpanel->setPosition(xPos,yPos);	
	xpanel->options.draw_order = -999;
	xpanel->setStyle(&defStyles.defaultFormHeaderStyle);
	addComponent((GCP_SPointer<GCP_FormComponent>)xpanel);

	//Сообщение с алармом
	messagebox = GCP_SPointer<GCP_Form>(new GCP_MessageBox(screen,450,150));
	messagebox->isParentLocking = true;
	messagebox->isVisible = false;
	messagebox->isDragable = false;	
	messagebox->options.draw_order = -100;
	messagebox->setPosition(width/2-messagebox->width/2,height/2-messagebox->height/2);
	messagebox->setCaption(GCP_Math::RUSCP1251_TO_WCHAR("УВЕДОМЛЕНИЕ"));
	//setFont("arial.ttf");
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
	//!!! Шрифт передаем!!!
	//component->setFont(getFont());
	_contextmenus.push_back(component);
}

void GCP_Form::addComponent(GCP_SPointer<GCP_FormComponent> const &component)
{
	for(int i=0; i<_components.size(); i++)
		if(component == _components.at(i))			//Два раза одно и тоже не принимаем
			return;

	//Координаты компонента идут оносительно левого верхнего угла формы
	component->setPosition(xPos+component->xPos,yPos+component->yPos);
	//component->setFont(getFont());
	_components.push_back(component);
    GCP_Math::quickSort<gcp_spFormCmpnt>(&_components,0,_components.size()-1, GCP_SORTBY_DRAWORDER);
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
	isVisible = !isVisible;
}

void GCP_Form::addSubForm(GCP_SPointer<GCP_Form> &form)
{
	//!!! Шрифт передаем!!!
	//form->setFont(getFont());
	form->setBufferSize(_swidth,_sheight);
	_subForms.push_back(form);
    GCP_Math::quickSort<gcp_spForm>(&_subForms,0,_subForms.size()-1, GCP_SORTBY_DRAWORDER);
}

void GCP_Form::setPosition(int x, int y)
{		
	int xPosNow = xPos;
	int yPosNow = yPos;
	int deltaX = x-xPos;
	int deltaY = y-yPos;
	xPos = x;
	yPos = y;
	for(unsigned int i=0; i<_components.size(); i++)
		_components.at(i)->setPosition(	_components.at(i)->xPos+deltaX,	_components.at(i)->yPos+deltaY);
	for(unsigned int i=0; i<_contextmenus.size(); i++)
		_contextmenus.at(i)->setPosition(	_contextmenus.at(i)->xPos+deltaX,	_contextmenus.at(i)->yPos+deltaY);
			
			
}

bool GCP_Form::OnDraw(SDL_Renderer* screen, int w, int h)
{
	if(!isVisible)
		return false;
			
	if(!isShowTopRightButtons)
		xbutton->isVisible = false;

	//!!! это надо один раз сообразить а не в цикле
	xpanel->setWidthHeight(width,30);
	//xpanel->cBackColor = colorHeadMenuBackground;
	//xpanel->cBackColorHover = colorHeadMenuBackground;
	//!!!!
			

	if(!isTransparent)
		GCP_Draw::Draw_FillRound(screen, xPos, yPos, width, height, 1,  getStyle()->cBackColor);
	GCP_Draw::Draw_Round(screen, xPos, yPos, width, height, 1,  getStyle()->colorHeadMenuBackground);
	
	
	//!!! Сортировку тоже надо один раз сообразить 
	//GCP_Math::quickSort<GCP_FormComponent*>(&_components,0,_components.size()-1, GCP_SORTBY_DRAWORDER);
	for(unsigned int i=0; i<_components.size(); i++)
			_components.at(i)->OnDraw(screen,_swidth,_sheight,xPos,yPos,width,height);
			
	//Всплывающие подсказки рисуются поверх компонент
	for(unsigned int i=0; i<_components.size(); i++)
		_components.at(i)->OnDrawInfo(screen,xPos,yPos,width,height);

	//Загаловок формы
	string font = getFont();
	if(font != "")
	GCP_Draw::renderText(_sCaption,xPos+width/2-65,yPos+xpanel->height/5,screen,&drawdata,c_white,font,20);

	//Рисуем Контекстные меню
	_isContextMenuOpened = false;
	for(unsigned int i=0; i<_contextmenus.size(); i++){
		_contextmenus.at(i)->setLock(_isContextMenuOpened);
		_contextmenus.at(i)->OnDraw(screen,_swidth,_sheight,xPos,yPos,width,height);
		if(_contextmenus.at(i)->isVisible && _contextmenus.at(i)->isContextMenuBlocking)
			_isContextMenuOpened = true;	//будем блокировать компоненты пока открыто это меню
	}
			
	basicOnDraw(screen,xPos,yPos,width,height);

	//Сообщения можно сделать с потоками. тогда они могут блокировать всю программу пока не нажмешь кнопку ОК
	//Но тогда надо отделять интерфейс от главного потока обработки событий SDL
	if(messages.size())
		if(messagebox->isVisible == false){			
			messagebox->messagelabel->text = messages.pop_first();
			messagebox->isVisible = true;
		}

	//!!! Сортировку тоже надо один раз сообразить 
    GCP_Math::quickSort<gcp_spForm>(&_subForms,0,_subForms.size()-1, GCP_SORTBY_DRAWORDER);
	bool isHavingSubformsThatLocking = false;
	for(unsigned int i=0; i<_subForms.size(); i++){
		_subForms.at(i)->OnDraw(screen, width, height);
		if(_subForms.at(i)->isParentLocking && _subForms.at(i)->isVisible)
			isHavingSubformsThatLocking = true;
	}

	//По хорошему месадж бокс должен блокировать другие формы с
	//следовательно рисоваться и обрабатываться он должен отдельно
	//messagebox->OnDraw(screen, width, height);

	_isLocked = false;
	if(isHavingSubformsThatLocking||isLocked)
		_isLocked = true;

	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////KEY EVENTS
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////OnKeyDown
////////////////////////////////////////////////////////////////////////////////////////////	
bool GCP_Form::OnTextInput(SDL_TextInputEvent text)
{
	if(!isVisible)
		return false;

	for(unsigned int i=0; i<_subForms.size(); i++){
		_subForms.at(i)->OnTextInput(text);	
	}

	if(_isLocked)
		return false;

	if(!_isContextMenuOpened)				
		for(unsigned int i=0; i<_components.size(); i++)
			_components.at(i)->OnTextInput(text);

	basicOnTextInput(text);
			
	return true;
}

bool GCP_Form::OnTextEdit(SDL_TextEditingEvent edit)
{
	if(!isVisible)
		return false;

	for(unsigned int i=0; i<_subForms.size(); i++){
		_subForms.at(i)->OnTextEdit(edit);	
	}

	if(_isLocked)
		return false;

	if(!_isContextMenuOpened)				
		for(unsigned int i=0; i<_components.size(); i++)
			_components.at(i)->OnTextEdit(edit);

	basicOnTextEdit(edit);
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////OnEvent
////////////////////////////////////////////////////////////////////////////////////////////
		gcp_formEvent GCP_Form::OnEvent( const int GCP_EVENT, sdl_events events)
		{
			//Будем возвращать где находился курсор когда произошло событие
			gcp_formEvent evt, other_evt;
			evt.isEventInsideForm = events.isPassingOnlyGlobalEvent;
			evt.isEventOnFormHead = false;	

			if(!isVisible)
				return evt;
			
			//WHY?  EVENTORDER = DRAWORDER^-1
            GCP_Math::quickSort<gcp_spForm>(&_subForms,0,_subForms.size()-1, GCP_SORTBY_EVENTORDER);
			//Передаем всем дочерним формам глобальное событие
			for(unsigned int i=0; i<_subForms.size(); i++){
				other_evt = _subForms.at(i)->OnEvent(GCP_EVENT, events);
				//Запоминаем если это событие произошло внутри хоть одной из активных форм
				evt.isEventInsideForm = evt.isEventInsideForm || other_evt.isEventInsideForm;
				//Все остальные формы получат только глобальные события если хоть на одной мы обработаем локальные
				events.isPassingOnlyGlobalEvent = events.isPassingOnlyGlobalEvent || evt.isEventInsideForm; 
			}

			if(_isLocked){
				evt.isEventInsideForm = false;
				evt.isEventOnFormHead = false;	
				return evt;			
			}

			if(GCP_EVENT == GCP_ON_MOUSE_GUP){
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
					_components.at(i)->OnEvent(GCP_EVENT, events);		//Вызываем глобальное событие у наших компонент
					
					//Если глобальное событие произошло над дочерней формой, локальные события для наших компонент не обрабатываем
					if(!isLocalEventsLocked) 
					if(!isMouseOverSomeComponent && !evt.isEventInsideForm)	{
						if(_components.at(i)->checkCollisionBox(events.mousex, events.mousey)){
							_components.at(i)->OnEvent(GCP_EVENT+1, events);
							if(GCP_EVENT == GCP_ON_MOUSE_GLDOWN)
								_componentThatWasLeftClicked = _components.at(i);

							if(_components.at(i)->isLocalEventsUnderneathBlocking)
								isMouseOverSomeComponent = true;
							//Передали локальное событие компоненту по этим координатам. 
							//Далее локальные события более не передаем
						}
					}
				}
			}

			events.isPassingOnlyGlobalEvent = evt.isEventInsideForm;
			if(!isLocalEventsLocked) 
			for(unsigned int i=0; i<_contextmenus.size(); i++)
				_contextmenus.at(i)->OnEvent(GCP_EVENT, events);

			if(GCP_EVENT == GCP_ON_MOUSE_GUP)
				_componentThatWasLeftClicked = 0; 
			if(GCP_EVENT == GCP_ON_MOUSE_GLDOWN)
				_isClickedOnTopHeader = false;

			//Обрабатываем глобальное и локальные события для формы
			basicOnEvent(GCP_EVENT, events);
			if (!events.isPassingOnlyGlobalEvent)
			if (checkCollisionBox(events.mousex, events.mousey)){
				mouse_x = events.mousex;
				mouse_y =  events.mousey;
				evt.isEventInsideForm = true;
				basicOnEvent(GCP_EVENT+1, events); 
				if(events.mousey<yPos+xpanel->height){
					if(GCP_EVENT == GCP_ON_MOUSE_GLDOWN)
						_isClickedOnTopHeader = true;
					evt.isEventOnFormHead = true;
				}
			}
			return evt;
		}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////OnMouseGlobalLeftHoldMotion
////////////////////////////////////////////////////////////////////////////////////////////
gcp_formEvent GCP_Form::OnMouseGlobalLeftHoldMotion(SDL_MouseMotionEvent motion) {
	gcp_formEvent evt;
	evt.isEventInsideForm = false;
	evt.isFormDragged = false;
	if(!isVisible)
		return evt;

	//WHY?  EVENTORDER = DRAWORDER^-1
    GCP_Math::quickSort<gcp_spForm>(&_subForms,0,_subForms.size()-1, GCP_SORTBY_EVENTORDER);
	bool isDragged = false;		
	bool isEventInsideChildForm = false;
	if(!_isDragStarted || _isLocked){
	for(unsigned int i=0; i<_subForms.size(); i++){
		evt = _subForms.at(i)->OnMouseGlobalLeftHoldMotion(motion);
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
		if (!isDragged && isDragable){
			if (_isClickedOnTopHeader || _isDragStarted){
					int xPosStart = xPos, yPosStart = yPos;
					xPos += motion.xrel;
					yPos += motion.yrel;
					xPos = max(0,min(_swidth-width,(int)xPos));
					yPos = max(0,min(_sheight-height,(int)yPos));

					int deltaX = xPos - xPosStart;
					int deltaY = yPos - yPosStart;
					for(unsigned int i=0; i<_components.size(); i++){
						SPoint previousPos = _components.at(i)->getPosition();
						_components.at(i)->setPosition(previousPos.x+deltaX,previousPos.y+deltaY); 
					}
					for(unsigned int i=0; i<_contextmenus.size(); i++){
						if(!_contextmenus.at(i)->isContextMenuBlocking)		{
						SPoint previousPos = _contextmenus.at(i)->getPosition();
						_contextmenus.at(i)->setPosition(previousPos.x+deltaX,previousPos.y+deltaY); 
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
				_components.at(i)->OnMouseGlobalLeftHoldMotion(motion,xPos,yPos+xpanel->height,width,height-xpanel->height);
				/*if(!isComponentClicked && !isDraggingSomeComponent)
				if(_components.at(i)==_componentThatWasLeftClicked){
					_components.at(i)->OnMouseLeftHoldMotion(motion,xPos,yPos+xpanel->height,width,height-xpanel->height);			
					isComponentClicked = true;
					isDraggingSomeComponent = true;
				}*/
			}

			///REFACTOR THIS!!!!
			if(_componentThatWasLeftClicked)
				if(_componentThatWasLeftClicked->isDragable&& !isComponentClicked && !isDraggingSomeComponent){
					_componentThatWasLeftClicked->OnMouseLeftHoldMotion(motion,xPos,yPos+xpanel->height,width,height-xpanel->height);			
					isComponentClicked = true;
					isDraggingSomeComponent = true;
				}

		}


	}

	if (checkCollisionBox(motion.x,motion.y)&&!isEventInsideChildForm){
		evt.isEventInsideForm = true;
		basicOnMouseLeftHoldMotion(motion,xPos,yPos,width,height);
	}

	basicOnMouseGlobalLeftHoldMotion(motion,xPos,yPos,width,height);

	evt.isFormDragged = _isDragStarted;
	return evt;
}


