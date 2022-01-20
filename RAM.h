#pragma once
#include "Base.h"
#define DIV 1048576

class RAM:public Base {
private:
    /*MEMORYSTATUSEX statex;
    float ramd = statex.dwMemoryLoad;//메모리 사용량%
    int total = statex.ullTotalPhys / DIV;//총 메모리 계산
    int free = statex.ullAvailPhys / DIV;//사용가능 메모리 계산*/
    //int barcount = ramd / tick;
public:
    void progressbar(float usage);// Base의 progressbar 오버로드
    void RAMusage(); // 시스템의 램 사용량을 나타내줌
};