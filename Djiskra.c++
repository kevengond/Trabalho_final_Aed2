#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define INF 1000000

void Dijkstra(int numero_vertice, int origem, int **Grafo, int *distancia, int *caminho);
void printMenorCaminho(int origem, int numero_vertice, int *distancia, int *caminho);

int main() {
    int numero_vertice = 10; // Defina o número de vértices aqui
    int **Grafo = (int **)malloc(numero_vertice * sizeof(int *));
    
    // Definindo o grafo (matriz de adjacências)
    int matriz_adjacencias[10][10] = {
          {0, 300, 500, 0, 0, 0, 0, 0, 0, 0},
        {300, 0, 0, 400, 0, 0, 0, 0, 0, 0},
        {500, 0, 0, 0, 0, 200, 300, 0, 0, 0},
        {0, 400, 0, 0, 200, 0, 0, 0, 0, 0},
        {0, 0, 0, 200, 0, 100, 0, 0, 200, 0},
        {0, 0, 200, 0, 100, 0, 0, 200, 0, 0},
        {0, 0, 300, 0, 0, 0, 0, 200, 0, 0},
        {0, 0, 0, 0, 0, 200, 200, 0, 0, 300},
        {0, 0, 0, 0, 200, 0, 0, 0, 0, 100},
        {0, 0, 0, 0, 0, 0, 0, 300, 100, 0}
        
    };


    // Copiar os valores da matriz_adjacencias para a matriz Grafo
    for (int i = 0; i < numero_vertice; i++) {
        Grafo[i] = (int *)malloc(numero_vertice * sizeof(int));
        for (int j = 0; j < numero_vertice; j++) {
            Grafo[i][j] = matriz_adjacencias[i][j];
        }
    }

    // Vamos supor que você queira encontrar o caminho mínimo do vértice 1 ao vértice 10 (índices 0 e 9, respectivamente):
    int vertice_origem = 0; // Vértice 1 (índice 0)
    int vertice_destino = 9; // Vértice 10 (índice 9)

    // Aloca memória para os arrays de distância e caminho
    int *distancia = (int *)malloc(numero_vertice * sizeof(int));
    int *caminho = (int *)malloc(numero_vertice * sizeof(int));

    Dijkstra(numero_vertice, vertice_origem, Grafo, distancia, caminho);
    printMenorCaminho(vertice_origem, numero_vertice, distancia, caminho);

    // Libera a memória alocada para o grafo e os arrays
    for (int i = 0; i < numero_vertice; i++) {
        free(Grafo[i]);
    }
    free(Grafo);
    free(distancia);
    free(caminho);

    return 0;
}

void Dijkstra(int numero_vertice, int origem, int **Grafo, int *distancia, int *caminho) {
    bool *visitado = (bool *)malloc(numero_vertice * sizeof(bool));

    for (int i = 0; i < numero_vertice; i++) {
        distancia[i] = INF;
        caminho[i] = -1;
        visitado[i] = false;
    }

    distancia[origem] = 0;

    for (int count = 0; count < numero_vertice - 1; count++) {
        int minDist = INF;
        int minIndex = -1;
        for (int v = 0; v < numero_vertice; v++) {
            if (!visitado[v] && distancia[v] < minDist) {
                minDist = distancia[v];
                minIndex = v;
            }
        }

        visitado[minIndex] = true;

        for (int v = 0; v < numero_vertice; v++) {
            if (!visitado[v] && Grafo[minIndex][v] &&
                distancia[minIndex] + Grafo[minIndex][v] < distancia[v]) {
                distancia[v] = distancia[minIndex] + Grafo[minIndex][v];
                caminho[v] = minIndex;
            }
        }
    }

    free(visitado);
}

void printMenorCaminho(int origem, int numero_vertice, int *distancia, int *caminho) {
    printf("Vertice\t\tDistancia\tCaminho\n");
    for (int i = 0; i < numero_vertice; i++) {
        if (i == origem)
            continue;
        
        printf("%d -> %d\t\t%d\t\t%d ", origem + 1, i + 1, distancia[i], i + 1);
        int caminho_atual = caminho[i];
        while (caminho_atual != -1) {
            printf("<- %d ", caminho_atual + 1);
            caminho_atual = caminho[caminho_atual];
        }
        printf("\n");
    }
}