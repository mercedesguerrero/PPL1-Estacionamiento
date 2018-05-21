#ifndef ESTRUCTURAPROPIETARIO_H_INCLUDED
#define ESTRUCTURAPROPIETARIO_H_INCLUDED

#define TAM 10
#define OCUPADO 1
#define LIBRE 0
#define CANTIDAD 10

typedef struct
{
    int idPropietario;
    char nombre[50];
    char direccion[50];
    char numTarjetaCred;
    int estado;
}ePropietario;


#endif // ESTRUCTURAPROPIETARIO_H_INCLUDED


int ePropietario_init(ePropietario[],int limite);
int ePropietario_buscarPorId(ePropietario[] ,int limite, int id);
int ePropietario_siguienteId(ePropietario[] ,int limite);
int ePropietario_buscarLugarLibre(ePropietario[],int limite);

void getString(char mensaje[], char input[]);
void getValidString(char mensaje[], char error[], char input[], int limite);

void ePropietario_mostrarUno(ePropietario propietario);
int ePropietario_mostrarlistadoPropietario(ePropietario[], int limite);
int ePropietario_mostrarlistadoPropietarioConBorrados(ePropietario[] ,int limite);

int ePropietario_alta(ePropietario[], int limite);
void ePropietario_baja(ePropietario[], int limite, int id);
int ePropietario_modificacion(ePropietario[] ,int limite, int id);

int ePropietario_ordenar(ePropietario[] ,int limite, int orden);

void mostrarMenu();
void presionarContinuar();


