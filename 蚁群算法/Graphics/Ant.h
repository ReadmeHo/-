#pragma once

class Ant{
	protected: 
		int START_CITY;//��ʼ����
		int CURRENT_CITY;//��ǰ����
		int ALLOWED[N];//���ɱ�
		Tour CURRENT_TOUR;
		int CURRENT_TOUR_INDEX;
	public:
		Ant(int start_city);
		void moveTO(int to_city);
};