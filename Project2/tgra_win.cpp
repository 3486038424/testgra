#include "tgra_win.h"
LRESULT CALLBACK WinSunProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
tgra_win::tgra_win(LPSTR name, int width, int height, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	wndcls.cbClsExtra = 0;//类的额外内存，默认为0即可
	wndcls.cbWndExtra = 0;//窗口的额外内存，默认为0即可
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//获取画刷句柄（将返回的HGDIOBJ进行强制类型转换）
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);//设置光标
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);//设置窗体左上角的图标
	wndcls.hInstance = hInstance;//设置窗体所属的应用程序实例
	wndcls.lpfnWndProc = WinSunProc;//设置窗体的回调函数，暂时没写，先设置为NULL，后面补上
	wndcls.lpszClassName = L"test";//设置窗体的类名
	wndcls.lpszMenuName = NULL;//设置窗体的菜单,没有，填NULL
	wndcls.style = CS_HREDRAW | CS_VREDRAW;//设置窗体风格为水平重画和垂直重画
	RegisterClass(&wndcls);//向操作系统注册窗体


	//产生一个窗体，并返回该窗体的句柄，第一个参数必须为要创建的窗体的类名，第二个参数为窗体标题名
	hwnd = CreateWindow(L"test", L"我的第一个窗口",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);//把窗体显示出来
	UpdateWindow(hwnd);//更新窗体
	screenDC = GetDC(hwnd);  // 获取屏幕DC

// 创建与屏幕兼容的内存DC和位图
	memDC = CreateCompatibleDC(screenDC);
	GetClientRect(hwnd, &rc);                       // 获取客户区矩形

	w = width;                 // 宽度
	h = height;                // 高度

	bitmap = CreateCompatibleBitmap(screenDC, width, height);
	SelectObject(memDC, bitmap);
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;  // 使用32位像素格式
	info.bmiHeader.biCompression = BI_RGB;
	GetDIBits(memDC, bitmap, 0, height, NULL, &info, DIB_RGB_COLORS);
	ptr = malloc(width * height * 4);  // 4字节per像素
}



int tgra_win::loop()
{

	// 设置位图的像素颜色
	MSG msg;
	//消息循环
	while (GetMessage(&msg, NULL, 0, 0))//如果消息不是WM_QUIT,返回非零值；如果消息是WM_QUIT，返回零
	{
		TranslateMessage(&msg);//翻译消息，如把WM_KEYDOWN和WM_KEYUP翻译成一个WM_CHAR消息
		DispatchMessage(&msg);//派发消息	
		int y = 0;
		for (; y < h; y++) {
			int offset = y * w;
			for (int x = 0; x < w; x++) {
				((int*)ptr)[offset + x] = RGB(125, 0, 0);
			}
		}
		for (; y < h; y++) {
			int offset = y * w;
			for (int x = 0; x < w; x++) {
				((int*)ptr)[offset + x] = RGB(0, 125, 0);
			}
		}

		// 把位图拷贝到屏幕上显示
		SetDIBits(memDC, bitmap, 0, h, ptr, &info, DIB_RGB_COLORS);
		BitBlt(screenDC, 0, 0, w, h, memDC, 0, 0, SRCCOPY);
	}

	DeleteDC(memDC);
	DeleteObject(bitmap);
	ReleaseDC(NULL, screenDC);
	return 0;
}