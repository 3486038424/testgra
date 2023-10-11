#include "tgra_win.h"

int tgra_win::loop()
{
	int t;
	while (1)//如果消息不是WM_QUIT,返回非零值；如果消息是WM_QUIT，返回零
	{
		t = clock();
		if (frame.size() <= 0)break;
		MSG msg;
		std::cout << '3' << std::endl;
		while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		for (int i = 0; i < frame.size(); i++) {
			while (PeekMessage(&msg, frame[i]->get_hwnd(), 0, 0, PM_REMOVE)) {
				std::cout << msg.message << std::endl;
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
				else if (msg.message == WM_LBUTTONDOWN)
				{
					frame[i]->lmouse_click = true;
				}
				else if (msg.message == WM_RBUTTONDOWN)
				{
					frame[i]->rmouse_click = true;
				}
				else if (msg.message == WM_MBUTTONDOWN)
				{
					frame[i]->wheel_click = true;
				}
				else if (msg.message == WM_MOUSEWHEEL)
				{
					frame[i]->wheel_position = GET_WHEEL_DELTA_WPARAM(msg.wParam) / 120;
				}
				/*
				else if (msg.message == WM_KEYDOWN)
				{
					frame[i]->keystate[msg.wParam] = 1;
				}
				else if (msg.message == WM_KEYUP)
				{
					frame[i]->keystate[msg.wParam] = 0;
				}*/
				TranslateMessage(&msg);
				DispatchMessage(&msg);
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
		t = t + framerate - clock();
		if (t>0)
			Sleep(t);
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