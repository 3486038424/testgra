#include "tgra_win.h"

int tgra_win::loop()
{
	while (1)//如果消息不是WM_QUIT,返回非零值；如果消息是WM_QUIT，返回零
	{
		if (frame.size() <= 0)break;
		MSG msg;
		for (int i = 0; i < frame.size(); i++) {
			while (PeekMessage(&msg, frame[i]->get_hwnd(), 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				if (msg.message == 161)
				{
					switch (msg.wParam)
					{
					case 2:
					case 9:
					case 11:
					case 15:
					case 17:
						frame[i]->GetCanvas()->reset();
					}
				}
			}
		}
		for (int i = 0; i < frame.size(); i++)
		{
			frame[i]->before_work();
		}
		work.run();
		for (int i = 0; i < frame.size(); i++)
		{
			frame[i]->after_work();
		}
	}
	return 0;
}
int tgra_win::one_loop()
{
	for (int i = 0; i < frame.size(); i++)
	{
		frame[i]->before_work();
		std::cout << "before_work" << '\n';
	}
	work.run();
	for (int i = 0; i < frame.size(); i++)
	{
		frame[i]->after_work();
		std::cout << "after_work" << '\n';
	}
	return 0;
}