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


	int *Chromosome = new int[Num_City];   //population�� city 2�����迭_CITY, ����->1�����迭

	int **Set_population = new int*[Num_Population];  //population�� city, 1�����迭->2�����迭
	for (i = 0; i < Num_Population; i++)
	{
		Set_population[i] = new int[Num_City];
		for (j = 0; j <= Num_City; j++)
		{
			Set_population[i][j];
		}
	}




	double *Total_Distance_arr = new double[Num_Population];  //�� population�� total distance 1�����迭
	double *Sum_Total_Distance_arr = new double[Num_Population];  //�� population�� total distance�� ���Ѱ� 1�����迭
	double *Accum_Probability_arr = new double[Num_Population];  //�� population�� ����Ȯ�� 1�����迭
	int *Sum_Total_Dart_arr = new int[Num_Population]; // �� ��Ʈ ������ ������ �迭 ����
	double **RePopulation_arr = new double*[Num_Population]; // ��  Population������ �������� 2�����迭 ����
	for (i = 0; i < Num_Population; i++)
	{
		RePopulation_arr[i] = new double[Num_City];
		for (j = 0; j <= Num_City; j++)
		{
			RePopulation_arr[i][j];
		}
	}
	//����

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
		double Sum_Total_Distance = 0; //��ü population�� �� �Ÿ� 





		//population random shuffle
		vector <int> Chromosome_random_shuffle(Num_City); //city ������ �����ϰ� population ������ �迭
		for (j = 0; j < Num_City; j++)
		{
			Chromosome_random_shuffle[j] = j;
			/*cout << Chromosome[j] << " ";
			 cout << Chromosome_random_shuffle[j] << " "; */
		}
		cout << endl;

		for (j = 0; j < 1; j++)  //�����ϰ� �ʱ� population ���ͷ� ����
		{
			random_shuffle(Chromosome_random_shuffle.begin(), Chromosome_random_shuffle.end());
		}
		Chromosome_random_shuffle.push_back(Chromosome_random_shuffle[0]);     //��ߵ��� = ����������

		/*for (vector<int>::size_type j = 0;j < Chromosome_random_shuffle.size(); ++j)
		{
		   cout << Chromosome_random_shuffle[j] << " ";
		}*/

		//int *Chromosome = new int[Num_City];   //population�� city 2�����迭_CITY, ����->�迭   ���� ����Ǿ�����
		for (j = 0; j <= Num_City; j++)
		{
			Chromosome[j] = Chromosome_random_shuffle[j];        //population ����->1�����迭->2�����迭
			Set_population[i][j] = Chromosome[j];
		}

		cout << "Initial Populattion[" << i << "] : ";
		for (j = 0; j <= Num_City; j++)
		{
			cout << Chromosome[j] << " ";
		}
		//cout << "��ĩ��" << endl; 


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

			temp_distance = City_Distance[temp_city1][temp_city2]; //city_distance �ҷ�����
			Total_Distance += temp_distance; //�� chromosome�� total distance
			//cout << temp_distance << " ";
		}
		//cout << Total_Distance << " ";
		Total_Distance_arr[i] = Total_Distance;
		cout << ", Total_distance : " << Total_Distance_arr[i] << " ";


		//Define Fitness function 
		/*Roulette wheel selection : population[i]�� distance / total distance

		/* �� distance�� ����ϰ� ����Ȯ���� ���Ѵ� (�� ����Ȯ������:1)
		-> �����ϰ� 0~1������ ���ڸ� �߻���Ų��(roulett wheel�� ��Ʈ)
		-> �ش��ϴ� ����Ȯ���� �ش��ϴ� ũ�ι��� �� ũ�ν����� �����   */
	}
	cout << endl;


	double Sum_Total_Distance = 0;
	for (k = 0; k < Num_Population; k++)
	{
		Sum_Total_Distance += Total_Distance_arr[k];  //��ü population �� ��distance �迭�� ������� 
	}
	//cout << "��üpopulation�� total distance : " << Sum_Total_Distance << endl;
	double Accum_Probability = 0;
	for (k = 0; k < Num_Population; k++)
	{
		double temp;   //�� chromosome�� total distance
		double fitness_function;

		temp = Total_Distance_arr[k];
		fitness_function = (Sum_Total_Distance / temp)*0.0401;         //�ڡ�FITNESS FUNCTION!!!!  �ش� population �� �ѰŸ�/ ��ü population �� �ѰŸ���  ��distance�������� ���� Ȯ�������� �ٽ� 
		cout << "Population[" << k << "]�� Fitness_function : " << fitness_function << ", Accumulative Probability : ";
		Accum_Probability += fitness_function;
		Accum_Probability_arr[k] = Accum_Probability;    //����Ȯ�� �迭�� ����(dart���� ������)
		cout << Accum_Probability_arr[k] << endl;

	}

	//Selection

	int dartsum = 0;

	// for(int j=0;j<5;j++){
	// std::cout << j+1 <<"��°" <<endl;
	for (a = 0; a < Num_Population; a++)
	{
		double Dart;
		double max = 32767;
		//�������������ϱ�(double)rand() / (RAND_MAX + 1)*(range_max - range_min) + range_min;

		//Dart = rand() / max;
		Dart = (double)rand() / (32767 + 1)*Accum_Probability_arr[Num_Population - 1];
		std::cout << "=====> Dart!! :" << Dart << endl;




		for (int a = 0; a < Num_Population; a++)
		{
			if (Dart == Accum_Probability_arr[a] || Dart < Accum_Probability_arr[a])
			{
				std::cout << a << endl;
				Sum_Total_Dart_arr[dartsum] = a; //�� ��Ʈ������ ������ �����س��� Sum_Total_Dart_arr�迭�� ���ʴ�� ����
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

	
	//  Sum_Total_Dart_arr�迭���� �´� Set_population �迭 �������
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
	cout << "--------------- ����ǽ���̼� �迭 �� Ȯ���غ� --------------" << endl;

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
		cout << "-------------------- Tournament ���� --------------------" << endl;
		int i, j;
		int a, t, k;


		double *Total_Distance_arr = new double[Num_Population];  //�� population�� total distance 1�����迭
		double *Sum_Total_Distance_arr = new double[Num_Population];  //�� population�� total distance�� ���Ѱ� 1�����迭
		double *Accum_Probability_arr = new double[Num_Population];  //�� population�� ����Ȯ�� 1�����迭
		int *Sum_Total_Dart_arr = new int[Num_Population]; // �� ��Ʈ ������ ������ �迭 ����
		double **RePopulation_arr = new double*[Num_Population]; // ��  Population������ �������� 2�����迭 ����
		int *Shortest_Distance = new int[Num_City + 1];
		Shortest_Distance[0] = 9999;

		for (i = 0; i < Num_Population; i++)
		{
			//initial population
			double Total_Distance = 0;
			double Sum_Total_Distance = 0; //��ü population�� �� �Ÿ� 

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

				temp_distance = City_Distance[temp_city1][temp_city2];    //city_distance �ҷ�����
				Total_Distance += temp_distance; //�� chromosome�� total distance
				//cout << temp_distance << " ";
			}
			//cout << Total_Distance << " ";
			Total_Distance_arr[i] = Total_Distance;
			cout << ", Total_distance : " << Total_Distance_arr[i] << " ";
			cout << endl;

			//Define Fitness function 
			/*Roulette wheel selection : population[i]�� distance / total distance

			/* �� distance�� ����ϰ� ����Ȯ���� ���Ѵ� (�� ����Ȯ������:1)
			-> �����ϰ� 0~1������ ���ڸ� �߻���Ų��(roulett wheel�� ��Ʈ)
			-> �ش��ϴ� ����Ȯ���� �ش��ϴ� ũ�ι��� �� ũ�ν����� �����   */
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
		cout << "-------------------- Tournament ��÷ --------------------" << endl;
		int i, j;
		int **Set_population = new int*[Num_Population];  //population�� city, 1�����迭->2�����迭
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


		double *Total_Distance_arr = new double[Num_Population];  //�� population�� total distance 1�����迭
		double *Sum_Total_Distance_arr = new double[Num_Population];  //�� population�� total distance�� ���Ѱ� 1�����迭
		double *Accum_Probability_arr = new double[Num_Population];  //�� population�� ����Ȯ�� 1�����迭
		int *Sum_Total_Dart_arr = new int[Num_Population]; // �� ��Ʈ ������ ������ �迭 ����
		double **RePopulation_arr = new double*[Num_Population]; // ��  Population������ �������� 2�����迭 ����
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

			//Ȧ���϶�
			if (Num_City % 2 == 0) {

				int torna = (Num_City / 2);

				//check1�� ������ ���� �����κ��� �״��..
				for (i = 0; i < torna; i++) {
					RePopulation_arr[t][i] = Set_population[check1][i];
				}
				//check1�� ���κ��� �״��..
				RePopulation_arr[t][Num_City] = Set_population[check1][Num_City];

				//torna��ŭ�� ������ check2�� ġȯ�ؾ���..

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
				//¦���϶�..
				int torna = (int)((double)(Num_City / 2) + 1);

				//check1�� ������ ���� �����κ��� �״��..
				for (i = 0; i < torna; i++) {
					RePopulation_arr[t][i] = Set_population[check1][i];
				}
				//check1�� ���κ��� �״��..
				RePopulation_arr[t][Num_City] = Set_population[check1][Num_City];

				//torna-1��ŭ�� ������ check2�� ġȯ�ؾ���..

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
			double Sum_Total_Distance = 0; //��ü population�� �� �Ÿ� 

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

				temp_distance = City_Distance[temp_city1][temp_city2];    //city_distance �ҷ�����
				Total_Distance += temp_distance; //�� chromosome�� total distance
				//cout << temp_distance << " ";
			}
			//cout << Total_Distance << " ";
			Total_Distance_arr[i] = Total_Distance;
			cout << ", Total_distance : " << Total_Distance_arr[i] << " ";
			cout << endl;

			//Define Fitness function 
			/*Roulette wheel selection : population[i]�� distance / total distance

			/* �� distance�� ����ϰ� ����Ȯ���� ���Ѵ� (�� ����Ȯ������:1)
			-> �����ϰ� 0~1������ ���ڸ� �߻���Ų��(roulett wheel�� ��Ʈ)
			-> �ش��ϴ� ����Ȯ���� �ش��ϴ� ũ�ι��� �� ũ�ν����� �����   */
		}
		cout << endl;
		//cout << "---------------����� ���� --------------" << endl;

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