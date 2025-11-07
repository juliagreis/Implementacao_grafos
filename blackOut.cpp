#include <iostream>
#include <vector>

struct edge{
    int peso;
    int v,u;
    edge(int v=-1,int u=-1,int peso=-1):v(v),u(u),peso(peso){}
};

bool operator <(const edge &a, const edge &b){
    return a.peso<b.peso;
}

class unionFind{
    public:
        std::vector<int> representante;

        void criarComponentes(int tam){
            for(int i=0;i<tam;i++){
                representante[i]=i;
            }        
        }

        bool isSameSet(int u,int v){
            return find(v)==find(v);
        }
        int find(int v){
            if(representante[v]==v) return v;
            representante[v]=find(representante[v]);
            return representante[v];
        }

        void unirComponentes(int v,int u){
            representante[find(v)]=find(u);
        }

};

int kruskal(std::vector<edge> &arestasExistentes, std::vector<bool> &arestasUtilizadas,int numVertices){
    arestasUtilizadas = std::vector<bool>(numVertices,false);
    sort(arestasExistentes.begin(),arestasExistentes.end());

    unionFind componentes;

    int contArestas=0;
    //agora precisamos percorrer em ordem
    for(int i=0;i<arestasExistentes.size();i++){
        if(contArestas==numVertices-1) return contArestas; //ja é uma arvore
        if(!componentes.isSameSet(arestasExistentes[i].v,arestasExistentes[i].u)){

            //nao forma ciclo, entao adicionamos
            contArestas++;
            arestasUtilizadas[i]=true;
            componentes.unirComponentes(arestasExistentes[i].v,arestasExistentes[i].u);
        }
    }
    return contArestas;

}

int main(){

    std::vector<edge> arestas;
    int numVertices, numArestasPossiveis;
    std::cin>>numVertices>>numArestasPossiveis;

    for(int i=0;i<numArestasPossiveis;i++){
        int p,a,b;
        std::cin>>p>>a>>b;

        //criamos uma aresta possivel que liga a e b de peso p
        arestas.push_back(edge(a,b,p));
    }
    std::vector<bool> utilizadas;
    kruskal(arestas,utilizadas,numVertices);

    
}
