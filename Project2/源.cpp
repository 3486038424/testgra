
#include"tgra_win.h"
#include <time.h>
#include<iostream>
int main(int argc, LPCWSTR* argv[]) {
	tgra_win* l = new tgra_win(L"╣з0ап", 1400, 800);
	l->loop();
	return 0;
}
