#include<bits/stdc++.h>
using namespace std;
namespace cppwr
{
    class vector{

        private:
        class DataRepresentation
        {
            private:
            int numberOfElements;
            int *a;
            public:
            DataRepresentation()
            {
                this->a=nullptr;
                this->numberOfElements=0;
            }

            void push_back(int num)
            {
                a = (int *)realloc(a,sizeof(int)*(numberOfElements+1));
                a[numberOfElements++] = num;
            }

            void pop_back()
            {
                if(a==nullptr or numberOfElements==0)
                {
                    string s="Array index out of bound";
                    throw s; 
                }
                numberOfElements--;
                a = (int *) realloc(a,sizeof(int)*(numberOfElements));
            }

            int size()
            {
                return numberOfElements;
            }

            int get(int pos)
            {
                if(numberOfElements<pos or a==nullptr)
                {
                    string error = "Array Index out of bound";
                    throw error;
                }
                else{
                    return a[pos-1];
                }
            }

            ~DataRepresentation()
            {
                delete(a);
            }
            
        };


        unique_ptr<DataRepresentation> obj;


        public:
        vector()
        {
           
        }



        int get(int pos)
        {
            int num;
            try{
               if(obj==nullptr)
               {
                   string error="Array index out of bound";
                   throw error;
               }
               num=obj.get()->get(pos);
            }
            catch(string ex)
            {
                cout<<"Memory access problem\n";
                cout<<ex<<"\n";
            }

            return num;
        }

        void push_back(int num)
        {
            if(obj==nullptr)
            {
                obj = make_unique<DataRepresentation>();
            }
            obj.get()->push_back(num);
        }

        void pop_back()
        {
           try{
               if(obj==nullptr)
               {
                   string error = "No data is present";
                   throw error;
               }
               obj.get()->pop_back();
           }
            catch(string err)
               {
                   cout<<err;
               }
        }

        int size()
        {
            try
            {
                string error = "Pointer not pointing to any data";
                if(obj==nullptr)
                {
                    throw error;
                }
                return obj.get()->size();
            }
            catch(string err)
            {
                cout<<err<<"\n";
            }
            return 0;
        }
    };
}

int main()
{
    cout<<sizeof(int *)<<" "<<sizeof(cppwr::vector)<<" "<<sizeof(vector<int>)<<"\n";
    cout<<sizeof(vector<cppwr::vector>)<<" "<<sizeof(vector<vector<int>>)<<"\n";

    //testcase

    cppwr::vector a;
    a.push_back(1);
    a.push_back(20);
    a.push_back(30);
    a.push_back(40);
    int size = a.size();
    for(int i=0;i<size;i++)
    {
        cout<<a.get(i)<<" ";
    }
}