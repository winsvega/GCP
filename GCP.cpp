#include "GCP.h"
#include "GCP_Form.h"
#include "GCP_Button.h"


GCP_Controller::GCP_Controller(SDL_Renderer *sdlRenderer, int width, int height)
{
	GCP_Draw::initConstants();	//дело в том что константы вне функкций почему то не объ€вл€ютс€ на некоторых компил€торах
	GCP_FormComponent::initStyles();
	TTF_Init();
	_screen = sdlRenderer;
	_width = width;
	_height = height;
	_mainForm = 0;
	_isLeftHold = false;
}

GCP_Controller::~GCP_Controller()
{
	TTF_Quit();
	//if(_mainForm != NULL)
	//	delete _mainForm;
}

//FormComponent.cpp
string SStyle::sFontDir = "";
defaultStyles defStyles = defaultStyles();
void GCP_Controller::setFont(string directory_path_string)
{
	_sFontDir = directory_path_string;						//путь к файоу шрифтов
	SStyle::sFontDir = _sFontDir;
	//defaultMenuStyle->sFontDir = _sFontDir;
	//GCP_FormComponent::_szukoZapomniUjeDirToYourFont = _sFontDir;
}

GCP_SPointer<GCP_Form> GCP_Controller::createForm(SDL_Renderer* screen)
{
	_mainForm =GCP_SPointer<GCP_Form>(new GCP_Form(screen, _width, _height));
	//_mainForm->setFont(_sFontDir);							//сейчас форма передает этот путь всем своим компонентам
	_mainForm->setBufferSize(_width,_height);
	return _mainForm;
}

void GCP_Controller::handleEvents(SDL_Event event)
{
	sdl_events evt;											//ќбработка событий от SDL
	evt.mousex = _mainForm->mouse_x;
	evt.mousey = _mainForm->mouse_y;
	evt.isPassingOnlyGlobalEvent = false;

	if( event.type == SDL_QUIT ) {}
	switch(event.type)
	{
		case SDL_KEYDOWN:
			evt.keyboard = event.key;
			_mainForm->OnEvent(GCP_ON_GKEYDOWN,evt); break;
		//case SDL_TEXTEDITING:
		//	_mainForm->OnTextEdit(event.edit);	break;
		case SDL_TEXTINPUT:
			_mainForm->OnTextInput(event.text);	break;
		case SDL_MOUSEMOTION:
			evt.mousex = event.motion.x;
			evt.mousey = event.motion.y;
			evt.mousemotion = event.motion;
			_mainForm->OnEvent(GCP_ON_MOUSE_GMOTION,evt);
			if (_isLeftHold)
				_mainForm->OnMouseGlobalLeftHoldMotion(event.motion);
			break;
		case SDL_MOUSEWHEEL:
			evt.mouswheel = event.wheel;

			if(event.wheel.y >= 0)
				_mainForm->OnEvent(GCP_ON_WHELL_GUP,evt);
			else
				_mainForm->OnEvent(GCP_ON_WHELL_GDOWN,evt);
			break;
		case SDL_MOUSEBUTTONDOWN:
			  evt.mousex = event.button.x;
			  evt.mousey = event.button.y;
			  evt.mousebutton = event.button;

			  _mainForm->OnEvent(GCP_ON_MOUSE_GDOWN,evt);
			  if (event.button.button == SDL_BUTTON_LEFT){
					_mainForm->OnEvent(GCP_ON_MOUSE_GLDOWN,evt);
					_isLeftHold = true;
				}
			break;
		case SDL_MOUSEBUTTONUP:
				evt.mousex = event.button.x;
				evt.mousey = event.button.y;
				evt.mousebutton = event.button;

				_mainForm->OnEvent(GCP_ON_MOUSE_GUP,evt);

				if( event.button.button == SDL_BUTTON_RIGHT )
					_mainForm->OnEvent(GCP_ON_GRIGHT_CLICK,evt);
				if( event.button.button == SDL_BUTTON_LEFT ) {
					_mainForm->OnEvent(GCP_ON_GLEFT_CLICK,evt);
					_isLeftHold = false;
				}
			break;
	}
}

void GCP_Controller::draw()
{
	_mainForm->OnDraw(_screen,_width,_height);
}


