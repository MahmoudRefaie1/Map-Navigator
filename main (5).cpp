//
//  main.cpp
//  Project
//
//  Created by Noor Abdelaziz on 03/12/2023.
//

#include <iostream>
using namespace std;
#include <stdio.h>
#include <map>
#include <math.h>
#include <fstream>
#include <stdlib.h>

bool found(map<string,int> city,string cityname,int index)
{
    if(city.contains(cityname))
        return true;
    else{
        return false;
    }
}

void insertSize(map<string,int> &city,string cityname1,int &index,int &size)
{
    if(found(city,cityname1,index)){
    }
    else{
        size++;
        city[cityname1]=index;
        index++;
    }
}

void insert(map<string,int> &city,string cityname1,int &index,int &size)
{
    if(found(city,cityname1,index)){
    }
    else{
        city[cityname1]=index;
        index++;
    }
}

int retrieveIndex(map<string,int>&city,string cityname)
{
    int j=city[cityname];
    return (j);
}




void insertEdgeWeight(int ** adjMatrix,string city1,string city2,int weight,map <string,int> &city)
{
    int i=retrieveIndex(city,city1);
    int j=retrieveIndex(city,city2);
    /*cout<<"City 1 is " << city1 << "and its index is " << city[city1]<<endl;
    cout<<"City 2 is " << city2 << "and its index is " << city[city2]<<endl;
    cout<<"The weight between them is  " << weight<<endl;*/
    adjMatrix[i][j]=weight;
    
    return;
}




void adjustArray(int **adjMatrix,int size)
{
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++)
        {
            if(i==j)
                adjMatrix[i][j]=0;
            else
                adjMatrix[i][j]=99999999;
        }
    }
    //just compute djikstra's algorithm and we are done.
}
void printGraph(int **adjMatrix,int size)
{
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            cout<< "The value of i is " << i <<" and the value of j is " << j << "and the weight between them is "<<adjMatrix[i][j]<<endl;
}

void dijkstra(int **adjMatrix, int src,int dst, int V,long int dist[],map <string,int> city)
{
    for(int i=0;i<V;i++)
    {
        dist[i]=99999999;
    }
    bool sptSet[V];//visited nodes
    int checked_index=0;
    int min_index=0;
    for(int i=0;i<V;i++)
    {
        sptSet[i]=false;
    }
    dist[src]=0;
    
    int i=src;
    
    sptSet[src]=true;
    
    while(i!=dst){
        long int min_Value=99999999; //check
        for(int j=0;j<V;j++)
        {
            if (sptSet[j]==true)
                continue;
            if( j==dst && adjMatrix[i][dst]!=99999999){
                checked_index=i;
                sptSet[checked_index]=true;
                dist[j]=dist[i]+adjMatrix[i][dst];
                cout<<"The value of the source is " << i << "and the value of the destination is " << j<<endl;
                cout<<"REACHED ! ";
                i=dst;
                min_index=j;    
                break;
            }
                
            if( adjMatrix[i][j]!=0 && adjMatrix[i][j]!=99999999 ){
                cout<<"The value of i is " << i << " and the value of j is " << j << "and the distance between them is " <<adjMatrix[i][j]<<endl;
                if( dist[i]+adjMatrix[i][j] < dist[j] ){
                    dist[j]=dist[i]+adjMatrix[i][j];
                }
                if(adjMatrix[i][j]< min_Value){
                    min_Value=adjMatrix[i][j];
                    min_index=j;
                    cout<<"The min_index is "<< min_index<<endl;
                    checked_index=i;
                }
            }
        }
        
        i=min_index;
        sptSet[checked_index]=true;
    }
}




void displayArray(int **adjMatrix,int size)\
{
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++)
            cout<<adjMatrix[i][j]<<" ";
        cout<<endl;
            }
}


int GetSize(int size, string fileName)
{
    string node1;
    string node2;
    int weight;
    int index=0;
    string line;
    map<string,int> citySize;
    ifstream infilee(fileName);
    string weightSize;
    string nodeSize1;
    string nodeSize2;
    while(infilee >> nodeSize1 >> nodeSize2>> weightSize) {
        insertSize(citySize,nodeSize1,index,size);
        insertSize(citySize,nodeSize2,index,size);
    }
    
    infilee.close();
    return size;
}

void displayNodeWeights(int arr[],int size)
{
    for(int i=0;i<size;i++)
        cout<<"The node with index " << i << "has a weight of " << arr[i]<<endl;
}
int main(int argc, const char * argv[]) {
    map<string,int> city;
    string s="/Users/noorabdelaziz/Downloads/CitiesData.txt";
    string node1;
    string node2;
    int weight;
    int index=0;
    int size=0;
    size=GetSize(0,s);
    index=0;
    ifstream infile;
    infile.open(s);
    int ** adjMatrix= new int *[size];
    for(int i=0;i<size;i++)
    {
        adjMatrix[i]=new int [size];
    }
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"The size is " <<size<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    adjustArray(adjMatrix,size);
    string weight1;
    while(infile >> node1 >> node2>> weight1) {
        insert(city,node1,index,size);
        insert(city,node2,index,size);
        weight=stoi(weight1);
        insertEdgeWeight(adjMatrix,node1,node2,weight,city);
    }
    infile.close();
    long int arr[size];

    int dist;
    int src;
    int city1;
    int city2;
    cout<<"Type the location where you want to start. " <<endl;
    cin>>city1;
    cout<<"Type the location where you want to End. " <<endl;
    cin>>city2;
    
    dijkstra(adjMatrix,city1,city2,size,arr,city);
    return 0;
}

