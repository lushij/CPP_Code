#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

#include <opencv2/opencv.hpp>
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")


using namespace cv;

int main()
{
    // ��ʼ�� Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "����: ��ʼ�� Winsock ʧ�ܡ�" << std::endl;
        return -1;
    }

    // �����׽���
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "����: �����׽���ʧ�ܡ�" << std::endl;
        WSACleanup();
        return -1;
    }

    // ���׽���
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "����: ���׽���ʧ�ܡ�" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // ��������
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "����: ����ʧ�ܡ�" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }
    std::cout << "�ȴ��ͻ�������..." << std::endl;

    // ���ܿͻ�������
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "����: ��������ʧ�ܡ�" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }
    std::cout << "�ͻ������ӳɹ���" << std::endl;

    // ʵ���� VideoCapture ����
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "����: �޷�������ͷ��" << std::endl;
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // ����֡�Ŀ�Ⱥ͸߶�
    cap.set(CAP_PROP_FRAME_WIDTH, 720);
    cap.set(CAP_PROP_FRAME_HEIGHT, 640);

    Mat frame;
    std::vector<uchar> buffer;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "����: ��֡��" << std::endl;
            break;
        }

        // ����֡ΪJPEG��ʽ
        imencode(".jpg", frame, buffer);
        int frameSize = buffer.size();

        // ����֡��С
        int bytesSent = send(clientSocket, (char*)&frameSize, sizeof(frameSize), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "����: ����֡��Сʧ�ܡ�" << std::endl;
            break;
        }

        // ����֡����
        bytesSent = send(clientSocket, (char*)buffer.data(), frameSize, 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "����: ����֡����ʧ�ܡ�" << std::endl;
            break;
        }

        // �ӳ�
        if (waitKey(30) == 'q') {
            std::cout << "�˳�..." << std::endl;
            break;
        }
    }

    // �ر��׽��ֺ�����
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
