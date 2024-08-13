#define TRUE 1
#define FALSE 0
#define MAXNUMVERTICES 100

typedef struct grafo {
  int vertices;
  int arestas;
  int matriz[MAXNUMVERTICES][MAXNUMVERTICES];
} Grafo;

int InicializaGrafoVazio(Grafo * grafo, int nv);
int InsereAresta(Grafo * grafo, int v1, int v2);
int RemoveAresta(Grafo * grafo, int v1, int v2);
int ExisteAresta(Grafo * grafo, int v1, int v2);
int ImprimeGrafo(Grafo * grafo);
int GrafoTransposto(Grafo * grafo, Grafo * grafoT);
int ProxListaAdj(Grafo * grafo, int v, int atual);
int ListaAdjVazia(Grafo * grafo, int v);
