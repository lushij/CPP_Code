// OpenCV_client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS 1
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;
using namespace cv;

int main()
{
    // 初始化 Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "错误: 初始化 Winsock 失败。" << endl;
        return -1;
    }

    // 创建套接字
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "错误: 创建套接字失败。" << endl;
        WSACleanup();
        return -1;
    }

    // 连接服务器
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.214.128"); // 服务器IP地址
    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        int errorCode = WSAGetLastError();
        cerr << "错误: 连接服务器失败，错误码：" << errorCode << endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
        return -1;
    }
    cout << "连接到服务器成功！" << endl;

    int frameSize;
    vector<uchar> buffer;
    Mat frame;

    while (true) {
        // 接收帧大小
        int bytesReceived = recv(clientSocket, (char*)&frameSize, sizeof(frameSize), 0);
        if (bytesReceived <= 0) {
            cerr << "错误: 接收帧大小失败或连接断开。" << endl;
            break;
        }

        // 接收帧数据
        buffer.resize(frameSize);
        int totalBytesReceived = 0;
        while (totalBytesReceived < frameSize) {
            bytesReceived = recv(clientSocket, (char*)buffer.data() + totalBytesReceived, frameSize - totalBytesReceived, 0);
            if (bytesReceived <= 0) {
                cerr << "错误: 接收帧数据失败或连接断开。" << endl;
                break;
            }
            totalBytesReceived += bytesReceived;
        }

        if (bytesReceived <= 0) {
            break;
        }

        // 解码并显示帧
        frame = imdecode(buffer, IMREAD_COLOR);
        if (frame.empty()) {
            cerr << "错误: 解码失败。" << endl;
            break;
        }
        imshow("接收到的帧", frame);

        if (waitKey(30) == 'q') {
            cout << "退出..." << endl;
            break;
        }
    }

    // 关闭套接字和清理
    closesocket(clientSocket);
    WSACleanup();


    return 0;
}
