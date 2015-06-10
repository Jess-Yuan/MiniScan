#include "Scanner.h"
#include <iostream>
#include <ctime>
#include <map>

using namespace std;

HANDLE hThread[2];
map<string, int> map1;

int main()
{
	//if (ConnectToHost(443,"127.0.0.1"))
	//	cout << "YES" << endl;
	//else
	//	cout << "NO" << endl;
	//CloseConnet();
	mutex = CreateMutex(NULL, FALSE, NULL);
	double start = clock();
	hThread[0] = CreateThread(NULL, 0, Proc1, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, Proc2, NULL, 0, NULL);
	//WaitForSingleObject(hThread, INFINITE);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	for (int i = 0; i < 2; i++)
		CloseHandle(hThread[i]);
	cout << clock() - start << endl;

	//map1["172.0.0.1"] = 12;
	//map1["192.168.10.10"] = 20;
	//for (auto item = map1.begin(); item != map1.end(); item++)
	//	cout << item->first.c_str() << " " << item->second << endl;
}