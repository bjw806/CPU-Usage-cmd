#pragma once
#include "Base.h"


class Function:public Base {//function 클래스
private:
	//float allcore;
	int pos[12] = { 0,5,10,20,30,40,50,57,70,80,90,100 };//출력할 x좌표 
public:
	void to_int(float usage);//usage를 소수점 없는 정수로 표현
	void to_float(float usage);//usage를 소수점 2자리까지 표현
	void position(int x, int y);//x,y값을 입력받아 커서의 위치를 바꾸어줌
	char* Converter(CString unicode);//unicode를 multibyte로 변환
	void ifusage(float usage);//usage의 값에 따라 색상 변경
	void textcolor(int foreground, int background);//text의 색상을 변경
	void progressbar(float usage);//Base의 progressbar 오버로드
	void otherCPUscore();//다른 CPU의 점수출력
};