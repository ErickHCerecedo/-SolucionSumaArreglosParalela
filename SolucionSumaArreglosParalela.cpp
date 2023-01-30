/*********************************************
* Programa: SolucionSumaArreglosParalela     
* Autor: Erick de Jesus Hernández Cerecedo
* ID: A01066428
* Fecha: 29/01/2023
*********************************************/
#include <iostream>
#include <stdlib.h>
using namespace std;

#ifdef _OPENMP
	#include <omp.h>
#else
	#define omp_get_thread_num() 0
#endif

void setArray(int *pointer, int size); // Prototipo de la funcion que llena arreglos
void showArray(int *pointer, int size);

int main()
{
    cout << "Estableciendo el tamano de los arreglos!\n";
    int size;           // Almacena el tamaño de los arreglos 
    int *A, *B, *R;     // Puntero a los arreglos
    int hilos=2, tid;     // Numero hilos e id hilo (threads)
    int threads[hilos];
    omp_set_num_threads(hilos);

    /* Estableciendo tamaño de arreglos por el usuario */ 
    cout << "Tamano de los arreglos: ";
	cin >> size; 

    /* Dispocicion de espacio en memoria para los arreglos */ 
    A = (int*)malloc(sizeof(int)*size);
    B = (int*)malloc(sizeof(int)*size);
    R = (int*)malloc(sizeof(int)*size);

    /* Llenado aleatorio de los arreglos A y B */
    setArray(A, size);
    setArray(B, size);

    /* Paralelizacion con OMP*/
    #pragma omp parallel
    {   
        int tid = omp_get_thread_num();
        threads[tid] = 0;

        /* Comienza paralelizacion de ciclo for*/
        #pragma omp for
        for(int i=0;i<size;i++)
        {
            R[i] = A[i]+B[i];
        }  
    }
    
    cout << "\nArreglo A: ";
    showArray(A, size);
    cout << "\nArreglo B: ";
    showArray(B, size);
    cout << "\nArreglo R: ";
    showArray(R, size);


    free(A);        

    return 0;
}

void setArray(int *pointer, int size)
{
    for(int i=0;i<size;i++)
    {
        pointer[i] = rand() % 101;
    }
}

void showArray(int *pointer, int size)
{
    for(int i=0;i<size;i++)
    {
        printf(" %d",pointer[i]);
    }
}