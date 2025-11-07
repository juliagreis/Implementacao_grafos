#include <iostream>
#include <vector>

void pintar(std::vector<std::string> &labirinto, int linha,int coluna){
    labirinto[linha][coluna]='#';
    if(labirinto.size()>linha+1 && labirinto[linha+1].size()>coluna && labirinto[linha+1][coluna]==' '){//se nao foi preenchido
        pintar(labirinto,linha+1,coluna);
    }if(linha-1>=0 && labirinto[linha-1].size()>coluna && labirinto[linha-1][coluna]==' '){//se nao foi preenchido
        pintar(labirinto,linha-1,coluna);
    }if(labirinto[linha].size()>coluna+1 && labirinto[linha][coluna+1]==' '){//se nao foi preenchido
        pintar(labirinto,linha,coluna+1);
    }if(coluna-1>=0 && labirinto[linha][coluna-1]==' '){//se nao foi preenchido
        pintar(labirinto,linha,coluna-1);
    }
}





int main(){

    int n;
    std::cin>>n;

        for(int i=0;i<n;i++){
            std::cin.ignore();
            std::vector<std::string> labirinto;
            int initL,initC;
            
            std::string linha;
            int j=0;
            while(std::getline(std::cin,linha)){
                labirinto.push_back(linha);
                bool fim=false;
                int i=0;
                for(char c: linha){
                    if(c=='_') fim=true;;
                    if(c=='*'){initL=i; initC=j;} //agora eu sei em que posicao o * esta
                    i++;
                }
                j++;
                if(fim) break;
            }

            pintar(labirinto,initL,initC);
            //imprimindo o labirinto
            for(std::string s:labirinto){
                std::cout<<s<<std::endl;
            }
    }

    return 0;
}