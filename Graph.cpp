#include "Graph.h"
/*

|
|
|
|
|
|
|
|
|
|
|
|
|                                            ______
|                            ___________    ��     ��
|                           ��          ��  ��       ��                                         ______________________
|                          ��            ����         ��                                       ��
|            ______       ��                          ��                                     ��
| __________��     ��_____��                            ��                               ������
|��                                                     ��_____________________________��
�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
��
��
������...

*/

void Graph::caldigit(float usage, int uptime) {
    Function Func;

    //int digit = usage / 5;
    int x;
    while (1) {
        int k = 0;
        if (usage < 5 * (k + 1) && usage >= 5 * k) {
            x = k + 1;
            Func.position(57 - uptime, 15 + x);//uptime=0���� ����
            line();
            break;
        }
        k++;
    }
 

/*
    for (int k = 0; k <= 20; k++) {
        if (digit <= 5 * k && digit > 5 * k) {
            Func.position(57 - uptime, 15 + digit);//uptime=0���� ����
            line();
            break;
        }
    }
 */

}

void Graph::Graping() {
    DrawGraph();

}

void Graph::DrawGraph() {
    Function Func;
    for (int i = 0; i < 20; i++) {
        Func.position(5, 20 + i);
        cout << "|" << endl;

        if (i == 14) {
            Func.position(5, 20 + i);
            cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
        }

    }
}

void Graph::line() {
    //i���� ���
    //i-1�� ���ʿ� ���
    //�ݺ�
    cout << "��";
}

void Graph::lineUp() {
    cout << "��";

}

void Graph::lineDown() {
    cout << "��";

}

void Graph::line2() {
    cout << "��";

}

