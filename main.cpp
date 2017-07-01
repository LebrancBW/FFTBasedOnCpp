/*
 * main.cpp
 *
 *  Created on: 2017��7��1��
 *      Author: LebrancBW
 */

#include "Complex.h"
#include <cstdio>
#include <iostream>
#include <math.h>
#include <bitset>
using std::cout;
using std::endl;
using std::printf;
using std::bitset;
int main()
{
	const int SCALE = 16;
	const double M_PI = 3.14159265358979323846;
	const int SCALEBITS = 4; //�����ģ����Ҫ�ı�����
	Complex rawData[SCALE]={5,7,6,2,9,1,4,7,0,6,0,14,0,7,8,15};
	int step = 1;//����step��Ϊ�����������������Ϊÿ�ε�ʽ����ʱ��Խ�Ĳ���
	Complex butterflyBuffer[SCALE];//��ʽ����Ļ�����
	unsigned char stack = 0;
	for(unsigned char counter=0;counter<SCALE;counter++)
	{
		unsigned char temp = counter;
		for(unsigned int i=0;i<SCALEBITS;i++)
			{
				stack = (stack << 1) + (temp&0x01);//ȡ���λ
				temp>>=1;
			}
		if(stack>=0&&stack<SCALE)
		{
			butterflyBuffer[counter] = rawData[stack];
			cout<<(int)counter<<"->"<<(int)stack<<endl;
		}
		else
			cout<<"error occurred"<<" stack is"<<stack<<endl;
		stack = 0;
	}//FFT�ĵ������

	for(;step<SCALE;step *= 2)//��һ��ѭ����������
	{
		cout<<"��"<<step<<"�ף�"<<endl;
		for(int butterIndex = 0;butterIndex<SCALE;butterIndex +=step*2)//�ڶ���ѭ��������ÿ�еĵ�ʽ����
		{
			cout<<"	��"<<butterIndex<<"ֻ��"<<endl;
			for(int wingIndex = 0;wingIndex<step;wingIndex++)//������ѭ��������ÿ�������ĳ��
			{
				Complex temp = butterflyBuffer[butterIndex+wingIndex];
				double tempNumber =2* M_PI *wingIndex*(int)pow(2,SCALEBITS-step)/(double)SCALE;	//��ת����W(k,N)
				Complex factor(cos(tempNumber),-sin(tempNumber));
				butterflyBuffer[butterIndex+wingIndex] = temp + factor*butterflyBuffer[butterIndex+wingIndex+step];
				butterflyBuffer[butterIndex+wingIndex+step] = temp - factor*butterflyBuffer[butterIndex+wingIndex+step];
				printf("		��%dֻ����ɵ���X[%d]��X[%d]�ĵ�ʽ����,��ת������W%d\n",wingIndex,butterIndex+wingIndex,butterIndex+wingIndex+step,(int)(wingIndex*pow(2,SCALEBITS-step)));
			}
		}
	}
	for(auto x:butterflyBuffer)
		cout<<x<<endl;
	return 0;
}


