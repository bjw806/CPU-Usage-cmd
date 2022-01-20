#include "Func.h"

void Function::otherCPUscore() {
    position(pos[7], 15);
    cout << "Intel_i7_8750H / x86: 58.71 MFlops / SSE2: 68.45 GFlops";
    position(pos[7], 16);
    cout << "Ryzen_R5_3600 4.4Ghz / x86: 46.29 MFlops / SSE2: 142.31 GFlops";
}

void Function::to_int(float usage) {
    printf("%3.0f", usage); // �ۼ�Ʈ ���
}

void Function::to_float(float usage) {
    printf("%3.2f", usage); // �ۼ�Ʈ ���
}

void Function::position(int x, int y) {
    COORD Pos = { x,y };//Ŀ�� �̵�
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

char* Function::Converter(CString unicode) {
    int Len = WideCharToMultiByte(CP_ACP, 0, unicode, -1, NULL, 0, NULL, NULL);

    char* Multibyte = new char[Len];
    memset(Multibyte, 0x00, (Len) * sizeof(char));

    WideCharToMultiByte(CP_ACP, 0, unicode, -1, Multibyte, Len, NULL, NULL);

    return Multibyte;
}

void Function::ifusage(float usage) {
    if (usage <= 25) {//25%���ϸ�
        textcolor(LIGHTGREEN, BLACK);//�ʷ�
    }
    else if (usage <= 50 && usage > 25) {//25�̻� 50�̸��̸�
        textcolor(LIGHTCYAN, BLACK);//û��
    }
    else if (usage <= 75 && usage > 50) {//...
        textcolor(YELLOW, BLACK);//���
    }
    else if (usage > 75) {//...
        textcolor(LIGHTRED, BLACK);//����
    }
}

void Function::textcolor(int foreground, int background) {
    int color = foreground + background * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Function::progressbar(float usage) {
    barcount = usage / tick;
    textcolor(WHITE, BLACK);
    printf("RAM: [");
    for (int i = 0; i < LEN; i++) {
        if (barcount > i) {
            ifusage(usage);
            printf("%c", bar);
        }
        else {
            printf("%c", blank);
        }
    }
    textcolor(WHITE, BLACK);
    printf("] %3.0f %% ", usage);
}