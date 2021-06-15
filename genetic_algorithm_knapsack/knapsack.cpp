#include<bits/stdc++.h>
using namespace std;
#define maxWeight 30
#define maxStringlength 10
#define startingPopulationLength 20
#define startPop 1000
#define totGeneration 30
#define totalPair 7
#define totalScore 98


vector<pair<int,int>>survivalItems;


struct GenerationTopResult
{
    string s;
    int weight;
    int value;
    float fitness_value;
    float average_fitness_value;
};

bool cmp(const pair<string,pair<int,int>>&a,const pair<string,pair<int,int>>&b)
{
    return a.second.second > b.second.second;
}



vector<string> select(vector<pair<string,pair<int,int>>>&totPopulation)
{
    vector<string>selectedParents;
    int totalPopulationWeightTillNow=0;
    vector<int>totalPopulationWeight(int(totPopulation.size()),0);
    for(int i=0;i<int(totPopulation.size());i++)
    {
        totalPopulationWeightTillNow+=totPopulation[i].second.first;
        if(i==0)
        {
            totalPopulationWeight[i]=totPopulation[i].second.first;
        }
        else{
            totalPopulationWeight[i]=totPopulation[i].second.first + totalPopulationWeight[i-1];
        }
    }

    vector<string>newPopulationParent;
    for(int i=1;i<=totalPair;i++)
    {
        int randNum1=0,randNum2=0;
        randNum1 = rand()%totalPopulationWeightTillNow;
        int positionNum1 = upper_bound(totalPopulationWeight.begin(),totalPopulationWeight.end(),randNum1) - totalPopulationWeight.begin();
        positionNum1-=1;
        randNum2 = rand()%totalPopulationWeightTillNow;
        int positionNum2 = upper_bound(totalPopulationWeight.begin(),totalPopulationWeight.end(),randNum2) - totalPopulationWeight.begin();
        positionNum2-=1;
        if(positionNum1<0)
        {
            positionNum1=0;
        }
        if(positionNum2<0)
        {
            positionNum2=0;
        }
        newPopulationParent.push_back(totPopulation[positionNum1].first);
        newPopulationParent.push_back(totPopulation[positionNum2].first);
        
    }

    return newPopulationParent;
}




vector<string> crossover(vector<string>parent)
{
    vector<string>offSpring;
    for(int i=0;i<int(parent.size());i+=2)
    {
        string s;
        for(int j=0;j<10;j++)
        {
            float randNum = (float(rand())/float(RAND_MAX))*100.0;
            if(randNum<=30)
            {
                s+='0';
            }
            else{
                s+=(( parent[i][j]=='1' or parent[i+1][j]=='1' )?'1':'0');
            }
        }

        offSpring.push_back(s);
    }
    return offSpring;
}


void mutation(vector<string>&parentOffSpring)
{
    for(int i=0;i< int(parentOffSpring.size());i++)
    {
        for(int j=0;j<10;j++)
        {
            float num = (float(rand())/ float(RAND_MAX) )*100.0;
            if(num<=1.0)
            {
                parentOffSpring[i][j] =  (parentOffSpring[i][j]=='1'?'0':'1'); 
            }
        }
    }
}





bool fitnessCheck(string chromosome,int *weight,int *value)
{
    for(int i=0;i<maxStringlength;i++)
    {
        if(chromosome[i]=='1')
        {
            (*weight)+=survivalItems[i].first;
            (*value)+=survivalItems[i].second;
        }
    }

    if(*weight>maxWeight)
    {
        return false;
    }

    return true;
}





vector<pair<string,pair<int,int>>> populationEvalution(vector<string>&population)
{
    vector<pair<string,pair<int,int>>>validPopulation;
  
    for(int i=0;i<int(population.size());i++)
    {
        int weight=0;
        int value=0;
        bool isValidChromosome=fitnessCheck(population[i],&weight,&value);
        
        if(isValidChromosome and  weight!=0)
        {
            validPopulation.push_back({population[i],{weight,value}});
        }
        if(validPopulation.size()==20)
        {
            break;
        }
  
    }

    return validPopulation;
}




string createGene()
{
    
    string chromo;
    for(int i=0;i<maxStringlength;i++)
    {
        float randNum = (float(rand()))/(float(RAND_MAX));
        if(randNum>0.5)
        {
            chromo+='1';
        }
        else{
            chromo+='0';
        }
    }
    
    return chromo;
}





vector<string> createPopulation()
{
    vector<string>startingPopulation;
    for(int i=1;i<=startPop;i++)
    {
        string chromosome = createGene();
        // cout<<chromosome<<"\n";
        startingPopulation.push_back(chromosome);
    }
    return startingPopulation;
}

GenerationTopResult createObject(string s,int weight,int value,float totweight,float totvalue)
{
    GenerationTopResult object;
    object.s=s;
    object.weight=weight;
    object.value=value;
    object.fitness_value = float(value)/float(weight);
    object.average_fitness_value = totvalue/totweight;
    return object;
}

void print(string s,int weight,int value,float fitnessValue,float averageFitnessValue)
{
    cout<<"Top solution based on Highest Survival Score:  ";

    for(int i=0;i<maxStringlength;i++)
    {
        if(i<9)
        cout<<s[i]<<", ";
        else{
            cout<<s[i]<<" ";
        }
    }
    cout<<"   ";
    cout<<"fitness score: "<<fitnessValue<<"    ";
    cout<<"Weight: "<<weight<<"    ";
    cout<<fixed<<setprecision(3)<<"Survival Points: "<<value<<"   ";
    cout<<fixed<<setprecision(3)<<"Average Fitness Value: "<<averageFitnessValue<<"\n";
}



int main()
{
    srand(time(nullptr));
    int weights[]={15,3,2,5,9,20,1,1,1,1};
    int values[]={15,7,10,5,8,17,13,10,12,9};
    for(int i=0;i<10;i++)
    {
        survivalItems.push_back({weights[i],values[i]});
    }

    vector<string>population  = createPopulation();
    vector<pair<string,pair<int,int>>>  newPopulation = populationEvalution(population);

    vector<GenerationTopResult>generationTopResult;
    for(int i=1;i<=totGeneration;i++)
    {
        vector<string> newPopulationParent = select(newPopulation);
        vector<string> parentOffSpring = crossover(newPopulationParent);
        mutation(parentOffSpring);
        vector<pair<string,pair<int,int>>>newOffSpringPopulation = populationEvalution(parentOffSpring);

        for(int i=0;i<int(newOffSpringPopulation.size());i++)
        {
            newPopulation.push_back(newOffSpringPopulation[i]);
        }
        
        sort(newOffSpringPopulation.begin(),newOffSpringPopulation.end(),cmp);
        float totweightsum=0,totvaluesum=0;
        for(int i=0;i<7;i++)
        {
            totweightsum+=newOffSpringPopulation[i].second.first;
            totvaluesum+=newOffSpringPopulation[i].second.second;
        }
        generationTopResult.push_back( createObject( newOffSpringPopulation[0].first,newOffSpringPopulation[0].second.first,newOffSpringPopulation[0].second.second,totweightsum/7,totvaluesum/7 ));
        if(i==30)
        {
            generationTopResult.push_back( createObject( newOffSpringPopulation[1].first,newOffSpringPopulation[1].second.first,newOffSpringPopulation[1].second.second,totweightsum/7,totvaluesum/7 ));
            generationTopResult.push_back( createObject( newOffSpringPopulation[2].first,newOffSpringPopulation[2].second.first,newOffSpringPopulation[2].second.second,totweightsum/7,totvaluesum/7 ));
            generationTopResult.push_back( createObject( newOffSpringPopulation[3].first,newOffSpringPopulation[3].second.first,newOffSpringPopulation[3].second.second,totweightsum/7,totvaluesum/7 ));
        }

        sort(newPopulation.begin(),newPopulation.end(),cmp);
        while(newPopulation.size()>20)
        {
            newPopulation.pop_back();
        }
    }

    cout<<"Startinng Genepool:\n\n";
        float totweightsum=0,totvaluesum=0;
        for(int i=0;i<int(newPopulation.size());i++)
        {
            totweightsum+=newPopulation[i].second.first;
            totvaluesum+=newPopulation[i].second.second;
        }
        totweightsum/=20;
        totvaluesum/=20;
        totvaluesum/=totweightsum;
        print(newPopulation[0].first,newPopulation[0].second.first,newPopulation[0].second.second,float(newPopulation[0].second.second)/newPopulation[0].second.first,totvaluesum);

        cout<<"\n\nOrdered:\n\n";

        for(int i=0;i<generationTopResult.size();i++)
        {
            print(generationTopResult[i].s,generationTopResult[i].weight,generationTopResult[i].value,generationTopResult[i].fitness_value,generationTopResult[i].average_fitness_value);
        }

    return 0;
}