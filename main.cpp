#include "Base.h"
#include "CPU.h"
#include "RAM.h"
#include "Func.h"
#include "Engine.h"
#include <thread>
using namespace std;

Function Func;
CPU Cpu;
RAM Ram;
Engine Eng;
int i = 0;
void ALLCORE() {//Ŭ������ ������� ���ý����� �ϸ� �����ǥ�� ������ ���ο� �Լ��� ������.
    
    while (1) {//���ѹݺ�
        Cpu.setallcore(Cpu.returnallcore());
        //Ram.RAMmod();
        if (i == 0) {
            Cpu.x86flops();
            Cpu.SSE2flops();
            Func.otherCPUscore();
        }
        i++;
    }
}

int main() {
    Cpu.getCPUname();//cpu ��
    //Eng.Graph();
    thread t1(ALLCORE); //������ ����
    //Cpu.EachCPU();
    Eng.EachCPU();
    t1.join();
    return 0;
}