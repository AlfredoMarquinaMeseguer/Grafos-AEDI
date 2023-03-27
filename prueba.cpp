// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
#include <stdlib.h> // Funcion exit
#include <string.h> // Funcion memset
#include <iostream> // Variables cin y cout
#include <list>
#include <limits.h>
#include <stdio.h>

// Máximo numero de vertices que puede tener un grafo
#define MAX_NODOS 9

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                  // Numero de nodos del grafo
int naristas;                // Numero de aristas del grafo
int grafo[MAX_NODOS][MAX_NODOS] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                       {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                       {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                       {0, 0, 2, 0, 0, 0, 6, 7, 0}};
// Matriz de adyacencia
bool visitado[MAX_NODOS];    // Marcas de nodos visitados

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int distanciaMin(int distancia[], bool visitado[])
{
    // Initialize min value
    int min = INT_MAX, indice_min;

    for (int v = 0; v < nnodos; v++)
    {
        if (visitado[v] == false && distancia[v] <= min)
        {
            min = distancia[v];
            indice_min = v;
        }
    }
    return indice_min;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < MAX_NODOS; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
int dijkstra(int salida, int meta)
{
    int distancia[nnodos]; // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool visitado[nnodos]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < MAX_NODOS; i++)
    {
        distancia[i] = INT_MAX;
        visitado[i] = false;
    }

    // Distancia desde un vertice a si mismo siempre es 0
    distancia[salida] = 0;

    // Camino mínimo a todos los vertices
    for (int count = 0; count < nnodos - 1; count++)
    {
        /*
            Coge el vertice de distancia minima no procesado.
            Es igual a salida en la primera iteracion.
        */
        int actual = distanciaMin(distancia, visitado);

        // Marca el vertice elegido como procesado
        visitado[actual] = true;

        // Actualizar valor de distancia de los vertices adyacente al vertice actual.
        for (int adyacente = 0; adyacente < MAX_NODOS; adyacente++)
            /*
             Actualizamos la distancia solo si:
                1-> no ha sido visitado antes
                2-> existe un camino entre ambos vertices
                3-> el peso total del camino de salida a adyacente a través de actual
                    es menor que su valor actual
            */
            if (!visitado[adyacente] && grafo[actual][adyacente] &&
                distancia[actual] != INT_MAX && distancia[actual] + grafo[actual][adyacente] < distancia[adyacente])
            {
                distancia[adyacente] = distancia[actual] + grafo[actual][adyacente];
            }
    }

    // print the constructed distance array
    printSolution(distancia, MAX_NODOS);

    return distancia[meta];
}

int main()
{
    /* Grafo ejemplo */
    nnodos = MAX_NODOS;
    int graph[MAX_NODOS][MAX_NODOS] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                       {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                       {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                       {0, 0, 2, 0, 0, 0, 6, 7, 0}};

    int distancia = dijkstra(0, 6);

    std::cout << distancia << std::endl;

    return 0;
}