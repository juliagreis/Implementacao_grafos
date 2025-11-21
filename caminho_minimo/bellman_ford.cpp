#include <iostream>
#include <vector>

int INF= 1000000;

struct Edge{
    int origem, destino, peso;
    Edge(int o,int d,int p){
        origem=o; destino=d; peso=p;
    }
};

bool bellman_ford(std::vector<Edge> arestas, int numVertices, int s){

    std::vector<int> custo(numVertices, INF);
    std::vector<int> pai(numVertices,-1);
    
    pai[s]=s; custo[s]=0;

    for(int i=0;i<numVertices-1;i++){ //relaxar v-1 vezes

        for(auto &e:arestas){
            int v=e.origem; int u=e.destino; int custo_v_u = e.peso;
            if(custo[u] != INF && custo[u] > custo[v] + custo_v_u){
                custo[u]=custo[v]+custo_v_u;
                pai[u]=v;
            }
        }
    }

    //aqui ja deveria ter encontrado a solucao ótima, então se nessa proxima reduzir o custo, significa que tem ciclo negativo
    for(auto &e:arestas){
        int v=e.origem; int u=e.destino; int custo_v_u = e.peso;
        if(custo[u] != INF && custo[u] > custo[v] + custo_v_u){
            return false;
        }
    }
    return true;
}