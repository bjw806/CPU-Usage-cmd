#pragma once
#include "Base.h"
#define DIV 1048576

class RAM:public Base {
private:
    /*MEMORYSTATUSEX statex;
    float ramd = statex.dwMemoryLoad;//�޸� ��뷮%
    int total = statex.ullTotalPhys / DIV;//�� �޸� ���
    int free = statex.ullAvailPhys / DIV;//��밡�� �޸� ���*/
    //int barcount = ramd / tick;
public:
    void progressbar(float usage);// Base�� progressbar �����ε�
    void RAMusage(); // �ý����� �� ��뷮�� ��Ÿ����
};