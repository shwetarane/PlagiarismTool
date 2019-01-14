/*
    KMP ALGORITHM

*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

void LPS(string &pattern, int f[])
{
    int m = pattern.length(), k;
    f[0] = -1;
    for (int i = 1; i < m; i++)
    {
        k = f[i - 1];
        while (k >= 0)
        {
            if (pattern[k] == pattern[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
}

//check whether target string contains pattern
bool KMP(string pattern, string target)
{
    int m = pattern.length();
    int n = target.length();
    int f[m];
    LPS(pattern, f);
    int i = 0;
    int k = 0;
    while (i < n)
    {
        if (k == -1)
        {
            i++;
            k = 0;
        }
        else if (target[i] == pattern[k])
        {
            i++;
            k++;
            if (k == m)
                return 1;
        }
        else
            k = f[k];
    }
    return 0;
}

int main()
{
    string base;
    string target;

    fstream fin;
    fstream fin1;
    int kfound = 0;
    string st1 = "data";
    string st2 = ".txt" ;
    string filename;
    int nlines = 0;
    clock_t k1, k2 ;
    k1=clock();


    cout<<" -------------------------------------------- " <<endl;
    cout<<"|                KMP Search                  |" <<endl;
    cout<<" -------------------------------------------- " <<endl;

    //fin1.open("Target.txt");
    fin.open("Base.txt");
    while(!fin.eof())
    {
        getline(fin, base, '.' );
        //cout << "BASE----"<<base<< endl;
        //fin1.open("Target.txt");
        for(int i=1; i<=100;i++)
        {
           // found = 0;
            //fname << name << i;
            // fin1.open(strcat(st1,(strcat((string)i,st2)))).c_str());
           //  fin1.open(strcat(strcat(st1,(strcat((string)i,st2)))),ios::in);
            stringstream ss;
            ss << i;
            filename = st1 + ss.str() + st2;
            fin1.open(filename.c_str());

           // cout<<filename<<endl;

            while(!fin1.eof())
            {
                getline( fin1, target);
                 nlines++;

                if(KMP(base, target))
                {
                    kfound++;
                    if (kfound>0)
                    {
                        cout<<"Plagiarized content found in file  " << filename <<endl;
                       // cout<<"Number of patterns found till now - " << kfound <<endl;
                    }
                }

            }
           // cout<<"Percentage of Plagiarized content in file : " << (((double)kfound ) *100 / nlines) <<"%"<<endl;
            fin1.close();


        }
  //  /* if (kfound>0)
      //  {
                //cout<<"Plagiarized content found in file  " << filename <<endl;
                //cout<<"Number of patterns found till now - " << kfound <<endl;
                 cout<<endl<<"Searching for next Pattern----"<<endl;

      //  }*/


    }
    cout<<"\nPercentage of Plagiarized content in files: " << (((double)kfound ) *100 / nlines) <<"%"<<endl;
    fin.close();
    k2 = clock();
    cout<<"Total time taken by KMP Algorithm: "<<(double)(k2-k1)/CLOCKS_PER_SEC<<" milliseconds"<<endl;


//    if (KMP(base, target))
//        cout<<"'"<<base<<"' found in string '"<<target<<"'"<<endl;
//    else
//        cout<<"'"<<base<<"' not found in string '"<<target<<"'"<<endl;
    return 0;
}
