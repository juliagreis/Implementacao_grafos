#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

//implementacao via matriz de incidencia, ou seja, vertices x vertices

class Grafo_denso
{ //implementacao usando matriz de adjacencia

private:
    int num_vertices;
    int num_arestas;
    std::vector<std::vector<int>> matriz;
    void imprimir_matriz()
    {

        std::cout << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < num_vertices; i++)
        {
            for (int j = 0; j < num_vertices; j++)
                std::cout << matriz[i][j] << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

public:
    //construtor e destrutor -> irrelevantes

    Grafo_denso(int qntd_vertices)
    {
        num_vertices = qntd_vertices;
        num_arestas = 0;

        matriz.resize(num_vertices);
        for (int i = 0; i < num_vertices; i++)
        {
            matriz[i].resize(num_vertices);
            for (int j = 0; j < num_vertices; j++)
            {
                matriz[i][j] = 0;
            }
        }
        imprimir_matriz();
    }
    ~Grafo_denso()
    {
        num_vertices = num_arestas = 0;
        for (int i = 0; i < num_vertices; i++)
        {
            matriz[i].clear();
        }
    }
    void inserir_aresta(int posv1, int posv2)
    {
        //++ permite que tenha arestas multiplas
        matriz[posv1][posv2]++;
        matriz[posv2][posv1]++;

        num_arestas++;

        /*
            poderia ser um vector<vector<bool>>, onde true indica que
            existe uma aresta entre os dois vetices, e false se nao houver,
            ou na mesma logica com inteiros, 1 para verdadeiro e 0 para falso

            obs: nessa implementacao, usar uma lista encadeada nao é vantajoso
            pq ela nao permite acesso aleatorio para incrementarmos o valor de arestas
            ou seja, usar vector<listaEncadeada<int>> ou ListaEncadeada<vector<int>>
            */
        imprimir_matriz();
    }
    bool existe_aresta(int posv1, int posv2)
    {
        std::cout << "Existe aresta entre os vértices " << posv1 << " e " << posv2 << "? " << matriz[posv1][posv2] << std::endl;
        return matriz[posv1][posv2] > 0;
    }

    int grau(int posv)
    {
        int cont = 0;
        for (int i = 0; i < num_vertices; i++)
        {
            if (matriz[posv][i] > 0)
                cont += matriz[posv][i];
        }
        return cont;

        /*
        obs: daria pra tornar essa busca mais eficiente se tivessemos um vector de inteiros,
        cujo tamanho seria o numero de vertices do grafo, guardando o grau de cada vertice
        mas usaria maior espaço de memoria
         */
    }

    void lista_vertices_vizinhos(int posv)
    {
        std::cout << "Vizinhos do vertice " << posv << " : ";
        for (int i = 0; i < num_vertices; i++)
            if (matriz[posv][i] > 0)
                std::cout << i << " , ";
        std::cout << std::endl;

        /*obs: nesse caso, utilizar uma lista encadeada no lugar do
            vector é vantajoso, pq nao usamos acesso aleatorio, e sim
            percorremos todos os valores daquela linha
            ou seja, usar vector<listaEncadeada<int>> ou ListaEncadeada<vector<int>> */
    }
    bool vertice_e_isolado(int posv)

    {
        bool check = true;
        for (int i = 0; i < num_vertices; i++)
            if (matriz[posv][i] > 0)
                check = false;
        return check;

        /*obs: nesse caso, utilizar uma lista encadeada no lugar do
            vector é vantajoso, pq nao usamos acesso aleatorio, e sim
            percorremos todos os valores daquela linha
            ou seja, usar vector<listaEncadeada<int>> ou ListaEncadeada<vector<int>> */
    }
};

class Grafo_esparco
{

    //implementacao usando lista de adjacencia, e nao matriz de adjacencia
    //entao como precisamos constantemente percorrer a lista por inteiro
    //é interessante utilizar lista encadeada
    //ja que o acesso aleatorio é irrelevante no caso da lista de adjacencia
private:
    int num_vertices;
    int num_arestas;
    std::vector<std::list<int>> lista_adj;
    void imprimir_lista(){
        for(int i=0;i<num_vertices;i++){
            std::cout<<"vizinhos de "<<i<<" : ";
            for(auto &el:lista_adj[i]){
                std::cout<<el<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;

    }

public:
    Grafo_esparco(int n_vertice)
    {
        num_vertices = n_vertice;
        num_arestas = 0;

        //inicializando o vector de n vertices com listas vazias
        //já que os vertices vizinhos ainda serao adicionados
        lista_adj.resize(num_vertices);
        for (int i = 0; i < num_vertices; i++)
            lista_adj[i].clear();
        imprimir_lista();
    }
    ~Grafo_esparco()
    {
        num_arestas = num_vertices = 0;
        for (int i = 0; i < num_vertices; i++)
        {
            lista_adj[i].clear();
        }
        lista_adj.clear();
    }
    void inserir_aresta(int posv1, int posv2)
    {   /*com a lista encadeada, inserir uma aresta nao será O(1)
        pq será o numero de viznhos de posv1, ja que é necessario percorrer
        a lista encadeada até o final, e entao adicionar posv2 a lista;
        antes aproveitavamos do acesso aleatorio na matriz de adjacencia utilizando 
        vector, operacao entao antes era O(1) */
        lista_adj[posv1].push_back(posv2);
        num_arestas++;
        
        imprimir_lista();
    }
    bool existe_aresta(int posv1, int posv2)
    {   
        /*em geral é mais eficiente com lista, pq teremos que percorrer todos os vizinhos, ou seja, um valor menor ou igual ao numero de vertices do grafo, verificando cada um deles pra ver se sao igual a posv2 */
        for(auto &el:lista_adj[posv1]){
            if(el==posv2) return true;
        }
        return false;
    }
    void lista_vertices_vizinhos(int posv)
    {
        std::cout << "Vizinhos do vertice " << posv << " : ";
        for (auto &el:lista_adj[posv])
        {
            std::cout << el<< " ";
        }
        std::cout << std::endl;
    }
    
    int grau(int posv)
    {
        return lista_adj[posv].size();
    }
    bool vertice_e_isolado(int posv)
    {
        return lista_adj[posv].size() == 0;
    }
};

int main()
{
    std::cout<<"grafo denso: \n\n\n\n ";
    Grafo_denso *g = new Grafo_denso(5);
    g->inserir_aresta(1, 2);
    g->inserir_aresta(2, 2);
    g->inserir_aresta(2, 1);
    g->inserir_aresta(0, 2);
    g->inserir_aresta(3, 2);
    g->inserir_aresta(3, 0);

    g->existe_aresta(3, 4);
    g->existe_aresta(2, 0);
    g->existe_aresta(1, 0);

    std::cout << "O grau do vertice 0 é " << g->grau(0) << std::endl;
    std::cout << "O grau do vertice 4 é " << g->grau(4) << std::endl;
    std::cout << "O grau do vertice 2 é " << g->grau(2) << std::endl;

    g->lista_vertices_vizinhos(2);
    g->lista_vertices_vizinhos(4);

    std::cout << "o vertice 4 é isolado? " << g->vertice_e_isolado(4) << std::endl;
    std::cout << "o vertice 0 é isolado? " << g->vertice_e_isolado(0) << std::endl;

    delete g;

    std::cout<<"grafo esparco: \n\n\n\n";


    Grafo_esparco *g2 = new Grafo_esparco(5);
    g2->inserir_aresta(1, 2);
    g2->inserir_aresta(2, 2);
    g2->inserir_aresta(2, 1);
    g2->inserir_aresta(0, 2);
    g2->inserir_aresta(3, 2);
    g2->inserir_aresta(3, 0);

    g2->existe_aresta(3, 4);
    g2->existe_aresta(2, 0);
    g2->existe_aresta(1, 0);

    std::cout << "O grau do vertice 0 é " << g2->grau(0) << std::endl;
    std::cout << "O grau do vertice 4 é " << g2->grau(4) << std::endl;
    std::cout << "O grau do vertice 2 é " << g2->grau(2) << std::endl;

    g2->lista_vertices_vizinhos(2);
    g2->lista_vertices_vizinhos(4);

    std::cout << "o vertice 4 é isolado? " << g2->vertice_e_isolado(4) << std::endl;
    std::cout << "o vertice 0 é isolado? " << g2->vertice_e_isolado(0) << std::endl;

    delete g2;

    return 0;
}
