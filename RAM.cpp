#include "RAM.h"
#include "Func.h"


void RAM::RAMusage() {//CPU와 동일
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    float ramd = statex.dwMemoryLoad;//메모리 사용량%
    int total = statex.ullTotalPhys / DIV;//총 메모리 계산
    int free = statex.ullAvailPhys / DIV;//사용가능 메모리 계산
    Function Func;
    Func.position(57, 3);//좌표 고정
    Func.textcolor(WHITE, BLACK);
    printf("RAM: ");
    progressbar(ramd);
    if (total - free >= 10000) {//사용량이 10000mb이상이면
        cout << total - free << " / " << total << "(MB)";//띄어쓰기 없음
    }
    else {
        cout << " " << total - free << " / " << total << "(MB)";//10000미만이면 띄어쓰기 있음
    }
}

void RAM::progressbar(float usage) {
    Function Func;
    Func.textcolor(WHITE, BLACK);//텍스트 흰색으로
    printf("["); //프로그레스바 시작  
    int barcount = usage / tick;
    for (int i = 0; i < LEN; i++) { // LEN길이의 프로그레스바 출력  
        if (barcount > i) { // 프로그레스바 길이보다 i가 작으면   
            Func.ifusage(usage);//%에 따라 색 변경
            printf("%c", bar);//bar
        }
        else { // i가 더 커지면  
            printf("%c", blank);//빈칸
        }
    }
    Func.textcolor(WHITE, BLACK);//텍스트 흰색으로
    cout << "] ";//끝
    printf("%3.0f", usage); // 퍼센트 출력
    cout << " % ";
}