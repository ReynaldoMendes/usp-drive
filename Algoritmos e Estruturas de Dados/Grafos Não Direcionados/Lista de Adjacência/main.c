#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"


int InicializaGrafoVazio(Grafo * grafo, int nv) {
    grafo->vertices = nv;
    grafo->arestas = 0;
    grafo->lista = (No**) calloc(nv,sizeof(No*));
    return TRUE;
}

int ExisteAresta(Grafo * grafo, int v1, int v2){
    int loop = 1;
    No * temp = grafo->lista[v1];
    while(loop){
        if(temp == 0){
            return 0;
        }
        if(temp->numvertice == v2){
            return 1;
        } else if(temp->prox == NULL) {
            return 0;
        }
        temp = temp->prox;
    }
    return 0;
}

int InsereAresta(Grafo * grafo, int v1, int v2, int peso){
    if(ExisteAresta(grafo, v1, v2)){
        return 0;
    }
    if(grafo->lista[v1] == 0){
        grafo->lista[v1] = (No*) calloc(1,sizeof(No));
        grafo->lista[v1]->numvertice = v2;
        grafo->lista[v1]->peso = peso;
        grafo->lista[v1]->prox = NULL;
        grafo->arestas++;
        return 1;
    }
    int loop = 1;
    No * temp = grafo->lista[v1];
    while(loop){
        if(temp->prox == NULL){
            temp->prox = (No*) calloc(1,sizeof(No));
            temp->prox->numvertice = v2;
            temp->prox->peso = peso;
            temp->prox->prox = NULL;
            grafo->arestas++;
            loop = 0;
            return 1;
        }
        temp = temp->prox;
    }
    return 0;
}

int RemoveAresta(Grafo * grafo, int v1, int v2){
    if(!ExisteAresta(grafo, v1, v2)){
        return 0;
    }
    int loop = 1;
    No * temp = grafo->lista[v1];
    No * ant;
    No * prox;
    if(grafo->lista[v1]->numvertice == v2){
        if(grafo->lista[v1]->prox == NULL){
            grafo->lista[v1] = 0;
            free(temp);
            return 1;
        }
        if(grafo->lista[v1]->prox != NULL){
            grafo->lista[v1] = grafo->lista[v1]->prox;
            free(temp);
            return 1;
        }
    }
    while(loop){
        if(temp->numvertice != v2){
            ant = temp;
            temp = temp->prox;
            continue;
        }
        if(temp->numvertice == v2){
            if(temp->prox == NULL){
                ant->prox = NULL;
                free(temp);
                return 1;
            }
            else {
                ant->prox = temp->prox;
                free(temp);
                return 1;
            }
        }
    }
}

int ImprimeGrafo(Grafo * grafo){
    for(int i = 0; i < grafo->vertices; i++){
        printf("Vértice %d: ", i);
        No * temp = grafo->lista[i];
        int loop = 1;
        while(loop){
            if(temp == 0){
                printf("Não há arestas com este vértice.");
                loop = 0;
                break;
            } 
            printf("Aresta(%d,%d) com Peso %d. ", i, temp->numvertice, temp->peso);
            if(temp->prox == NULL){
                loop = 0;
                break;
            }
            temp = temp->prox;
        }
        printf("\n");
    }
}

int ListaAdjVazia(Grafo * grafo, int v){
if(grafo->lista[v] == 0){
  return 1;
}
else {
  return 0;
}

}

int ProxListaAdj(Grafo * grafo, int v, int atual){
  if(ListaAdjVazia(grafo, v)){
    return -1;
  }
  int prox;
  No * temp = grafo->lista[v];
  if(atual == -1){
    return temp->numvertice;
  }
  while(atual != temp->numvertice){
    temp = temp->prox;
    if(temp == NULL){
      return -1;
    }
  }
  if(temp->prox == NULL){
    return -1;
  }
return temp->prox->numvertice;
}

int Liberagrafo(Grafo * grafo){
  No ** lista = grafo->lista;
  for(int i = 0; i < grafo->vertices; i++){
    No * temp = grafo->lista[i];
    No * ant;
    int loop = 1;
    if(grafo->lista[i] == 0){
      continue;
    }
    if(temp->prox == NULL){
      free(temp);
      grafo->lista[i] = 0;
      continue;
    } else{
      while (temp != NULL) {
      ant = temp;
      temp = temp->prox;
      free(ant);
      }
    }
  }
  free(lista);
  return 1;
}

void VisitaCiclo(Grafo * grafo, int v, char * cor, int * ciclos){
    for(int i = 0; i<grafo->vertices;i++){
        ciclos[i] = -1;
    }
    cor[v] = 'c';
    int atual = -1;
    int prox = ProxListaAdj(grafo, v, atual);
    ciclos[0] = v;
    for(int i = 0; i < grafo->vertices; i++){
        if(prox == v){
            return;
        } else if (prox == -1) {
          break;
        }  
        ciclos[i]= prox;
        prox = ProxListaAdj(grafo, prox, atual);
        
    }
    ciclos[0] = -1;
    return;
    
}

void IdentificaCiclos(Grafo * grafo){
    char cor[grafo->vertices];
    int ciclos[grafo->vertices];
    for(int i=0;i<grafo->vertices;i++){
        cor[i] = 'b';
    }
    for(int i=0;i<grafo->vertices;i++){
        if(cor[i]=='b'){
            VisitaCiclo(grafo, i, cor, ciclos);
        }
        if(ciclos[0]!=-1){
            printf("Ciclo: %d ", i);
            for(int j = 0; ciclos[j] != -1; j++){
                printf(" %d", ciclos[j]);
            }
            printf("\n");
        }
    }
}

int main(void){
    printf("-----------------------------------------------------------------------------\nBem-vindo ao programa que implementa Grafos através de Lista de Adjacência! \nOs comandos são: \n inicializagrafo <número de vértices> \n inserearesta <vértice 1> <vértice 2> <peso> \n removearesta <vértice 1> <vértice 2> \n imprimegrafo \n proxlistaadj <vértice> <atual>\n liberagrafo \n ciclos \n fim \n-----------------------------------------------------------------------------\n");
    int loop = 1;
    char comando[40];
    int nv, v1,v2, peso;
    int verificador = 0;
    Grafo grafo;
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
      scanf("%d %d %d", &v1, &v2, &peso);
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
      if(InsereAresta(&grafo, v1, v2, peso)){
        InsereAresta(&grafo, v2, v1, peso);
        printf("Aresta inserida com sucesso!\n");
      } else {
        printf("Esta aresta já existe. Tente novamente!\n");
      }
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
        RemoveAresta(&grafo, v2, v1);
        printf("Aresta removida com sucesso!\n");
      } else {
        printf("Esta aresta não existe. Tente novamente!\n");
      }
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
      } else {
          printf("O próximo vértice é: %d\n", prox);
          continue;
        }    
      }
    }
    if(!strcmp(comando, "imprimegrafo")){
      if(!verificador){
        printf("Inicialize o Grafo antes de imprimi-lo!\n");
        continue;
      }
      ImprimeGrafo(&grafo);
      continue;
    }
    if(!strcmp(comando, "liberagrafo")){
      if(!verificador){
        printf("Inicialize o Grafo antes de liberá-lo!\n");
        continue;
      }
      if(Liberagrafo(&grafo)){
        printf("Grafo liberado com sucesso!\n");
      }
      verificador = 0;
      continue;
    }
    if(!strcmp(comando, "ciclos")){
      IdentificaCiclos(&grafo);
      continue;
    }
    if(!strcmp(comando, "fim")){
      loop = 0;
      break;
    }
    printf("Comando inválido. Tente digitar um dos comandos da lista!\n");
  }

  return 0;
}
