/*
 * tspexhaustive.cpp
 *
 *  Created on: May 04, 2009
 *  Originally developed in Turbo C++ 4.5 IDE
--------- Program Authors -------------
--- 05/CSE/06 : SOMNATH SARKAR ----------
--- 05/CSE/08 : PRATIK KARMAKAR ---------
--- 05/CSE/09 : PRADIPTO BISWAS ---------
--- 05/CSE/39 : ADITYA GHUWALEWALA ------
*/

#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

#define true 1
#define false 0
#define totcity 100
#define popsize 100
static int population[popsize][totcity],costmatrix[totcity][totcity];
static int fitness[popsize][2],no_diversity[popsize];

//-------------------- any random tour ---------------------------------------

//-------------- tour with initial city provided -----------------------------

			  //------------ Display Population -----------

static void displaypop(int psize,int csize)
{
	int i,j,psz=psize,csz=csize;
	for(i=0;i<psz;i++)
	{
		for(j=0;j<=csz;j++)  cout<<population[i][j]<<",";
		cout<<"\t";
	}
	cout<<"\n\n";
}

			 //--------------------------------------------


static void initialpop(int psize,int csize,int startcity)
{
 time_t t;
 int r,i,j,avlbl[totcity],c=1,psz=psize,csz=csize,start=startcity;
// srand((unsigned)time(&t));
//	srand((unsigned)(time(&t)) + rand());
 for(i=0;i<psz;i++)
 {
	srand((unsigned)(time(&t)) + rand());
	population[i][0]=start;population[i][csz]=start;
	avlbl[start-1]=false;
  for(j=0;j<csz;j++)
	if(j!=(start-1))
		avlbl[j]=true;
		//cout<<"\n";
		//cout<<population[i][0]<<",";
		while(c!=csz)
		{
			r=rand()%csz+1;
			if(avlbl[r-1]==true)
			{
				avlbl[r-1]=false;
				population[i][c++]=r;
				//cout<<r<<",";
			}
		}
		c=1;
 }
 displaypop(psize,csize);
}


//--------------------- Cost Matrix ------------------------------------------

static void getcostmatrix(int city)
{
	int i,j;
	cout<<"\nEnter Distances between each pair of cities(cost) in the TSP Cost Matrix\n";
	for(i=0;i<city;i++)
	{
		for(j=0;j<city;j++)
		{
			if(costmatrix[i][j]==0 && (i!=j))
			{
				cout<<"\ninput distance for ("<<i<<","<<j<<") = ("<<j<<","<<i<<") : ";
				cin>>costmatrix[i][j];
				costmatrix[j][i]=costmatrix[i][j];
			}
		}
	}
	for(i=0;i<city;i++)
	{
	 for(j=0;j<city;j++)
	  cout<<costmatrix[i][j]<<" ";
	 cout<<"\n";
	}
}

//------------------- Evaluate Fitness Function and Sort ---------------------

	  //--------------- sort fitness values - ascending ------------

static void fitnesssort(int psz)
{
	int i,j,temp1,temp2,pz=psz;
		for(i=0;i<(pz-1);i++)
		{
			for(j=(i+1);j<pz;j++)
			{
				if(fitness[i][0]>fitness[j][0])
				{
					temp1=fitness[i][0];temp2=fitness[i][1];
					fitness[i][0]=fitness[j][0];fitness[i][1]=fitness[j][1];
					fitness[j][0]=temp1;fitness[j][1]=temp2;
				}
			}
		}
		for(i=0;i<pz;i++)
		{
			cout<<fitness[i][0]<<" ---- "<<fitness[i][1];;
			cout<<"\n";
		}
}

	 //-------------------------------------------------------------
			//------------ initialise fitness values -----------------

			static void initfitness(int psize)
			{
				int i,psz=psize;
				for(i=0;i<psz;i++)
				{ fitness[i][0]=0; fitness[i][1]=0; }

			}

			//--------------------------------------------------------

static void evalfitness(int psize,int csize)
{
	int csz=csize,psz=psize,i,j;//temp1,temp2;
  //	cout<<fitness[3][0];    // test output for intermediate value check
  initfitness(psz);
		for(i=0;i<psz;i++)
		{
			for(j=0;j<csz;j++)
			{
				fitness[i][0]+=costmatrix[population[i][j]-1][population[i][j+1]-1];
			}
			  fitness[i][1]=i;
			//cout<<"\n"<<fitness[i];
		}
		fitnesssort(psz);
}

//--------------------- Special Crossover -----------------------------------

					static void specialcrossover(int cell1,int cell2,int crsovrpt,int csize)
					{
						int k1=cell1,k2=cell2,csz=csize,r=crsovrpt,avlbl1[totcity],avlbl2[totcity];
						int i,j;
							for(i=0;i<csz;i++)
							{	avlbl1[i]=true; avlbl2[i]=true; }
							for(i=0;i<r;i++)
							 avlbl1[population[k1][i]-1]=false;
							for(i=r;i<csz;i++)
							{
								for(j=0;j<csz;j++)
								{ if(avlbl1[j]==true) population[k1][i]=(j+1); }
							}
							for(i=0;i<r;i++)
							 avlbl2[population[k2][i]-1]=false;
							for(i=r;i<csz;i++)
							{
								for(j=0;j<csz;j++)
								{ if(avlbl2[j]==true) population[k2][i]=(j+1); }
							}
					}


//---------------------- Crossover-----------------------------------------------------

static void crossover(int psize,int csize)
{
	int r; //crossover point
	int csz=csize,psz=psize,i,cell,maxfit,child1[totcity],child2[totcity],fakeinput;//parent1,parent2,flag=1,maxfit,flag=1;
	int j,compare1=0,compare2=0,cell1,cell2,val=csz-1;
	time_t t;
	srand((unsigned)(time(&t)) + rand());
	r=rand()%val+2;
	cout<<"Crossover Point = "<<r<<"\n Press any key to continue \n";
	cin>>fakeinput;

	 //----------------------------------
		 maxfit=fitness[0][0];cell=0;//compare1=0,compare2=0;
		 while(fitness[cell][0]==maxfit)
		 {	cell++; }
		 for(i=cell;i<psz;i+=2)
		 {
			for(j=0;j<r;j++)
			{ child1[j]=population[fitness[i][1]][j]; child2[j]=population[fitness[i+1][1]][j];}
			for(j=r;j<csz;j++)
			{ child1[j]=population[fitness[i+1][1]][j]; child2[j]=population[fitness[i][1]][j];}
			for(j=0;j<csz;j++)
			{
				for(j=0;j<csz;j++)
				{
				 if(child1[j]==child1[i]) compare1++;
				 if(child2[j]==child2[i]) compare2++;
				}
				if(compare1>1 || compare2>1)
				{
				 cell1=fitness[i][1];
				 cell2=fitness[i+1][1];
				 specialcrossover(cell1,cell2,r,csz);
				 break;
				}
				compare1=0;
            compare2=0;
			}
		 }
		 displaypop(psz,csz);
		 evalfitness(psz,csz);

}                  //function close

//--------------------------------------------------------------------

//-------------------------- Mutation ---------------------------------------

static void mutation(int psize,int csize)
{
	 int i,temp,psz=psize,csz=csize/*,maxfit=fitness[0][0]*/,cell=0,high=0,index=0,ref2;
	 int r1,r2,ref;
	 time_t t;
  //	 int no_diversity[popsize];
		for(i=0;i<psz;i++)
		{
			ref=fitness[i][0]; ref2=i;
			while(fitness[i++][0]==ref)
			{
				if(i==psz) break;
				no_diversity[cell]++;
			}
			if(no_diversity[cell]>high)
			{	high=no_diversity[cell]; index=ref2; }
			cell++; i--;
		}
		srand((unsigned)(time(&t)) + rand());
	for(i=index;high>=0;i++)
	{
		 do
		 {
			r1=rand()%(csz-1)+1;
			r2=rand()%(csz-1)+1;
		 }while(r1==r2);
		temp=population[i][r1];
		population[i][r1]=population[i][r2];
		population[i][r2]=temp;
		high--;
	}
	displaypop(psz,csz);
	evalfitness(psz,csz);
}

//---------------------------------------------------------------------------

	static int geneticmain()
	{
		//initialpop(100,6); ------ without initial city being provided
		int i,csize,stct,ch;
		clock_t t_start, t_stop;
		cout<<"\n\nenter the number of cities  :  ";
		cin>>csize;
		cout<<"\n\nenter the starting city  : ";
		cin>>stct;
		initialpop(100,csize,stct);
		t_start = clock();  // clock start
		getcostmatrix(csize);
		evalfitness(100,csize);
		cout<< "   CROSSOVER   \n";
		do
		{
				crossover(100,csize);
		cout<<" \nmore crossover ? (1/0) :";
				cin>>ch;
	  	}while(ch==1);
		cout<<"\n\n MUTATION \n";
		do
		{
				mutation(100,csize);
				cout<<"\n more mutation ? (1/0) : ";
				cin>>ch;
		}while(ch==1);
		t_stop = clock();  // clock stop
		cout<<"\n\n  BEST SOLUTION : DISTANCE = "<<fitness[0][0]<<" ---- TRAVEL SEQUENCE = ";
			for(i=0;i<=csize;i++)
			 cout<<population[fitness[0][1]][i]<<",";
	return (t_stop - t_start);
	}





