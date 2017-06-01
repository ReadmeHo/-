#include "StdAfx.h"
#include "Ant.h"
#include "ACSAnt.h"
#include "NNAnt.h"
#include "AntColonySystem.h"

extern doubleMatrix D;

AntColonySystem::AntColonySystem(double alpha,double beta,double rho,double q0,double alpha1){
	ALPHA=alpha;
	BETA=beta;
	RHO=rho;
	Q0=q0;
	ALPHA1=alpha1;
}

AntColonySystem::~AntColonySystem(void)
{
}

double AntColonySystem::calc_tau0(void){
	double best_length=(double)N*Calculate::max_dist(D);
	for(int n=0;n<N;n++){
		NNAnt* nnANT=new NNAnt(n);
		Tour* tour;
		tour=nnANT->search();
		double tour_length=Calculate::calc_length(tour,D);
		if(tour_length<best_length)
			best_length=tour_length;
		delete nnANT;
	}
	return 1.0/((double)N*best_length);
}

// ��ʼ��TAU0
void AntColonySystem::init_tau_by_value(double TAU0){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			TAU[i][j]=TAU0;
}
//�þ����ʾ�ĳ�ʼ��Ϣ��
void AntColonySystem::init_tau_by_value(doubleMatrix matrix){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			TAU[i][j]=matrix[i][j];
}

// ���Ͼ��ȷֲ��ڳ�����
void AntColonySystem::init_uniform(void){
	for(int k=0;k<M;k++)
		ANTS[k]=new ACSAnt(this,(k%N));
}
// ����ֲ�
void AntColonySystem::init_random(void){
	for(int k=0;k<M;k++)
		ANTS[k]=new ACSAnt(this,(int)((double)N*(rand()/(double)RAND_MAX)));
}
// ÿ�����������һֻ����
void AntColonySystem::init_randomMOAPC(void){
	bool MOAPCarry[N];
	assert(M<N);
	for(int n=0;n<N;n++)
		MOAPCarry[n]=false;
	for(int k=0;k<M;k++){
		int c;
		do
			c=(int)((double)N*(rand()/(double)RAND_MAX));
		while(MOAPCarry[c]);
		MOAPCarry[c]=true;
		ANTS[k]=new ACSAnt(this,c);
	}
}
// �ǵ�ȷ��
double AntColonySystem::ETA(int i, int j){
	return (1.0/D[i][j]);
}
// ����ת�ƹ���
double AntColonySystem::transition(int i, int j){
	if(i!=j)
		return (pow(TAU[i][j],ALPHA1)*pow(ETA(i,j),BETA));
	else
		return (0.0);
}

double AntColonySystem::sum_transition(int i,int allowed[]){
	double sum=0.0;
	for(int j=0;j<N;j++)
		sum+=((double)allowed[j]*transition(i,j));
	return sum;
}
// ����Ⱥϵͳ��ִ�д˲�����������ϵͳ����ִ��
void AntColonySystem::local_update_rule(int i, int j){
	Q0=Q0+TAU[i][j];
	TAU[j][i]=TAU[i][j];
}
// ���ȫ�ָ��¹켣��
void AntColonySystem::clear_global_update(void){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			dTAU[i][j]=0.0;
}
// ����ȫ�ָ���
void AntColonySystem::add_global_updat(Tour* tour,double length){
	for(int n=0;n<N;n++){
		int i=(*tour)[n][0];
		int j=(*tour)[n][1];
		dTAU[i][j]=dTAU[i][j]+(1.0/length);
		dTAU[j][i]=dTAU[i][j]+(1.0/length);
	}
}
// ȫ�ָ��¹���
void AntColonySystem::global_update_rule(void){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			TAU[i][j]=(1.0-ALPHA)*TAU[i][j]+ALPHA*dTAU[i][j];
}

// �þ����ʾ���º�Ĺ켣��
doubleMatrix* AntColonySystem::get_tau(void){
	return &TAU;
}
// �ҳ���ǰѭ�������·����������ȫ�ּ��ظ���
Tour* AntColonySystem::search(int T){
	Tour* tour;
	double best_length=(double)N*Calculate::max_dist(D),tour_length;
	for(int t=0;t<T;t++){
		for(int k=0;k<M;k++){
			tour=ANTS[k]->search();
			tour_length=Calculate::calc_length(tour,D);
			if(tour_length<best_length){
				for(int i=0;i<N;i++){
					this->best_tour[i][0]=(*tour)[i][0];
					this->best_tour[i][1]=(*tour)[i][1];
				}
				best_length=tour_length;
				clear_global_update();
				add_global_updat(tour,tour_length);
			}
		}
		global_update_rule();
	}
	return (&best_tour);
}
