#pragma once
#include "Base.h"


class Function:public Base {//function Ŭ����
private:
	//float allcore;
	int pos[12] = { 0,5,10,20,30,40,50,57,70,80,90,100 };//����� x��ǥ 
public:
	void to_int(float usage);//usage�� �Ҽ��� ���� ������ ǥ��
	void to_float(float usage);//usage�� �Ҽ��� 2�ڸ����� ǥ��
	void position(int x, int y);//x,y���� �Է¹޾� Ŀ���� ��ġ�� �ٲپ���
	char* Converter(CString unicode);//unicode�� multibyte�� ��ȯ
	void ifusage(float usage);//usage�� ���� ���� ���� ����
	void textcolor(int foreground, int background);//text�� ������ ����
	void progressbar(float usage);//Base�� progressbar �����ε�
	void otherCPUscore();//�ٸ� CPU�� �������
};