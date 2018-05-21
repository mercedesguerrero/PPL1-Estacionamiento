#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Propietario.h"


void mostrarMenu()
{
    system("cls");

    printf("\nESTACIONAMIENTO>>> Seleccione una opcion: \n\n");

    printf("1- Registrar Propietario \n");
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


    int idPropietario[15] = {1,2,3,4};
    char nombre[][20]= {"Juan","Luis","Maria","Jose"};
    char numTarjetaCred[][20]= {"111-111","222-222","333-333","444-444"};
    char direccion[][20]= {"mitre","urquiza","belgrano","alsina"};


    int i;

    for(i=0; i<15; i++)
    {
        propietarios[i].idPropietario=idPropietario[i];
        propietarios[i].estado = 1;
        strcpy(propietarios[i].nombre, nombre[i]);
        strcpy(propietarios[i].numTarjetaCred, numTarjetaCred[i]);
        strcpy(propietarios[i].direccion, direccion[i]);
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
        for(i=0;i<limite;i++)
        {
            if(propietarios[i].estado == LIBRE)
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/**< BUSCA EL MAYOR Y DEVUELVE EL SIGUIENTE */
int ePropietario_siguienteId(ePropietario propietarios[],int limite)
{
    int retorno = 0;
    int i;
    int flag=0;

    if(limite > 0 && propietarios != NULL)
    {
        flag =1;
        for(i=0; i<limite; i++)
        {
            if(propietarios[i].estado == OCUPADO)
            {
                    if(propietarios[i].idPropietario> retorno)
                    {
                         retorno= propietarios[i].idPropietario;
                    }

            }
        }
    }

    if(flag==1)
    {
        retorno= retorno+1; //LE SUMO 1 PARA QUE DE EL SIGUIENTE ID
    }
    if(flag==0)
    {
        retorno=-1;
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

        if(indice== 0)//HAY LUGAR LIBRE EN EL VECTOR
        {
            retorno = -3;
            idPropietario = ePropietario_siguienteId(propietarios, limite);

            if(idPropietario>= 0)//por si hay inconsistencia
            {
                getValidString("Ingrese nombre y apellido: \n", "Ha superado el maximo. ", nombre, 50);
                strcpy(propietarios[indice].nombre, nombre);
                propietarios[indice].idPropietario = idPropietario;
                strcpy(propietarios[indice].direccion, direccion);
                strcpy(propietarios[indice].numTarjetaCred, tarjeta);
                propietarios[indice].estado = OCUPADO;
                retorno = 0;
            }
        }
    }
    return retorno;
}

/**< BUSCA POR ID Y SI LO ENCUENTRA DEVUELVE EL ÍNDICE */
int ePropietario_buscarPorId(ePropietario propietarios[] ,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && propietarios != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(propietarios[i].estado == OCUPADO && propietarios[i].idPropietario == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/**< MUESTRA LISTA DE USUARIOS */
int ePropietario_mostrarlistadoPropietario(ePropietario propietarios[], int limite)
{
    int retorno = -1;
    int i;


    if(limite > 0 && propietarios != NULL)
    {
        retorno = 0;
        for(i=0; i<limite; i++)
        {
            if(propietarios[i].estado==OCUPADO)
            {
                ePropietario_mostrarUno(propietarios[i]);
            }
        }
    }
    return retorno;
}

/**< MUESTRA UN USUARIO */
void ePropietario_mostrarUno(ePropietario propietario)
{
     printf("\n %s - %d - %s - %s - %d", propietario.nombre, propietario.idPropietario, propietario.direccion, propietario.numTarjetaCred, propietario.estado);
}

int ePropietario_mostrarlistadoPropietarioConBorrados(ePropietario propietarios[],int limite)
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
            ePropietario_mostrarUno(propietarios[i]);
        }
    }
    return retorno;
}


/**< DA DE BAJA USUARIOS */
void ePropietario_baja(ePropietario propietarios[], int limite, int id)
{
    int i;

    ePropietario_mostrarlistadoPropietario(propietarios, CANTIDAD);

    printf( "\n \t Seleccione ID a dar de baja");
    scanf("%d", i);//VER ESTO getchar();

    for (i=0; i<limite; i++)
    {
        if(propietarios[i].estado == OCUPADO && propietarios[i].idPropietario == id)
            {
                propietarios[i].idPropietario= 0;
                propietarios[i].estado== LIBRE;
            }
    }
}

/**< PIDE UN STRING DE CARACTERES */
void getString(char mensaje[], char input[])
{
    printf("%s", mensaje);
    scanf("%s", input);
}

/** \brief VALIDA QUE UN STRING DE CARACTERES NO SE EXCEDA DEL LÍMITE
 *
 * \param mensaje a ser mostrado
 * \param mensaje de error
 * \param input Array donde se cargará el texto ingresado
 * \param limite de caracteres
 */

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

