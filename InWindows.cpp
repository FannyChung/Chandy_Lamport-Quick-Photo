#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<time.h>
#include <string.h>
#include <sstream>
using namespace std;


int main(){
	
	double tSum = 0;
	FILE *myexcel;
	fopen_s(&myexcel, "out.txt", "w");
	
	int seed = 5;
	double R;
	double t;
	string s0;
	char msgs[60][10];
	int current[3][3] = { { 100, 0, 0 }, { 0, 100, 0 }, { 0, 0, 100 } };
	double d[3][3] = { { 0, 0.500, 0.300 }, { 0.400, 0, 0.550 }, { 0.350, 0.550, 0 } };
	bool arrive[60];
	double times[60];
	for (int i = 0; i < 60; i++)
	{
		arrive[i] = false;
		times[i] = 0;
	}
	int pho[10];
	for (int j = 2; j < 3; j++){
		seed = 9;
		srand(seed);

		for (int i = 0; i < 10;)
		{
			int c = rand() % 60;
			bool tag = true;
			for (int j = 0; j < i; j++)
			{
				if (pho[j] == c){
					tag = false;
					break;
				}
			}
			if (tag){
				pho[i] = c;
				i++;
			}
		}

		int i = 0;
		int n1 = 0;
		int n2 = 0;
		tSum = 0;
		while (i<60){
			bool isPho1 = false;
			for (int k = 0; k < 10; k++)
			{
				if (i == pho[k]){
					isPho1 = true;
					break;
				}
			}
			for (int j = 0; j < i; j++)
			{
				
				if (!arrive[j]){
					int cc = msgs[j][1] - '0';
					if (cc==1)//发送资源的类型
					{
						int k = j;
						int a = msgs[j][3] - '0' - 1;
						int b = msgs[j][5] - '0' - 1;
						if ((tSum - times[j])>d[a][b]){
							arrive[j] = true;
							int c = (msgs[j][6] - '0') * 100 + (msgs[j][7] - '0') * 10 + (msgs[j][8] - '0');
							current[a][b] -= c;
							current[b][b] += c;
							cout << a + 1 << " arrives at " << b + 1 << " amount: " << c << endl;
							cout << endl;
						}
					}
				}
					
			}
			
			cout << endl;
			cout << "当前状态：  "<<endl;
			for (int mm = 0; mm < 3; mm++){
				for (int nn = 0; nn < 3; nn++)
				{
					cout << current[mm][nn] << "\t";
				}
				cout << endl;
			}
				cout << "次数" << i << endl;
			if (!isPho1){
					int a, b, c;
					do
					{
						a = rand() % 3;
					} while (current[a][a] == 0);


					//a！=b
					do{
						b = rand() % 3;
					} while (a == b);
					c = (rand() % (current[a][a])) + 1;

					current[a][a] -= c;
					current[a][b] += c;


					R = ((double)rand()) / RAND_MAX;
					t = -2 * log(R);
					Sleep(t);
					tSum += t;
					times[i] = tSum;
					sprintf_s(msgs[i], "01%02d%02d%03d", a + 1, b + 1, c);
					cout << msgs[i] << endl;
					cout << "time = " << t;
					cout << endl;
					 
					fprintf(myexcel, "%f\n", t);
					n1++;
					i++;
			}
			else{
					int a, b;
					a = n2 + 1;
					b = rand() % 3;

					R = ((double)rand()) / RAND_MAX;
					t = -2 * log(R);
					Sleep(t);
					tSum += t;
					times[i] = tSum;
					sprintf_s(msgs[i], "02%02d%02d", a, b + 1);
					cout << msgs[i] << endl;
					cout << "time = " << t;
					cout << endl;
					fprintf(myexcel, "%f\n", t);
					n2++;
					i++;
			}
		}
		fclose(myexcel);
		cout << "总时间" << tSum << endl;
	}
	
	
	return  0;
}
