#pragma once
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <atlstr.h>
#include <stdio.h> 
#include <windows.h> 
#include <intrin.h>//__cpuid
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <tchar.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <string>
#include <comdef.h>
#include <Wbemidl.h>
#include <tchar.h>
#include <thread>
#include <cstring>
#include <thread>
#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define YELLOW 14 
#define WHITE 15
#define MIN_WAIT_MS 500
#define LOOP_REPS 4294967295
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "wbemuuid.lib")
using namespace std;

//기반클래스
class Base {
private:
	float Usage;      //_fCPUv; = float allcore; = > Usage
public:
	void progressbar(float usage); //입력값을 시각적으로 바꾸어주는 함수
	void setUsage(float input); //usage값을 set해줌

	//progressbar을 구성하는 요소들
	const char bar = '=';
	const char blank = ' ';
	const int LEN = 30;
	float tick = (float)100 / LEN;
	int barcount = Usage / tick;
};

/*base


func
프로그레스바
텍스트 색상
커서위치
유니코드 컨버터
사용율 색상


cpu
사용율
올코어

ram
사용율

*/