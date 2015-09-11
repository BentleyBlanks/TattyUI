#ifndef T2_EVENTDRIVER_H
#define T2_EVENTDRIVER_H

#include <TattyUI/common/t2Settings.h>

namespace TattyUI
{
    class t2DivController;

	// 内置TattyUI事件类型
	enum t2EventType
	{
		T2_EVENT_MOUSE_MOVED = 0,
		T2_EVENT_MOUSE_PRESSED,
		T2_EVENT_MOUSE_RELEASED,
		T2_EVENT_MOUSE_SCROLLED,

		T2_EVENT_KEY_PRESSED,
		T2_EVENT_KEY_RELEASED,

		// 为Move与Scroll做占位符
		T2_EVENT_NONE = 100,
	};

	class t2EventController
	{
	public:
		static t2EventController* getInstance();

		// 以下设计方便虚拟io的接入
		// 事件类型 鼠标位置 按键类型
		void triggerMouseEvent(int x, int y, int px, int py, int button, t2EventType type);

		void triggerKeyEvent(int key, t2EventType type);

	private:
		// 不可删除 不可复制 不可自己创建实例
		t2EventController();
		t2EventController(const t2EventController&){}
		~t2EventController(){}
		t2EventController& operator=(const t2EventController& event) const{}

		// pimple
		class t2RegistrantList;
		t2RegistrantList* registrantList;
	};
}

#endif