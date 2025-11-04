#include <iostream>
#include <vector>

bool dfs_bipartido(std::vector<std::vector<int> >&adj,std::vector<int> &cor,int v){
    //aqui a ideia é usar o proprio vetor cor como visitados tambem
    //0-> nao foi visitado. cor a=-1, cor b=1

    for(int u:adj[v]){
        if(cor[u]==0){
            //se nao foi visitado ainda
            cor[u]=-cor[v];
            if(!dfs_bipartido(adj,cor,u)) return false;
        }
        else{
            //ja foi pintado
            //mas contradiz v?
            if(cor[u]==cor[v]) return false;
        }
    }
    return true;
}


int main(){

    

    return 0;
}