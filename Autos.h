#ifndef AUTOS_H_INCLUDED
#define AUTOS_H_INCLUDED

#define LIMITE_AUTOMOVILES 200
#define LIMITE_ESTACIONADOS 20
#define TAM_PATENTE 20
#define TAM_MARCA 20
#define ALPHA_ROMEO 1
#define FERRARI 2
#define AUDI 3
#define OTRO 4
#define NO_ESTACIONADO 0
#define LIBRE 1
#define BAJA 2
#define ESTACIONADO 3

typedef struct
{
    int idAutomovil;
    char patente[TAM_PATENTE];
    int marca;
    int idPropietario;
    int estado;
}eAutomovil;

void eAutomovil_init(eAutomovil[],int limite);
void eAutomovil_hardcodeo(eAutomovil[],int limite);
int eAutomovil_buscarPorId(eAutomovil[] ,int limite, int id);
int eAutomovil_buscarPorIdEstacionados(eAutomovil[] ,int limite, int id);
int eAutomovil_buscarPorIdPropietario(eAutomovil[] ,int limite, int idPropietario);
int eAutomovil_siguienteId(eAutomovil[] ,int limite);
int eAutomovil_ultimoIngresado(eAutomovil[],int limite);
int eAutomovil_buscarLugarLibre(eAutomovil[],int limite);
int eAutomovil_validarLimiteEstacionados(eAutomovil[],int limite);

void eAutomovil_mostrarUno(eAutomovil parametro, char nombrePropietario[]);
void eAutomovil_mostrarUnoConEstado(eAutomovil parametro, char nombrePropietario[]);
int eAutomovil_mostrarListadoPropietario(eAutomovil[], int limite, int idPropietario, char nombrePropietario[]);

int eAutomovil_alta(eAutomovil[], int limite, int idPropietario, char nombrePropietario[]);

void eAutomovil_retornaMarca(int marca, char nombreMarca[]);
int eAutomovil_ordenaPorPatente(eAutomovil[], int limite);
int eAutomovil_filtraEstacionados(eAutomovil listaOrigen[], eAutomovil listaDestino[], int limite);

#endif // AUTOS_H_INCLUDED
