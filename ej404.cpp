#include <stdlib.h> // Funcion exit
#include <string.h> // Funcion memset
#include <iostream> // Variables cin y cout
#include <list>
#include <limits.h>
#include <stdio.h> // Variables
using namespace std;

#define MAX_NODOS 2000
#define INFINITO INT_MAX

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                      // Numero de nodos del grafo
int naristas;                    // Numero de aristas del grafo
int A;                           // Vertice de salida
int B;                           // Vertice de meta
int C;                           // Vertice de paso
int grafo[MAX_NODOS][MAX_NODOS]; // Matriz de adyacencia
bool visitado[MAX_NODOS];        // Marcas de nodos visitados

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void leeGrafo(void)
// Procedimiento para leer un grafo de la entrada
{
    cin >> nnodos;
    cin >> naristas;
    cin >> A >> B >> C;
    A--;
    B--;
    C--;
    if (nnodos < 0 || nnodos > MAX_NODOS)
    {
        cerr << "Numero de nodos (" << nnodos << ") no valido\n";
        exit(0);
    }
    memset(grafo, 0, sizeof(grafo));
    int vertice1, vertice2, peso;
    for (int i = 0; i < naristas; i++)
    {
        cin >> vertice1 >> vertice2 >> peso;
        grafo[vertice1 - 1][vertice2 - 1] = peso;
        grafo[vertice2 - 1][vertice1 - 1] = peso;
    }
}

//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

/*
    Funcion auxiliar.
    Encuentra el vertice con el menor valor de distancia de entre los
    vertices que todavía no se han incluido en visitado.
*/
int distanciaMin(int distancia[], bool visitado[])
{
    // Initialize min value
    int min = INFINITO, indice_min = 0;

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

/*
    Función que implementa el algoritmo de Dijkstra para encontrar el camino
    mínimo entre todos los vertices y devuelve el camino mínimo entre la meta
    y la salida.
*/
int dijkstra(int salida, int meta)
{
    int distancia[nnodos]; // Distancia minima de los nodos a salida

    bool visitado[nnodos]; // devuelve true si ya se ha procesado un camino desde la salida

    // Initialize all distances as INFINITE and stpSet[] as false
    // Inicializar todas las salidas como INFINITO, hará de infinito,
    // y los visitado como false.
    for (int i = 0; i < nnodos; i++)
    {
        distancia[i] = INFINITO;
        visitado[i] = false;
    }

    // Distancia desde un vertice a si mismo siempre es 0
    distancia[salida] = 0;

    // Camino mínimo a todos los vertices
    for (int count = 0; count < nnodos - 1; count++)
    {
        /*
            Coge el vertice de distancia mínima no procesado.
            Es igual a salida en la primera iteracion.
        */
        int actual = distanciaMin(distancia, visitado);

        // Marca el vertice elegido como procesado
        visitado[actual] = true;

        // Actualizar valor de distancia de los vertices adyacente al vertice actual.
        for (int adyacente = 0; adyacente < nnodos; adyacente++)
            /*
             Actualizamos la distancia solo si:
                1-> no ha sido visitado antes
                2-> existe un camino entre ambos vertices
                3-> el peso total del camino de salida a adyacente a través de actual
                    es menor que su valor actual
            */
            if (!visitado[adyacente] && grafo[actual][adyacente] &&
                distancia[actual] != INFINITO && distancia[actual] + grafo[actual][adyacente] < distancia[adyacente])
            {
                distancia[adyacente] = distancia[actual] + grafo[actual][adyacente];
            }
    }

    return distancia[meta];
}

/*
 Funcion que llama al algoritmo de dijkstra para encontrar la ruta A-C y A-B.
*/
void dijkstraPrincipal()
{
    int distanciaAC = dijkstra(A, C);

    // Si la ruta A-C es imposible, no es necesario calcular la segunda
    if (distanciaAC == INFINITO)
    {
        std::cout << "IMPOSIBLE" << std::endl;
        return;
    }

    int distanciaCB = dijkstra(C, B);

    // Si la ruta C-B es imposible, el camino no existe
    if (distanciaCB == INFINITO)
    {
        std::cout << "IMPOSIBLE" << std::endl;
    }
    else
    {
        // El resultado es la suma de sus partes: (A-C) + (C-B)
        std::cout << (distanciaAC + distanciaCB) << std::endl;
    }
}

int main()
{

    int ncasos;
    cin >> ncasos;
    for (int i = 0; i < ncasos; i++)
    {
        leeGrafo();
        dijkstraPrincipal();
    }

    return 0;
}