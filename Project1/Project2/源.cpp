#include <iostream>
#include <graphics.h>
#include<conio.h>
using namespace std;

// ����ͼ�����͵�ö��
enum DrawType {
    LINE,
    ELLIPSE,
    RECTANGLE
};

// ����洢��ͼ�����Ľṹ��
struct DrawOperation {
    DrawType type; // ͼ������
    COLORREF color; // ��ɫ
    int x1, y1, x2, y2; // ������Ϣ
};

const int MAX_OPERATIONS = 10000;
DrawOperation operations[MAX_OPERATIONS];
int num_operations = 0;

// ����ֱ��
void DrawLine(int x1, int y1, int x2, int y2, COLORREF color) {
    line(x1, y1, x2, y2);
    DrawOperation op = { LINE, color, x1, y1, x2, y2 };
    if (num_operations < MAX_OPERATIONS) {
        operations[num_operations++] = op;
    }
}

// ������Բ
void DrawEllipse(int x1, int y1, int x2, int y2, COLORREF color) {
    ellipse(x1, y1, x2, y2);
    DrawOperation op = { ELLIPSE, color, x1, y1, x2, y2 };
    if (num_operations < MAX_OPERATIONS) {
        operations[num_operations++] = op;
    }
}

// ���ƾ���
void DrawRectangle(int x1, int y1, int x2, int y2, COLORREF color) {
    rectangle(x1, y1, x2, y2);
    DrawOperation op = { RECTANGLE, color, x1, y1, x2, y2 };
    if (num_operations < MAX_OPERATIONS) {
        operations[num_operations++] = op;
    }
}

// ��������
void Undo() {
    if (num_operations > 0) {
        DrawOperation op = operations[--num_operations];
        setcolor(WHITE);
        switch (op.type) {
        case LINE:
            line(op.x1, op.y1, op.x2, op.y2);
            break;
        case ELLIPSE:
            ellipse(op.x1, op.y1, op.x2, op.y2);
            break;
        case RECTANGLE:
            rectangle(op.x1, op.y1, op.x2, op.y2);
            break;
        }
    }
}

// ��������
void Redo() {
    if (num_operations < MAX_OPERATIONS) {
        DrawOperation op = operations[num_operations++];
        setcolor(op.color);
        switch (op.type) {
        case LINE:
            line(op.x1, op.y1, op.x2, op.y2);
            break;
        case ELLIPSE:
            ellipse(op.x1, op.y1, op.x2, op.y2);
            break;
        case RECTANGLE:
            rectangle(op.x1, op.y1, op.x2, op.y2);
            break;
        }
    }
}

int main() {
    initgraph(640, 480);

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    bool is_drawing = false;
    COLORREF color = RED;

    while (true) {
        // ��ȡ���״̬
        MOUSEMSG msg = GetMouseMsg();
        switch (msg.uMsg) {
        case WM_LBUTTONDOWN:
            x1 = msg.x;
            y1 = msg.y;
            is_drawing = true;
            break;
        case WM_MOUSEMOVE:
            if (is_drawing) {
                x2 = msg.x;
                y2 = msg.y;
                setcolor(color);
                // ����ͼ��
                switch (msg.mkCtrl ? 2 : msg.mkShift ? 1 : 0) {
                case 0: // ֱ��
                    line(x1, y1, x2, y2);
                    break;
                case 1: // ��Բ
                    ellipse(x1, y1, x2, y2);
                    break;
                case 2: // ����
                    rectangle(x1, y1, x2, y2);
                    break;
                }
            }
            break;
        case WM_LBUTTONUP:
            is_drawing = false;
            x2 = msg.x;
            y2 = msg.y;
            setcolor(color);
            // ����ͼ��
            switch (msg.mkCtrl ? 2 : msg.mkShift ? 1 : 0) {
            case 0: // ֱ��
                DrawLine(x1, y1, x2, y2, color);
                break;
            case 1: // ��Բ
                DrawEllipse(x1, y1, x2, y2, color);
                break;
            case 2: // ����
                DrawRectangle(x1, y1, x2, y2, color);
                break;
            }
            break;
        case WM_RBUTTONDOWN:
            // �Ҽ���������
            Undo();
            break;
        case WM_MBUTTONDOWN:
            // �м���������
            Redo();
            break;
        }

        // ��ȡ����״̬
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
            case 'c': // ����
                cleardevice();
                num_operations = 0;
                break;
            case 'r': // �ı���ɫΪ��ɫ
                color = RED;
                break;
            case 'g': // �ı���ɫΪ��ɫ
                color = GREEN;
                break;
            case 'b': // �ı���ɫΪ��ɫ
                color = BLUE;
                break;
            }
        }
    }

    return 0;
}