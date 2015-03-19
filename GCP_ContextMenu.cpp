#include "GCP_ContextMenu.h"
#include "GCP_Button.h"
#include "GCP_Vector.h"
using namespace gcp;

//Контекстное меню это набор кнопок, которые открываются например на правый клик по формочке
GCP_ContextMenu::GCP_ContextMenu(){
	_isVisible = false;
	iType = GCP_MENU_MVERTICAL;		//меню может быть вертикальным либо горизонтальным
}



GCP_ContextMenu::~GCP_ContextMenu(){
	//for(int i =0; i<menu.size(); i++)
	//	delete menu.at(i);				//удалим все кнопки которые есть в меню. так как указатели на них хранятся только здесь
}



void GCP_ContextMenu::setLock(bool flag)
{
	_isLocked = flag;					//отключает обработку событий конктекстного меню. (нужно например чтобы заморозить интерфейс)
}


/*void GCP_ContextMenu::initTexture(SDL_Renderer* screen)
{
	unsigned int iMenuSize = menu.size();
	for(unsigned int i=0; i<iMenuSize; i++)
		menu.at(i)->initTexture(screen);	//Сечас эта функция не делает ничего. но по хорошему должна осуществлять предзагрузку картинок кнопок
}*/

void GCP_ContextMenu::addButton(const GCP_SPointer<GCP_Button> &button)	{
	menu.push_back(button);
}

void GCP_ContextMenu::addButton(const string &type)
{
	_iSeparators.push_back( menu.size());	//В меню можно добавлять разделители. Разделитель не кнопка, а отступ / либо линия
}

void GCP_ContextMenu::open(int x, int y)
{
	_isVisible = true;						//Открыть менб в заданых координатах
	_position.topLeft.X = x;
	_position.topLeft.Y = y;
}

void GCP_ContextMenu::close(void *obj)
{
	_isVisible = false;
}


gcp_formEvent GCP_ContextMenu::OnMouseGlobalLeftHoldMotion(const GCP_Event &event)	{
	//Context menu is not dragable
	return gcp_formEvent();
}

gcp_formEvent GCP_ContextMenu::OnEvent(const GCP_Event &event)
{
	gcp_formEvent evt;
	evt.isEventInsideForm = false;
	evt.isEventOnFormHead = false;
	evt.isFormDragged = false;
	if(!isVisible() || _isLocked)
		return evt;

	unsigned int iMenuSize = menu.size();
	for(unsigned int i=0; i<iMenuSize; i++){
		menu.at(i)->OnEvent(event);				//Глобальное событие
		if(!event.isPassingOnlyGlobalEvent)
			if(menu.at(i)->checkCollisionBox(event.mousex, event.mousey)){
				menu.at(i)->OnEvent(MakeEventLocal(event));		//локальное событие
			}
	}

	basicOnEvent(event);
	return evt;
}



void GCP_ContextMenu::OnDraw(const GCP_Event &event)
{
	if(!isVisible())
		return;

	//Вывод кнопок на экран
	//Calculate Size For OutOfSurface Correlation
	int maxMenuWidth = 0;							//Максимальная ширина компонентов в меню
	int maxMenuHeight = 0;							//Максимальная высота компонентов в меню
	int stackWidth=0, stackHeight=0;				//Суммарная ширина и высота самого меню
	unsigned int iMenuSize = menu.size();
	for(unsigned int i=0; i<iMenuSize; i++)	{
		if (menu.at(i)->getPosition().height()>maxMenuHeight)
			maxMenuHeight = menu.at(i)->getPosition().height();
		if (menu.at(i)->getPosition().height()>maxMenuWidth)
			maxMenuWidth = menu.at(i)->getPosition().width();

		if(iType==GCP_MENU_MVERTICAL){
			stackHeight += menu.at(i)->getPosition().height();
			stackWidth = maxMenuWidth;
		}

		if(iType==GCP_MENU_MHORIZONTAL){
			stackWidth += menu.at(i)->getPosition().width();
			stackHeight = maxMenuHeight;
		}
	}

	//Двигаем меню если оно выходит за буфер / форму
	GCP_Point<int> normPos = GCP_Math::normalizeRectInRect<int>(
				GCP_Rect<int>(_position.x(), _position.y(), stackWidth + iMenuSize, stackHeight + iMenuSize),
				event.drawRect, 1);
	_position.topLeft.X = (int)normPos.X;
	_position.topLeft.Y = (int)normPos.Y;


	//Теперь когда мы его подвинули нам надо подвинуть все компоненты уже с учетом того что сдвинули наше меню
	//!!! разделители не учитывались в цикле выше!!!
	stackWidth=0;   //recalc for calculationg drawing coordinates
	stackHeight=0;
	unsigned int currentSeparator=0;
	for(unsigned int i=0; i<iMenuSize; i++)	{

		if(iType==GCP_MENU_MVERTICAL){
			if(currentSeparator < _iSeparators.size())
				if(i==_iSeparators.at(currentSeparator))	{
					stackHeight += 5; currentSeparator++;
				}
			menu.at(i)->setPosition(_position.x(), _position.y() + stackHeight);
			stackHeight += menu.at(i)->getPosition().height()+1;
			stackWidth = maxMenuWidth;
		}

		if(iType==GCP_MENU_MHORIZONTAL){
			if(currentSeparator < _iSeparators.size())
				if(i==_iSeparators.at(currentSeparator)){
					stackWidth += 5;currentSeparator++;
				}
			menu.at(i)->setPosition(_position.x() + stackWidth, _position.y());
			stackWidth += menu.at(i)->getPosition().width()+1;
			stackHeight =  maxMenuHeight;
		}
	}

	//if(!isContextMenuBlocking)
	//_isContextMenuOpened = false;

	//Рисуем все наши компоненты
	for(unsigned int i=0; i<iMenuSize; i++){
		menu.at(i)->setWidthHeight(maxMenuWidth,maxMenuHeight);
		//menu.at(i)->setColor(cBackColor, cTextColor, cBackColorHover, cTextColorHover);
		//menu.at(i)->iRoundCff = iRoundCff;
		menu.at(i)->OnDraw( event);
		//if(!isContextMenuBlocking)
		//_isContextMenuOpened = (menu.at(i)->_isContextMenuOpened || _isContextMenuOpened);
	}

	//Всплывающие подсказки рисуются поверх компонент
	for(unsigned int i=0; i<iMenuSize; i++)
		menu.at(i)->OnDrawInfo( event);


	GCP_Draw::Render()->Draw_Round(_position.x(),  _position.y(),  stackWidth, stackHeight, getStyle()->roundCff, c_black);

}//OnDraw
