#ifndef ESTRUCTURAPROPIETARIO_H_INCLUDED
#define ESTRUCTURAPROPIETARIO_H_INCLUDED

#define OCUPADO 1
#define LIBRE 0
#define BAJA 2

#define LIMITE_INGRESOS 200
#define INGRESADO 0
#define LUGAR_LIBRE 1
#define RETIRADO 2

#define LIMITE_EGRESOS 200
#define E_OCUPADO 0
#define E_LIBRE 1
#define IMPORTE_ALPHA_ROMEO 150
#define IMPORTE_FERRARI 175
#define IMPORTE_AUDI 200
#define IMPORTE_OTRO 250

typedef struct
{
    int idPropietario;
    char nombre[50];
    char direccion[50];
    char numTarjetaCred[30];
    int estado;
}ePropietario;

typedef struct
{
    char patente[10];
    int marca;
	int idAuto;
    int idPropietario;
    int estado;
}eAuto;

typedef struct
{
    int idIngreso;
    int idAutomovil;
    int estado;
}eIngreso;

typedef struct
{
    int idEgreso;
    int idIngreso;
    float importe;
    int estado;
}eEgreso;

int ePropietario_init(ePropietario[],int limite);
void inicializarPropietariosHardCode(ePropietario[]);

int ePropietario_buscarPorId(ePropietario[] ,int limite, int id);
int ePropietario_siguienteId(ePropietario[], int limite);
int ePropietario_buscarLugarLibre(ePropietario[],int limite);

void getString(char mensaje[], char input[]);

/** \brief VALIDA QUE UN STRING DE CARACTERES NO SE EXCEDA DEL LÍMITE
 *
 * \param mensaje a ser mostrado
 * \param mensaje de error
 * \param input Array donde se cargará el texto ingresado
 * \param limite de caracteres
 */
void getValidString(char mensaje[], char error[], char input[], int limite);
void pedirString(char mensaje[], char input[], int limite);

int pedirNumEntero(char mensaje[]);

void mostrarUnPropietario(ePropietario propietario);
int mostrarListadoPropietarios(ePropietario[], int limite);
int mostrarListadoPropietariosConBorrados(ePropietario[] ,int limite);
int ePropietario_mostrarListadoConOcupados(ePropietario propietarios[], int limite);
void ePropietario_mostrarUnoConEstado(ePropietario propietario);

int ePropietario_alta(ePropietario[], int limite);
int ePropietario_modificacion(ePropietario[] ,int limite);
int ePropietario_baja(ePropietario[], int limite, int posId);

int ePropietario_ordenar(ePropietario[] ,int limite, int orden);

void mostrarMenu();
void presionarContinuar();

void eIngreso_init(eIngreso[],int limite);
int eIngreso_buscarPorId(eIngreso[] ,int limite, int id);
int eIngreso_buscarPorIdAutomovil(eIngreso[] ,int limite, int idAutomovil);
int eIngreso_siguienteId(eIngreso[] ,int limite);
int eIngreso_buscarLugarLibre(eIngreso listado[],int limite);

void eIngreso_mostrarUno(eIngreso parametro, char nombrePropietario[], char patente[], char marca[]);

int eIngreso_alta(eIngreso[] ,int limite, int idAutomovil);
int eIngreso_baja(eIngreso[] ,int limite, int idAutomovil);

void eEgreso_init(eEgreso[],int limite);
int eEgreso_buscarPorId(eEgreso[] ,int limite, int id);
int eEgreso_siguienteId(eEgreso[] ,int limite);
int eEgreso_buscarLugarLibre(eEgreso listado[],int limite);

void eEgreso_mostrarTicket(char nombrePropietario[], char patenteAutomovil[], char marcaAutomovil[], int horasEstadia, float precioEstadia);

int eEgreso_alta(eEgreso[] ,int limite, int idIngreso, char nombrePropietario[], char patenteAutomovil[], char marcaAutomovil[], int horasEstadia, float precioEstadia);
int eEgreso_devolverHorasEstadia(void);


#endif // ESTRUCTURAPROPIETARIO_H_INCLUDED


