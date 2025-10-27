#include <iostream>
#include <vector>
#include <stack>

void dfs_recursivo(std::vector<std::vector<int> >&adj,std::vector<int> &processados,int inicial){

    processados[inicial]=true;  //processo
    std::cout << "Visitando vertice: "<< inicial << std::endl;

    for(int i=0;i<adj[inicial].size();i++){
        if(!processados[adj[inicial][i]])// se nao processei esse vizinho do vertice inicial...
            dfs_recursivo(adj,processados,adj[inicial][i]); //visita seus vizinhos que ainda nao foram visitados
        //se esse vizinho já foi processado, ignoro
    }
}
void dfs_pilha(std::vector<std::vector<int> >&adj,std::vector<int> &processados,int v){
    std::stack<int> pilha;
    pilha.push(v);

    while(!pilha.empty()){
        int v=pilha.top(); pilha.pop(); //pego o vertice que ta na fila
        //esse vertice já foi processado?
        if(processados[v]) continue; //ignore esse vizinho
        //se nao foi processado ainda
        std::cout << "Visitando vertice: "<< v << std::endl; //processa
        processados[v]=true; //informa que foi processado

        //colocamos seus vizinhos na fila tambem, porem só aqueles que nao foram processados ainda
        for(int i=0;i<adj[v].size();i++){
            if(!processados[adj[v][i]]) pilha.push(adj[v][i]);
            //se ja processei, nem coloco na pilha
        }
    }
}
void dfs_recursivo_vertices_e_arestas(std::vector<std::vector<int> >&adj,std::vector<int> &processados,int v){
    processados[v]=true;
    std::cout<<"Vertice "<<v<<" processado\n";

    for(int i=0;i<adj[v].size();i++){
        if(!processados[adj[v][i]]){
            std::cout<<"Aresta "<<v<<"-"<<adj[v][i]<<std::endl;
            dfs_recursivo_vertices_e_arestas(adj,processados,adj[v][i]);
            
        }
    }
}

void dfs_pilha_vertices_e_arestas(std::vector<std::vector<int> >&adj,std::vector<int> &processados,int v){
    std::stack<int> pilha;
    pilha.push(v);
    

    while(!pilha.empty()){
        v=pilha.top(); pilha.pop();
        
        //se esse vertice ja foi processado, ignoro
        if(processados[v]) continue;
        //se ainda nao foi processado, processo ele e seus vizinhos nao processados
        processados[v]=true;
        std::cout<<"vertice "<<v<<"sendo processado\n";

        for(int i=0;i<adj[v].size();i++){
            if(!processados[adj[v][i]]){
                pilha.push(adj[v][i]);
            }
            if(v<adj[v][i])std::cout<<"Aresta "<<v<<"-"<<adj[v][i]<<std::endl;
        }
        
    }
}

void imprimir_dfs(std::vector<std::vector<int> >&adj){
    std::vector<int> processados(adj.size());
    //dfs_recursivo(adj,processados,0);
    dfs_pilha(adj,processados,0);
}
void imprimir_dfs_vertices_e_arestas(std::vector<std::vector<int> >&adj){
    std::vector<int> processados(adj.size());
    //dfs_recursivo_vertices_e_arestas(adj,processados,0);
    dfs_pilha_vertices_e_arestas(adj,processados,0);
}



int main(){

    int nv,na;
    std::cin>>nv>>na;

    //lista de adjacencia do grafo
    std::vector<std::vector<int> >adj(nv);
    for(int i=0;i<na;i++){
        int v,u;
        std::cin>>v>>u;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    //percorrer em dfs imprimindo o grafo
    imprimir_dfs(adj);
    imprimir_dfs_vertices_e_arestas(adj);




    return 0;
}