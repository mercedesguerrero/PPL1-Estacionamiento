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
    printf("\n5- Ingreso de automovil\n");
    printf("\n6- Egreso de automovil\n");
    printf("\n7- Listado de automoviles\n");
    printf("\n8- Recaudacion Total\n");
    printf("\n9- Recaudacion Total por Marca\n");
    printf("\n10- Listado de automoviles estacionados por propietario\n");
    printf("\n11- Listado de propietarios con automoviles Audi estacionados\n");
    printf("\n12- Listado de automoviles estacionados\n\n");
    printf("\n13- Salir\n");

    printf("\nLa opcion es: ");
}

void presionarContinuar()
{
    printf("\nPresione cualquier tecla para continuar ");
    getch();
}

/**< INICIALIZA ESTADO EN LIBRE Y ID DE USUARIO EN 0 */
int ePropietario_init (ePropietario propietarios[], int limite)
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
        propietarios[i].estado = OCUPADO;
        strcpy(propietarios[i].nombre, nombre[i]);
        strcpy(propietarios[i].direccion, direccion[i]);
        strcpy(propietarios[i].numTarjetaCred, numTarjetaCred[i]);

    }
}

/**< BUSCA UN LUGAR LIBRE EN EL ARRAY */
int ePropietario_buscarLugarLibre(ePropietario propietarios[], int limite)
{
    int retorno = -3;
    int i;
    int posicionLibre = -1; //Guarda la primer posicion con estado LIBRE que encuentra
    int posicionBaja = -1; //Guarda la primer posicion con estado BAJA que encuentra

    if(limite > 0 && propietarios != NULL)
    {
        retorno = -2;
        for(i=0; i<limite; i++)
        {
            if(propietarios[i].estado == LIBRE)
            {
                posicionLibre = i;
                break;
            }
        }
    }

    if(posicionLibre < 0) //No hay posiciones con estado LIBRE, busco la primer posición con estado BAJA
        {
            for(i=0;i<limite;i++)
            {
                if(propietarios[i].estado == BAJA)
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
            if(propietarios[i].estado==OCUPADO || propietarios[i].estado== BAJA)
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

void pedirString(char mensaje[], char input[], int limite)
{
    printf("%s", mensaje);
    gets(input);
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
            fflush(stdin);
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

void ePropietario_mostrarUnoConEstado(ePropietario propietario)
{
    switch(propietario.estado)
    {
    case LIBRE: //No muestro las posiciones con estado LIBRE porque contienen basura
        break;
    case BAJA:
        printf("\n %d - %s - %s - %s - %s", propietario.idPropietario, propietario.nombre, propietario.direccion, propietario.numTarjetaCred, "[BAJA]");
        break;
    case OCUPADO:
        printf("\n %d - %s - %s - %s", propietario.idPropietario, propietario.nombre, propietario.direccion, propietario.numTarjetaCred);
        break;
    default:
        printf("\n %d - %s - %s - %s - %s", propietario.idPropietario, propietario.nombre, propietario.direccion, propietario.numTarjetaCred, "[N/A]");
        break;
    }
}

int ePropietario_mostrarListadoConOcupados(ePropietario propietarios[], int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && propietarios != NULL)
    {
        retorno = 0;
        for(i=0; i<limite; i++)
        {
            if(propietarios[i].estado== OCUPADO)
            {
                retorno = 1;
                //Se muestra al menos un elemento del array
                mostrarUnPropietario(propietarios[i]);
            }
        }

        if(retorno == 0)
        {
            printf("\nNO HAY ELEMENTOS PARA MOSTRAR");
        }
    }
    return retorno;
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
int ePropietario_modificacion(ePropietario propietarios[], int limite)
{
    int retorno= -2;
    int indice;
    int muestraListado;
    ePropietario temporario;
    char confirma[3];
    int cancelaAccion = 0;

    if(limite > 0 && propietarios != NULL)
    {
        retorno -1;

        do
        {
            muestraListado = ePropietario_mostrarListadoConOcupados(propietarios, limite);

            switch(muestraListado)
            {
            case 0:
                printf("\nNo hay propietarios para modificar");
                break;
            case 1:
                temporario.idPropietario = pedirNumEntero("\nIngrese ID del propietario a modificar: ");
                indice = ePropietario_buscarPorId(propietarios, limite, temporario.idPropietario);
                if(indice < 0)
                {
                    printf("No se encontro el ID ingresado. Por favor reingrese\n");
                }
                else
                {
                    temporario = propietarios[indice];

                    retorno = -3;
                    //Modificación de campos
                    do
                    {
                        getValidString("Ingrese numero de tarjeta de credito del propietario: ", "Se ha excedido", temporario.numTarjetaCred, 30);
                        if(strcmp(temporario.numTarjetaCred, "") == 0)
                        {
                            printf("El dato es obligatorio, por favor reingrese\n");
                        }
                    } while(strcmp(temporario.numTarjetaCred, "") == 0);

                    retorno = -4;
                    //Confirmación de la acción por parte del usuario
                    do
                    {
                        printf("\nSe va a modificar:");
                        mostrarUnPropietario(propietarios[indice]);
                        printf("\nPor: ");
                        mostrarUnPropietario(temporario);
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
                        propietarios[indice] = temporario;
                    }
                    else //(retorno = -3 || retorno = -4)
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
            if(propietarios[i].estado==BAJA || propietarios[i].estado==OCUPADO)
            {
                retorno= 0;
                ePropietario_mostrarUnoConEstado(propietarios[i]);
            }
        }
    }
    return retorno;
}

void eIngreso_init(eIngreso listado[],int limite)
{
    int i;
    if(limite > 0 && listado != NULL)
    {
        for(i=0; i<limite; i++)
        {
            listado[i].estado= LUGAR_LIBRE;
            listado[i].idIngreso= 0;
        }
    }
}

int eIngreso_buscarLugarLibre(eIngreso listado[],int limite)
{
    int retorno = -1;
    int i;
    int posicionLibre = -1; //Guarda la primer posicion con estado LIBRE que encuentra

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == LUGAR_LIBRE)
            {
                posicionLibre = i;
                break;
            }
        }

        if(posicionLibre >= 0)
        {
            retorno = posicionLibre; //Retorno la primera posición con estado LIBRE
        }
    }

    return retorno;
}

int eIngreso_siguienteId(eIngreso listado[],int limite)
{
    int retorno = 0;
    int i;
    if(limite > 0 && listado != NULL)
    {
        for(i=0; i<limite; i++)
        {
            if(listado[i].estado == INGRESADO || listado[i].estado == RETIRADO)
            {
                    if(listado[i].idIngreso>retorno)
                    {
                         retorno=listado[i].idIngreso;
                    }

            }
        }
    }

    return retorno+1; //Retorno el mayor ID más 1
}


int eIngreso_buscarPorId(eIngreso listado[] ,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == INGRESADO && listado[i].idIngreso == id)
            {
                retorno = i;
                //Hallé el elemento que buscaba y retorno su indice
                break;
            }
        }
    }
    return retorno;
}

int eIngreso_buscarPorIdAutomovil(eIngreso listado[] ,int limite, int idAutomovil)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == INGRESADO && listado[i].idAutomovil == idAutomovil)
            {
                retorno = i;
                //Hallé el elemento que buscaba y retorno su indice
                break;
            }
        }
    }
    return retorno;
}

void eIngreso_mostrarUno(eIngreso parametro, char nombrePropietario[], char patente[], char marca[])
{
    printf("\n %d - %s - %s - %s", parametro.idIngreso, patente, marca, nombrePropietario);

}

int eIngreso_alta(eIngreso listado[], int limite, int idAutomovil)
{
    int retorno = -1;
    int indice;

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        //Busca lugar libre en el array
        indice = eIngreso_buscarLugarLibre(listado,limite);
        if(indice >= 0)
        {
            retorno = 0;
            //OK
            listado[indice].idIngreso = eIngreso_siguienteId(listado,limite);
            listado[indice].idAutomovil = idAutomovil;
            listado[indice].estado = INGRESADO;
        }
        else //retorno = -2
        {
            printf("No hay espacio suficiente para agregar datos\n");
        }
    }
    return retorno;
}

void eEgreso_init(eEgreso listado[],int limite)
{
    int i;
    if(limite > 0 && listado != NULL)
    {
        for(i=0; i<limite; i++)
        {
            listado[i].estado= E_LIBRE;
            listado[i].idIngreso= 0;
        }
    }
}

int eEgreso_buscarLugarLibre(eEgreso listado[],int limite)
{
    int retorno = -1;
    int i;
    int posicionLibre = -1; //Guarda la primer posicion con estado LIBRE que encuentra

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == E_LIBRE)
            {
                posicionLibre = i;
                break;
            }
        }

        if(posicionLibre >= 0)
        {
            retorno = posicionLibre; //Retorno la primera posición con estado LIBRE
        }
    }

    return retorno;
}

int eEgreso_siguienteId(eEgreso listado[],int limite)
{
    int retorno = 0;
    int i;
    if(limite > 0 && listado != NULL)
    {
        for(i=0; i<limite; i++)
        {
            if(listado[i].estado == OCUPADO)
            {
                    if(listado[i].idEgreso>retorno)
                    {
                         retorno=listado[i].idEgreso;
                    }

            }
        }
    }

    return retorno+1; //Retorno el mayor ID más 1
}


int eEgreso_buscarPorId(eEgreso listado[] ,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == OCUPADO && listado[i].idEgreso == id)
            {
                retorno = i;
                //Hallé el elemento que buscaba y retorno su indice
                break;
            }
        }
    }
    return retorno;
}

void eEgreso_mostrarTicket(char nombrePropietario[], char patenteAutomovil[], char marcaAutomovil[], int horasEstadia, float precioEstadia)
{
    float importeEstadia = (float)horasEstadia * precioEstadia;
    printf("\nNombre del Propietario: %s\nPatente del Automovil: %s\nMarca del Automovil: %s\nValor de la Estadia: %5.2f\n", nombrePropietario, patenteAutomovil, marcaAutomovil, importeEstadia);

}

int eEgreso_alta(eEgreso listado[], int limite, int idIngreso, char nombrePropietario[], char patenteAutomovil[], char marcaAutomovil[], int horasEstadia, float precioEstadia)
{
    int retorno = -1;
    int indice;

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        //Busca lugar libre en el array
        indice = eEgreso_buscarLugarLibre(listado,limite);
        if(indice >= 0)
        {
            retorno = 0; //OK
            eEgreso_mostrarTicket(nombrePropietario, patenteAutomovil, marcaAutomovil, horasEstadia, precioEstadia);
            pausarEjecucion();
            listado[indice].idEgreso = eEgreso_siguienteId(listado,limite);
            listado[indice].idIngreso = idIngreso;
            listado[indice].importe = (float)horasEstadia * precioEstadia;
            listado[indice].estado = OCUPADO;
        }
        else //retorno = -2
        {
            printf("No hay espacio suficiente para agregar datos\n");
        }
    }
    return retorno;
}

int eEgreso_devolverHorasEstadia(void)
{
    int horas;

    srand(time(NULL));

    horas = (rand()%24)+1;

    return horas ;

}


