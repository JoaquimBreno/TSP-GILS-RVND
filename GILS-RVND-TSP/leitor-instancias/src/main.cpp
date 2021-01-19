#include "readData.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

double **matrizAdj; // matriz de adjacencia
int dimension;      // quantidade total de vertices

void printData();

//E strutura com dados de arestas removidas e custos
struct InsertionInfo {
    int noInserido; // número do nó a ser inserido
    int arestaRemovida; // aresta { i , j } onde o nó seria inserido
    double custo; // delta ao inserir o nó na aresta
};

vector<int> construcao(double alfa, vector<int> listaDeCandidatos){

  vector<int> s;

  // Inicia o percurso com o depósito
  s.push_back(listaDeCandidatos[1]);
  listaDeCandidatos.erase(listaDeCandidatos.begin());

  // Subtour, definindo aleatoriamente as cidades:
  for (int c = 0; c < 3; c++){
    int l = rand() % listaDeCandidatos.size();
    s.insert(s.begin() + 1, listaDeCandidatos[l]);
    listaDeCandidatos.erase(listaDeCandidatos.begin() + l);
  }

  // Cálculo do custo de inserção de nós
  while (!listaDeCandidatos.empty()){ // lista de candidatos deve estar zerada ao final do processo

    vector <InsertionInfo> custoInsercao(s.size() - 1 * listaDeCandidatos.size()); 

    for (int i = 0, j = 1, l = 0; i < s.size() - 2; i++, j++){
      for(auto k : listaDeCandidatos){
        custoInsercao[l].custo = matrizAdj[s[i]][k] + matrizAdj[s[j]][k] - matrizAdj[s[i]][s[j]];
        custoInsercao[l].noInserido = k;
        custoInsercao[l].arestaRemovida = i;
        l++;
      }
    }

    // Ordenação SD pelos custos de inserção
    sort( custoInsercao.begin(), custoInsercao.end(), [](InsertionInfo a, InsertionInfo b){ 
      return a.custo < b.custo;
    });

    // Gerador de desordem na definição dos elementos iniciais por meio de um valor aleatório
    int sAleatorios = alfa * custoInsercao.size();  

    

  }
}

int main(int argc, char **argv){

  readData(argc, argv, &dimension, &matrizAdj);

  // Seed para geração de números aleatórios
  srand(time(NULL));

  // Início do algoritmo principal
  /** Geração de valor aleatório para a construção**/
  double valorRand = rand() % 100 / 100;
  /** Vetor que armazena as cidades **/
  vector<int> cidades;
  for (int i = 1; i <= dimension; i++){ // gera vetor para as cidades
    cidades.push_back(i);
  }
  construcao(valorRand, cidades);

  printData();
  return 0;
}

void printData(){
  cout << "dimension: " << dimension << endl;
  for (size_t i = 1; i <= dimension; i++){
    for (size_t j = 1; j <= dimension; j++){
      cout << matrizAdj[i][j] << " ";
    }
    cout << endl;
  }
}
