#include "GCP_ContextMenu.h"
#include "GCP_Button.h"
#include "GCP_Vector.h"


//Контекстное меню это набор кнопок, которые открываются например на правый клик по формочке	
GCP_ContextMenu::GCP_ContextMenu(){
	bool isVisible = false;
	int iType = GCP_MENU_MVERTICAL;		//меню может быть вертикальным либо горизонтальным
}



GCP_ContextMenu::~GCP_ContextMenu(){
	//for(int i =0; i<menu.size(); i++)
	//	delete menu.at(i);				//удалим все кнопки которые есть в меню. так как указатели на них хранятся только здесь
}



void GCP_ContextMenu::setLock(bool flag)
{
	_isLocked = flag;					//отключает обработку событий конктекстного меню. (нужно например чтобы заморозить интерфейс)
}

	     
void GCP_ContextMenu::initTexture(SDL_Renderer* screen)
{
	unsigned int iMenuSize = menu.size();	
	for(unsigned int i=0; i<iMenuSize; i++)	
		menu.at(i)->initTexture(screen);	//Сечас эта функция не делает ничего. но по хорошему должна осуществлять предзагрузку картинок кнопок
}

void GCP_ContextMenu::setFont(std::string str)
{
	unsigned int iMenuSize = menu.size();
	for(unsigned int i=0; i<iMenuSize; i++){
		menu.at(i)->setFont(str);
	}
}

void GCP_ContextMenu::addButton(GCP_SPointer<GCP_Button> &button)	{
	button->setFont(getFont());				//передаем кнопке путь к файлу шрифтов вообще надо чтобы за шрифты отвечала стуктура с парметрами компонента
	menu.push_back(button);
}

void GCP_ContextMenu::addButton(string type)	{			
	_iSeparators.push_back( menu.size());	//В меню можно добавлять разделители. Разделитель не кнопка, а отступ / либо линия
}

void GCP_ContextMenu::open(int x, int y)
{
	isVisible = true;						//Открыть менб в заданых координатах
	xPos = x;
	yPos = y;
}

void GCP_ContextMenu::close(void *obj)
{
	isVisible = false;
}

	
bool GCP_ContextMenu::OnMouseGlobalLeftHoldMotion(SDL_MouseMotionEvent motion, int fx, int fy, int fw, int fh)	{
	//Context menu is not dragable
	return false;
}

gcp_formEvent GCP_ContextMenu::OnEvent( const int GCP_EVENT, sdl_events events)
{
	gcp_formEvent evt;
	evt.isEventInsideForm = false;
	evt.isEventOnFormHead = false;
	evt.isFormDragged = false;
	if(!isVisible || _isLocked)
		return evt;

	unsigned int iMenuSize = menu.size();
	for(unsigned int i=0; i<iMenuSize; i++){
			menu.at(i)->OnEvent(GCP_EVENT,events);				//Глобальное событие
			if(!events.isPassingOnlyGlobalEvent)
			if(menu.at(i)->checkCollisionBox(events.mousex, events.mousey)){
				menu.at(i)->OnEvent(GCP_EVENT+1,events);		//локальное событие
			}
		}

	basicOnEvent(GCP_EVENT,events);
	return evt;
}

		

void GCP_ContextMenu::OnDraw(SDL_Renderer* screen,int w, int h, int formx, int formy, int formw, int formh)
{
	if(!isVisible) 
		return;

	//Вывод кнопок на экран
	//Calculate Size For OutOfSurface Correlation
	int maxMenuWidth = 0;							//Максимальная ширина компонентов в меню
	int maxMenuHeight = 0;							//Максимальная высота компонентов в меню
	int stackWidth=0, stackHeight=0;				//Суммарная ширина и высота самого меню
	unsigned int iMenuSize = menu.size();
	for(unsigned int i=0; i<iMenuSize; i++)	{
		if (menu.at(i)->height>maxMenuHeight)
			maxMenuHeight = menu.at(i)->height;
		if (menu.at(i)->height>maxMenuWidth)
			maxMenuWidth = menu.at(i)->width;

		if(iType==GCP_MENU_MVERTICAL){
			stackHeight += menu.at(i)->getPosition().height;
			stackWidth = maxMenuWidth;
		}

		if(iType==GCP_MENU_MHORIZONTAL){
			stackWidth += menu.at(i)->getPosition().width;
			stackHeight = maxMenuHeight;
		}
	}

	//Двигаем меню если оно выходит за буфер / форму
	GCP_Point normPos = GCP_Math::normalizeRectInRect(GCP_Point(formx,formy),
						GCP_Point(formx+formw,formy+formh),xPos,yPos,stackWidth+iMenuSize,stackHeight+iMenuSize,1);
	xPos = (int)normPos.X; 
	yPos = (int)normPos.Y;


	//Теперь когда мы его подвинули нам надо подвинуть все компоненты уже с учетом того что сдвинули наше меню
	//!!! разделители не учитывались в цикле выше!!! 
	stackWidth=0;   //recalc for calculationg drawing coordinates
	stackHeight=0;  
	int currentSeparator=0;
	for(unsigned int i=0; i<iMenuSize; i++)	{

		if(iType==GCP_MENU_MVERTICAL){
			if(currentSeparator < _iSeparators.size())
			if(i==_iSeparators.at(currentSeparator))	{
				stackHeight += 5; currentSeparator++;
			}
			menu.at(i)->setPosition(xPos, yPos + stackHeight);
			stackHeight += menu.at(i)->getPosition().height+1;
			stackWidth = maxMenuWidth;
		}

		if(iType==GCP_MENU_MHORIZONTAL){
			if(currentSeparator < _iSeparators.size())
			if(i==_iSeparators.at(currentSeparator)){
				stackWidth += 5;currentSeparator++;
			}
			menu.at(i)->setPosition(xPos + stackWidth, yPos);
			stackWidth += menu.at(i)->getPosition().width+1;
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
		menu.at(i)->OnDraw(screen, w,h,formx,  formy,  formw,  formh);
		//if(!isContextMenuBlocking)
		//_isContextMenuOpened = (menu.at(i)->_isContextMenuOpened || _isContextMenuOpened);
	}

	//Всплывающие подсказки рисуются поверх компонент
	for(unsigned int i=0; i<iMenuSize; i++)
		menu.at(i)->OnDrawInfo(screen, formx,  formy,  formw,  formh);

			
	GCP_Draw::Draw_Round(screen,xPos, yPos, stackWidth, stackHeight, getStyle()->iRoundCff, c_black); 
			
}//OnDraw
