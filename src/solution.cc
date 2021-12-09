#include "threadsafe_queue.h"
#include "position_parse.h"
#include<WINSOCK2.H>
#include<vector>
#include<string>
#include<sys/timeb.h>
#include <cstdlib>
#include <thread>
#pragma comment(lib,"WS2_32.lib")

using namespace std;
namespace {
    using myFunc = void (*)(std::vector<double>&, std::vector<double>&, std::vector<double>&);
    void dataFilter(std::vector<double>&, std::vector<double>&, std::vector<double>&) {}
}

class Solution{
public:
    [[noreturn]] void UDP_Client(const char* ip, int port) {
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
        while (true) {
            int recvlen = recvfrom(RecvSocket, RecvBuf, 1024, 0, (SOCKADDR *)&serverAddr, &len);
            this->data_queue_.push(string(RecvBuf));
        }
        //关闭socket，结束接收数据
        closesocket(RecvSocket);
        WSACleanup();
    }

    [[noreturn]] void ParsePositionJSON(myFunc process){
        bool isStart = false;
        bool isEnd = false;
        std::vector<double> x;
        std::vector<double> y;
        std::vector<double> ts;
        
        PositionParse parsed;

        bool start=false;
        
        while(true){
            x.clear();
            y.clear();
            ts.clear();
            
            std::string res = this->data_queue_.wait_and_pop();
            parsed.ParseFromString(res);
            while(parsed.IsBegin()){
                start=true;
                continue;
            }
            while(start){
                std::string res = this->data_queue_.wait_and_pop();
                parsed.ParseFromString(res);
                if(!parsed.IsEnd()){
                    x.push_back(parsed.GetX());
                    y.push_back(parsed.GetY());
                    ts.push_back(parsed.GetTS());
                }else{
                    start=false;
                    process(x, y ,ts);
                }  
            }
        }
    }


    void Run(){
        char ip[] = { "118.202.40.213" };
        int port = 8080;
        std::thread producer(&Solution::UDP_Client,this, ip, port);
        std::thread processer(&Solution::ParsePositionJSON,this, &dataFilter);
        producer.join();
        processer.join();
    }

    private:
    threadsafe_queue<string> data_queue_;
};





int main()
{
    Solution test;
    test.Run();
    return 0;
}