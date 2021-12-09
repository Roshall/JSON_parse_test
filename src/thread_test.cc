#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <string>
#include <iostream>
 
class ThreadX
{
private:
	std::string threadName;
	int loopStart;
	int loopEnd;
	int loopStep;
public:
	ThreadX(int x, int y, int z) : loopStart(x), loopEnd(y), loopStep(z) { }
	void SetThreadName(std::string name)
	{
		threadName = name;
	}
	static unsigned __stdcall ThreadEntryPoint(void* pThis)
	{
		ThreadX* pTh = (ThreadX*)pThis;
		pTh->StartUp();
 
		return 1;
	}
	void StartUp()
	{
		for (int i = loopStart; i < loopEnd; ++i)
		{
			if (i % loopStep == 0)
			{
				//std::cout << threadName << ": " << i << std::endl;
				printf("%s : %d \n", threadName.c_str(), i);
			}
		}
		printf("%s terminating...\n", threadName.c_str());
	}
};
 
int main()
{
	ThreadX* obj1 = new ThreadX(0, 1000000, 20000);
	obj1->SetThreadName("Thread1");
	HANDLE hThread1;
	unsigned thread1Id;
	hThread1 = (HANDLE)_beginthreadex(NULL,
		0,
		ThreadX::ThreadEntryPoint,
		obj1,
		CREATE_SUSPENDED,
		&thread1Id);
	if (hThread1 == NULL)
	{
		printf("Failed to create Thread 1. \n");
	}
	DWORD dwExitCode;
	GetExitCodeThread(hThread1, &dwExitCode);
	printf("initial thread 1 exit code = %d \n", dwExitCode);
 
	ThreadX* obj2 = new ThreadX(-1000000, 0, 20000);
	obj2->SetThreadName("Thread2");
	HANDLE hThread2;
	unsigned thread2Id;
	hThread2 = (HANDLE)_beginthreadex(NULL,
		0,
		ThreadX::ThreadEntryPoint,
		obj2,
		CREATE_SUSPENDED,
		&thread2Id);
	if (hThread2 == NULL)
	{
		printf("Failed to create Thread 1. \n");
	}
	GetExitCodeThread(hThread1, &dwExitCode);
	printf("initial thread 2 exit code = %d \n", dwExitCode);
 
	ResumeThread(hThread1);
	ResumeThread(hThread2);
 
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
 
	GetExitCodeThread(hThread1, &dwExitCode);
	printf("thread 1 exit with code : %d \n", dwExitCode);
 
	GetExitCodeThread(hThread2, &dwExitCode);
	printf("thread 2 exit with code : %d \n", dwExitCode);
 
	CloseHandle(hThread1);
	CloseHandle(hThread2);
 
	delete(obj1);
	obj1 = NULL;
	delete(obj2);
	obj2 = NULL;
 
	system("pause");
	return 0;
}