////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Система SDL GUI CHECK POINT 
/////////////////////////////////////Интерфейс для SDL
////////////////////////////////////////////////////////////////////////////////////////////
//////Модуль отвечает за обработку событий SDL и передает их своему компоненту: _mainForm
//////Контроллер должен знать максимальную ширину и высоту буфера чтобы ограничеть передвижение формы
//////Для работы контроллера надо вызвать функции handleEvents и draw в цикле программы
//////ПРИМЕР:
//////=====ON CREATE
//////GCP_Controller *Interface = new GCP_Controller(sdlRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);
//////Interface->setFont(font_path.str());								// путь к файлу шрифтов 
//////GCP_Form *MainInterfaceForm = Interface->createForm(sdlRenderer); // главная форма интерфейса
//////=====MAIN WHILE
//////SDL_RenderClear(sdlRenderer);								
//////while( SDL_PollEvent( &event ) )		//Обработчик всех событий от SDL
//////{ 		
//////	Interface->handleEvents(event);		//Обрабатываем интерфейс	
//////	if( event.type == SDL_QUIT ) 
//////		return -1;
//////} 	
//////draw();									//Рисуем нашу логику
//////Interface->draw();						//Рисуем интерфейс	
//////SDL_RenderPresent(sdlRenderer);			//Выводим на экран
//////================
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef GCP_MainH
#define GCP_MainH
#include "GCP_Form.h"
#include "GCP_Button.h"
#include "SDL_ttf.h"
#include "SDL.h"

class GCP_Controller: public GCP_SPointerBase
{
	protected:
		SDL_Renderer *_screen;				//то на что рисуем. надо бы определить структуру. ведь рисовать мы можем на сдл а можем и на что-то совсем другое 
		int _width, _height;				//размер буфера экрана. некоторые системы валятся если пробуешь нарисовать за буфер. GCP будет учитывать это.
		GCP_SPointer<GCP_Form> _mainForm;				//Главная форма интерфейса
		bool _isLeftHold;					//переключатель для события драг ен дроп
		string _sFontDir;					//путь к шрифту для TTF
	public: 
		GCP_Controller(SDL_Renderer *sdlRenderer, int width, int height);	
		~GCP_Controller();
		void setFont(string directory_path_string);
		GCP_SPointer<GCP_Form> createForm(SDL_Renderer* screen);
		void handleEvents(SDL_Event event);
		void draw();
};


#endif