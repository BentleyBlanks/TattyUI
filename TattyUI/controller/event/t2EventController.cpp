#include <TattyUI/controller/event/t2EventController.h>

#include <TattyUI/div/t2Div.h>
#include <TattyUI/div/t2DivController.h>

namespace TattyUI
{
	class t2EventController::t2RegistrantList
	{
	public:
        t2RegistrantList();

        void notifyMouseEvent(int x, int y, int px, int py, int button, t2EventType type);

        void notifyKeyEvent(int key, t2EventType type);

        t2DivController* divController;
    };

    t2EventController::t2RegistrantList::t2RegistrantList()
    {
        divController = t2DivController::getInstance();
    }

	void t2EventController::t2RegistrantList::notifyMouseEvent(int x, int y, int px, int py, int button, t2EventType type)
	{
        switch(type)
        {
        case T2_EVENT_MOUSE_MOVED:
            divController->onMouseMoved(x, y, px, py);
            break;
        case T2_EVENT_MOUSE_PRESSED:
            divController->onMousePressed(x, y, px, py, button);
            break;
        case T2_EVENT_MOUSE_RELEASED:
            divController->onMouseReleased(x, y, px, py, button);
            break;
        case T2_EVENT_MOUSE_SCROLLED:
            divController->onMouseScrolled(x, y, px, py);
            break;
        case T2_EVENT_NONE:
            t2Log("出现这种问题，神仙也救不了你.\n");
            break;
        }
	}

    void t2EventController::t2RegistrantList::notifyKeyEvent(int key, t2EventType type)
	{
        switch(type)
        {
        case T2_EVENT_KEY_PRESSED:
            divController->onKeyPressed(key);
            break;
        case T2_EVENT_KEY_RELEASED:
            divController->onKeyReleased(key);
            break;
        case T2_EVENT_NONE:
            t2Log("出现这种问题，神仙也救不了你.\n");
            break;
        }
	}

	// t2EventController
	t2EventController* t2EventController::getInstance()
	{
		static t2EventController eventController;
		return &eventController;
	}

	t2EventController::t2EventController()
	{
		registrantList = new t2RegistrantList();
	}

	void t2EventController::triggerMouseEvent(int x, int y, int px, int py, int button, t2EventType type)
	{
        registrantList->notifyMouseEvent(x, y, px, py, button, type);
	}

	void t2EventController::triggerKeyEvent(int key, t2EventType type)
	{
        registrantList->notifyKeyEvent(key, type);
	}
}