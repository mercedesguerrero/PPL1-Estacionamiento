#include <stdio.h>
#include <stdlib.h>
#include "Propietario.h"
#define TAMPROPIETARIO 50


int main()
{

    char seguir='s';
    int opcion=0;
    int i;


    ePropietario listadoPropietario[TAMPROPIETARIO];

    ePropietario_init(listadoPropietario, TAMPROPIETARIO);


    /*
    ePropietario_mostrarListadoConBorrados(propietario, TAMPROPIETARIO);
    getchar();
    ePropietario_alta(propietario, TAMPROPIETARIO);
    ePropietario_alta(propietario, TAMPROPIETARIO);
    printf( "\n \t cargo dos elementos y muestro el array");
    ePropietario_mostrarListado(propietario, TAMPROPIETARIO);
    ePropietario_baja(propietario, TAMPROPIETARIO, id);
    printf( "\n \t muestro el array con los borrados y vacios");
    ePropietario_mostrarListadoConBorrados(propietario, TAMPROPIETARIO);
    */


    do
    {
        mostrarMenu();
        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                //printf("\nALTA DE PROPIETARIO \n");
                ePropietario_alta(listadoPropietario, TAMPROPIETARIO);
                presionarContinuar();
                break;
            case 2:

                printf("\nMODIFICAR DATOS DEL PROPIETARIO \n");
                presionarContinuar();
                break;
            case 3:
                printf("\nBAJA DEL PROPIETARIO \n");
                presionarContinuar();
                break;
            case 4:
                if(listadoPropietario[i].estado==OCUPADO)
                {
                    ePropietario_mostrarlistadoPropietario(listadoPropietario, TAMPROPIETARIO);
                    system("pause");
                }

                presionarContinuar();

                break;
            case 5:
                seguir = 'n';
                break;
        }
    }while(seguir=='s');

    presionarContinuar();

    return 0;
}
