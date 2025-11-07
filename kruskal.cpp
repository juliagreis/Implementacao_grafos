#include <iostream>
#include <vector>

class unionFind{
    public:

    std::vector<int> representante;
    unionFind(){}

    void criarComponente(int tam){
        representante.resize(tam);
        for(int i=0;i<tam;i++){
            representante[i]=i;
        }
    }
    int find(int u){
        
        if(representante[u]==u) return u; //se ele é o representante dele mesmo

        representante[u]=find(representante[u]);
        return representante[u];
    }

    bool mesmoComponente(int v,int u){
        return find(v)==find(u);
    }

    void unirComponente(int v,int u){
        if(find(v)==find(u)) //se sao de componentes iguais nao precisamos unir
            return;
        
        //o representante de um vai apontar para o representante do outro, logo todos tem um mesmo representante agora
        representante[find(v)]=find(u);
        return;
    }
};

struct edge{
    int peso;
    int v,u;
    edge(int v=-1,int u=-1,int peso=-1) :v(v),u(u),peso(peso){}
};

bool operator <(const edge &a, const edge &b){
    return a.peso<b.peso;
}

int krukal(std::vector<int> arestas_utilizadas, int numVertices,std::vector<edge> arestas_existentes){
    //primeiro pegamos as nossas arestas utilizadas (por agora 0)
    arestas_utilizadas=std::vector<int> (arestas_existentes.size(),0); //todas as arestas estao inicializadas como nao utilizadas
    //agora ordenamos as arestas existentes de acordo com o peso de cada uma
    sort(arestas_existentes.begin(),arestas_existentes.end()); //agora ordenamos em ordem crescente

    //criamos os componenentes, ou seja, cada vertice esta em um componente diferente inicialmente
    unionFind componentes;
    componentes.criarComponente(numVertices); //cada vertice é representante do seu proprio componente

    //agora vamos olhar aresta por aresta, vendo se podemos adiciona-la sem criar ciclo
    //e paramos quando ela ja for uma arvore de numVertices

    int contArestas=0;

    for(int i=0;i<arestas_existentes.size();i++){
        if(numVertices-1 == contArestas) return contArestas;

        //se ainda nao temos uma arvore geradora minima
        //aresta i se adicionada forma ciclo?
        if(!componentes.mesmoComponente(arestas_existentes[i].v,arestas_existentes[i].u)){
            //se eles sao de componentes diferentes...
            arestas_utilizadas[i]=1; //usamos essa aresta
            componentes.unirComponente(arestas_existentes[i].v,arestas_existentes[i].u);
            contArestas++;
        }
    }
    return contArestas;
}