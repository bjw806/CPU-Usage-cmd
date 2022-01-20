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
void ALLCORE() {//클래스를 쓰레드로 동시실행을 하면 출력좌표가 꼬여서 새로운 함수로 만들음.
    
    while (1) {//무한반복
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
    Cpu.getCPUname();//cpu 모델
    //Eng.Graph();
    thread t1(ALLCORE); //쓰레드 실행
    //Cpu.EachCPU();
    Eng.EachCPU();
    t1.join();
    return 0;
}