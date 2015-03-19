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
#define GCP_VERSION "1.01c"
#include "GCP_Form.h"
#include "GCP_Button.h"
#include "SDL.h"

namespace gcp
{
	class GCP_Controller : public GCP_SPointerBase
	{
	protected:
		int _width, _height;				      //размер буфера экрана. некоторые системы валятся если пробуешь нарисовать за буфер. GCP будет учитывать это.
		GCP_SPointer<GCP_Form> _mainForm;	//Главная форма интерфейса
		bool _isLeftHold;					      //переключатель для события драг ен дроп
	public:
		GCP_Controller(SDL_Renderer *sdlRenderer, int width, int height);
		~GCP_Controller();
		void setFont(const string &directory_path_string);
		GCP_SPointer<GCP_Form> createForm();
		void handleEvents(const SDL_Event &event);
		void draw();
		void deInit()
		{
			GCP_Draw::DeInit();
		}
	};
}
#endif
