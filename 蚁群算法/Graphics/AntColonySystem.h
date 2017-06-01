#pragma once

class ACSAnt;
class AntColonySystem{
	public:
		AntColonySystem(double alpha,double beta,double rho,double q0,double alphal);
		~AntColonySystem(void);
		double Q0;//����Q0��Ϊ�㣬��Ϊ����ϵͳ
		Tour best_tour;
	private:
		double ALPHA;//��Ϣ�ع켣�������Ҫ��
		double BETA;//�ܼ��ȵ������Ҫ��
		double RHO;//��Ϣ�ع켣�ĳ־���
		double TAU0;//��ʼ����Ϣ�ص���
		double ALPHA1;
		doubleMatrix TAU;
		doubleMatrix dTAU;
		ACSAnt* ANTS[M];
	public:
		double calc_tau0(void);	
		void init_tau_by_value(double value);//��ʼ��TAU0
		void init_tau_by_value(doubleMatrix matrix);
		void init_uniform(void);// ���Ͼ��ȷֲ��ڳ�����	
		void init_random(void);// ����ֲ�
		void init_randomMOAPC(void);// ÿ�����������һֻ����	
		double ETA(int i, int j);// �ǵ�ȷ��
		double transition(int i, int j);// ����ת�ƹ���
		double sum_transition(int i,int allowed[]);
		void local_update_rule(int i, int j);// ����Ⱥϵͳ��ִ�д˲�����������ϵͳ����ִ��
		void clear_global_update(void);// ���ȫ�ָ��¹켣��
		void add_global_updat(Tour* tour,double length );// ����ȫ�ָ���
		void global_update_rule(void);// ȫ�ָ��¹���
		doubleMatrix* get_tau(void);// �þ����ʾ���º�Ĺ켣��
		Tour* search(int T);// �ҳ���ǰѭ�������·����������ȫ�ּ��ظ���
};
