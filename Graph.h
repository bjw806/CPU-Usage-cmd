#pragma once
#include "Base.h"
#include "Func.h"
#include "CPU.h"
#include "RAM.h"

class Graph :public Base, public CPU, public RAM, public Function {
private:
	char digits[20][40] = { "' '" };
	
public:
	void Graping();
	void DrawGraph();
	void line();
	void lineUp();
	void lineDown();
	void line2();
	void caldigit(float usage,int uptime);
};