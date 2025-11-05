/*
Implemente a função abaixo (você poderá criar funções auxiliares se necessário). Dada a lista de adjacência (adj) de um grafo G (não direcionado), 
ela deverá armazenar em compsCompletoso número de componentes conexos de G que são subgrafos completos (ou seja, você deverá contar um componente
conexo <-> o componente inteiro for um grafo completo) e deverá armazenar em compsComCiclos o número de componentes conexos de G que contêm ciclos 
(ou seja, você deverá contar um componente conexo C <-> houver pelo menos um ciclo em C).

*/

#include <iostream>
#include <vector>

//número de componentes conexos de G que são subgrafos completos -> ou seja, se o componente conexo tem numArestas= v.(v-1)/2
//número de componentes conexos de G que contêm ciclos -> se o componente é conexo e tem ciclo, basta que ele nao seja uma arvore, ou seja, NumArestas != numVertices-1

void dfs(const std::vector<std::vector<int>> &adj, int &compsCompletos, int &compsComCiclos,std::vector<int> &processados,int v,int &somaDosGraus,int &nVerticesDoComp){

    processados[v]=1;
    nVerticesDoComp++;
    for(int u:adj[v]){ //percorrendo os vizinhos
        if(processados[u]==0){ //se ainda nao processei
            dfs(adj,compsCompletos,compsComCiclos,processados,u,somaDosGraus,nVerticesDoComp);
        }
        somaDosGraus++;
    }
}

void analisa(const std::vector<std::vector<int>> &adj, int &compsCompletos, int &compsComCiclos) {

    int numVertices=adj.size();
    std::vector<int> processados(numVertices,0);
    int somaDosGraus,nVerticesDoComp;

    
    for(int i=0;i<numVertices;i++){
        if(processados[i]==0){ //se nao foi processado ainda
            somaDosGraus=0;
            nVerticesDoComp=0; //reinicializa a cada novo componente conexo

            dfs(adj,compsCompletos,compsComCiclos,processados,i,somaDosGraus,nVerticesDoComp);
            int numArestas=somaDosGraus/2;
            if(numArestas!=nVerticesDoComp-1) compsComCiclos++;
            if(numArestas==nVerticesDoComp*(nVerticesDoComp-1)/2) compsCompletos++;
        }
        
    }
}

/* Considere uma árvore (com raiz) representada por um vetor “pai” (ou seja, pai[v] representa o pai de cada vértice v da árvore, 
sendo o pai da raiz representado por -1). Implemente uma função que, dado o vetor “pai” (argumento da função), cria uma matriz de adjacência
 (chame-a de “mat”) e uma lista de adjacência (chame-a de “adj”) para a árvore (a árvore no grafo resultante não deverá ter raiz -- ou seja,
  deverá ser não direcionada). Obs 1: você não precisa se preocupar em retornar o que foi criado -- basta criar e assumir que algo será feito
  com as estruturas de dados criadas. Obs 2: você poderá criar funções auxiliares se necessário.
*/
void criaListaEMatrix(const std::vector<int> &pai) {
	//Declare aqui a lista de adjacencia e a matriz de adj
    int numVertices=pai.size();
    std::vector<std::vector<int> > mat(numVertices,std::vector<int>(numVertices,0));
    std::vector<std::vector<int> > adj(numVertices);


	//Implemente o codigo para preencher a lista de adjacencia e a matriz de adj

    for(int i=0;i<numVertices;i++){ //percorrendo o vetor de pai
        int v=pai[i]; // i é filho de v
        if(v==-1) continue; //ou seja, se é a raiz vou para o proximo
        adj[v].push_back(i); adj[i].push_back(v);
        mat[v][i]=1; mat[i][v]=1;
    }   
}

/*
Esta questão foi adaptada de um problema utilizado em uma entrevista de emprego para Engenheiro de Software 3 da Amazon/Seattle. Dada a dependência de compilação de alguns pacotes Java, determine a ordem em que eles devem ser compilados de modo a satisfazer essas restrições. A entrada começará com dois inteiros representando o número de pacotes (P) e o número de dependências (D). A seguir, há D linhas cada uma contendo um par de inteiros (a,b) indicando que o pacote a depende do pacote b para poder ser compilado
Exemplo de entrada (a explicação entre parênteses não faz parte da entrada):
4 3 (ha 4 pacotes que precisam ser compilados e 3 restrições sobre a ordem de compilacao)
1 2 (o pacote 1 só pode ser compilado após a 2 ter sido compilado)
1 3 (o pacote 1 só pode ser compilado após a 3 ter sido compilado)
2 3 (o pacote 2 só pode ser compilado após a 3 ter sido compilado)

Possivel saida: 4 3 2 1 
(se os pacotes forem compilados nessa ordem, as dependências acima serão satisfeitas)

Para facilitar, suponha que a entrada já foi lida e que sua tarefa será apenas implementar uma função para processá-la. Termine a implementação da função abaixo (que, dado o número de pacotes e um vetor contendo as dependências, imprime a saída do problema (dependencias[i].first so pode ser compilado após dependencias[i].second ter sido).

*/
#include <queue>
void imprimeOrdem(int pacotes, const std::vector<std::pair<int,int> > &dependencias) { 

    //precisamos montar o grafo e guardar os graus de entrada
    std::vector<int> graus(pacotes,0);
    std::vector<std::vector<int> > adj(pacotes);
    std::queue<int> fila;

    for(int i=0;i<dependencias.size();i++){
        adj[dependencias[i].second].push_back(dependencias[i].first);
        graus[dependencias[i].first]++;
    }

    //agora coloco todo mundo de grau=0 na fila
    for(int i=0;i<pacotes;i++){
        if(graus[i]==0) fila.push(i);
    }

    //agora processo a minha fila
    while(!fila.empty()){
        int v=fila.front(); fila.pop();
        std::cout<<v<<" "; //escrevi ele

        for(int u:adj[v]){ //percorrendo todos os vizinhos diminuindo o grau deles
            graus[u]--;
            if(graus[u]==0) fila.push(u);
        }
    }



}

