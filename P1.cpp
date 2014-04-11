#include<iostream>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<stdio.h>

#include <string.h>
#include <sstream>
#include<time.h>
#include<unistd.h>
#include<math.h>
using namespace std;


int main(){
	clock_t start, finish=clock();
	double  duration;
	int tSum=0;
	int i = 0;
	int seed = 5;
	double R;
	double t;
	string s0;
	char s1[] = { 'i', 'j', 'k' };
	int current[3][3] = { {100,0,0}, {100,0,0}, {100,0,0} };
	srand(seed);
	int pho[10];
	for (int i = 0; i < 10; ++i)
	{
		pho[i]=rand()%60;
	}

	while (i<60){
		for (int j = 0; j < i; ++j)
		{
			/* huoqu xiaoxi  */
		}
		start = finish;
		
		cout << endl;
		cout << current[0][0]<<'\t'<<current[1][1]<<'\t'<<current[2][2]<<endl;
		for (int j = 0; j < 10; ++j)
		{
			if(i==pho[i]){
				tag=true;
				break;
			}
		}
		if (!tag){
				int a, b=0, c;
				s0 = "01";
				do
				{
					a = rand() % 3;
				} while (current[a][a]==0);
				
				
				//a！=b
				
				do{
					b = rand() % 3;
				} while (a==b);
				c = (rand() % (current[a][a]))+1;
				
				current[a][a] -= c;



				//current[b][b] += c;


				R = ((double)rand()) / RAND_MAX;
				t = -2 * log(R);
				sleep(t);
				tSum+=t;

				finish = clock();
				duration = (double)(finish - start);
				cout << s0 << '\t' << s1[a] << '\t' << s1[b] << '\t' << c << '\t' << i<< endl;
				cout << "time = " << t;
				cout << endl;
				i++;
		}
		else{
				int a, b;
				s0 = "02";
				a = n2 + 1;
				b = rand() % 3;

				R = ((double)rand()) / RAND_MAX;
				t = -2 * log(R);
				sleep(t);
				tSum+=t;

				finish = clock();
				duration = (double)(finish - start);

				cout << s0 << '\t' << a << '\t' << s1[b] << '\t' << i<<endl;
				cout << "time = " << t;
				cout << endl;
				i++;
		}
	}

	cout<<"total time= "<<tSum<<endl;
	return  0;
}
