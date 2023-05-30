#include <iostream>
#include <graphics.h>
#include<conio.h>
using namespace std;

// 定义图形类型的枚举
enum DrawType {
    LINE,
    ELLIPSE,
    RECTANGLE
};

// 定义存储画图操作的结构体
struct DrawOperation {
    DrawType type; // 图形类型
    COLORREF color; // 颜色
    int x1, y1, x2, y2; // 坐标信息
};

const int MAX_OPERATIONS = 10000;
DrawOperation operations[MAX_OPERATIONS];
int num_operations = 0;

// 绘制直线
void DrawLine(int x1, int y1, int x2, int y2, COLORREF color) {
    line(x1, y1, x2, y2);
    DrawOperation op = { LINE, color, x1, y1, x2, y2 };
    if (num_operations < MAX_OPERATIONS) {
        operations[num_operations++] = op;
    }
}

// 绘制椭圆
void DrawEllipse(int x1, int y1, int x2, int y2, COLORREF color) {
    ellipse(x1, y1, x2, y2);
    DrawOperation op = { ELLIPSE, color, x1, y1, x2, y2 };
    if (num_operations < MAX_OPERATIONS) {
        operations[num_operations++] = op;
    }
}

// 绘制矩形
void DrawRectangle(int x1, int y1, int x2, int y2, COLORREF color) {
    rectangle(x1, y1, x2, y2);
    DrawOperation op = { RECTANGLE, color, x1, y1, x2, y2 };
    if (num_operations < MAX_OPERATIONS) {
        operations[num_operations++] = op;
    }
}

// 撤销操作
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

// 重做操作
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
        // 获取鼠标状态
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
                // 绘制图形
                switch (msg.mkCtrl ? 2 : msg.mkShift ? 1 : 0) {
                case 0: // 直线
                    line(x1, y1, x2, y2);
                    break;
                case 1: // 椭圆
                    ellipse(x1, y1, x2, y2);
                    break;
                case 2: // 矩形
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
            // 绘制图形
            switch (msg.mkCtrl ? 2 : msg.mkShift ? 1 : 0) {
            case 0: // 直线
                DrawLine(x1, y1, x2, y2, color);
                break;
            case 1: // 椭圆
                DrawEllipse(x1, y1, x2, y2, color);
                break;
            case 2: // 矩形
                DrawRectangle(x1, y1, x2, y2, color);
                break;
            }
            break;
        case WM_RBUTTONDOWN:
            // 右键撤销操作
            Undo();
            break;
        case WM_MBUTTONDOWN:
            // 中键重做操作
            Redo();
            break;
        }

        // 获取键盘状态
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
            case 'c': // 清屏
                cleardevice();
                num_operations = 0;
                break;
            case 'r': // 改变颜色为红色
                color = RED;
                break;
            case 'g': // 改变颜色为绿色
                color = GREEN;
                break;
            case 'b': // 改变颜色为蓝色
                color = BLUE;
                break;
            }
        }
    }

    return 0;
}