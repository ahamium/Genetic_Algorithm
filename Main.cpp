#include "stdafx.h"
#include "function.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <tchar.h>
#include <stdlib.h>

#include <iterator>
#include <algorithm>   //random shuffle
#include <vector>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(0));
	ifstream fin("17city.txt");

	time_t begin, end;
	double duration;
	begin = clock();


	int iTmp1;
	char chTmp1;
	int i, j;
	int Num_City;   //The number of city 
	int Num_Population = 10;     //The number of population
	//fin >> Num_City;
	fin >> iTmp1 >> chTmp1;
	Num_City = iTmp1;




	int **City_Distance = new int*[Num_City];   //���ð� �Ÿ� 2����;  
	for (i = 0; i < Num_City; i++)
	{
		City_Distance[i] = new int[Num_City];
		for (j = 0; j < Num_City; j++)
		{
			City_Distance[i][j];
		}
	}

	for (i = 0; i < Num_City; i++)  //���ð� �Ÿ� data input 
	{
		for (j = 0; j < Num_City; j++)
		{
			//fin >> City_Distance[i][j];
			fin >> iTmp1 >> chTmp1;
			City_Distance[i][j] = iTmp1;
		}
	}


	//crossover--------------------------------------------------------------------------

	double **getCrossoverValue = new double*[Num_City];   //crossover�Լ� ���ϰ� �޾ƿ� 2���� �迭 ����;  
	for (i = 0; i < Num_City; i++)
	{
		getCrossoverValue[i] = new double[Num_City];
		for (j = 0; j < Num_City; j++)
		{
			getCrossoverValue[i][j];
		}
	}

	int instance = 20; //The Number Of Generation
	int Final_Shortest_Distance = 999999;
	int *Shortest_Distance = new int[Num_City + 1];
	Shortest_Distance[0] = 9999;

	double whentornament = 0.5; //���⿡ ��ʸ�Ʈ ������ Ȯ�� ����

	//���⿡ �ݺ��ϰ� ���� ���� h�� ����..
	for (int h = 0; h < instance; h++) 
	{
		cout << "Generation" << h + 1 << "===========================================================================================================" << endl;
		getCrossoverValue = CrossOver(Num_City, Num_Population, City_Distance);
		cout << "-------------------- Selection -------------------------" << endl;
		for (i = 0; i < Num_Population; i++)
		{
			cout << "Selected Population[" << i << "] : ";
			for (j = 0; j <= Num_City; j++)
			{
				cout << getCrossoverValue[i][j] << " ";
			}
			cout << endl;
		}

		//cout << "---------------- setcrossovervalue�Լ����� -------------" << endl;
		Shortest_Distance = setCrossoverValue(getCrossoverValue, Num_Population, Num_City, City_Distance, whentornament);

		//cout << "---------------- �޾ƿ����� -------------" << endl;

		//�ν��Ͻ���ŭ�� ������ �ּҰ�
		if (Final_Shortest_Distance > Shortest_Distance[0]) {
			Final_Shortest_Distance = Shortest_Distance[0];
		}
		

	}
	cout << "=================================================================================================================" << endl;
	cout << "*Shortest_Distance(Objective Function) : " << Final_Shortest_Distance << endl;
	cout << "*������ �湮 ���� : ";	
	for (j = 0; j <= Num_City; j++)
	{
		cout << Shortest_Distance[j + 1] << " ";
	}
	cout << endl;
	


	//CPU time
	end = clock();
	duration = (double(end - begin)) / CLK_TCK;
	cout << "*CPU time : " << duration << endl;
	cout << "=================================================================================================================" << endl;
	begin = 0;
	end = 0;


}










