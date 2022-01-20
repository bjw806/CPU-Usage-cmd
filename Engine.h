#pragma once
#include "Base.h"
#include "Func.h"
#include "CPU.h"
#include "RAM.h"

class Engine :public Base, public CPU, public RAM, public Function {
public:
	void EachCPU();//±¸Çö
};