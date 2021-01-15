//// Algoritmo de busca em largura em C

#include <stdio.h>
#include <stdlib.h>
#define TAM 40

struct fila {
  int items[TAM];
  int frente;
  int tras;
};

struct fila* criarFila();
void addFila(struct fila* f, int);
int remvFila(struct fila* f);
int vazia(struct fila* f);
void mostrarFila(struct fila* f);

struct no {
  int vertice;
  struct no* prox;
};

struct no* criarNo(int);

struct Arvore {
  int numVertices;
  struct no** listaAdj;
  int* visitado;
};

// Algoritmo de busca em largura
void buscaLargura(struct Arvore* arvr, int verticeInicial) {
  struct fila* f = criarFila();

  arvr->visitado[verticeInicial] = 1;
  addFila(f, verticeInicial);

  while (!vazia(f)) {
    mostrarFila(f);
    int verticeAtual = remvFila(f);
    printf("\nVisitado %d\n", verticeAtual);

    struct no* temp = arvr->listaAdj[verticeAtual];

    while (temp) {
      int verticeAdj = temp->vertice;

      if (arvr->visitado[verticeAdj] == 0) {
        arvr->visitado[verticeAdj] = 1;
        addFila(f, verticeAdj);
      }
      temp = temp->prox;
    }
  }
}

// criar um no
struct no* criarNo(int v) {
  struct no* novoNo = malloc(sizeof(struct no));
  novoNo->vertice = v;
  novoNo->prox = NULL;
  return novoNo;
}

// criar arvore
struct Arvore* criarArvore(int vertices) {
  struct Arvore* arvr = malloc(sizeof(struct Arvore));
  arvr->numVertices = vertices;

  arvr->listaAdj = malloc(vertices * sizeof(struct no*));
  arvr->visitado = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    arvr->listaAdj[i] = NULL;
    arvr->visitado[i] = 0;
  }

  return arvr;
}

// Adicionar no filho
void noFilho(struct Arvore* arvr, int src, int dest) {
	
  struct no* novoNo = criarNo(dest);
  novoNo->prox = arvr->listaAdj[src];
  arvr->listaAdj[src] = novoNo;

  novoNo = criarNo(src);
  novoNo->prox = arvr->listaAdj[dest];
  arvr->listaAdj[dest] = novoNo;
}

//criar fila
struct fila* criarFila() {
  struct fila* f = malloc(sizeof(struct fila));
  f->frente = -1;
  f->tras = -1;
  return f;
}

int vazia(struct fila* f) {
  if (f->tras == -1)
    return 1;
  else
    return 0;
}

void addFila(struct fila* f, int valor) {
  if (f->tras == TAM - 1)
    printf("\nFila cheia!!");
  else {
    if (f->frente == -1)
      f->frente = 0;
    f->tras++;
    f->items[f->tras] = valor;
  }
}

int remvFila(struct fila* f) {
  int item;
  if (vazia(f)) {
    printf("Fila vazia");
    item = -1;
  } else {
    item = f->items[f->frente];
    f->frente++;
    if (f->frente > f->tras) {
      f->frente = f->tras = -1;
    }
  }
  return item;
}

void mostrarFila(struct fila* f) {
  int i = f->frente;

  if (vazia(f)) {
    printf("Fila vazia");
  } else {
    printf("\nA fila contem \n");
    for (i = f->frente; i < f->tras + 1; i++) {
      printf("%d ", f->items[i]);
    }
  }
}

int main() {
  struct Arvore* arvr = criarArvore(6);
  noFilho(arvr, 0, 1);
  noFilho(arvr, 0, 2);
  noFilho(arvr, 1, 2);
  noFilho(arvr, 1, 4);
  noFilho(arvr, 1, 3);
  noFilho(arvr, 2, 4);
  noFilho(arvr, 3, 4);

  buscaLargura(arvr, 0);

  return 0;
}

