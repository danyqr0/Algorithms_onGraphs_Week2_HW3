//============================================================================
// Name        : Algorithms_onGraphs_Week2_HW3.cpp
// Author      : Daniel Ramirez
// Version     :
// Copyright   : HW3_Week2
// Description : Advanced problem: Checking Whether Any Intersection in a
//               City is Reachable from Any Other in C++, Ansi-style
//============================================================================
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
using std::vector;

class Graph{
 private:
   int V;
   int E;
   vector<vector<int> > adj;
   vector<vector<int> > adjR;
   int scc_total;
   bool flag_scc;
 public:
   Graph(int v, int e);
   void addVertex(int x, int y);
   int SCC();
   void DFSExplore(vector<int> &v_visited,int i, stack<int> &dfs_s);
   void DFSExploreGr(vector<int> &v_visited, int s_top);
};

Graph::Graph(int v, int e){
   this->V=v;
   this->E=e;
   adj.resize(this->V,vector<int>());
   adjR.resize(this->V,vector<int>());
   scc_total=0;
   flag_scc=false;
}

void Graph::addVertex(int x, int y){
	adj[x-1].push_back(y-1);
	adjR[y-1].push_back(x-1);
}

int Graph::SCC(){
	vector<int> v_visited(this->V,-1);
	vector<int> v_processing(this->V,-1);
    stack<int> dfs_s;
    int s_top;

    for(int i=0;i<this->V;i++){
    	if(v_visited[i]!=i){
    		 DFSExplore(v_visited,i,dfs_s);
    	}
    }

    std::fill (v_visited.begin(), v_visited.end(),-1);
    while(!dfs_s.empty()){
    	s_top=dfs_s.top();dfs_s.pop();
    	if(v_visited[s_top]!=s_top){
    		scc_total++;
    		DFSExploreGr(v_visited,s_top);
    	}
    }
    return scc_total;
}

void Graph::DFSExploreGr(vector<int> &v_visited,int s_top){
	vector<int>::iterator it;
	v_visited[s_top]=s_top;
	for(it=adjR[s_top].begin();it!=adjR[s_top].end();it++){
		if(v_visited[*it] !=*it)
			DFSExploreGr(v_visited,*it);
	}
}

void Graph::DFSExplore(vector<int> &v_visited,int i, stack<int> &dfs_s){
	vector<int>::iterator it;
	v_visited[i]=i;
	for(it=adj[i].begin();it!=adj[i].end();it++){
		if(v_visited[*it] !=*it)
			DFSExplore(v_visited,*it,dfs_s);
	}
	dfs_s.push(i);
}

int main() {
   int n,m,x,y;
   cin>>n>>m;
   if( (n>=1 && n<=1e4) && (m>=0 && m<=1e4) ){
      Graph *g=new Graph(n,m);
      for(int i=0;i<m;i++){
	     cin>>x>>y;
         g->addVertex(x,y);
      }
      cout<<g->SCC();
   }
   else
	   cout<<0;
   return 0;
}
