#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Propietario.h"
#include "Autos.h"

#define TAMPROPIETARIO 50

int eAutomovil_mostrarListado(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);
int eAutomovil_mostrarListadoEstacionados(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);
int eAutomovil_ingreso(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);
int eAutomovil_egreso(eAutomovil[], ePropietario[], eIngreso[], int limiteAutomoviles, int limitePropietarios, int limiteIngresos);
int eIngreso_mostrarListado(eIngreso[], ePropietario[], eAutomovil[], int limiteAutomoviles, int limitePropietarios, int limiteIngresos);
float eEgreso_devolverPrecioEstadia(int marca);
void eIngreso_hardcodeo(eIngreso[], eAutomovil[], int limiteIngresos, int limiteAutomoviles);
void eEgreso_hardcodeo(eEgreso[], eIngreso[], eAutomovil[], int limiteEgresos, int limiteIngresos, int limiteAutomoviles);
int ePropietario_baja(ePropietario[], eEgreso[], eIngreso[], eAutomovil[], int limitePropietarios, int limiteEgresos, int limiteIngresos, int limiteAutomoviles);
float recaudacionMarca(int idMarca, eAutomovil[], eIngreso[], eEgreso[], int limiteAutomoviles, int limiteIngresos, int limiteEgresos);
int ePropietario_mostrarAutomovilesEstacionados(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);
int ePropietario_mostrarAutomovilesEstacionadosAudi(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);


int main()
{

    char seguir='s';
    int opcion=0;
    int i;
    int funcionOK;
    int idAutomovil;
    int idIngreso;
    int posicionIngreso;
    int posicionAutomovil;
    int posicionPropietario;
    int horasEstadia;
    float precioEstadia;
    char nombrePropietario[30];
    char marcaAutomovil[TAM_MARCA];
    char patenteAutomovil[TAM_PATENTE];
    float importeTotal;


    //Declaro array donde guardo los datos de la estructura Propietario
    ePropietario listadoPropietarios[TAMPROPIETARIO];
    eAutomovil listaAutomoviles[LIMITE_AUTOMOVILES];
    eIngreso listaIngresos[LIMITE_INGRESOS];
    eEgreso listaEgresos[LIMITE_EGRESOS];


    //Inicializo el flag de estado junto con hardcodeo de datos
    inicializarPropietariosHardCode(listadoPropietarios);
    eAutomovil_hardcodeo(listaAutomoviles, LIMITE_AUTOMOVILES);
    eIngreso_hardcodeo(listaIngresos, listaAutomoviles, LIMITE_INGRESOS, LIMITE_AUTOMOVILES);
    eEgreso_init(listaEgresos, LIMITE_EGRESOS);
    ePropietario_init(listadoPropietarios, TAMPROPIETARIO);

    do
    {
        mostrarMenu();
        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                funcionOK= ePropietario_alta(listadoPropietarios, TAMPROPIETARIO);
                if(funcionOK == 0)
                {
                    printf("\nAlta de propietario OK");
                }

                presionarContinuar();
                break;
            case 2:
                funcionOK= ePropietario_modificacion(listadoPropietarios, TAMPROPIETARIO);
                if(funcionOK == 0)
                {
                    printf("\nModificacion de propietario OK");
                }

                presionarContinuar();
                break;
            case 3:
                funcionOK = ePropietario_baja(listaPropietarios, listaEgresos, listaIngresos, listaAutomoviles, LIMITE_PROPIETARIOS, LIMITE_EGRESOS, LIMITE_INGRESOS, LIMITE_AUTOMOVILES);
                if(funcionOK == 0)
                {
                    printf("\nBaja de propietario OK");
                }
                presionarContinuar();
                break;
            case 4:
                //mostrarListadoPropietarios(listadoPropietarios, TAMPROPIETARIO);
                funcionOK = ePropietario_mostrarListadoConOcupados(listaPropietarios, LIMITE_PROPIETARIOS);
                if(funcionOK == 1)
                {
                    printf("\nListado de propietarios OK");
                }

                presionarContinuar();

                break;
            case 5:
                idAutomovil = eAutomovil_ingreso(listaAutomoviles, listaPropietarios, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS);
                if(idAutomovil > 0)
                {
                    posicionAutomovil = eAutomovil_buscarPorId(listaAutomoviles, LIMITE_AUTOMOVILES, idAutomovil);
                    funcionOK = eIngreso_alta(listaIngresos, LIMITE_INGRESOS, idAutomovil);
                    if(funcionOK == 0)
                    {
                        listaAutomoviles[posicionAutomovil].estado = ESTACIONADO;
                        printf("\nIngreso de automovil OK");
                    }
                }
                else
                {
                    printf("\nNo se pudo obtener un ID de automovil para ingresar. Por favor reintente");
                }
                break;
            case 6:
                idIngreso = eAutomovil_egreso(listaAutomoviles, listaPropietarios, listaIngresos, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS, LIMITE_INGRESOS);
                if(idIngreso > 0)
                {
                    posicionIngreso = eIngreso_buscarPorId(listaIngresos, LIMITE_INGRESOS, idIngreso);
                    if(posicionIngreso >= 0)
                    {
                        posicionAutomovil = eAutomovil_buscarPorIdEstacionados(listaAutomoviles, LIMITE_AUTOMOVILES, listaIngresos[posicionIngreso].idAutomovil);
                        if(posicionAutomovil >= 0)
                        {
                            posicionPropietario = ePropietario_buscarPorId(listaPropietarios, LIMITE_PROPIETARIOS, listaAutomoviles[posicionAutomovil].idPropietario);
                            if(posicionPropietario >= 0)
                            {
                                strcpy(nombrePropietario, listaPropietarios[posicionPropietario].nombreApellido);
                                strcpy(patenteAutomovil, listaAutomoviles[posicionAutomovil].patente);
                                eAutomovil_retornaMarca(listaAutomoviles[posicionAutomovil].marca, marcaAutomovil);
                                horasEstadia = eEgreso_devolverHorasEstadia();
                                precioEstadia = eEgreso_devolverPrecioEstadia(listaAutomoviles[posicionAutomovil].marca);
                                funcionOK = eEgreso_alta(listaEgresos, LIMITE_EGRESOS, idIngreso, nombrePropietario, patenteAutomovil, marcaAutomovil, horasEstadia, precioEstadia);
                                if(funcionOK == 0)
                                {
                                    listaAutomoviles[posicionAutomovil].estado = NO_ESTACIONADO;
                                    listaIngresos[posicionIngreso].estado = RETIRADO;
                                    printf("\nEgreso de automovil OK");
                                }
                            }
                        }
                    }
                }
                else
                {
                    printf("\nNo se pudo obtener un ID de automovil para egresar. Por favor reintente");
                }
                break;
            case 7:
                funcionOK = eAutomovil_mostrarListado(listaAutomoviles, listaPropietarios, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS);
                if(funcionOK == 1)
                {
                    printf("\nListado de automoviles OK");
                }
                break;
            case 8:
                importeTotal = 0.0;

                for(i = 0; i < 4; i++)
                {
                    importeTotal = importeTotal + recaudacionMarca(i + 1, listaAutomoviles, listaIngresos, listaEgresos, LIMITE_AUTOMOVILES, LIMITE_INGRESOS, LIMITE_EGRESOS);
                }
                printf("\nRecaudacion Total del Estacionamiento: %5.2f", importeTotal);
                break;
            case 9:
                for(i = 0; i < 4; i++)
                {
                    importeTotal = 0.0;
                    importeTotal = importeTotal + recaudacionMarca(i + 1, listaAutomoviles, listaIngresos, listaEgresos, LIMITE_AUTOMOVILES, LIMITE_INGRESOS, LIMITE_EGRESOS);
                    eAutomovil_retornaMarca(i + 1, marcaAutomovil);
                    printf("\nRecaudacion %s: %5.2f", marcaAutomovil, importeTotal);
                }
                break;
            case 10:
                funcionOK = ePropietario_mostrarAutomovilesEstacionados(listaAutomoviles, listaPropietarios, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS);
                if(funcionOK == 1)
                {
                    printf("\nListado de automoviles estacionados por propietario OK");
                }
                break;
            case 11:
                funcionOK = ePropietario_mostrarAutomovilesEstacionadosAudi(listaAutomoviles, listaPropietarios, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS);
                if(funcionOK == 1)
                {
                    printf("\nListado de automoviles estacionados de marca Audi OK");
                }
                break;
            case 12:
                funcionOK = eAutomovil_mostrarListadoEstacionados(listaAutomoviles, listaPropietarios, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS);
                if(funcionOK == 1)
                {
                    printf("\nListado de automoviles estacionados OK");
                }
                break;
            case 13:
                seguir = 'n';
                break;
        }
    }while(seguir=='s');

    presionarContinuar();

    return 0;
}

int eAutomovil_mostrarListado(eAutomovil listaAutomoviles[], ePropietario listaPropietarios[], int limiteAutomoviles, int limitePropietarios)
{
    int retorno = -1;
    int i;
    int posicionPropietario;

    if(limiteAutomoviles > 0 && listaAutomoviles != NULL && listaPropietarios != NULL)
    {
        retorno = 0;
        for(i=0; i<limiteAutomoviles; i++)
        {
            if(listaAutomoviles[i].estado==NO_ESTACIONADO || listaAutomoviles[i].estado==ESTACIONADO)
            {
                retorno = 1;

                posicionPropietario = ePropietario_buscarPorId(listaPropietarios, limitePropietarios, listaAutomoviles[i].idPropietario);
                //Se muestra al menos un elemento del array
                eAutomovil_mostrarUnoConEstado(listaAutomoviles[i], listaPropietarios[posicionPropietario].nombreApellido);
            }
        }

        if(retorno == 0)
        {
            printf("\n*** NO HAY ELEMENTOS PARA MOSTRAR ***");
        }
    }
    return retorno;
}

int eAutomovil_mostrarListadoEstacionados(eAutomovil listaAutomoviles[], ePropietario listaPropietarios[], int limiteAutomoviles, int limitePropietarios)
{
    int retorno = -1;
    int i;
    int posicionPropietario;
    eAutomovil listaOrdenada[LIMITE_AUTOMOVILES];
    //int ordena;

    if(limiteAutomoviles > 0 && listaAutomoviles != NULL && listaPropietarios != NULL)
    {
        retorno = eAutomovil_filtraEstacionados(listaAutomoviles, listaOrdenada, limiteAutomoviles);
        if(retorno == 1)
        {
            retorno = eAutomovil_ordenaPorPatente(listaOrdenada, limiteAutomoviles);
            for(i=0; i<limiteAutomoviles; i++)
            {
                posicionPropietario = ePropietario_buscarPorId(listaPropietarios, limitePropietarios, listaOrdenada[i].idPropietario);
                //Se muestra al menos un elemento del array
                eAutomovil_mostrarUnoConEstado(listaOrdenada[i], listaPropietarios[posicionPropietario].nombreApellido);
            }
        }

        if(retorno == 0)
        {
            printf("\n*** NO HAY ELEMENTOS PARA MOSTRAR ***");
        }
    }
    return retorno;
}

int eAutomovil_ingreso(eAutomovil listaAutomoviles[], ePropietario listaPropietarios[], int limiteAutomoviles, int limitePropietarios)
{
    int idPropietario;
    int indicePropietario;
    int idAutomovil = 0;
    int indiceAutomovil;
    int ingresoAutomovil;
    int limiteEstacionados;
    int muestraListado;

    limiteEstacionados = eAutomovil_validarLimiteEstacionados(listaAutomoviles, LIMITE_AUTOMOVILES);
    if(limiteEstacionados < 0)
    {
        printf("\nNo hay lugar disponible para ingresar automoviles");
    }
    else
    {
        do
        {
            muestraListado = ePropietario_mostrarListadoConOcupados(listaPropietarios, LIMITE_PROPIETARIOS);

            switch(muestraListado)
            {
            case 0:
                printf("\nNo hay propietarios para hacer ingresos"); //retorno = -2
                break;
            case 1:
                idPropietario = pedirEnteroSinValidar("\nIngrese ID del propietario a hacer el ingreso: ");
                indicePropietario = ePropietario_buscarPorId(listaPropietarios, LIMITE_PROPIETARIOS, idPropietario);
                if(indicePropietario < 0)
                {
                    printf("No se encontro el ID ingresado. Por favor reingrese\n");
                }
                break;
            default:
                printf("\Error al listar...\n"); //retorno = -2
                break;
            }
        } while(indicePropietario < 0 && muestraListado == 1);

        do
        {
            muestraListado = eAutomovil_mostrarListadoPropietario(listaAutomoviles, LIMITE_AUTOMOVILES, idPropietario, listaPropietarios[indicePropietario].nombreApellido);

            if(muestraListado == 1)
            {
                idAutomovil = pedirEnteroSinValidar("\nIngrese ID del automovil del propietario a hacer el ingreso, o 0 para ingresar un nuevo automovil: ");
            }
            else
            {
                printf("\n"); //Hago retorno de carro para separar mensajes en pantalla en caso que no haya automóviles
            }

            /*
            Si el propietario ya tiene automóviles ingresados pero quiere ingresar uno nuevo
            ==> el if entra por idAutomovil == 0
            Pero si el propietario no tiene ningún automóvil ingresado el sistema va a pedir directamente
            que el operador ingrese un automóvil para el propietario
            ==> el if entra por muestraListado == 0 ya que dicha función devuelve cero si no hay automóviles para mostrar
            */
            if(idAutomovil == 0 || muestraListado == 0)
            {
                ingresoAutomovil = eAutomovil_alta(listaAutomoviles, LIMITE_AUTOMOVILES, idPropietario, listaPropietarios[indicePropietario].nombreApellido);
                if(ingresoAutomovil == 0)
                {
                    indiceAutomovil = eAutomovil_ultimoIngresado(listaAutomoviles, LIMITE_AUTOMOVILES);
                    idAutomovil = listaAutomoviles[indiceAutomovil].idAutomovil;
                    printf("\nAlta de automovil OK");
                }
                else
                {
                    indiceAutomovil = -1;
                    printf("Por favor reingrese\n");
                }
            }
            else
            {
                indiceAutomovil = eAutomovil_buscarPorId(listaAutomoviles, LIMITE_AUTOMOVILES, idAutomovil);
                if(indiceAutomovil < 0)
                {
                    printf("No se encontro el ID ingresado. Por favor reingrese\n");
                }
            }
        } while(indiceAutomovil < 0 && muestraListado == 1);
    }

    return idAutomovil;
}

int eIngreso_mostrarListado(eIngreso listaIngresos[], ePropietario listaPropietarios[], eAutomovil listaAutomoviles[], int limiteIngresos, int limitePropietarios, int limiteAutomoviles)
{
    int retorno = -1;
    int i;
    int posicionAutomovil;
    int posicionPropietario;
    char nombrePropietario[TAM_NOMBRE_APELLIDO];
    char patente[TAM_PATENTE];
    char marca[TAM_MARCA];

    if(limiteIngresos > 0 && listaIngresos != NULL)
    {
        retorno = 0;
        for(i=0; i<limiteIngresos; i++)
        {
            if(listaIngresos[i].estado==INGRESADO)
            {
                //Busco el ID del Automóvil en la entidad correspondiente
                posicionAutomovil = eAutomovil_buscarPorIdEstacionados(listaAutomoviles, limiteAutomoviles, listaIngresos[i].idAutomovil);
                if(posicionAutomovil >= 0) //Si encuentro el ID del Automóvil
                {
                    posicionPropietario = ePropietario_buscarPorId(listaPropietarios, limitePropietarios, listaAutomoviles[posicionAutomovil].idPropietario);
                    if(posicionPropietario >= 0) //Si encuentro el ID del Propietario
                    {
                        retorno = 1;
                        strcpy(nombrePropietario, listaPropietarios[posicionPropietario].nombreApellido); //Nombre del Propietario
                        strcpy(patente, listaAutomoviles[posicionAutomovil].patente); //Patente del Automóvil
                        eAutomovil_retornaMarca(listaAutomoviles[posicionAutomovil].marca, marca); //Marca del Automóvil

                        //Se muestra al menos un elemento del array
                        eIngreso_mostrarUno(listaIngresos[i], nombrePropietario, patente, marca);
                    }
                }

            }
        }

        if(retorno == 0)
        {
            printf("\n*** NO HAY ELEMENTOS PARA MOSTRAR ***");
        }
    }
    return retorno;
}

int eAutomovil_egreso(eAutomovil listaAutomoviles[], ePropietario listaPropietarios[], eIngreso listaIngresos[], int limiteAutomoviles, int limitePropietarios, int limiteIngresos)
{
    int idIngreso;
    int indiceIngreso;
    int muestraListado;

    do
    {
        muestraListado = eIngreso_mostrarListado(listaIngresos, listaPropietarios, listaAutomoviles, limiteIngresos, limitePropietarios, limiteAutomoviles);

        switch(muestraListado)
        {
        case 0:
            printf("\nNo hay propietarios para hacer egresos"); //retorno = -2
            break;
        case 1:
            idIngreso = pedirEnteroSinValidar("\nIngrese ID del ingreso, para efectuar su salida: ");
            indiceIngreso = eIngreso_buscarPorId(listaIngresos, LIMITE_INGRESOS, idIngreso);
            if(indiceIngreso < 0)
            {
                printf("No se encontro el ID ingresado. Por favor reingrese\n");
            }
            break;
        default:
            printf("\Error al listar...\n"); //retorno = -2
            break;
        }
    } while(indiceIngreso < 0 && muestraListado == 1);

    return idIngreso;
}


float eEgreso_devolverPrecioEstadia(int marca)
{
    float precioEstadia;

    switch(marca)
    {
    case ALPHA_ROMEO:
        precioEstadia = IMPORTE_ALPHA_ROMEO;
        break;
    case FERRARI:
        precioEstadia = IMPORTE_FERRARI;
        break;
    case AUDI:
        precioEstadia = IMPORTE_AUDI;
        break;
    default:
        precioEstadia = IMPORTE_OTRO;
    }

    return precioEstadia;
}

void eIngreso_hardcodeo(eIngreso listaIngresos[], eAutomovil listaAutomoviles[], int limiteIngresos, int limiteAutomoviles)
{
    int i;
    int id[10]= {1,2,3,4,5,6,7,8,9,10};
    int posicionAutomovil;

    eIngreso_init(listaIngresos, limiteIngresos);

    for(i = 0; i < 10; i++)
    {
        listaIngresos[i].idIngreso = id[i];
        listaIngresos[i].idAutomovil = id[i];
        listaIngresos[i].estado = INGRESADO;
        //Cambio estado en la entidad Automovil
        posicionAutomovil = eAutomovil_buscarPorId(listaAutomoviles, limiteAutomoviles, listaIngresos[i].idAutomovil);
        listaAutomoviles[posicionAutomovil].estado = ESTACIONADO;
    }
}

void eEgreso_hardcodeo(eEgreso listaEgresos[], eIngreso listaIngresos[], eAutomovil listaAutomoviles[], int limiteEgresos, int limiteIngresos, int limiteAutomoviles)
{
    int i;
    int id[10]= {1,2,3,4,5,6,7,8,9,10};
    float importe[10]= {100,200,100,300,100,100,200,200,100,100};
    int posicionIngreso;
    int posicionAutomovil;

    eEgreso_init(listaEgresos, limiteEgresos);

    for(i = 0; i < 10; i++)
    {
        listaEgresos[i].idEgreso = id[i];
        listaEgresos[i].idIngreso = id[i];
        listaEgresos[i].importe = importe[i];
        listaEgresos[i].estado = OCUPADO;
        //Cambio estado en la entidad Ingreso
        posicionIngreso = eIngreso_buscarPorId(listaIngresos, limiteIngresos, listaEgresos[i].idIngreso);
        listaIngresos[posicionIngreso].estado = RETIRADO;
        //Cambio estado en la entidad Automovil
        posicionAutomovil = eAutomovil_buscarPorIdEstacionados(listaAutomoviles, limiteAutomoviles, listaIngresos[posicionIngreso].idAutomovil);
        listaAutomoviles[posicionAutomovil].estado = NO_ESTACIONADO;
    }
}

int ePropietario_baja(ePropietario listaPropietarios[], eEgreso listaEgresos[], eIngreso listaIngresos[], eAutomovil listaAutomoviles[], int limitePropietarios, int limiteEgresos, int limiteIngresos, int limiteAutomoviles)
{
    int retorno = -1;
    int indice;
    int muestraListado;
    int id;
    char confirma[3];
    int cancelaAccion = 0;
    int posicionAutomovil;
    int posicionIngreso;
    char marcaAutomovil[TAM_MARCA];
    int horasEstadia;
    float precioEstadia;
    float importeTotal = 0.0;

    if(limitePropietarios > 0 && listaPropietarios != NULL)
    {
        retorno = -2;
        do
        {
            muestraListado = ePropietario_mostrarListadoConOcupados(listaPropietarios, limitePropietarios);

            switch(muestraListado)
            {
            case 0:
                printf("\nNo hay propietarios para dar de baja"); //retorno = -2
                break;
            case 1:
                id = pedirEnteroSinValidar("\nIngrese ID del propietario a dar de baja: ");
                indice = ePropietario_buscarPorId(listaPropietarios, limitePropietarios, id);
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
                        ePropietario_mostrarUno(listaPropietarios[indice]);
                        pedirString("\nConfirma esta accion? (S/N): ", confirma, 3);
                        if(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0)
                        {
                            printf("Debe ingresar S o N. Por favor reingrese\n");
                        }
                    } while(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0);

                    if(stricmp(confirma, "S") == 0)
                    {
                        do //Doy de baja los automóviles estacionados del propietario
                        {
                            posicionAutomovil = eAutomovil_buscarPorIdPropietario(listaAutomoviles, limiteAutomoviles, id);
                            do //doy de baja el ingreso del automóvil, si lo hubiere
                            {
                                posicionIngreso = eIngreso_buscarPorIdAutomovil(listaIngresos, limiteIngresos, listaAutomoviles[posicionAutomovil].idAutomovil);
                                if(posicionIngreso >= 0) //Hago el egreso
                                {
                                    eAutomovil_retornaMarca(listaAutomoviles[posicionAutomovil].marca, marcaAutomovil);
                                    horasEstadia = eEgreso_devolverHorasEstadia();
                                    precioEstadia = eEgreso_devolverPrecioEstadia(listaAutomoviles[posicionAutomovil].marca);
                                    importeTotal = importeTotal + (horasEstadia * precioEstadia);
                                    retorno = eEgreso_alta(listaEgresos, limiteEgresos, listaIngresos[posicionIngreso].idIngreso, listaPropietarios[indice].nombreApellido, listaAutomoviles[posicionAutomovil].patente, marcaAutomovil, horasEstadia, precioEstadia);

                                    if(retorno == 0) //Si la baja fue satisfactoria
                                    {
                                        listaIngresos[posicionIngreso].estado = RETIRADO;
                                    }
                                }
                            } while(posicionIngreso >= 0);

                            listaAutomoviles[posicionAutomovil].estado = BAJA;
                        } while(posicionAutomovil >= 0);

                        printf("\nImporte total a abonar por el Propietario: %5.2f", importeTotal);
                        retorno = 0; //OK
                        listaPropietarios[indice].estado = BAJA;
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

float recaudacionMarca(int idMarca, eAutomovil listaAutomoviles[], eIngreso listaIngresos[], eEgreso listaEgresos[], int limiteAutomoviles, int limiteIngresos, int limiteEgresos)
{
    float importeTotal = 0.0;
    int i;
    int j;
    int k;

    if(limiteAutomoviles > 0 && listaAutomoviles != NULL)
    {
        for(i = 0; i < limiteAutomoviles; i++)
        {
            if(listaAutomoviles[i].marca == idMarca)
            {
                for(j = 0; j < limiteIngresos; j++)
                {
                    if(listaIngresos[j].idAutomovil == listaAutomoviles[i].idAutomovil)
                    {
                        for(k = 0; k < limiteEgresos; k++)
                        {
                            if(listaEgresos[k].idIngreso == listaIngresos[j].idIngreso)
                            {
                                importeTotal = importeTotal + listaEgresos[k].importe;
                            }
                        }
                    }
                }
            }
        }
    }

    return importeTotal;
}

int ePropietario_mostrarAutomovilesEstacionados(eAutomovil listaAutomoviles[], ePropietario listaPropietarios[], int limiteAutomoviles, int limitePropietarios)
{
    int retorno = -1;
    int i;
    int posicionPropietario;
    int idPropietario;
    int muestraListado;

    if(limiteAutomoviles > 0 && listaAutomoviles != NULL && listaPropietarios != NULL)
    {
        retorno = 0;
        //Muestro listado de propietarios
        muestraListado = ePropietario_mostrarListadoConOcupados(listaPropietarios, limitePropietarios);
        //El usuario elige el propietario del cual quiere ver los automóviles que tiene estacionados
        if(muestraListado == 1) //Sólo si hay propietarios que mostrar
        {
            do //Pido ingreso de un ID de propietario válido
            {
                idPropietario = pedirEnteroSinValidar("\nIngrese ID del Propietario a listar los automoviles estacionados: ");
                posicionPropietario = ePropietario_buscarPorId(listaPropietarios, limitePropietarios, idPropietario);
                if(posicionPropietario < 0)
                {
                    printf("No se encontro el ID ingresado. Por favor reingrese\n");
                }
            } while(posicionPropietario < 0);

            for(i=0; i<limiteAutomoviles; i++)
            {
                if(listaAutomoviles[i].estado == ESTACIONADO && listaAutomoviles[i].idPropietario == idPropietario)
                {
                    retorno = 1;

                    //Se muestra al menos un elemento del array
                    eAutomovil_mostrarUnoConEstado(listaAutomoviles[i], listaPropietarios[posicionPropietario].nombreApellido);
                }
            }

            if(retorno == 0)
            {
                printf("\n*** NO HAY ELEMENTOS PARA MOSTRAR ***");
            }
        }
    }
    return retorno;
}

int ePropietario_mostrarAutomovilesEstacionadosAudi(eAutomovil listaAutomoviles[], ePropietario listaPropietarios[], int limiteAutomoviles, int limitePropietarios)
{
    int retorno = -1;
    int i;
    int posicionPropietario;

    if(limiteAutomoviles > 0 && listaAutomoviles != NULL && listaPropietarios != NULL)
    {
        retorno = 0;
        for(i=0; i<limiteAutomoviles; i++)
        {
            if(listaAutomoviles[i].estado == ESTACIONADO && listaAutomoviles[i].marca == AUDI)
            {
                retorno = 1;
                posicionPropietario = ePropietario_buscarPorId(listaPropietarios, limitePropietarios, listaAutomoviles[i].idPropietario);
                if(posicionPropietario >= 0)
                {
                    eAutomovil_mostrarUnoConEstado(listaAutomoviles[i], listaPropietarios[posicionPropietario].nombreApellido);
                }
            }
        }

        if(retorno == 0)
        {
            printf("\n*** NO HAY ELEMENTOS PARA MOSTRAR ***");
        }
    }
    return retorno;
}
