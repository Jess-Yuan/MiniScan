#include "Scanner.h"
#include <iostream>

using namespace std;


int main()
{
	Scanner instance(443, "127.0.0.1");
	if (instance.ScanPort())
		cout << "YES" << instance.ports[1] << endl;
	else
		cout << "NO" << endl;
	instance.CloseConnet();
}