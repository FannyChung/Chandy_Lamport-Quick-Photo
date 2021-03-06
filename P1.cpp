#include <iostream>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <algorithm>

using namespace std;

int main()
{
    double tSum=0;

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
    for (int j = 2; j < 3; j++)
    {
        seed = 9;
        srand(seed);

        for (int i = 0; i < 10;)
        {
            int c = rand() % 60;
            bool tag = true;
            for (int j = 0; j < i; j++)
            {
                if (pho[j] == c)
                {
                    tag = false;
                    break;
                }
            }
            if (tag)
            {
                pho[i] = c;
                i++;
            }
        }
        sort(pho,pho+10);
        tSum = 0;
        int pp=0;
        int i = 0;
        int n2=0;
        while (i<60)
        {
            cout << endl;
            cout << "当前状态：  "<<endl;
            for (int mm = 0; mm < 3; mm++)
            {
                for (int nn = 0; nn < 3; nn++)
                {
                    cout << current[mm][nn] << "\t";
                }
                cout << endl;
            }
            cout << "次数： " << i << endl;
            if (i!=pho[pp])
            {
                int a, b, c;
                do
                {
                    a = rand() % 3;
                }
                while (current[a][a] == 0);
                //a！=b
                do
                {
                    b = rand() % 3;
                }
                while (a == b);
                c = (rand() % (current[a][a])) + 1;

                current[a][a] -= c;
                current[a][b] += c;
                sprintf(msgs[i], "01%02d%02d%03d", a + 1, b + 1, c);
                cout << msgs[i] << endl;
                //fprintf(myexcel, "%f\n", t);
            }
            else
            {
                pp++;
                int a, b;
                a = n2 + 1;
                b = rand() % 3;

                sprintf(msgs[i], "02%02d%02d", a, b + 1);
                cout << msgs[i] << endl;
                //fprintf(myexcel, "%f\n", t);
                n2++;
            }

            R = ((double)rand()) / RAND_MAX;
            t = -2 * log(R);
            times[i] = tSum;
            tSum += t;
            cout << "time = " << t<<endl;

            for (int j = 0; j <= i; j++)
            {
                if (!arrive[j])
                {
                    int cc = msgs[j][1] - '0';
                    if (cc==1)
                    {
                        int a = msgs[j][3] - '0' - 1;
                        int b = msgs[j][5] - '0' - 1;
                        if ((tSum - times[j])>d[a][b])
                        {
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
            i++;
        }
    }

    int result[10][3][3];
    for(int k=0; k<10; k++)
    {
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(i==j)
                {
                    result[k][i][j]=100;
                }
                else
                {
                    result[k][i][j]=0;
                }
            }
        }
    }
    cout<<"total time= "<<tSum<<endl;

    cout<<" photo result is "<<endl;
    //caculate photo
    for (int i = 0; i < 10; i++)
    {
        int s = pho[i];
        int start = msgs[s][5] - '0' - 1;
        for (int j = 0; j < 60; j++ )
        {
            int type = msgs[j][1];
            if (type == '1')
            {
                int a = msgs[j][3] - '1';
                int b = msgs[j][5] - '1';
                int amount = (msgs[j][6] - '0') * 100 + (msgs[j][7] - '0') * 10 + (msgs[j][8] - '0');
                if (times[j] < times[s] + d[start][a]) //send
                {
                    result[i][a][a] -= amount;
                }
                if (times[j] + d[a][b] < times[s] + d[start][b]) //receive
                {
                    result[i][b][b] += amount;
                }
                //caculate the tongdao
                if (!(a == start))
                {
                    if ((times[j]>times[s] - d[a][start]) && (times[j] < times[s] + d[start][a]))
                    {
                        result[i][a][b] += amount;
                    }
                }
            }
        }
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cout << result[i][j][k] << '\t';
            }
            cout << endl;
        }
        cout << endl;
    }

    //write in
    key_t shm_key[5];
    int shm_id[5];
    char *buf[5];
    for (int n = 0; n < 5; n++)
    {
        shm_key[n] = ftok("/tmp/shm_demo", 101 + n);
        shm_id[n] = shmget(shm_key[n], 16, IPC_CREAT | 0666);
        buf[n] = (char *) shmat(shm_id[n], NULL, 0);
    }

    for(int j=0; j<5; j++)
    {
        snprintf(buf[j], 10, msgs[0]);
    }
    cout<<0<<" "<<msgs[0];
    for(int i=1; i<60; i++)
    {
        double t=times[i]-times[i-1];
        sleep(t);
        cout<<" t= "<<t<<endl;
        for(int j=0; j<5; j++)
        {
            snprintf(buf[j], 10, msgs[i]);
        }
        cout<<i<<" "<<msgs[i];
    }
    return  0;
}



