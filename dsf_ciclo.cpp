#include <iostream>
#include <vector>

bool dfs_ciclo(std::vector<std::vector<int> >&adj,             std::vector<int>&pai,    std::vector<bool> &processados,          int v){
    processados[v]=true;
    for(int u:adj[v]){
        if(!processados[u]){
            pai[u]=v; //atualizamos quem é o pai do vertice que estamos analisando
            bool ciclo=dfs_ciclo(adj,pai,processados,u); //se ainda nao foi processado 
            if(ciclo) return true;

        }else{ //entretanto, se ele ja foi processado
            if(pai[v]==u){ //ou seja, se estou voltando pelo caminho que eu vim: 
                //pai[v]---> v----> u 
                // ^----------------|
                //isso configura um ciclo
                return true;
            }
        }
    }
    return false;
}

bool tem_ciclo(std::vector<std::vector<int> >&adj){

    int n=adj.size(); //n = numero de vertices
    std::vector<int> pai(n,-1);
    std::vector<bool> processados(n,-1);

    //pra todo vertice que nao foi visitado, fazemos uma dfs que percorre ele
    for(int i;i<n;i++){
        if(!processados[i]){ //se nao foi processado
            bool ciclo=dfs_ciclo(adj,pai,processados,i);
            if(ciclo) // se tem ciclo, ja posso retornar que tem ciclo
            // mas se nao tem ciclo, ainda tenho que checar em relacao aos outros vertices
            return true;
        }
    }
    //se terminou e nao teve ciclo em nenhum lugar, entao nao tem ciclo
    return false;

}





int main(){

    return 0;
}