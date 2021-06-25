#include<bits/stdc++.h>
using namespace std;

enum OperationType{upper='U',lower='L'};

int main()
{
    cout<<"Enter a string: ";
    // cin.ignore();
    string s;
    getline(cin,s);
    char ch;
    bool rightChoice = false;
    bool firstTime=false;
    while(1)
    {
        if(!firstTime)
        {
            firstTime=true;
        }
        else{
            cout<<"\n";
        }
        cout<<"What do you want to convert to, U for Upper, L for Lower: ";
        cin>>ch;
        switch (ch)
        {
        case upper:{ int length=s.length();
                    rightChoice=true;
                    for(int i=0;i<length;i++)
                    {
                        if(islower(s[i]))
                        {
                            s[i]=toupper(s[i]);
                        }
                        
                    }
                    break;}
        case lower: {
                        rightChoice=true;
                        int length = s.length();
                        for(int i=0;i<length;i++)
                        {
                            if(isupper(s[i]))
                            {
                                s[i]=tolower(s[i]);
                            }
                        }
                        break;
                    }
        default:
                cout<<"Wrong choice: Enter again.";
                break;
        }
        if(rightChoice)
        {
            cout<<"Updated string: "<<s<<"\n";
            break;
        }
    }
}