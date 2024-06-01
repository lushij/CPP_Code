#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

#include <opencv2/opencv.hpp>
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")


using namespace cv;

int main()
{
    // 初始化 Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "错误: 初始化 Winsock 失败。" << std::endl;
        return -1;
    }

    // 创建套接字
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "错误: 创建套接字失败。" << std::endl;
        WSACleanup();
        return -1;
    }

    // 绑定套接字
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "错误: 绑定套接字失败。" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // 监听连接
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "错误: 监听失败。" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }
    std::cout << "等待客户端连接..." << std::endl;

    // 接受客户端连接
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "错误: 接受连接失败。" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }
    std::cout << "客户端连接成功！" << std::endl;

    // 实例化 VideoCapture 对象
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "错误: 无法打开摄像头。" << std::endl;
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // 设置帧的宽度和高度
    cap.set(CAP_PROP_FRAME_WIDTH, 720);
    cap.set(CAP_PROP_FRAME_HEIGHT, 640);

    Mat frame;
    std::vector<uchar> buffer;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "错误: 空帧。" << std::endl;
            break;
        }

        // 编码帧为JPEG格式
        imencode(".jpg", frame, buffer);
        int frameSize = buffer.size();

        // 发送帧大小
        int bytesSent = send(clientSocket, (char*)&frameSize, sizeof(frameSize), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "错误: 发送帧大小失败。" << std::endl;
            break;
        }

        // 发送帧数据
        bytesSent = send(clientSocket, (char*)buffer.data(), frameSize, 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "错误: 发送帧数据失败。" << std::endl;
            break;
        }

        // 延迟
        if (waitKey(30) == 'q') {
            std::cout << "退出..." << std::endl;
            break;
        }
    }

    // 关闭套接字和清理
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
