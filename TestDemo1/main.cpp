#include "Scanner.h"
#include <iostream>
#include <ctime>

using namespace std;

HANDLE hThread[2];


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
}