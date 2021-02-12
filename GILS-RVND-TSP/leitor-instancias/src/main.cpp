#include "readData.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

double **matrizAdj; // matriz de adjacencia
int dimension;      // quantidade total de vertices



// Estrutura com dados de arestas removidas e custos
struct InsertionInfo {
    int noInserido; // número do nó a ser inserido
    int arestaRemovida; // aresta { i , j } onde o nó seria inserido
    double custo; // delta ao inserir o nó na aresta
};

// Swap
double swap(vector <int> s){
  double delta;


  for( int i = 1; i < s.size(); i++){
    for( int j = i + 1; j < s.size(); j++){
      // Para i = 2 , j = 5 ...
      // c24 +  c26 + c51 + c53 - ( c21 + c23 + c54 + c56)
      // cij-1 + cij+1 + cji-1 + cji+1 - (cii-1 + cii+1 + cjj-1 + cjj+1)
      delta= matrizAdj[s[i]][s[j-1]] + matrizAdj[s[i]][s[j+1]] + matrizAdj[s[j]][s[i-1]] + matrizAdj[s[j]][s[i+1]] - ( matrizAdj[s[i]][s[i-1]] + matrizAdj[s[i]][s[i+1]] + matrizAdj[s[j]][s[j-1]] + matrizAdj[s[j]][s[j+1]]);
    }
  }


}

// Estruturas de vizinhança
void RVND(vector <int> &s){
  swap(s);
}

// Calcula o custo total da distância entre todos os nós da solução
double custoTotal(vector <int> s){

  double custoTotal = 0;
  for(int i = 0; i < s.size()-1; i++){
    custoTotal += matrizAdj[s[i]][s[i+1]];
  }

  return custoTotal;
}

// Função vector que retorna uma solução viável para o tsp
vector<int> construcao(double alfa, vector<int> listaDeCandidatos){

  vector<int> s;

  // Inicia o percurso com o depósito
  s.push_back(listaDeCandidatos[0]);
  s.push_back(listaDeCandidatos[0]);
  listaDeCandidatos.erase(listaDeCandidatos.begin());

  // Subtour, definindo aleatoriamente as cidades:
  for (int c = 0; c < 3; c++){
    int l = rand() % listaDeCandidatos.size();
    s.insert(s.begin() + 1, listaDeCandidatos[l]);
    listaDeCandidatos.erase(listaDeCandidatos.begin() + l);
  }

  // Cálculo do custo de inserção de nós
  while (!listaDeCandidatos.empty()){ // lista de candidatos deve estar zerada ao final do processo
  
    vector <InsertionInfo> custoInsercao((s.size() - 1) * listaDeCandidatos.size()); 

    for (int i = 0, j = 1, l = 0; i < s.size() - 1; i++, j++){
      for(auto k : listaDeCandidatos){
        custoInsercao[l].custo = matrizAdj[s[i]][k] + matrizAdj[s[j]][k] - matrizAdj[s[i]][s[j]];
        custoInsercao[l].noInserido = k;
        custoInsercao[l].arestaRemovida = i;
        l++;
      }
    }
  
    // Ordenação SD pelos custos de inserção
    sort( custoInsercao.begin(), custoInsercao.end(), [](InsertionInfo a, InsertionInfo b){ 
      return a.custo < b.custo; // Retorna o custo de inserção do menor ao maior
    });    
    // Gerador de desordem na definição dos elementos iniciais por meio de um valor aleatório
    int sAleatorios = alfa * custoInsercao.size(); 
    // Escolhe aleatoriamente um dos elementos de sAleatorios aleatoriamente
    int nAleatorios = rand() % sAleatorios;
    //Insere nó escolhido no subtour
    s.insert(s.begin() + (custoInsercao[nAleatorios].arestaRemovida + 1) ,  custoInsercao[nAleatorios].noInserido);
 
    //Apagando nó da lista de candidatos
    for(int l = 0; l < listaDeCandidatos.size(); l++){
      if(listaDeCandidatos[l] == custoInsercao[nAleatorios].noInserido){
        listaDeCandidatos.erase(listaDeCandidatos.begin() + l );
      }
    }
  }
  return s;
}



int main(int argc, char **argv){

  readData(argc, argv, &dimension, &matrizAdj);
  int iIls;
  // Seed para geração de números aleatórios
  srand(time(NULL));

  // Controla o número de tentativas de melhorar a solução
  if(dimension>=150){
    iIls=dimension/2;
  }
  else{
    iIls=dimension;
  }

  // Início do algoritmo principal

  for( int iMax = 1; iMax <= 50; iMax++){
  //srand(time(NULL));
  // Vetor que armazena as cidades 
  vector<int> cidades;
  //double somatorioS;/**somatoriosA;**/
  // Geração de valor aleatório alfa para a construção
  double valorRand = (rand() % 100) /100.0 ;

  // Produz vetor para as cidades
    for (int i = 1; i << dimension; i++){ 
      cidades.push_back(i);
    }

  vector <int> s = construcao(valorRand, cidades);
  vector <int> sA = s; 

  int iterIls = 0;
  
   while(iterIls < iIls){
    
   RVND(s);

   double somatorioS = custoTotal(s);
   // double somatoriosA = custoTotal(sA);
    //if
   // iterIls++;
    cout << somatorioS << endl;
    //}
  }

  return 0;
}

