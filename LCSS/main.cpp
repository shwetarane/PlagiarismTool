/*
    LCSS ALGORITHM

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


/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int LCSS( char *X, char *Y, int m, int n )
{
   int L[m+1][n+1];
   int i, j;

   /* Following steps build L[m+1][n+1] in bottom up fashion. Note
      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
   for (i=0; i<=m; i++)
   {
     for (j=0; j<=n; j++)
     {
       if (i == 0 || j == 0)
         L[i][j] = 0;

       else if (X[i-1] == Y[j-1])
         L[i][j] = L[i-1][j-1] + 1;

       else
         L[i][j] = max(L[i-1][j], L[i][j-1]);
     }
   }

   /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
   return L[m][n];
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b)? a : b;
}

int main()
{
    string base;
    string target;
    int len=0;
    fstream fin;
    fstream fin1;
    int lfound = 0;
    string st1 = "data";
    string st2 = ".txt" ;
    string filename;
    int nlines = 0;
    clock_t l1, l2 ;
    l1=clock();
    string line;
    int c=0;//chars counter
    char cur = '\0';
    char last = '\0';
    float perc=0;
    cout<<" -------------------------------------------- " <<endl;
    cout<<"|               LCSS Algorithm               |" <<endl;
    cout<<" -------------------------------------------- " <<endl;

    //fin1.open("Target.txt");
    fin.open("Base.txt");

    while(!fin.eof())
    {

        getline(fin, base, '\n' );
        //cout<<"Para"<<base<<endl;
        //cout << "BASE----"<<base<< endl;
        //fin1.open("Target.txt");
        int nb=base.length();
        char basechar[nb+1];
        strcpy(basechar,base.c_str());
        for(int i=1; i<=49;i++)
        {
            stringstream ss;
            ss << i;
            filename = st1 + ss.str() + st2;
            fin1.open(filename.c_str());
            //cout<<filename<<endl;
            while (fin1.get(cur)) {
            if (cur == '\n' ||(cur == '\f' && last == '\r'))
                continue;
            else
                c++;
            }
            fin1.close();
            fin1.open(filename.c_str());
            while(!fin1.eof())
            {
                getline( fin1, target,'\n');
                //cout<<"Target Para:"<<target<<endl;
                //nlines++;
                int nt=target.length();
                char targchar[nt+1];
                strcpy(targchar,target.c_str());
                //cout<<LCSS(basechar,targchar,nb,nt)<<endl;
                len=max(LCSS(basechar,targchar,nb,nt),len);

            }
            //cout<<"Length of longest common subsequence found in File"<<i<<" is: - " << len <<endl<<endl;
            //cout<<"chars"<<c<<endl;
            cout<<"Percentage of SubSequence found in the file "<<i<<" is "<<(float(len)/float(c))*100<<"%."<<endl;
            c=0;
            len=0;
            fin1.close();
        }

    }

   fin.close();
   l2 = clock();


    cout<<"Total time taken by LCSS Algorithm: "<<(double)(l2-l1)/CLOCKS_PER_SEC<<" milliseconds"<<endl;

    return 0;
}
