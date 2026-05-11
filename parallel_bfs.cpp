#include<iostream>
#include<omp.h>
#include<vector>
#include<queue>
using namespace std;

int main()
{
    int n , e;
    cout<<"enter the number of node:";
    cin>>n;

    cout<<"enter the number of edges:";
    cin>>e;

    vector<vector<int>> graph(n);

    cout<<"enter the edges:";
    for(int i = 0;i<e;i++)
    {
        int u,v;
        cin>>u;
        cin>>v;

        graph[u].push_back(v);
        graph[v].push_back(u);
      
    }

    vector<bool>visited(n,false);
    queue <int> q;

    int start;
    cout<<"enter the starting node:";
    cin>>start;

    visited[start] = true;
    q.push(start);

    cout<<"bfs traversal:";
    while(!q.empty())
    {
        int size = q.size();

       #pragma omp parallel for
       for(int i = 0;i<size;i++)
       {
        int node;
        #pragma omp critical
        {
            node = q.front();
            q.pop();
            cout<<node<<" ";

        }

        for(int nei :graph[node])
        {
            if(!visited[nei])
            {
                #pragma omp critical
                {
                    if(!visited[nei])
                    {
                        visited[nei] = true;
                        q.push(nei);

                    }
                }
            }
        }


       }
    }

    return 0;
}