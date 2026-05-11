#include<iostream>
#include<omp.h>
#include<vector>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

void dfs(int node)
{
    visited[node] = true;

    #pragma omp critical
    cout<<node<<" ";

    #pragma omp parallel for
    for(int i = 0;i<graph[node].size();i++)
    {

        int adj = graph[node][i];

        if(!visited[adj])
        {
            dfs(adj);
        }

    }

}


int main()
{
    int n , e;
    cout<<"enter the number of node:";
    cin>>n;

    cout<<"enter the number of edges:";
    cin>>e;

    graph.resize(n);
    visited.resize(n,false);

    cout<<"enter the edges:";
    for(int i = 0;i<e;i++)
    {
        int u,v;
        cin>>u;
        cin>>v;

        graph[u].push_back(v);
        graph[v].push_back(u);
      
    }

    int start;
    cout<<"enter the starting node:";
    cin>>start;

    #pragma omp parallel
    {
        #pragma omp single
        {
            dfs(start);
        }
    }
}