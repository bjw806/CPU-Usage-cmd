#include "CPU.h"
//#include "Func.h"

CPU::CPU()//생성자
    : //_nCPUv(0),
    _fCPUv(0.0f),
    _dwLastRun(0),
    _lRunCount(0)
{
    ZeroMemory(&_ftPrevSysKernel, sizeof(FILETIME));
    ZeroMemory(&_ftPrevSysUser, sizeof(FILETIME));
    ZeroMemory(&_ftPrevSysIdle, sizeof(FILETIME));

    _dwLastRun = GetTickCount();
}

void CPU::readcpu()//cpu전체 사용률을 읽음
{
    if (::InterlockedIncrement(&_lRunCount) == 1)
    {
        if (enoughTimePassed() == false)
        {
            Sleep(MIN_WAIT_MS);
        }

        FILETIME ftSysIdle, ftSysKernel, ftSysUser = { 0 };
        FILETIME ftProcCreation, ftProcExit, ftProcKernel, ftProcUser = { 0 };

        if (GetSystemTimes(&ftSysIdle, &ftSysKernel, &ftSysUser) == false)
        {
            ::InterlockedDecrement(&_lRunCount);
            return;
        }

        if (firstrun() == false)
        {
            ULONGLONG ftSysKernelDiff = subtractTimes(ftSysKernel, _ftPrevSysKernel);
            ULONGLONG ftSysUserDiff = subtractTimes(ftSysUser, _ftPrevSysUser);
            ULONGLONG ftSysIdleDiff = subtractTimes(ftSysIdle, _ftPrevSysIdle);
            ULONGLONG nTotalSys = ftSysKernelDiff + ftSysUserDiff;

            if (nTotalSys == 0.0)
            {
                _fCPUv = 0.0;
            }
            else
            {
                double _fv = double(nTotalSys) - double(ftSysIdleDiff);
                _fv *= 100.0;
                _fv /= double(nTotalSys);

                _fCPUv = (float)_fv;
            }
        }

        _ftPrevSysKernel = ftSysKernel;
        _ftPrevSysUser = ftSysUser;
        _ftPrevSysIdle = ftSysIdle;

        _dwLastRun = GetTickCount();
    }

    ::InterlockedDecrement(&_lRunCount);
}

ULONGLONG CPU::subtractTimes(const FILETIME& ftA, const FILETIME& ftB) {
    {
        ULONGLONG a, b = 0;

        memcpy(&a, &ftA, sizeof(ULONGLONG));
        memcpy(&b, &ftB, sizeof(ULONGLONG));

        return a - b;
    }
}

bool CPU::enoughTimePassed() {
    {
        DWORD dwCurrentTickCount = GetTickCount();

        if ((dwCurrentTickCount - _dwLastRun) > MIN_WAIT_MS)
        {
            return true;
        }
        return false;
    }
}

void CPU::getCPUname() {
    Function Func;
    int CPUInfo[4] = { -1 };
    __cpuid(CPUInfo, 0x80000000);
    unsigned int nExIds = CPUInfo[0];

    char CPUBrandString[0x40] = { 0 };
    for (unsigned int i = 0x80000000; i <= nExIds; ++i)
    {
        __cpuid(CPUInfo, i);
        if (i == 0x80000002)
        {
            memcpy(CPUBrandString,
                CPUInfo,
                sizeof(CPUInfo));
        }
        else if (i == 0x80000003)
        {
            memcpy(CPUBrandString + 16,
                CPUInfo,
                sizeof(CPUInfo));
        }
        else if (i == 0x80000004)
        {
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        }
    }
    Func.textcolor(BLACK, WHITE);
    Func.position(5, 1);
    cout << "CPU: " << CPUBrandString;
    Func.textcolor(LIGHTGRAY, BLACK);
    //return CPUBrandString;
}

void CPU::setallcore(float all) {//올코어 사용률을 변경해줌
    allcore = all;
}

void CPU::getallcore() {
    Function Func;
    readcpu();
    //return _fCPUv;
    Func.position(5, 3);//좌표를 먼저 잡아줌
    printf("ALLCORE: ");
    progressbar(_fCPUv);
    Func.to_float(_fCPUv);
    cout << " %";
}

void CPU::progressbar(float usage) {
    Function Func;
    //float cpud = usage;
    //int bar_cpu = cpud / tick; // 프로그레스바 갯수 계산 
    Func.textcolor(WHITE, BLACK);//텍스트 흰색으로
    int barcount = usage / tick;
    printf("["); //프로그레스바 시작  
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
    //printf("%3.0f", usage); // 퍼센트 출력
    //cout << " %";
}

void CPU::x86flops() {
    Function Func;
    Func.position(57, 7);
    cout << "x86 flops 계산중...";
    cout.setf(ios_base::fixed);
    clock_t rl_start = clock();
    for (volatile uint32_t rl_index = 0; rl_index < LOOP_REPS; ++rl_index) {
    }
    clock_t rl_end = clock();
    double rl_time = difftime(rl_end, rl_start) / CLOCKS_PER_SEC;

    volatile float a = 1.5;
    volatile float b = 1.6;
    clock_t fl_start = clock();
    for (volatile uint32_t fl_index = 0; fl_index < LOOP_REPS; ++fl_index) {
        a *= b; // multiplication operation
        b += a; // addition operation
    }
    clock_t fl_end = clock();
    double fl_time = difftime(fl_end, fl_start) / CLOCKS_PER_SEC;
    unsigned long flops = LOOP_REPS / ((fl_time - rl_time) / 2);
    Func.position(57, 8);
    cout << "Single Core: ";
    Func.to_float(flops / double(10000000));
    cout << " MFlops";
}

void CPU::SSE2flops()
{
    Function Func;
    Func.position(57, 10);
    cout << "SSE2 flops 계산중...";

    biggestIntSize cycles= 4294967295;
    biggestIntSize trials= 5;

    vector<double> clickDelays;

    for (biggestIntSize j = 0; j < trials; j++)
    {
        double firstTime = clock();
        for (biggestIntSize i = 0; i < cycles; i++);
        double secondTime = clock();
        double Delay = secondTime - firstTime;
        clickDelays.push_back(Delay);
    }

    double clickDelay = getAverage(clickDelays);
    double timeDelay = (double)clickDelay / CLOCKS_PER_SEC;
    double flops = cycles / timeDelay;
    double sciFlops = flops / 10000000;

    Func.position(57, 11);
    cout << "Multi Core: ";// << sciFlops 
    Func.to_float(sciFlops);
    cout << " GFlops";
}

double CPU::getAverage(const vector<double>& input)
{
    double sum = 0;
    for (biggestIntSize i = 0; i < input.size(); i++)
    {
        sum += input.at(i);
    }
    double average = sum / input.size();
    return average;
}