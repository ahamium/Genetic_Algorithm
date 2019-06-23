#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <tchar.h>
#include <stdlib.h>

#include <iterator>
#include <algorithm>   //random shuffle
#include <vector>
using namespace std;


double** CrossOver(int Num_City, int Num_Population, int ** City_Distance) {

	int a, i, j, t, k;


	int *Chromosome = new int[Num_City];   //population별 city 2차원배열_CITY, 벡터->1차원배열

	int **Set_population = new int*[Num_Population];  //population별 city, 1차원배열->2차원배열
	for (i = 0; i < Num_Population; i++)
	{
		Set_population[i] = new int[Num_City];
		for (j = 0; j <= Num_City; j++)
		{
			Set_population[i][j];
		}
	}




	double *Total_Distance_arr = new double[Num_Population];  //각 population의 total distance 1차원배열
	double *Sum_Total_Distance_arr = new double[Num_Population];  //각 population의 total distance다 더한것 1차원배열
	double *Accum_Probability_arr = new double[Num_Population];  //각 population의 누적확률 1차원배열
	int *Sum_Total_Dart_arr = new int[Num_Population]; // 각 다트 값들을 저장할 배열 선언
	double **RePopulation_arr = new double*[Num_Population]; // 각  Population값들을 재저장할 2차원배열 선언
	for (i = 0; i < Num_Population; i++)
	{
		RePopulation_arr[i] = new double[Num_City];
		for (j = 0; j <= Num_City; j++)
		{
			RePopulation_arr[i][j];
		}
	}
	//선언끝

	   /*cout << Num_City << endl;
		for (i = 0; i < Num_City; i++)
		{
		for (j = 0; j < Num_City; j++)
		{
		cout << City_Distance[i][j] << " ";
		}
		cout << endl;}*/


	for (i = 0; i < Num_Population; i++)
	{
		//initial population
		double Total_Distance = 0;
		double Sum_Total_Distance = 0; //전체 population의 총 거리 





		//population random shuffle
		vector <int> Chromosome_random_shuffle(Num_City); //city 순서를 랜덤하게 population 생성할 배열
		for (j = 0; j < Num_City; j++)
		{
			Chromosome_random_shuffle[j] = j;
			/*cout << Chromosome[j] << " ";
			 cout << Chromosome_random_shuffle[j] << " "; */
		}
		cout << endl;

		for (j = 0; j < 1; j++)  //랜덤하게 초기 population 벡터로 생성
		{
			random_shuffle(Chromosome_random_shuffle.begin(), Chromosome_random_shuffle.end());
		}
		Chromosome_random_shuffle.push_back(Chromosome_random_shuffle[0]);     //출발도시 = 마지막도시

		/*for (vector<int>::size_type j = 0;j < Chromosome_random_shuffle.size(); ++j)
		{
		   cout << Chromosome_random_shuffle[j] << " ";
		}*/

		//int *Chromosome = new int[Num_City];   //population별 city 2차원배열_CITY, 벡터->배열   위에 선언되어있음
		for (j = 0; j <= Num_City; j++)
		{
			Chromosome[j] = Chromosome_random_shuffle[j];        //population 벡터->1차원배열->2차원배열
			Set_population[i][j] = Chromosome[j];
		}

		cout << "Initial Populattion[" << i << "] : ";
		for (j = 0; j <= Num_City; j++)
		{
			cout << Chromosome[j] << " ";
		}
		//cout << "흥칫뿡" << endl; 


		/*   for (j = 0; j <= Num_City; j++)
		   {
			  cout << Set_population[i][j] << " ";
		   }
		   cout << endl;*/


		   //calculate the total distance 
		for (j = 0; j < Num_City; j++)
		{
			int temp_distance;
			int temp_city1 = Chromosome[j];      // city i
			int temp_city2 = Chromosome[j + 1];       // city j

			temp_distance = City_Distance[temp_city1][temp_city2]; //city_distance 불러오기
			Total_Distance += temp_distance; //각 chromosome의 total distance
			//cout << temp_distance << " ";
		}
		//cout << Total_Distance << " ";
		Total_Distance_arr[i] = Total_Distance;
		cout << ", Total_distance : " << Total_Distance_arr[i] << " ";


		//Define Fitness function 
		/*Roulette wheel selection : population[i]의 distance / total distance

		/* 총 distance와 비례하게 누적확률을 구한다 (총 누적확률의합:1)
		-> 랜덤하게 0~1사이의 숫자를 발생시킨다(roulett wheel에 다트)
		-> 해당하는 누적확률에 해당하는 크로무즘 을 크로스오버 대상선택   */
	}
	cout << endl;


	double Sum_Total_Distance = 0;
	for (k = 0; k < Num_Population; k++)
	{
		Sum_Total_Distance += Total_Distance_arr[k];  //전체 population 의 총distance 배열로 들고있음 
	}
	//cout << "전체population의 total distance : " << Sum_Total_Distance << endl;
	double Accum_Probability = 0;
	for (k = 0; k < Num_Population; k++)
	{
		double temp;   //각 chromosome의 total distance
		double fitness_function;

		temp = Total_Distance_arr[k];
		fitness_function = (Sum_Total_Distance / temp)*0.0401;         //★★FITNESS FUNCTION!!!!  해당 population 의 총거리/ 전체 population 의 총거리합  ★distance작은값이 높은 확률갖도록 다시 
		cout << "Population[" << k << "]의 Fitness_function : " << fitness_function << ", Accumulative Probability : ";
		Accum_Probability += fitness_function;
		Accum_Probability_arr[k] = Accum_Probability;    //누적확률 배열로 받음(dart값과 비교위해)
		cout << Accum_Probability_arr[k] << endl;

	}

	//Selection

	int dartsum = 0;

	// for(int j=0;j<5;j++){
	// std::cout << j+1 <<"번째" <<endl;
	for (a = 0; a < Num_Population; a++)
	{
		double Dart;
		double max = 32767;
		//난수랜덤생성하기(double)rand() / (RAND_MAX + 1)*(range_max - range_min) + range_min;

		//Dart = rand() / max;
		Dart = (double)rand() / (32767 + 1)*Accum_Probability_arr[Num_Population - 1];
		std::cout << "=====> Dart!! :" << Dart << endl;




		for (int a = 0; a < Num_Population; a++)
		{
			if (Dart == Accum_Probability_arr[a] || Dart < Accum_Probability_arr[a])
			{
				std::cout << a << endl;
				Sum_Total_Dart_arr[dartsum] = a; //각 다트값들을 이전의 선언해놓은 Sum_Total_Dart_arr배열에 차례대로 저장
				break;
			}
		}
		dartsum++;
	}

	/*for (int i = 0; i < dartsum; i++) {
	   cout << "Sum_Total_Dart_arr[dartsum] : " << Sum_Total_Dart_arr[i] << endl;
	}*/

	/*for (int o = 0; o < Num_Population; o++)
	{
	   Set_population[i] = new int[Num_City];
	   for (j = 0; j <= Num_City; j++)
	   {
		  cout << Set_population[o][j] << " ";
	   }
	   cout << endl;
	}*/

	
	//  Sum_Total_Dart_arr배열값에 맞는 Set_population 배열 최종출력
	for (int i = 0; i < dartsum; i++) {
		for (j = 0; j <= Num_City; j++)
		{
			//cout << Set_population[Sum_Total_Dart_arr[i]][j] << " ";
			RePopulation_arr[i][j] = Set_population[Sum_Total_Dart_arr[i]][j];
		}
		//cout << endl;
	}
	//cout << endl;

	
	/*for (int o = 0; o < Num_Population; o++)
	{
		RePopulation_arr[i] = new double[Num_City];
		for (j = 0; j <= Num_City; j++)
		{
			cout << RePopulation_arr[o][j] << " ";
		}
		cout << endl;
	}
	cout << "--------------- 리퍼퓰레이션 배열 값 확인해봐 --------------" << endl;

	for (int i = 0; i < Num_Population; i++) {
		cout << "Populattion" << i << " : ";
		for (j = 0; j <= Num_City; j++)
		{
			cout << RePopulation_arr[i][j] << " ";
		}
		cout << endl;
	}*/





	return RePopulation_arr;
}



int* setCrossoverValue(double **getCrossoverValue, int Num_Population, int Num_City, int ** City_Distance, double whentornament) {
	if (((double)rand() / (32767 + 1) * 10) > (10 * whentornament)) {
		cout << "-------------------- Tournament 생략 --------------------" << endl;
		int i, j;
		int a, t, k;


		double *Total_Distance_arr = new double[Num_Population];  //각 population의 total distance 1차원배열
		double *Sum_Total_Distance_arr = new double[Num_Population];  //각 population의 total distance다 더한것 1차원배열
		double *Accum_Probability_arr = new double[Num_Population];  //각 population의 누적확률 1차원배열
		int *Sum_Total_Dart_arr = new int[Num_Population]; // 각 다트 값들을 저장할 배열 선언
		double **RePopulation_arr = new double*[Num_Population]; // 각  Population값들을 재저장할 2차원배열 선언
		int *Shortest_Distance = new int[Num_City + 1];
		Shortest_Distance[0] = 9999;

		for (i = 0; i < Num_Population; i++)
		{
			//initial population
			double Total_Distance = 0;
			double Sum_Total_Distance = 0; //전체 population의 총 거리 

			//cout << "Selected Population[" << i << "] : ";
			for (j = 0; j <= Num_City; j++)
			{
				//cout << getCrossoverValue[i][j] << " ";
			}



			//calculate the total distance 
			for (j = 0; j < Num_City; j++)
			{
				int temp_distance;
				//int temp_city1 = Chromosome[j];      // city i
				//int temp_city2 = Chromosome[j + 1];       // city j
				int temp_city1 = getCrossoverValue[i][j];
				int temp_city2 = getCrossoverValue[i][j + 1];

				temp_distance = City_Distance[temp_city1][temp_city2];    //city_distance 불러오기
				Total_Distance += temp_distance; //각 chromosome의 total distance
				//cout << temp_distance << " ";
			}
			//cout << Total_Distance << " ";
			Total_Distance_arr[i] = Total_Distance;
			cout << ", Total_distance : " << Total_Distance_arr[i] << " ";
			cout << endl;

			//Define Fitness function 
			/*Roulette wheel selection : population[i]의 distance / total distance

			/* 총 distance와 비례하게 누적확률을 구한다 (총 누적확률의합:1)
			-> 랜덤하게 0~1사이의 숫자를 발생시킨다(roulett wheel에 다트)
			-> 해당하는 누적확률에 해당하는 크로무즘 을 크로스오버 대상선택   */
		}
		cout << endl;

		for (i = 0; i < Num_Population; i++) {
			if (Shortest_Distance[0] > Total_Distance_arr[i]) {
				Shortest_Distance[0] = Total_Distance_arr[i];
				for (j = 0; j <= Num_City; j++)
				{
					Shortest_Distance[j + 1] = getCrossoverValue[i][j];
				}
			}
		}
		return Shortest_Distance;
	}


	else {
		cout << "-------------------- Tournament 당첨 --------------------" << endl;
		int i, j;
		int **Set_population = new int*[Num_Population];  //population별 city, 1차원배열->2차원배열
		for (i = 0; i < Num_Population; i++)
		{
			Set_population[i] = new int[Num_City];
			for (j = 0; j <= Num_City; j++)
			{
				Set_population[i][j];
			}
		}


		for (i = 0; i < Num_Population; i++)
		{
			for (j = 0; j <= Num_City; j++)
			{
				Set_population[i][j] = getCrossoverValue[i][j];
			}
		}


		//for (i = 0; i < Num_Population; i++)
		//{
		//	//cout << "Seleted Populattion[" << i << "] : ";
		//	for (j = 0; j <= Num_City; j++)
		//	{
		//		cout << getCrossoverValue[i][j] << " ";
		//	}
		//	cout << " " << endl;
		//}


		cout << "-------------------- Start ------------------------------" << endl;
		int a, t, k, p = 0;


		double *Total_Distance_arr = new double[Num_Population];  //각 population의 total distance 1차원배열
		double *Sum_Total_Distance_arr = new double[Num_Population];  //각 population의 total distance다 더한것 1차원배열
		double *Accum_Probability_arr = new double[Num_Population];  //각 population의 누적확률 1차원배열
		int *Sum_Total_Dart_arr = new int[Num_Population]; // 각 다트 값들을 저장할 배열 선언
		double **RePopulation_arr = new double*[Num_Population]; // 각  Population값들을 재저장할 2차원배열 선언
		int *Shortest_Distance = new int[Num_City + 1];
		Shortest_Distance[0] = 9999;
		for (j = 1; j <= Num_City + 1; j++)
		{
			Shortest_Distance[j];
		}

		for (i = 0; i < Num_Population; i++)
		{
			RePopulation_arr[i] = new double[Num_City];
			for (j = 0; j <= Num_City; j++)
			{
				RePopulation_arr[i][j];
			}
		}

		//(double)rand() / (32767 + 1)*(range_max - range_min) + range_min;
		for (t = 0; t < Num_Population; t++) {
			int check1 = (double)rand() / (32767 + 1) * 4;
			int check2 = (double)rand() / (32767 + 1) * 4;
			
			while (check1 == check2) {
				check2 = (double)rand() / (32767 + 1) * 4;
			}
			cout << "Parents[1] : " << check1 << endl;
			cout << "Parents[2] : " << check2 << endl;
			cout << "Population[" << check1 << "] : ";
			for (j = 0; j <= Num_City; j++)
			{
				cout << Set_population[check1][j] << " ";
			}
			cout << " " << endl;
			cout << "Population[" << check2 << "] : ";
			for (j = 0; j <= Num_City; j++)
			{
				cout << Set_population[check2][j] << " ";
			}
			cout << endl;
			//cout << "---------------------------------------------------------" << endl;

			//홀수일때
			if (Num_City % 2 == 0) {

				int torna = (Num_City / 2);

				//check1의 반으로 갈라서 그전부분은 그대로..
				for (i = 0; i < torna; i++) {
					RePopulation_arr[t][i] = Set_population[check1][i];
				}
				//check1의 끝부분은 그대로..
				RePopulation_arr[t][Num_City] = Set_population[check1][Num_City];

				//torna만큼의 갯수를 check2랑 치환해야해..

				for (i = torna; i < 2 * torna; i++) {
					for (j = 0; j <= Num_City; j++) {
						if (Set_population[check1][i] != Set_population[check2][j])
						{
							p = 0;
							for (k = 0; k < i; k++) {
								if (Set_population[check2][j] == Set_population[check1][k]) {
									p++;
								}
							}
							if (p == 0) {
								RePopulation_arr[t][i] = Set_population[check2][j];
								Set_population[check1][i] = Set_population[check2][j];
								break;
							}

						}
					}

				}
				if (RePopulation_arr[t][2 * torna - 1] < 0) {
					RePopulation_arr[t][2 * torna - 1] = Set_population[check1][2 * torna - 1];
				}


			}
			else {
				//짝수일때..
				int torna = (int)((double)(Num_City / 2) + 1);

				//check1의 반으로 갈라서 그전부분은 그대로..
				for (i = 0; i < torna; i++) {
					RePopulation_arr[t][i] = Set_population[check1][i];
				}
				//check1의 끝부분은 그대로..
				RePopulation_arr[t][Num_City] = Set_population[check1][Num_City];

				//torna-1만큼의 갯수를 check2랑 치환해야해..

				for (i = torna; i < 2 * torna - 1; i++) {
					for (j = 0; j <= Num_City; j++) {
						if (Set_population[check1][i] != Set_population[check2][j])
						{
							p = 0;
							for (k = 0; k < i; k++) {
								if (Set_population[check2][j] == Set_population[check1][k]) {
									p++;
								}
							}
							if (p == 0) {
								RePopulation_arr[t][i] = Set_population[check2][j];
								Set_population[check1][i] = Set_population[check2][j];
								break;
							}

						}
					}

				}
				if (RePopulation_arr[t][2 * torna - 2] < 0) {
					RePopulation_arr[t][2 * torna - 2] = Set_population[check1][2 * torna - 2];
				}
			}


		}
		/*for (t = 0; t < Num_Population; t++) {
			cout << "Population[" << t << "] : ";
			for (i = 0; i <= Num_City; i++) {
				cout << RePopulation_arr[t][i] << " ";
			}
			cout << endl;
		}*/
		cout << "--------------------END--------------------------------" << endl;



		for (i = 0; i < Num_Population; i++)
		{
			//initial population
			double Total_Distance = 0;
			double Sum_Total_Distance = 0; //전체 population의 총 거리 

			cout << "Population[" << i << "] : ";
			for (j = 0; j <= Num_City; j++)
			{
				cout << RePopulation_arr[i][j] << " ";
			}


			//calculate the total distance 
			for (j = 0; j < Num_City; j++)
			{
				int temp_distance;
				//int temp_city1 = Chromosome[j];      // city i
				//int temp_city2 = Chromosome[j + 1];       // city j
				int temp_city1 = RePopulation_arr[i][j];
				int temp_city2 = RePopulation_arr[i][j + 1];

				temp_distance = City_Distance[temp_city1][temp_city2];    //city_distance 불러오기
				Total_Distance += temp_distance; //각 chromosome의 total distance
				//cout << temp_distance << " ";
			}
			//cout << Total_Distance << " ";
			Total_Distance_arr[i] = Total_Distance;
			cout << ", Total_distance : " << Total_Distance_arr[i] << " ";
			cout << endl;

			//Define Fitness function 
			/*Roulette wheel selection : population[i]의 distance / total distance

			/* 총 distance와 비례하게 누적확률을 구한다 (총 누적확률의합:1)
			-> 랜덤하게 0~1사이의 숫자를 발생시킨다(roulett wheel에 다트)
			-> 해당하는 누적확률에 해당하는 크로무즘 을 크로스오버 대상선택   */
		}
		cout << endl;
		//cout << "---------------깔끔한 시작 --------------" << endl;

		for (i = 0; i < Num_Population; i++) {
			if (Shortest_Distance[0] > Total_Distance_arr[i]) {
				Shortest_Distance[0] = Total_Distance_arr[i];

				for (j = 0; j <= Num_City; j++)
				{
					Shortest_Distance[j + 1] = RePopulation_arr[i][j];
				}
			}
		}


		return Shortest_Distance;
	}
}