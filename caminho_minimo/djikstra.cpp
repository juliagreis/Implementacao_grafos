#include <iostream>
#include <vector>
#include <queue>

int INF = 1000000;

int vertice_menor_custo(std::vector<int> &custo, std::vector<bool> fechado){
    int menorCusto=INF;
    int indiceMenorCusto=-1;
    for(int i=0;i<custo.size();i++){
        if(custo[i] < menorCusto && !fechado[i]){
            menorCusto=custo[i];
            indiceMenorCusto=i;
        }
    }
    return indiceMenorCusto;

}

//implementacao de complexidade v ao quadrado, porque para todo vertice percorremos todos os seus vizinhos

void dijkstra_v_ao_2(std::vector<std::vector<std::pair<int,int> > > adj, int s){
    int numVertices = adj.size();
    //primeiro iniciailizamos as variaveis

    std::vector<int> custo(numVertices,INF);
    std::vector<int> pai(numVertices,-1);
    std::vector<bool> fechado(numVertices,false);

    pai[s]=s; custo[s]=0; //custo da origem ate ele mesmo é 0, e não tem pai, entao colocamos ele mesmo

    while(true){

        //procuramos vertice aberto com menor custo
        int v = vertice_menor_custo(custo,fechado); //Complexidade O(numVertices)
        if(v==-1) break; //nao tem mais nenhum vertice aberto
        fechado[v]=true; //vou percorrer todos os vizinhos dele agora, entao ja posso fecha-lo

        //percorrendo os vizinhos de v
        for(auto [u,peso]:adj[v]){
            if(!fechado[u] && custo[v]+peso < custo[u]){
                custo[u]=custo[v]+peso;
                pai[u]=v;
            }
        }
    }

    //-----------------saida:----------------------------//
    std::cout << "\nResultado do Dijkstra a partir de " << s << ":\n";
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Vertice " << i 
             << " | custo = " << custo[i] 
             << " | pai = " << pai[i] << "\n";
    }

}



//-----------------------------------------------------------------------------------------------------------//

void dijkstra_log(std::vector<std::vector <std::pair<int,int> > >&adj, int s){
    int numVertices=adj.size();
    std::vector<int> custo(numVertices,INF);
    std::vector<int> pai(numVertices,-1);

    heap<int,int> h; //<vertice, custo>
    h.push(s,0);

    while(!h.empty()){ //enquanto tiver elementos na fila de prioridade

        int v= h.top(); h.pop();

        //percorro os vizinhos de v
        for(auto [u,peso]:adj[v]){

            if(custo[u]==INF){ // u nunca foi inserido no heap
                custo[u]=custo[v]+peso;
                pai[u]=v;
                heap.push(u,custo[u]);
            }
            else if(custo[u]>custo[v]+peso){ //ja foi inserido, mas o custo usando essa aresta é menor
                custo[u]=custo[v]+peso;
                pai[u]=v;
                h.atualiza(u,custo[u]); //atualiza no heap
            }
        }
    }
}






//--------------main de teste ------------------//

int main(){

    int n, m;
    std::cout << "Numero de vertices: ";
    std::cin >> n;

    std::cout << "Numero de arestas: ";
    std::cin >> m;

    // lista de adjacencia
    std::vector<std::vector<std::pair<int,int> > > adj(n);

    std::cout << "Digite as arestas (u v peso):\n";
    for(int i = 0; i < m; i++){
        int u, v, w;
        std::cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});  // remova se quiser grafo direcionado
    }

    int origem;
    std::cout << "Vertice origem: ";
    std::cin >> origem;

    dijkstra_v_ao_2(adj, origem);

    return 0;
}