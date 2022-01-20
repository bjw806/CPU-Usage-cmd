#pragma once
#include "Base.h"
#include "Func.h"
#include "RAM.h"
#include <vector>

typedef unsigned long long int biggestIntSize;

class CPU :public Base {//CPUUsage Ŭ����
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
	//float  usage() { readcpu(); return _fCPUv; }//�Ҽ���
	void progressbar(float usage);//Base�� progressbar �����ε�
	void setallcore(float all);//allcore�� set
	void getallcore();//���ھ� ����� ���
	void getCPUname();//CPU�� �귣������

//protected:
	void readcpu();//CPU���� ������ �о��
	float returnallcore() { readcpu(); return _fCPUv; }//���ھ� ������ ������
	//float returncoregraph() { return allcore; }
	void x86flops();//Single core flops ���
	void SSE2flops();//multi core flops ���
	double getAverage(const vector<double>& input);//
};