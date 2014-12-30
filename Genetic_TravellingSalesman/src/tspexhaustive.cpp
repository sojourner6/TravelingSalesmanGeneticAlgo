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
#include<cstring>
#include<time.h>

using namespace std;

static void char_permutation(char str[],char append[],int stct)
{
	char finstr[100],sct=stct;
	int i,length = strlen(str),cell=0;
	finstr[cell++]=char(sct+48);
		if (length)
		{
			for(int i=0;i<length;++i)
			{
			 char* str1 = new char[length+1];
			 int cnt;
			 int cnt2;
				for(cnt=0,cnt2=0; cnt<length; ++cnt,++cnt2)
				{
					if (cnt == i)
					{
						str1[cnt] = str[++cnt2];
						continue;
					}
					else
						str1[cnt] = str[cnt2];
				}
				str1[cnt] = '\0';

				int alength = strlen(append);
				char* append1 = new char [alength+2];
				strncpy(append1,append,alength);
				append1[alength] = str[i];
				append1[alength+1] = '\0';

				char_permutation(str1,append1,sct);

				delete []str1;
				delete []append1;
			}
		}
		else
		{
			for(i=0;append[i]!='\0';i++)
				finstr[cell++]=append[i];
			finstr[cell++]=char(sct+48);finstr[cell]='\0';
			cout <<finstr<<endl;
		}
}

//-----------------------------------------------------------------------

static int exhaustivemain()
{
char str[100],str2[100];
char append[] = "\0";
int i,cell=0,stct;
double start,stop;
cout<<"\nenter the cities : "<<endl;
cin>>str2;
cout<<"\nstart city ? ";
cin>>stct;
  for(i=0;str2[i]!='\0';i++)
  {
	 if(char(stct+48)==str2[i]) continue;
	 else str[cell++]=str2[i];
  }
  str[cell]='\0';
cout << "Original = " << str << endl;
start=clock();
char_permutation(str,append,stct);
stop=clock();
cout<<endl<<(stop-start)<<" milliseconds"<<endl;

return 0;
}
