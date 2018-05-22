#ifndef ESTRUCTURAPROPIETARIO_H_INCLUDED
#define ESTRUCTURAPROPIETARIO_H_INCLUDED

#define OCUPADO 1
#define LIBRE 0
#define CANTIDAD 10

typedef struct
{
    int idPropietario;
    char nombre[50];
    char direccion[50];
    char numTarjetaCred[30];
    int estado;
}ePropietario;


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

int pedirNumEntero(char mensaje[]);

void mostrarUnPropietario(ePropietario propietario);
int mostrarListadoPropietarios(ePropietario[], int limite);
int mostrarListadoPropietariosConBorrados(ePropietario[] ,int limite);

int ePropietario_alta(ePropietario[], int limite);
int ePropietario_modificacion(ePropietario[] ,int limite, int posId);
int ePropietario_baja(ePropietario[], int limite, int posId);

int ePropietario_ordenar(ePropietario[] ,int limite, int orden);

void mostrarMenu();
void presionarContinuar();


#endif // ESTRUCTURAPROPIETARIO_H_INCLUDED


