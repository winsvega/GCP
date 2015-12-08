#include "SDL.h"
#include "GCP.h"
#ifdef __WIN32__
	#include <direct.h>
#else
	#include <unistd.h>
#endif

SDL_Window *sdlWindow_;
SDL_Renderer *sdlRenderer_;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
using namespace gcp;

class gcpWindow
{
private:
	GCP_SPointer<GCP_Controller> Interface;
	GCP_SPointer<GCP_Form> MainInterfaceForm;
	GCP_SPointer<GCP_ContextMenu> RightButtonMenu;

public:
	gcpWindow(){ init(); }

	void init()
	{
		//Main controller and form
		Interface = GCP_SPointer<GCP_Controller>(new GCP_Controller(sdlRenderer_, SCREEN_WIDTH, SCREEN_HEIGHT));
		MainInterfaceForm = Interface->createForm();
		string working_directory = "C:\\";

#ifdef __WIN32__
		char buff[200];
		buff[0] = '\0';
		strcat_s(buff, _getcwd(NULL, 0));
		strcat_s(buff, "\\");
		working_directory = buff;
#else
		working_directory = getcwd(NULL, 0);
#endif

		////TTF Init (Weak point here) make sure TTF font is loaded!
		std::stringstream directory_path;
		directory_path << working_directory.c_str() << "/arial.ttf";
		std::string directory_path_string = directory_path.str();
		Interface->setFont(directory_path.str());


		MainInterfaceForm->setCaption("Example Form");

		//Example button with message box handler
		gcp_spButton bNew = gcp_spButton(new GCP_Button());
		bNew->setWidthHeight(105, 25);
		bNew->setCaption("Example Button");
		bNew->setPosition(SCREEN_WIDTH / 2 - bNew->getPosition().width() / 2, SCREEN_HEIGHT / 2 - bNew->getPosition().height() / 2);
		bNew->setButtonType(GCP_BUTTON_ROUNDRECT);
		bNew->setOnMouseLeftClick(this, &gcpWindow::onHelloWorldButtonClick);
		MainInterfaceForm->addComponent(GCP_SPointer<GCP_FormComponent>(bNew));

		//Label
		GCP_SPointer<GCP_Label> infolabel = GCP_SPointer<GCP_Label>(new GCP_Label());
		infolabel->setPosition(10, 40);
		infolabel->text = "GCP Version: ";
		infolabel->text += GCP_VERSION;
		MainInterfaceForm->addComponent(GCP_SPointer<GCP_FormComponent>(infolabel));


		int x0 = 100, y0 = 100, separation = 30, i = 0;
		////////////////
		////     Y=0
		////////////////
		//Example Label with hint
		GCP_SPointer<GCP_Label> label6 = GCP_SPointer<GCP_Label>(new GCP_Label());
		label6->setPosition(x0, y0 + separation*i);
		label6->text = "Example Label:";
		label6->setInfo("Example Hint");
		MainInterfaceForm->addComponent(GCP_SPointer<GCP_FormComponent>(label6));

		//Example Select with options
		GCP_SPointer<GCP_Select> select = GCP_SPointer<GCP_Select>(new GCP_Select());
		select->setPosition(x0 + 140, y0 + separation*i - 5);
		select->setWidthHeight(130, separation - 5);
		select->options.draw_order = -1;
		select->addItem("ex. select 1");
		select->addItem("ex. select 2");
		select->addItem("ex. select 3");
		select->selectItem(0);
		MainInterfaceForm->addComponent(GCP_SPointer<GCP_FormComponent>(select));

		//Edit Label
		GCP_SPointer<GCP_Label> editLabel = GCP_SPointer<GCP_Label>(new GCP_Label());
		editLabel->setPosition(x0 + 300, y0 + separation*(i-1));
		editLabel->text = "Input text field:";
		editLabel->setInfo("Double Digits symbols only");
		MainInterfaceForm->addComponent(GCP_SPointer<GCP_FormComponent>(editLabel));

		//Example Edit
		GCP_SPointer<GCP_Edit> edit = GCP_SPointer<GCP_Edit>(new GCP_Edit());
		edit->setPosition(x0 + 300, y0 + separation*i - 5);
		edit->setWidthHeight(130, separation - 5);
		edit->options.draw_order = -1;
		edit->inputType = DIGITONLY;


		MainInterfaceForm->addComponent(GCP_SPointer<GCP_FormComponent>(edit));
		////////////////
		////     Y=1
		////////////////
		i++;
		//Example Checkbox
		GCP_SPointer<GCP_CheckBox> CheckBox1 = GCP_SPointer<GCP_CheckBox>(new GCP_CheckBox());
		CheckBox1->setPosition(x0, y0 + separation*i);
		CheckBox1->setCaption("Example Checkbox");
		MainInterfaceForm->addComponent(GCP_SPointer<GCP_FormComponent>(CheckBox1));

		//Some color schemas for interface
		gcp_spStyle mainStyle = gcp_spStyle(new GCP_Style(E_DEFAULT));
		mainStyle->backgroundColor = c_lime;

		//Example Blocking Subform
		GCP_SPointer<GCP_Form> OptionsForm = GCP_SPointer<GCP_Form>(new GCP_Form(300, 400));
		OptionsForm->isParentLocking = true;
		OptionsForm->setStyle(mainStyle);
		OptionsForm->setVisible(false);
		OptionsForm->setDragable(true);
		OptionsForm->setPosition(SCREEN_WIDTH / 2 - OptionsForm->getPosition().width() / 2, SCREEN_HEIGHT / 2 - OptionsForm->getPosition().height() / 2);
		string bcaption4 = "Example Form";
		OptionsForm->setCaption(bcaption4);
		MainInterfaceForm->addSubForm(OptionsForm);


		//Graph Label
		GCP_SPointer<GCP_Label> graphLabel = GCP_SPointer<GCP_Label>(new GCP_Label());
		graphLabel->setPosition(x0 + 500, y0 + separation*(i - 1));
		graphLabel->text = "Example Graphic:";
		graphLabel->setInfo("Spherical graph");
		MainInterfaceForm->addComponent(GCP_SPointer<GCP_FormComponent>(graphLabel));

		//Example Graph
		typedef GCP_Graph graph;
		GCP_SPointer<graph> grapharea = GCP_SPointer<graph>(new graph());
		grapharea->setPosition(x0 + 500, y0 + separation*i - 5);
		grapharea->setWidthHeight(130, 130);
		grapharea->options.draw_order = -1;

		grapharea->setValue(10, 10);
		grapharea->setValue(12, 5);

		/*//Values could be set from -X...X that will morph into 0...360 on spherical graph
	  for (int i = 0; i < 1200; i+=2)
		 grapharea->setValue(i, i*2);

	  //Negative Values would be drawn blue and to opposite direction
	  for (int i = 1000; i < 1100; i += 2)
		 grapharea->setValue(i, -2222);

	  //Values also could be added or substracted to current value
	  for (int i = 1040; i < 1060; i += 2)
		 grapharea->addValue(i, 3522);
		 */
		grapharea->type = ENORMAL_GRAPH;

		MainInterfaceForm->addComponent(GCP_SPointer<GCP_FormComponent>(grapharea));

		////////////////
		////     Y=2
		////////////////
		i++;
		//Button that opens subform
		GCP_SPointer<GCP_Button> bForm = GCP_SPointer<GCP_Button>(new GCP_Button());
		bForm->setWidthHeight(105, 25);
		bForm->setCaption("Example Form");
		bForm->setPosition(x0, y0 + separation*i);
		bForm->setButtonType(GCP_BUTTON_ROUNDRECT);
		bForm->setOnMouseLeftClick(OptionsForm.getPointer(), &GCP_Form::toggleVisibility);
		MainInterfaceForm->addComponent(GCP_SPointer<GCP_FormComponent>(bForm));

		//Right button context menu
		RightButtonMenu = GCP_SPointer<GCP_ContextMenu>(new GCP_ContextMenu());
		RightButtonMenu->setPosition(100, 100);

		//First button in context menu
		GCP_SPointer<GCP_Button> bcCreatePoint = GCP_SPointer<GCP_Button>(new GCP_Button());
		bcCreatePoint->setWidthHeight(120, 25);
		bcCreatePoint->setCaption("Example Menu 1");
		bcCreatePoint->setButtonType(GCP_BUTTON_ROUNDRECT);
		bcCreatePoint->setOnMouseLeftClick(this, &gcpWindow::onHelloWorldButtonClick);
		RightButtonMenu->addButton(bcCreatePoint);

		//A button with image in context menu
		/*GCP_SPointer<GCP_Button> bcCenterView = GCP_SPointer<GCP_Button>(new GCP_Button());
	  bcCenterView->setWidthHeight(120,25);
	  bcCenterView->setIcon(working_directory+"image.bmp");
	  bcCenterView->iType = GCP_BUTTON_ROUNDRECT;
	  bcCenterView->setOnMouseLeftClick(this,&gcpWindow::onHelloWorldButtonClick);
	  RightButtonMenu->addButton(bcCenterView);	*/


		//Hide out menu
		RightButtonMenu->setVisible(false);
		RightButtonMenu->setMenuType(GCP_MENU_MVERTICAL);
		MainInterfaceForm->addComponent(RightButtonMenu);

		//Add Main form handlers
		MainInterfaceForm->setOnMouseRightClick(this, &gcpWindow::OnMouseGlobalRightClick);
		MainInterfaceForm->setOnMouseLeftClick(RightButtonMenu.getPointer(), &GCP_ContextMenu::close);
	}

	void OnMouseGlobalRightClick(void *obj)
	{
		RightButtonMenu->open(MainInterfaceForm->mouse_x, MainInterfaceForm->mouse_y);
	}
	void onHelloWorldButtonClick(void *obj)
	{
		MainInterfaceForm->showmessage("Hello World!", "NOTICE");
	}

	int update()
	{
		SDL_Event event;
		SDL_RenderClear(sdlRenderer_);
		while (SDL_PollEvent(&event))
		{
			Interface->handleEvents(event);		//Handle interface events
			if (!MainInterfaceForm->isVisible())
			{
				//Interface->deInit();
				return -1;
			}
		}
		draw();									//Draw your logic
		Interface->draw();						//Draw interface over it
		SDL_RenderPresent(sdlRenderer_);
		return 0;
	}

	void draw()
	{
		//Draw your logic here
	}
};

int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
		return 1;

	sdlWindow_ = SDL_CreateWindow("GUI Check Point", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (sdlWindow_ == NULL)
		return 2;

	sdlRenderer_ = SDL_CreateRenderer(sdlWindow_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (sdlRenderer_ == NULL)
		return 3;

	SDL_SetRenderDrawColor(sdlRenderer_, 0, 220, 120, 0);

	gcpWindow *wnd = new gcpWindow();
	while (wnd->update() == 0)
		SDL_Delay(10);

	delete wnd;

	SDL_DestroyRenderer(sdlRenderer_);
	SDL_DestroyWindow(sdlWindow_);

	SDL_Quit();
	return 0;
}

#pragma endregion
