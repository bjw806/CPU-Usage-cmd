#pragma once
#include "Base.h"
#include "Func.h"
#include "RAM.h"
#include <vector>

typedef unsigned long long int biggestIntSize;

class CPU :public Base {//CPUUsage 클래스
private:
	bool firstrun() const { return (_dwLastRun == 0); }
	FILETIME    _ftPrevSysKernel;
	FILETIME    _ftPrevSysUser;
	FILETIME    _ftPrevSysIdle;

	float       _fCPUv;
	DWORD       _dwLastRun;

	volatile
		LONG        _lRunCount;

	ULONGLONG subtractTimes(const FILETIME& ftA, const FILETIME& ftB); //Unsigned long long

	bool enoughTimePassed();
	//int barcount = _fCPUv / tick;
	float allcore;
public:
	CPU();
	//float  usage() { readcpu(); return _fCPUv; }//소수점
	void progressbar(float usage);//Base의 progressbar 오버로드
	void setallcore(float all);//allcore을 set
	void getallcore();//올코어 사용율 출력
	void getCPUname();//CPU의 브랜드정보

//protected:
	void readcpu();//CPU에서 정보를 읽어옴
	float returnallcore() { readcpu(); return _fCPUv; }//올코어 사용률을 리턴함
	//float returncoregraph() { return allcore; }
	void x86flops();//Single core flops 계산
	void SSE2flops();//multi core flops 계산
	double getAverage(const vector<double>& input);//
};