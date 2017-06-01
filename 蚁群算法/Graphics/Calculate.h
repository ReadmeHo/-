#pragma once

#define N 6//���������Ϊ6
#define M 6//����������Ϊ6
#define Q 100//Ӱ��켣���¹����Qֵ��С

typedef int Tour[N][N];
typedef double doubleMatrix[N][N];

class Calculate{
	public:
		Calculate(void);
		~Calculate(void);
		static double dist(double C[][2],int i, int j);// �����м�ļ��ξ���
		static void calc_dist(double D[][N],double C[][2]);// �����ڽӾ���
		static double max_dist(doubleMatrix D);// �����м��������
		static double calc_length(Tour* tour,doubleMatrix D);// ����n�����е�һ��·������
		static int sum_sequence(int aarray[], int count);// �þ����ʾ�ľ���n�����е�·������
};
