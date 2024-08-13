#include "grafos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int InicializaGrafoVazio(Grafo * grafo, int nv) {
  grafo->vertices = nv;
  grafo->arestas = 0;
  for (int i = 0; i < nv; i++) {
    for (int j = 0; j < nv; j++) {
      grafo->matriz[i][j] = 0;
    }
  }
  return 1;
}

int ImprimeGrafo(Grafo * grafo) {
  for (int i = 0; i < grafo->vertices; i++) {
    for (int j = 0; j < grafo->vertices; j++) {
      printf("%d", grafo->matriz[i][j]);

    }
    printf("\n");
  }
  return 1;
}

int ExisteAresta(Grafo * grafo, int v1, int v2){
   if(grafo->matriz[v1][v2] == 1) {
    return 1;
  }
  else {
    return 0;
  }
}

int InsereAresta(Grafo * grafo, int v1, int v2) {
  if(ExisteAresta(grafo, v1, v2)) {
    return 0;
  }
  grafo->arestas++;
  grafo->matriz[v1][v2] = 1;
  return 1;
}

int RemoveAresta(Grafo * grafo, int v1, int v2){
  if(!ExisteAresta(grafo, v1, v2)) {
    return 0;
  }
  grafo->arestas--;
  grafo->matriz[v1][v2] = 0;
  return 1;
}

int GrafoTransposto(Grafo * grafo, Grafo * grafoT){
  grafoT->vertices = grafo->vertices;
  grafoT->arestas = grafo->arestas;
  for(int i = 0; i < grafo->vertices; i++){
    for(int j = 0; j < grafo->vertices; j++){
      grafoT->matriz[i][j] = grafo->matriz[j][i];
    }
  }
  return 1;
}

int ListaAdjVazia(Grafo * grafo, int v){
  for(int i = 0;i < grafo->vertices; i++){
    if(grafo->matriz[v][i] == 1){
      return 0;
    }
  }
  return 1;
}

int ProxListaAdj(Grafo * grafo, int v, int atual){
  if(ListaAdjVazia(grafo, v)){
    return -1;
  }
  int prox = atual + 1;
  while(grafo->matriz[v][prox] == 0){
    prox++;
    if(prox > (grafo->vertices - 1)){
      return -1;
    }
  }
  return prox;
}

int main(void) {



  printf("-----------------------------------------------------------------------------\nBem-vindo ao programa que implementa Grafos através de Matriz de Adjacência! \nOs comandos são: \n inicializagrafo <número de vértices> \n inserearesta <vértice 1> <vértice 2> \n removearesta <vértice 1> <vértice 2> \n imprimegrafo \n grafotransposto \n proxlistaadj <vértice> <atual> \n fim\n-----------------------------------------------------------------------------\n");
  int loop = 1;
  char comando[40];
  int nv, v1,v2;
  int verificador = 0;
  Grafo grafo;
  Grafo grafoT;
  while(loop) {
    scanf("%s", comando);
    if(!strcmp(comando, "inicializagrafo")){
      scanf("%d", &nv);
      if(verificador == 1){
        printf("O grafo já foi inicializado!\n");
        continue;
      }
      InicializaGrafoVazio(&grafo, nv);
      verificador = 1;
      printf("Grafo inicializado!\n");
      continue;
    }
    if(!strcmp(comando, "inserearesta")){
      scanf("%d %d", &v1, &v2);
      if(!verificador){
        printf("Inicialize o Grafo antes de inserir arestas!\n");
        continue;
      }
      if(v1 < 0 || v2 < 0){
        printf("Selecione uma aresta válida!\n");
        continue;
      }
      if(v1 >= nv || v2 >= nv){
        printf("Selecione uma aresta válida!\n");
        continue;
      }
      if(InsereAresta(&grafo, v1, v2)){
        printf("Aresta inserida com sucesso!\n");
      } else {
        printf("Esta aresta já existe. Tente novamente!\n");
      }
      continue;
    }
    if(!strcmp(comando, "imprimegrafo")){
      if(!verificador){
        printf("Inicialize o Grafo antes de imprimi-lo!\n");
        continue;
      }
      ImprimeGrafo(&grafo);
      continue;
    }
    if(!strcmp(comando, "removearesta")){
      scanf("%d %d", &v1, &v2);
      if(!verificador){
        printf("Inicialize o Grafo antes de remover arestas!\n");
        continue;
      }
      if(v1 < 0 || v2 < 0){
        printf("Selecione uma aresta válida!\n");
        continue;
      }
      if(v1 >= nv || v2 >= nv){
        printf("Selecione uma aresta válida!\n");
        continue;
      }
      if(RemoveAresta(&grafo, v1, v2)){
        printf("Aresta removida com sucesso!\n");
      } else {
        printf("Esta aresta não existe. Tente novamente!\n");
      }
      continue;
    }
    if(!strcmp(comando, "grafotransposto")){
      if(!verificador){
        printf("Inicialize o Grafo antes de imprimir o Grafo Transposto!\n");
        continue;
      }
      GrafoTransposto(&grafo, &grafoT);
      ImprimeGrafo(&grafoT);
      continue;
    }
    if(!strcmp(comando, "proxlistaadj")){
      scanf("%d %d",&v1, &v2);
      if(!verificador){
        printf("Inicialize o Grafo antes de imprimir uma lista de adjacência!\n");
        continue;
      }
      if(v1<0){
        printf("Selecione uma aresta válida!\n");
        continue;
      }
      if(v1>=nv){
        printf("Selecione uma aresta válida!\n");
        continue;
      }
      if(ListaAdjVazia(&grafo, v1)){
        printf("A lista de ajacência deste vértice está vazia!\n");
        continue;
      }
      else {
      int prox = ProxListaAdj(&grafo, v1, v2);
      if(prox == -1){
        printf("Não há mais vértices adjacentes!\n");
        continue;
      }
      printf("O próximo vértice é: %d\n", prox);
      continue;
      }
    }
    if(!strcmp(comando, "fim")){
      loop = 0;
      break;
    }
    printf("Comando inválido. Tente digitar um dos comandos da lista!\n");
  }

  return 0;
}
