#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Propietario.h"


void mostrarMenu()
{
    system("cls");

    printf("\nESTACIONAMIENTO>>> Seleccione una opcion: \n");

    printf("\n1- Registrar Propietario \n");
    printf("\n2- Modificar datos de propietario\n");
    printf("\n3- Dar de baja propietario\n");
    printf("\n4- Listar propietarios\n");
    printf("\n5- Salir\n");

    printf("\nLa opcion es: ");
}

void presionarContinuar()
{
    printf("\nPresione cualquier tecla para continuar ");
    getch();
}

/**< INICIALIZA ESTADO EN LIBRE Y ID DE USUARIO EN 0 */
int ePropietario_init (ePropietario propietarios[],int limite)
{
    int retorno = -1;
    int i;

    if(limite > 0 && propietarios != NULL)
    {
        retorno = 0;
        for(i=0; i<limite; i++)
        {
            propietarios[i].estado= LIBRE;
            propietarios[i].idPropietario= 0;
        }
    }
    return retorno;
}

/**< HARDCODEAR DATOS */
void inicializarPropietariosHardCode(ePropietario propietarios[])
{


    int idPropietario[4] = {1,2,3,4};
    char nombre[4][30]= {"Juan","Luis","Maria","Jose"};
    char direccion[4][30]= {"Mitre","Urquiza","Belgrano","Alsina"};
    char numTarjetaCred[4][20]= {"111-111","222-222","333-333","444-444"};

    int i;

    for(i=0; i<4; i++)
    {
        propietarios[i].idPropietario= idPropietario[i];
        propietarios[i].estado = 1;
        strcpy(propietarios[i].nombre, nombre[i]);
        strcpy(propietarios[i].direccion, direccion[i]);
        strcpy(propietarios[i].numTarjetaCred, numTarjetaCred[i]);

    }
}

/**< BUSCA UN LUGAR LIBRE EN EL ARRAY */
int ePropietario_buscarLugarLibre(ePropietario propietarios[], int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && propietarios != NULL)
    {
        retorno = -2;
        for(i=0; i<limite; i++)
        {
            if(propietarios[i].estado == LIBRE)
            {
                retorno = i;
                break;
            }
        }
    }

    if(retorno<0)
    {
        printf("No hay lugar libre\n");
    }

    return retorno;
}

/**< SIGUIENTE ID */
int ePropietario_siguienteId(ePropietario propietarios[],int limite)
{
    int retorno = 0;

    if(limite > 0 && propietarios != NULL)
    {
        for(int i=0; i<limite; i++)
        {
            if(propietarios[i].estado==OCUPADO)
            {
                    if(propietarios[i].idPropietario > retorno)
                    {
                         retorno= propietarios[i].idPropietario;
                    }
            }
        }
    }
    return retorno+1;
}

/**< PIDE UN STRING DE CARACTERES */
void getString(char mensaje[], char input[])
{
    printf("%s", mensaje);
    scanf("%s", input);
}

/**< VALIDA TAMAÑO DE STRING */
void getValidString(char mensaje[], char error[], char input[], int limite)
{
    int j;
    char auxString[limite+200]; //por si se pasa

    getString(mensaje, input);

    j= strlen(input);

    while (j>= limite)
    {
        printf("Ha ingresado %d caracteres\n %s", j, error);
        getString(mensaje, input);

        j= strlen(input);

    }

    strcpy(auxString, input);
}

int pedirNumEntero(char mensaje[])
{
    int numeroEntero;

    printf("%s", mensaje);
    scanf("%d", &numeroEntero);

    return numeroEntero;
}

/**< BUSCA POR ID Y SI LO ENCUENTRA DEVUELVE EL ÍNDICE */
int ePropietario_buscarPorId(ePropietario propietarios[] ,int limite, int id)
{
    int retorno = -1;

    if(limite > 0 && propietarios != NULL)
    {
        retorno = -2;
        for(int i=0; i<limite; i++)
        {
            if(propietarios[i].estado == OCUPADO && propietarios[i].idPropietario == id)
            {
                printf("\nSe encontro el id %d", id);
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/**< DA DE ALTA USUARIOS */
int ePropietario_alta(ePropietario propietarios[], int limite)
{
    int retorno = -1;
    char nombre[50];
    int idPropietario;
    char direccion[50];
    char tarjeta[50];
    int indice;

    if(limite > 0 && propietarios != NULL)
    {
        retorno = -2;
        indice = ePropietario_buscarLugarLibre(propietarios, limite);

        if(indice>= 0)//HAY LUGAR LIBRE EN EL VECTOR
        {
            getValidString("Ingrese nombre: \n", "Ha superado el maximo. ", nombre, 50);
            strcpy(propietarios[indice].nombre, nombre);
            idPropietario= ePropietario_siguienteId(propietarios, limite);
            propietarios[indice].idPropietario = idPropietario;
            getValidString("Ingrese direccion: \n", "Ha superado el maximo. ", direccion, 50);
            strcpy(propietarios[indice].direccion, direccion);
            getValidString("Ingrese numero de tarjeta: \n", "Ha superado el maximo. ", tarjeta, 50);
            strcpy(propietarios[indice].numTarjetaCred, tarjeta);
            propietarios[indice].estado = OCUPADO;
            retorno = 0;
        }
        else
        {
            printf("\n No hay lugar para cargar propietarios");
        }
    }
    return retorno;
}

/**< MUESTRA UN USUARIO */
void mostrarUnPropietario(ePropietario propietario)
{
     printf("\n %s - %d - %s - %s - %d", propietario.nombre, propietario.idPropietario, propietario.direccion, propietario.numTarjetaCred, propietario.estado);
}

/**< LISTA CON BORRADOS */
int mostrarListadoPropietariosConBorrados(ePropietario propietarios[],int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && propietarios != NULL)
    {
        retorno = 0;
        for(i=0; i<limite; i++)
        {
            if(propietarios[i].estado==LIBRE)
            {
                printf("\n[LIBRE]");
            }
            mostrarUnPropietario(propietarios[i]);
        }
    }
    return retorno;
}

/**< MODIFICA TARJETA PROPIETARIO */
int ePropietario_modificacion(ePropietario propietarios[], int limite, int posId)
{
    int retorno= -2;
    char tarjeta[30];

    if(limite > 0 && propietarios != NULL)
    {
        retorno -1;

        if(posId>=0)
        {
            retorno= 0;
            getValidString("\nIngrese Tarjeta: ","\nNumero muy largo", tarjeta, 30);
            strcpy(propietarios[posId].numTarjetaCred, tarjeta);
            propietarios[posId].estado= OCUPADO;

            printf("\nSe modifico tarjeta");

        }
        else
        {
            retorno= -3;
            printf("\nNo se encontro el id ingresado");
        }
    }

    return retorno;

}

/**< BAJA DE USUARIOS */
int ePropietario_baja(ePropietario propietarios[], int limite, int posId)
{
    int retorno= -2;

    if(limite > 0 && propietarios != NULL)
    {
        retorno -1;

        if(posId>=0)
        {
            retorno= 0;
            propietarios[posId].idPropietario= 0;
            propietarios[posId].estado= LIBRE;

            printf("\nSe dio de baja el propietario");

        }
        else
        {
            retorno= -3;
            printf("\nNo se encontro el id ingresado");
        }
    }

    return retorno;
}

/**< MUESTRA LISTA DE USUARIOS */
int mostrarListadoPropietarios(ePropietario propietarios[], int limite)
{
    int retorno = -2;
    int i;

    printf("%s\t %s\t\t %s\t %s\n","\nID","Nombre", "Direccion", "Numero de tarjeta");


    if(limite > 0 && propietarios != NULL)
    {
        for(i=0; i<limite; i++)
        {
            retorno = -1;
            if(propietarios[i].estado==OCUPADO)
            {
                retorno= 0;
                printf("%d\t %s\t\t %s\t\t %s\n", propietarios[i].idPropietario, propietarios[i].nombre, propietarios[i].direccion, propietarios[i].numTarjetaCred);
            }
        }
    }
    return retorno;
}


