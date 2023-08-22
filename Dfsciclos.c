#include <stdio.h>
#include <stdlib.h>

struct Grafo {
  int vertices;
  int arestas;
  int **matrizAdjacencia;
};

struct Grafo *criarGrafo(int vertices) {
  struct Grafo *grafo = (struct Grafo *)malloc(sizeof(struct Grafo));
  grafo->vertices = vertices;
  grafo->arestas = 0;
  grafo->matrizAdjacencia = (int **)malloc(vertices * sizeof(int *));
  for (int i = 0; i < vertices; i++) {
    grafo->matrizAdjacencia[i] = (int *)malloc(vertices * sizeof(int));
    for (int j = 0; j < vertices; j++) {
      grafo->matrizAdjacencia[i][j] = 0;
    }
  }
  return grafo;
}

void adicionarAresta(struct Grafo *grafo, int origem, int destino) {
  grafo->matrizAdjacencia[origem][destino] = 1;
  grafo->arestas++;
}
void dfs(struct Grafo *grafo, int vertice, int visitados[], int pilhaRecursao[], int *cicloEncontrado) {
  visitados[vertice] = 1;
  pilhaRecursao[vertice] = 1;

  for (int vizinho = 0; vizinho < grafo->vertices; vizinho++) {
    if (grafo->matrizAdjacencia[vertice][vizinho]) {
      if (!visitados[vizinho]) {
        dfs(grafo, vizinho, visitados, pilhaRecursao, cicloEncontrado);
      } else if (pilhaRecursao[vizinho]) {
        *cicloEncontrado = 1;
        return;
      }
    }
  }

  pilhaRecursao[vertice] = 0;
}

void verificarCiclos(struct Grafo *grafo) {
  for (int i = 0; i < grafo->vertices; i++) {
    int visitados[grafo->vertices];
    int pilhaRecursao[grafo->vertices];
    int cicloEncontrado = 0;

    for (int j = 0; j < grafo->vertices; j++) {
      visitados[j] = 0;
      pilhaRecursao[j] = 0;
    }

    dfs(grafo, i, visitados, pilhaRecursao, &cicloEncontrado);

    if (cicloEncontrado) {
      printf("Ciclo encontrado no vertice %d\n", i);
    } else {
      printf("Nenhum ciclo encontrado no vértice %d\n", i);
    }
  }
}

int main() {
  struct Grafo* grafo = criarGrafo(8);

  adicionarAresta(grafo, 0, 1);
  adicionarAresta(grafo, 0, 3);
  adicionarAresta(grafo, 0, 4);
  adicionarAresta(grafo, 1, 0);
  adicionarAresta(grafo, 1, 2);
  adicionarAresta(grafo, 1, 5);
  adicionarAresta(grafo, 2, 1);
  adicionarAresta(grafo, 2, 3);
  adicionarAresta(grafo, 2, 6);
  adicionarAresta(grafo, 3, 0);
  adicionarAresta(grafo, 3, 2);
  adicionarAresta(grafo, 3, 7);
  adicionarAresta(grafo, 4, 0);
  adicionarAresta(grafo, 4, 5);
  adicionarAresta(grafo, 4, 7);
  adicionarAresta(grafo, 5, 1);
  adicionarAresta(grafo, 5, 4);
  adicionarAresta(grafo, 5, 6);
  adicionarAresta(grafo, 6, 2);
  adicionarAresta(grafo, 6, 5);
  adicionarAresta(grafo, 6, 7);
  adicionarAresta(grafo, 7, 3);
  adicionarAresta(grafo, 7, 4);
  adicionarAresta(grafo, 7, 6);

 verificarCiclos(grafo);
  return 0;
}