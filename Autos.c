#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Autos.h"

void eAutomovil_init(eAutomovil listado[],int limite)
{
    int i;
    if(limite > 0 && listado != NULL)
    {
        for(i=0; i<limite; i++)
        {
            listado[i].estado= LIBRE;
            listado[i].idAutomovil= 0;
        }
    }
}

void eAutomovil_hardcodeo(eAutomovil listado[],int limite)
{
    int i;
    int id[10]= {1,2,3,4,5,6,7,8,9,10};
    char patente[10][20]= {"AAA","CCC","DDD","BBB","ZZZ","III","HHH","EEE","FFF","GGG"};
    int marca[10]= {1,3,3,2,2,3,3,4,3,1};
    int propietario[10]= {2,1,2,1,3,3,4,1,4,3};

    eAutomovil_init(listado, limite);

    for(i = 0; i < 10; i++)
    {
        listado[i].idAutomovil = id[i];
        strcpy(listado[i].patente, patente[i]);
        listado[i].marca = marca[i];
        listado[i].idPropietario = propietario[i];
        listado[i].estado = NO_ESTACIONADO;
    }
}
int eAutomovil_buscarLugarLibre(eAutomovil listado[],int limite)
{
    int retorno = -1;
    int i;
    int posicionLibre = -1; //Guarda la primer posicion con estado LIBRE que encuentra
    int posicionBaja = -1; //Guarda la primer posicion con estado BAJA que encuentra

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == LIBRE)
            {
                posicionLibre = i;
                break;
            }
        }

        if(posicionLibre < 0) //No hay posiciones con estado LIBRE, busco la primer posición con estado BAJA
        {
            for(i=0;i<limite;i++)
            {
                if(listado[i].estado == BAJA)
                {
                    posicionBaja = i;
                    break;
                }
            }

            if(posicionBaja >= 0)
            {
                retorno = posicionBaja; //Retorno la primera posición con estado BAJA
            }
        }
        else
        {
            retorno = posicionLibre; //Retorno la primera posición con estado LIBRE
        }
    }

    return retorno;
}

int eAutomovil_siguienteId(eAutomovil listado[],int limite)
{
    int retorno = 0;
    int i;
    if(limite > 0 && listado != NULL)
    {
        for(i=0; i<limite; i++)
        {
            if(listado[i].estado == NO_ESTACIONADO || listado[i].estado == BAJA || listado[i].estado == ESTACIONADO) //Tengo en cuenta las bajas lógicas para no duplicar id al rehabilitar
            {
                    if(listado[i].idAutomovil>retorno)
                    {
                         retorno=listado[i].idAutomovil;
                    }

            }
        }
    }

    return retorno+1; //Retorno el mayor ID más 1
}

int eAutomovil_ultimoIngresado(eAutomovil listado[],int limite)
{
    int retorno = -1;
    int i;
    int mayorId;
    int posicionMayorId;
    int flag = 0;

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == NO_ESTACIONADO && (listado[i].idAutomovil > mayorId || flag == 0))
            {
                flag = 1;
                posicionMayorId = i;
                mayorId = listado[i].idAutomovil;
            }
        }

        if(flag == 1)
        {
            retorno = posicionMayorId;
        }
    }
    return retorno;
}

int eAutomovil_buscarPorId(eAutomovil listado[] ,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == NO_ESTACIONADO && listado[i].idAutomovil == id)
            {
                retorno = i;
                //Hallé el elemento que buscaba y retorno su indice
                break;
            }
        }
    }
    return retorno;
}

int eAutomovil_buscarPorIdEstacionados(eAutomovil listado[] ,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == ESTACIONADO && listado[i].idAutomovil == id)
            {
                retorno = i;
                //Hallé el elemento que buscaba y retorno su indice
                break;
            }
        }
    }
    return retorno;
}

int eAutomovil_buscarPorIdPropietario(eAutomovil listado[] ,int limite, int idPropietario)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if((listado[i].estado == ESTACIONADO || listado[i].estado == NO_ESTACIONADO) && listado[i].idPropietario == idPropietario)
            {
                retorno = i;
                //Hallé el elemento que buscaba y retorno su indice
                break;
            }
        }
    }
    return retorno;
}

int eAutomovil_validarLimiteEstacionados(eAutomovil listado[],int limite)
{
    int retorno = -1;
    int cantidadEstacionados = 0;
    int i;

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i = 0; i < limite; i++)
        {
            if(listado[i].estado == ESTACIONADO)
            {
                cantidadEstacionados++;
            }
        }

        if(cantidadEstacionados < LIMITE_ESTACIONADOS)
        {
            retorno = 0; //OK
        }
    }

    return retorno;
}

void eAutomovil_mostrarUno(eAutomovil parametro, char nombrePropietario[])
{
    char nombreMarca[TAM_MARCA];

    eAutomovil_retornaMarca(parametro.marca, nombreMarca); //Devuelve el nombre de la marca.

    printf("\n %d - %s - %s - %s", parametro.idAutomovil, parametro.patente, nombreMarca, nombrePropietario);

}

void eAutomovil_mostrarUnoConEstado(eAutomovil parametro, char nombrePropietario[])
{
    char nombreMarca[TAM_MARCA];

    eAutomovil_retornaMarca(parametro.marca, nombreMarca); //Devuelve el nombre de la marca.

    switch(parametro.estado)
    {
    case LIBRE: //No muestro las posiciones con estado LIBRE porque contienen basura
        break;
    case BAJA:
        printf("\n %d - %s - %s - %s - %s", parametro.idAutomovil, parametro.patente, nombreMarca, nombrePropietario, "[BAJA]");
        break;
    case NO_ESTACIONADO:
        printf("\n %d - %s - %s - %s", parametro.idAutomovil, parametro.patente, nombreMarca, nombrePropietario);
        break;
    case ESTACIONADO:
        printf("\n %d - %s - %s - %s - %s", parametro.idAutomovil, parametro.patente, nombreMarca, nombrePropietario, "[ESTACIONADO]");
        break;
    default:
        printf("\n %d - %s - %s - %s - %s", parametro.idAutomovil, parametro.patente, nombreMarca, nombrePropietario, "[N/A]");
        break;
    }
}

int eAutomovil_mostrarListadoPropietario(eAutomovil listado[], int limite, int idPropietario, char nombrePropietario[])
{
    int retorno = -1;
    int i;

    if(limite > 0 && listado != NULL)
    {
        retorno = 0;
        for(i=0; i<limite; i++)
        {
            if(listado[i].estado==NO_ESTACIONADO && listado[i].idPropietario == idPropietario)
            {
                retorno = 1;

                //Se muestra al menos un elemento del array
                eAutomovil_mostrarUno(listado[i], nombrePropietario);
            }
        }

        if(retorno == 0)
        {
            printf("\n*** NO HAY ELEMENTOS PARA MOSTRAR ***");
        }
    }
    return retorno;
}

int eAutomovil_alta(eAutomovil listado[], int limite, int idPropietario, char nombrePropietario[])
{
    int retorno = -1;
    eAutomovil temporario;
    int indice;
    char confirma[3];

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        //Busca lugar libre en el array
        indice = eAutomovil_buscarLugarLibre(listado,limite);
        if(indice >= 0)
        {
            retorno = -3;
            //Campos con valores iniciales calculados
            temporario.idAutomovil = eAutomovil_siguienteId(listado,limite);
            temporario.idPropietario = idPropietario;
            temporario.estado = NO_ESTACIONADO;

            retorno = -4;
            //Campos con valores pedidos al usuario
            do
            {
                pedirString("Ingrese patente del automovil: ", temporario.patente, TAM_PATENTE);
                if(strcmp(temporario.patente, "") == 0)
                {
                    printf("El dato es obligatorio, por favor reingrese\n");
                }
            } while(strcmp(temporario.patente, "") == 0);

            temporario.marca = pedirEntero("Ingrese marca del automovil (1)ALPHA_ROMEO (2)FERRARI (3)AUDI (4)OTRO: ", 1, 4);

            retorno = -5;
            //Confirmación de la acción por parte del usuario
            do
            {
                printf("\nSe va a dar de alta:");
                eAutomovil_mostrarUno(temporario, nombrePropietario);
                pedirString("\nConfirma esta accion? (S/N): ", confirma, 3);
                if(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0)
                {
                    printf("Debe ingresar S o N. Por favor reingrese\n");
                }
            } while(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0);

            if(stricmp(confirma, "S") == 0)
            {
                retorno = 0;
                //OK
                listado[indice] = temporario;
            }
            else //retorno = -5
            {
                printf("Accion cancelada por el usuario\n");
            }
        }
        else //retorno = -2
        {
            printf("No hay espacio suficiente para agregar datos\n");
        }
    }
    return retorno;
}

/*
int ePropietario_baja(ePropietario listado[],int limite)
{
    int retorno = -1;
    int indice;
    int muestraListado;
    int id;
    char confirma[3];
    int cancelaAccion = 0;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        do
        {
            muestraListado = ePropietario_mostrarListadoConOcupados(listado, limite);
            switch(muestraListado)
            {
            case 0:
                printf("\nNo hay propietarios para dar de baja"); //retorno = -2
                break;
            case 1:
                id = pedirEnteroSinValidar("\nIngrese ID del propietario a dar de baja: ");
                indice = ePropietario_buscarPorId(listado, limite, id);
                if(indice < 0)
                {
                    printf("No se encontro el ID ingresado. Por favor reingrese\n");
                }
                else
                {
                    retorno = -3;
                    //Confirmación de la acción por parte del usuario
                    do
                    {
                        printf("\nSe va a dar de baja:");
                        ePropietario_mostrarUno(listado[indice]);
                        pedirString("\nConfirma esta accion? (S/N): ", confirma, 3);
                        if(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0)
                        {
                            printf("Debe ingresar S o N. Por favor reingrese\n");
                        }
                    } while(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0);
                    if(stricmp(confirma, "S") == 0)
                    {
                        retorno = 0;
                        //OK
                        listado[indice].estado = BAJA;
                    }
                    else //retorno = -3
                    {
                        printf("Accion cancelada por el usuario\n");
                        cancelaAccion = 1;
                    }
                }
                break;
            default:
                printf("\Error al listar...\n"); //retorno = -2
                break;
            }
        } while(indice < 0 && muestraListado == 1 && cancelaAccion == 0);
    }
    return retorno;
}
*/
void eAutomovil_retornaMarca(int marca, char nombreMarca[])
{
    switch(marca)
    {
    case ALPHA_ROMEO:
        strcpy(nombreMarca, "ALPHA_ROMEO");
        break;
    case FERRARI:
        strcpy(nombreMarca, "FERRARI");
        break;
    case AUDI:
        strcpy(nombreMarca, "AUDI");
        break;
    case OTRO:
        strcpy(nombreMarca, "OTRO");
        break;
    default:
        strcpy(nombreMarca, "N/A");
        break;
    }
}

int eAutomovil_ordenaPorPatente(eAutomovil listado[], int limite)
{
    int i;
    int j;
    eAutomovil auxiliar;
    int retorno = 0;

    if(limite > 0 && listado != NULL)
    {
        retorno = 1;

        for(i = 0; i < limite - 1; i++)
        {
            for(j = i + 1; j < limite; j++)
            {
                if(stricmp(listado[i].patente, listado[j].patente) > 0)
                {
                    auxiliar = listado[i];
                    listado[i] = listado[j];
                    listado[j] = auxiliar;
                }
            }
        }
    }

    return retorno;
}

int eAutomovil_filtraEstacionados(eAutomovil listaOrigen[], eAutomovil listaDestino[], int limite)
{
    int i;
    int retorno = -1;
    int posicionDestino = 0;

    eAutomovil_init(listaDestino, limite);

    if(limite > 0 && listaOrigen != NULL)
    {
        retorno = 0;

        for(i = 0; i < limite; i++)
        {
            if(listaOrigen[i].estado == ESTACIONADO)
            {
                retorno = 1;
                listaDestino[posicionDestino] = listaOrigen[i];
                posicionDestino++;
            }
        }
    }

    return retorno;
}
