#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<int> >adj, std::vector<int> visitados, int v){
    visitados[v]=1;
    for(int u:adj[v]){
        if(visitados[u]==0){
            dfs(adj,visitados,u);
        }
    }
}

int main(){
    int n,m;
    std::cin>>n>>m;

    for(int i=0;i<n;i++){
        //n casos de teste
        std::vector<std::vector<int>> adj_mensagens(m);
        std::vector<std::vector<int>> adj_transporte(m);

        for(int j=0;j<m;j++){
            int a,b;
            std::cin>>a>>b;

            //agora a->b e b->a para mensagens
            adj_mensagens[a].push_back(b);
            adj_mensagens[b].push_back(a);
            
            //agora a->b para transporte
            adj_transporte[a].push_back(b);

            //para mensagens basta ver se a e b estao no mesmo componente conexo
            std::vector<int> visitados_mensagens(m);
            dfs(adj_mensagens,visitados_mensagens,a);

            bool mensagens;
            for(int v :visitados_mensagens){
                if(v==0) mensagens=false;
            }

            //para transporte
            std::vector<int> visitados_transporte(m);
            dfs(adj_mensagens,visitados_transporte,a);

            bool transporte;
            for(int v :visitados_transporte){
                if(v==0) transporte=false;
            }

            if(transporte && mensagens) std::cout<<"S\n";
            else std::cout<<"N\n";
        }
    }
}