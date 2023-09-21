#include "tgra_win.h"
LRESULT CALLBACK unload(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)//通过判断消息进行消息响应
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);//销毁窗口并发送WM_DESTROY消息，但是程序没有退出
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//发出WM_QUIT消息，结束消息循环
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//对不感兴趣的消息进行缺省处理，必须有该代码，否则程序有问题
	}
	return 0;
}
tgra_win::tgra_win(LPCWSTR name, int width, int height,LPCWSTR class_name, decltype(unload) WinSunProc )
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	wndcls.cbClsExtra = 0;//类的额外内存，默认为0即可
	wndcls.cbWndExtra = 0;//窗口的额外内存，默认为0即可
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//获取画刷句柄（将返回的HGDIOBJ进行强制类型转换）
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);//设置光标
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);//设置窗体左上角的图标
	wndcls.hInstance = hInstance;//设置窗体所属的应用程序实例
	wndcls.lpfnWndProc = WinSunProc;//设置窗体的回调函数，暂时没写，先设置为NULL，后面补上
	wndcls.lpszClassName = class_name;//设置窗体的类名
	wndcls.lpszMenuName = NULL;//设置窗体的菜单,没有，填NULL
	wndcls.style = CS_HREDRAW | CS_VREDRAW;//设置窗体风格为水平重画和垂直重画
	RegisterClass(&wndcls);//向操作系统注册窗体
	//产生一个窗体，并返回该窗体的句柄，第一个参数必须为要创建的窗体的类名，第二个参数为窗体标题名
	hwnd = CreateWindow(class_name, name,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, width, height,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);//把窗体显示出来
	UpdateWindow(hwnd);//更新窗体
	UpdateWindow(hwnd);//更新窗体
	screen.init(hwnd);
}

int tgra_win::loop()
{
	MSG msg;
	while (1)//如果消息不是WM_QUIT,返回非零值；如果消息是WM_QUIT，返回零
	{
		int t = clock();
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message==WM_QUIT)
			TranslateMessage(&msg);//翻译消息，如把WM_KEYDOWN和WM_KEYUP翻译成一个WM_CHAR消息
			DispatchMessage(&msg);//派发消息	
		}
		if (msg.message == 161)
		{
			switch (msg.wParam)
			{
			case 2:
			case 9:
			case 11:
			case 15:
			case 17:
				screen.reset();
			}
		}
		
		screen.clear();
		work.run();
		screen.draw();
		std::cout << clock() - t << std::endl;
		
	}
	return 0;
}
int tgra_win::one_loop()
{
		int t = clock();
		screen.clear();
		work.run();
		screen.draw();
		std::cout << clock() - t << std::endl;
	return 0;
}