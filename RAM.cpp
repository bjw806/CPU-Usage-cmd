#include "RAM.h"
#include "Func.h"


void RAM::RAMusage() {//CPU�� ����
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    float ramd = statex.dwMemoryLoad;//�޸� ��뷮%
    int total = statex.ullTotalPhys / DIV;//�� �޸� ���
    int free = statex.ullAvailPhys / DIV;//��밡�� �޸� ���
    Function Func;
    Func.position(57, 3);//��ǥ ����
    Func.textcolor(WHITE, BLACK);
    printf("RAM: ");
    progressbar(ramd);
    if (total - free >= 10000) {//��뷮�� 10000mb�̻��̸�
        cout << total - free << " / " << total << "(MB)";//���� ����
    }
    else {
        cout << " " << total - free << " / " << total << "(MB)";//10000�̸��̸� ���� ����
    }
}

void RAM::progressbar(float usage) {
    Function Func;
    Func.textcolor(WHITE, BLACK);//�ؽ�Ʈ �������
    printf("["); //���α׷����� ����  
    int barcount = usage / tick;
    for (int i = 0; i < LEN; i++) { // LEN������ ���α׷����� ���  
        if (barcount > i) { // ���α׷����� ���̺��� i�� ������   
            Func.ifusage(usage);//%�� ���� �� ����
            printf("%c", bar);//bar
        }
        else { // i�� �� Ŀ����  
            printf("%c", blank);//��ĭ
        }
    }
    Func.textcolor(WHITE, BLACK);//�ؽ�Ʈ �������
    cout << "] ";//��
    printf("%3.0f", usage); // �ۼ�Ʈ ���
    cout << " % ";
}