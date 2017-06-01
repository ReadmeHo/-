function[MaxE,MinE,Path,Energy]=Annealing(Path,Energy,Temperature,MaxE,MinE,NumCity,Distance,MaxTrialN)

TrialN=0;%��¼��������
for i=1:MaxTrialN
	NewPath=Path;%�����µ�·��
	%���ѡ����������
	Index=ceil(rand(2,1)*NumCity);
	Temp1=NewPath(Index);
	%��������������
	NewPath(Index(1,1))=Temp1(1,2);
	NewPath(Index(2,1))=Temp1(1,1);
	NewEnergy=sum(Distance((NewPath([1:NumCity,1])-1)*NumCity+NewPath([2:NumCity,1:2])));%�����»�·��·������
	%���»�·���̣�������»�·
	if NewEnergy<Energy
		Energy=NewEnergy;%��������
		Path=NewPath;%���»�·
		MinE=min([MinE,Energy]);%������С����
		MaxE=max([MaxE,Energy]);%�����������
	%���򣬰���һ�����ʾ����Ƿ�����»�·
	else
		if rand<1/(1+exp((NewEnergy-Energy)/Temperature));
			Energy=NewEnergy;
			Path=NewPath;
			MinE=min([MinE,Energy]);
			MaxE=max([MaxE,Energy]);
		end
	end
end