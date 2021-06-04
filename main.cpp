#include "UltraEngine.h"
#include "Table.h"

using namespace UltraEngine;

bool RescaleUI(const Event& event, shared_ptr<Object> extra)
{
	float dpiscale = float(event.data) / 100.0f;
	auto ui = dynamic_pointer_cast<Interface>(extra);
	ui->SetScale(dpiscale);
	auto window = dynamic_pointer_cast<Window>(event.source);
	window->SetShape(event.position.x, event.position.y, event.size.x, event.size.y);
	return true;
}

int main(int argc, const char* argv[])
{
	//Get displays
	auto displays = GetDisplays();
	if (displays.empty()) return 1;
	float dpiscale = displays[0]->scale;

	//Create window
	auto mainwindow = CreateWindow("Ultra App Kit", 0, 0, 1000 * dpiscale, 600 * dpiscale, displays[0], WINDOW_HIDDEN | WINDOW_CENTER | WINDOW_TITLEBAR | WINDOW_RESIZABLE);

	//Create user interface
	auto ui = CreateInterface(mainwindow);
	iVec2 sz = ui->root->ClientSize();
	auto tableTest = CreateTable(0, 0, sz.x, sz.y, ui->root);
	

	//Enable DPI scaling changes
	ui->SetScale(dpiscale);
	ListenEvent(EVENT_WINDOWDPICHANGED, mainwindow, RescaleUI, ui);
	
	//Show the window
	mainwindow->Show();
	mainwindow->Activate();

	while (true)
	{
		const Event event = WaitEvent();
		switch (event.id)
		{
		case EVENT_WIDGETSELECT:
			break;
		case EVENT_WIDGETACTION:
			break;
		case EVENT_WINDOWCLOSE:
			if (event.source == mainwindow) return 0;
			break;
		}
	}
	return 0;
}