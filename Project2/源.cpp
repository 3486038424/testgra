#include"tgra_win.h"
#include <time.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	tgra_win* l = new tgra_win(L"╣з0ап", 1400, 800, hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	l->loop();
	return 0;
}



	