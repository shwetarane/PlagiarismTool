/*
    RABIN-KARP ALGORITHM

*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cmath>
#define d 256
using namespace std;

bool RabinKarp(char Pattern[], char Text[], int q)
{
    bool state=false;
    int M = strlen(Pattern);
    int N = strlen(Text);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M-1; i++)
        h = (h*d)%q;

    // Calculating the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (d*p + Pattern[i])%q;
        t = (d*t + Text[i])%q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters on by one
        if ( p == t )
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (Text[i+j] != Pattern[j])
                    break;
            }

            // if p == t and Pattern[0...M-1] = Text[i, i+1, ...i+M-1]
            if (j == M)
                state=true;
        }

        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < N-M )
        {
            t = (d*(t - Text[i]*h) + Text[i+M])%q;

            // converting negative value of to positive
            if (t < 0)
            t = (t + q);
        }
    }
    return state;
}

int main()
{
    string base;
    string target;
    fstream fin;
    ifstream fin1;
    int rfound = 0;
    string st1 = "data";
    string st2 = ".txt" ;
    string filename;

    clock_t r1,r2;
    r1=clock();

    cout<<" -------------------------------------------- " <<endl;
    cout<<"|        Rabin-Karp Search Algorithm         |" <<endl;
    cout<<" -------------------------------------------- " <<endl;

    //fin1.open("Target.txt");
    fin.open("Base.txt");

    while(!fin.eof())
    {
        getline(fin,base,'.');
        //cout << "BASE----"<<base<< endl;
        //fin1.open("Target.txt");
        int nb=base.length();
        char basechar[nb+1];
        strcpy(basechar,base.c_str());
        rfound=0;
        for(int i=1; i<=1;i++)
        {
            stringstream ss;
            ss << i;
            filename = st1 + ss.str() + st2;
            fin1.open(filename.c_str());
            int nlines = 0;
            while(!fin1.eof())
            {
                getline(fin1,target,'.');
                    nlines++;
                   // cout<<nlines<<endl;
                // cout<<filename<<endl;
                //cout<<target<< endl;
                int nt=target.length();

                char targchar[nt+1];
                strcpy(targchar,target.c_str());
                if(RabinKarp(basechar, targchar,101))
                {
                    rfound++;
                }
                if (rfound>0)
                {
                    cout<<"Plagiarized content found in file  " << filename <<endl;
                   // cout<<"Number of patterns found till now - " << rfound <<endl;
                   // cout<<"Percentage of Plagiarized content in file : " << (((double)rfound )*100 / nlines) <<"%"<<endl;
                }
            }
            //cout<<"Percentage of Plagiarized content in file : " << (((double)rfound )*100 / nlines) <<"%"<<endl;
            //rfound=0;
            fin1.close();
        }
    }
    cout<<"Percentage of Plagiarized content in files : " << (((double)rfound )*100 / nlines) <<"%"<<endl;
    fin.close();
    r2 = clock();
    cout<<"Total time taken by Rabin Karp Algorithm: "<<(double)(r2-r1)/CLOCKS_PER_SEC<<" milliseconds"<<endl;

    return 0;
}

