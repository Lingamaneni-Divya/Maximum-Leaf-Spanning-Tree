#include<bits/stdc++.h>
using namespace std;

//max leafy forest
int parent[100005]={0};
int d[100005]={0};
int size[100005]={0};

int findparent(int v)
{
    if(v==parent[v])
        return v;
    return parent[v]= findparent(parent[v]);
}
void unionbyrank(int u,int v)
{
    int a=findparent(u);
    int b=findparent(v);
    if(a!=b)
    {
        if(size[a]>size[b])
        {
            parent[b]=a;
            size[a]=size[a]+size[b];
        }
        else
        {
            parent[a]=b;
            size[b]=size[a]+size[b];
        }
    }
}

set<pair<int,int>> buildMaximallyLeafyForest(int noofvertices,vector<int> G[])
{
    set<pair<int,int>> F;
    int i,j;
    for(i =0;i<noofvertices;i++)
    {
        d[i]=0;
        parent[i]=i;
        size[i]=1;
    }
    for(i=0;i<noofvertices;i++)
    {
        set<pair<int,int> > s1;
        int d1=0;
        
        int v=i;
        for(j=0;j<G[i].size();j++)
        {
            int u=G[i][j];
            if(findparent(u)!=findparent(v) and  s1.find( make_pair(u,findparent(u)) )==s1.end())
            {
                d1=d1+1;
                s1.insert(make_pair(u,findparent(u)) );
            }
            
        }
	if(d[v]+d1>=3)
            {
                for(auto it=s1.begin();it!=s1.end();it++)
                {
                    pair<int,int> u=*it;
                    F.insert(make_pair(v,u.first));    
                    F.insert(make_pair(u.first,v));
                    unionbyrank(v,u.second);
                    d[u.first]=d[u.first]+1;
                    d[v]=d[v]+1;
                }
            }
    }
    return F;
}















//kruskal

int parent1[100005]={0};
int size1[100005]={0};
int findparent1(int x)
{
    if(parent1[x]==x)
        return x;
    return parent1[x]=findparent1(parent1[x]);

}
void unionbyrank1(int u,int v)
{
    int a=findparent1(u);
    int b=findparent1(v);
    if(a!=b)
    {
        if(size1[a]>size1[b])
        {
            parent1[b]=a;
            size1[a]=size1[a]+size1[b];
        }
        else
        {
            parent1[a]=b;
            size1[b]=size1[a]+size1[b];
        }
    }
}
set<pair<int,int>> kruskal(int noofvertices,set<pair<int,int>> F)
{    
    int i;
    set<pair<int,int>> spanningtree;
    for(i=0;i<noofvertices;i++)
        parent1[i]=i;
    for(auto it=F.begin();it!=F.end();it++)
    {
        pair<int,int> p=*it;
        int x=p.first;
        int y=p.second;
        if(findparent1(x)!=findparent1(y))
        {
            spanningtree.insert(make_pair(x,y));
            unionbyrank1(x,y);
        }
        
    }
    return spanningtree;    
}









int main()
{
    cout<<"enter no of vertices"<<endl;
    int noofvertices;
    cin>>noofvertices;
    int noofedges;
    cin>>noofedges;
    vector<pair<int,int>> inputedges;
    int i,j;
    for(i=0;i<noofedges;i++)
    {
        int x,y;
        cin>>x>>y;
        inputedges.push_back(make_pair(x,y));
    }
    vector<int> G[100005];
    for(i=0;i<noofedges;i++)
    {
        pair<int,int> x=inputedges[i];
        int u=x.first;
        int v=x.second;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    set<pair<int,int> > F;
   /*for(i=0;i<noofvertices;i++)
    {
        for(j=0;j<G[i].size();j++)
        {
		F.insert(make_pair(i,G[i][j]));
		F.insert(make_pair(G[i][j],i));
	}
    }*/
   F=buildMaximallyLeafyForest(noofvertices,G);
   set<int> verticesinF;
    for(auto it=F.begin();it!=F.end();it++)
    {
        pair<int,int> x=*it;
        verticesinF.insert(x.first);

        verticesinF.insert(x.second);
    }
  for(i=0;i<noofvertices;i++)
    {
        for(j=0;j<G[i].size();j++)
        {
            int u=i;
            int v=G[i][j];

       
           if(verticesinF.find(u)==verticesinF.end() and verticesinF.find(v)==verticesinF.end())
            {
                F.insert(make_pair(u,v));
                F.insert(make_pair(v,u));

            }
            
else if(findparent(u)!=findparent(v))
            {

                F.insert(make_pair(u,v));
                F.insert(make_pair(v,u));

            }
        }
    }
/*cout<< "result"<<endl;
for(auto it=F.begin();it!=F.end();it++)
                {
                    cout << (*it).first << " "<<(*it).second <<endl;
                }*/
set<pair<int,int>> result = kruskal(noofvertices,F);
    cout<< "result"<<endl;
    for(auto it=result.begin();it!=result.end();it++)
                {
                    cout << (*it).first << " "<<(*it).second <<endl;
                }

    
    return 0;
}
