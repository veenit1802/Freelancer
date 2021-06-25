#include<bits/stdc++.h>
using namespace std;
const int row = 4;
const int col=3;

int main()
{   

    srand(time(0));
    int arr2D1[row][col],arr2D2[row][col];

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            arr2D1[i][j] = (rand()% (11))+10 ; 
        }
    }

    cout<<"The randomly generated array is\n";

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<arr2D1[i][j]<<" ";
        }
        cout<<"\n";
    }

    cout<<"Enter the "<<row*col<<" Integers :";

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cin>>arr2D2[i][j];
        }
    }

    int mp[1000]={0};
    int cnt=0;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(arr2D1[i][j] == arr2D2[i][j] and mp[arr2D1[i][j]]==0)
            {
                mp[ arr2D1[i][j]]++;
                cnt++;
            }
        }
    }

    int d1arr[cnt],k=0;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(mp[arr2D1[i][j]]>=1)
                {
                    d1arr[k++]=arr2D1[i][j];
                    mp[arr2D1[i][j]]--;
                }
        }
    }

 for(int i=0;i<cnt;i++)
 {
     cout<<d1arr[i]<<"\n";
 }



    return 0;
}