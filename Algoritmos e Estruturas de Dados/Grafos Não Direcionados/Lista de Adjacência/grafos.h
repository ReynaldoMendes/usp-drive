#define TRUE 1
#define FALSE 0
#define MAXNUMVERTICES 100
#define NULO -1

typedef struct No {
    int numvertice;
    int peso;
    struct No * prox;
} No;

typedef struct grafo {
    int vertices;
    int arestas;
    struct No ** lista;
} Grafo;

int InicializaGrafoVazio(Grafo * grafo, int nv);
int ImprimeGrafo(Grafo * grafo);
int InsereAresta(Grafo * grafo, int v1, int v2, int peso);
int RemoveAresta(Grafo * grafo, int v1, int v2);
int ExisteAresta(Grafo * grafo, int v1, int v2);
int ListaAdjVazia(Grafo * grafo, int v);
int ProxListaAdj(Grafo * grafo, int v, int atual);
int LiberaGrafo(Grafo * grafo);
