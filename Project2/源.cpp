
#include"tgra_win.h"
#include <time.h>
#include<iostream>
int main(int argc, LPCWSTR* argv[]) {
	tgra_win* l = new tgra_win(L"��0��", 1400, 800);
	l->loop();
	return 0;
}
