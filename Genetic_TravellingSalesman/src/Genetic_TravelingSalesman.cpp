//============================================================================
// Name        : Genetic_TravellingSalesman.cpp
// Author      : Somnath Sarkar
// Version     :
// Copyright   : Public access
// Description : Analysis of the Traveling Salesman problem
//				 exhaustive vs genetic algorithm"
//============================================================================

#include <ctime>
#include <iostream>
#include "tspexhaustive.cpp"
#include "tspgenetic.cpp"

using namespace std;

int main()
{
	cout<<endl<<"Traveling Salesman Problem - Time Analysis";
	cout<<endl<<"Exhaustive Search: "<<exhaustivemain()/1000<<" milliseconds";
	cout<<endl<<"Genetic Algorithm: "<<geneticmain()/1000<<" milliseconds";
return 0;
}
