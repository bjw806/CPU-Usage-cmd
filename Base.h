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

//���Ŭ����
class Base {
private:
	float Usage;      //_fCPUv; = float allcore; = > Usage
public:
	void progressbar(float usage); //�Է°��� �ð������� �ٲپ��ִ� �Լ�
	void setUsage(float input); //usage���� set����

	//progressbar�� �����ϴ� ��ҵ�
	const char bar = '=';
	const char blank = ' ';
	const int LEN = 30;
	float tick = (float)100 / LEN;
	int barcount = Usage / tick;
};

/*base


func
���α׷�����
�ؽ�Ʈ ����
Ŀ����ġ
�����ڵ� ������
����� ����


cpu
�����
���ھ�

ram
�����

*/