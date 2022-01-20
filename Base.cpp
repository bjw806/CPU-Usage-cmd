#include "Base.h"

void Base::setUsage(float input) {//올코어 사용률을 변경해줌
    Usage = input;
}

void Base::progressbar(float usage) {
    barcount = usage / tick;
    printf("RAM: [");
    for (int i = 0; i < LEN; i++) {
        if (barcount > i) {
            
            printf("%c", bar);
        }
        else {
            printf("%c", blank);
        }
    }
    printf("] %3.0f %% ", usage);
}

