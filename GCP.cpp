#include "GCP.h"
#include "GCP_Form.h"
#include "GCP_Button.h"
using namespace gcp;

string GCP_Draw::_sDefaultFontPath = "";
GCP_Controller::GCP_Controller(SDL_Renderer *sdlRenderer, int width, int height)
{	
	GCP_Draw::InitSDL2(sdlRenderer);

	_width = width;
	_height = height;
	_mainForm = 0;
	_isLeftHold = false;
}

GCP_Controller::~GCP_Controller()
{
	GCP_Draw::DeInit();
}


void GCP_Controller::setFont(const string &sFontPath)
{
	GCP_Draw::setFontPath(E_ARIAL, sFontPath);
}

GCP_SPointer<GCP_Form> GCP_Controller::createForm()
{
	_mainForm = GCP_SPointer<GCP_Form>(new GCP_Form(_width, _height));
	_mainForm->setBufferSize(_width,_height);
	return _mainForm;
}

void GCP_Controller::handleEvents(const SDL_Event &event)
{
	//Обработка событий от SDL
	GCP_Event baseEvent;
	baseEvent.eventType = GCP_EVENT_NONE;
	baseEvent.mousex = _mainForm->mouse_x;
	baseEvent.mousey = _mainForm->mouse_y;
	baseEvent.isPassingOnlyGlobalEvent = false;

	if( event.type == SDL_QUIT ) {}

	switch(event.type)
	{
	case SDL_KEYDOWN:
		baseEvent.eventType = GCP_ON_GKEYDOWN;
		baseEvent.keycode = event.key.keysym.sym;
		_mainForm->OnEvent(baseEvent);
		break;

		//case SDL_TEXTEDITING:
		//	_mainForm->OnTextEdit(event.edit);	break;

	case SDL_TEXTINPUT:
		baseEvent.eventType = GCP_ON_GTEXTINPUT;
		baseEvent.sTextInput = event.text.text;
		_mainForm->OnEvent(baseEvent);
		break;

	case SDL_MOUSEMOTION:
		baseEvent.eventType = GCP_ON_MOUSE_GMOTION;
		baseEvent.mousex = event.motion.x;
		baseEvent.mousey = event.motion.y;
		baseEvent.iMouseXRel = event.motion.xrel;
		baseEvent.iMouseYRel = event.motion.yrel;
		//evt.mousemotion = event.motion;
		_mainForm->OnEvent(baseEvent);
		if (_isLeftHold)
		{
			GCP_Event evt = baseEvent;
			evt.eventType = GCP_ON_MOUSE_GLHMOTION;
			_mainForm->OnMouseGlobalLeftHoldMotion(evt);
		}
		break;

	case SDL_MOUSEWHEEL:
		if (event.wheel.y >= 0)
			baseEvent.eventType = GCP_ON_WHELL_GUP;
		else
			baseEvent.eventType = GCP_ON_WHELL_GDOWN;

		_mainForm->OnEvent(baseEvent);
		break;

	case SDL_MOUSEBUTTONDOWN:
		baseEvent.mousex = event.button.x;
		baseEvent.mousey = event.button.y;
		//evt.mousebutton = event.button;
		baseEvent.eventType = GCP_ON_MOUSE_GDOWN;
		_mainForm->OnEvent(baseEvent);

		if (event.button.button == SDL_BUTTON_LEFT){
			GCP_Event evt = baseEvent;
			evt.eventType = GCP_ON_MOUSE_GLDOWN;
			_mainForm->OnEvent(evt);
			_isLeftHold = true;
		}

		break;
	case SDL_MOUSEBUTTONUP:
		baseEvent.mousex = event.button.x;
		baseEvent.mousey = event.button.y;
		//evt.mousebutton = event.button;
		baseEvent.eventType = GCP_ON_MOUSE_GUP;
		_mainForm->OnEvent(baseEvent);

		if (event.button.button == SDL_BUTTON_RIGHT)
		{
			GCP_Event evt = baseEvent;
			evt.eventType = GCP_ON_GRIGHT_CLICK;
			_mainForm->OnEvent(evt);
		}

		if( event.button.button == SDL_BUTTON_LEFT )
		{
			GCP_Event evt = baseEvent;
			evt.eventType = GCP_ON_GLEFT_CLICK;
			_mainForm->OnEvent(evt);
			_isLeftHold = false;
		}

		break;
	}
}


void GCP_Controller::draw()
{
	GCP_Event drawEvent;
	drawEvent.eventType = GCP_ON_GDRAW;
	drawEvent.drawRect = GCP_Rect<int>(0, 0, _width, _height);
	_mainForm->OnDraw(drawEvent);
}


