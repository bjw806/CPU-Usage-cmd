#include "Base.h"

void Base::setUsage(float input) {//���ھ� ������ ��������
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

