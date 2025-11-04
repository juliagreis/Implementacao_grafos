#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<int> >&adj,std::vector<int> &visitados,int v){
    visitados[v]=1;
    for(int u:adj[v]){
        if(visitados[u]==0){//se nao foi visitado
            dfs(adj,visitados,u);
        }
    }
}

int qntd_componentes(std::vector<std::vector<int> >&adj){
    int numV=adj.size();
    std::vector<int> visitados(numV,0);
    int cc=0;

    for(int i=0;i<numV;i++){
        if(visitados[i]==0){//se nao foi visitado, percorremos com dfs
            cc++;
            dfs(adj,visitados,i);
        }
    }
    return cc;

}