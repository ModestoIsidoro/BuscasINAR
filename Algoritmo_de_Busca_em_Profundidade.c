//// Algoritmo de busca em profundidade em C

#include <stdio.h>
#include <stdlib.h>

struct no {
  int vertice;
  struct no* prox;
};

struct no* criarNo(int v);

struct Arvore {
  int numVertices;
  int* visitado;

  struct no** listaAdj;
};

//// Algoritmo de busca em profundidade
void buscaProfundidade(struct Arvore* arvore, int vertice) {
  struct no* listaAdj = arvore->listaAdj[vertice];
  struct no* temp = listaAdj;

  arvore->visitado[vertice] = 1;
  printf("Visitado %d \n", vertice);

  while (temp != NULL) {
    int verticeConectado = temp->vertice;

    if (arvore->visitado[verticeConectado] == 0) {
      buscaProfundidade(arvore, verticeConectado);
    }
    temp = temp->prox;
  }
}

struct no* criarNo(int v) {
  struct no* novoNo = malloc(sizeof(struct no));
  novoNo->vertice = v;
  novoNo->prox = NULL;
  return novoNo;
}

struct Arvore* criarArvore(int vertices) {
  struct Arvore* arvore = malloc(sizeof(struct Arvore));
  arvore->numVertices = vertices;

  arvore->listaAdj = malloc(vertices * sizeof(struct no*));

  arvore->visitado = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    arvore->listaAdj[i] = NULL;
    arvore->visitado[i] = 0;
  }
  return arvore;
}

void noFilho(struct Arvore* arvore, int src, int dest) {

  struct no* novoNo = criarNo(dest);
  novoNo->prox = arvore->listaAdj[src];
  arvore->listaAdj[src] = novoNo;

  novoNo = criarNo(src);
  novoNo->prox = arvore->listaAdj[dest];
  arvore->listaAdj[dest] = novoNo;
}

void imprimirArvore(struct Arvore* arvore) {
  int v;
  for (v = 0; v < arvore->numVertices; v++) {
    struct no* temp = arvore->listaAdj[v];
    printf("\n Lista dos nos adjacentes %d\n ", v);
    while (temp) {
      printf("%d -> ", temp->vertice);
      temp = temp->prox;
    }
    printf("\n");
  }
}

int main() {
  struct Arvore* arvore = criarArvore(4);
  noFilho(arvore, 0, 1);
  noFilho(arvore, 0, 2);
  noFilho(arvore, 1, 2);
  noFilho(arvore, 2, 3);

  imprimirArvore(arvore);

  buscaProfundidade(arvore, 2);

  return 0;
}

