#include<WINSOCK2.H>
#include<iostream>
#include<vector>
#include<string>
#include<sys/timeb.h>
#pragma comment(lib,"WS2_32.lib")
using namespace std;

void UDP_Client(const char* ip, int port, void(*f)(vector<string>&));
DWORD CurrentTime();
void printVec(vector<string>& vec);   //换成接口函数传递给UDP_Client

const int interval = 2 * 60 * 100;        // 2min调用一次接口函数

int main()
{
	char ip[] = { "118.202.40.213" };
	int port = 8080;
	UDP_Client(ip, port, printVec);
	return 0;
}

void UDP_Client(const char* ip, int port, void(*f)(vector<string>&)) {
	vector<string> result;
	WSADATA wsaData;
	sockaddr_in serverAddr;
	//初始化Socket
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建接收数据报的socket
	SOCKET RecvSocket = socket(AF_INET, SOCK_DGRAM, 0);
	//将socket与制定端口绑定
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr(ip);
	serverAddr.sin_port = htons(port);
	int len = sizeof(serverAddr);
	char buf[] = {"Start receive data!"};
	sendto(RecvSocket,buf,strlen(buf),0,(sockaddr*)&serverAddr,len);
	char RecvBuf[1024] = { 0 };//发送数据的缓冲区
	DWORD t1 = CurrentTime();
	DWORD t2 = t1;
	while (true) {
		int recvlen = recvfrom(RecvSocket, RecvBuf, 1024, 0, (SOCKADDR *)&serverAddr, &len);
		result.emplace_back(string(RecvBuf));
		//cout << RecvBuf << " ";
		t2 = CurrentTime();
		if ((t2 - t1) > interval) {
			(*f)(result);
			t1 = t2;
			result.clear();
		}
	}
	//关闭socket，结束接收数据
	closesocket(RecvSocket);
	WSACleanup();
}

DWORD CurrentTime() {
	struct timeb rawtime;
	ftime(&rawtime);
	return DWORD(rawtime.time * 1000 + rawtime.millitm);
}

void printVec(vector<string>& vec) {
	for (auto& v : vec) {
		cout << v << endl;
	}
}