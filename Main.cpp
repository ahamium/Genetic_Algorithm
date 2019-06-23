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




	int **City_Distance = new int*[Num_City];   //도시간 거리 2차원;  
	for (i = 0; i < Num_City; i++)
	{
		City_Distance[i] = new int[Num_City];
		for (j = 0; j < Num_City; j++)
		{
			City_Distance[i][j];
		}
	}

	for (i = 0; i < Num_City; i++)  //도시간 거리 data input 
	{
		for (j = 0; j < Num_City; j++)
		{
			//fin >> City_Distance[i][j];
			fin >> iTmp1 >> chTmp1;
			City_Distance[i][j] = iTmp1;
		}
	}


	//crossover--------------------------------------------------------------------------

	double **getCrossoverValue = new double*[Num_City];   //crossover함수 리턴값 받아올 2차원 배열 선언;  
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

	double whentornament = 0.5; //여기에 토너먼트 실행할 확률 선언

	//여기에 반복하고 싶은 수를 h에 대입..
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

		//cout << "---------------- setcrossovervalue함수시작 -------------" << endl;
		Shortest_Distance = setCrossoverValue(getCrossoverValue, Num_Population, Num_City, City_Distance, whentornament);

		//cout << "---------------- 받아왔지롱 -------------" << endl;

		//인스턴스만큼의 값들의 최소값
		if (Final_Shortest_Distance > Shortest_Distance[0]) {
			Final_Shortest_Distance = Shortest_Distance[0];
		}
		

	}
	cout << "=================================================================================================================" << endl;
	cout << "*Shortest_Distance(Objective Function) : " << Final_Shortest_Distance << endl;
	cout << "*최종해 방문 순서 : ";	
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










