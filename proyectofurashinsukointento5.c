
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXIMO_EMPLEADOS 256
#define archivo_principal "trabajadoresprincipal.txt"
#define archivo_extrabajadores "extrabajadores.txt"
#define archivo_cargo "cargo.txt"
#define archivo_departamento "departamento.txt"
#define limpiar "clear" //Esto es para limpiar pantalla, este codigo fue hecho en Windows asi que
//Usamos "cls, pero como sera migrado a Linux ahora es clear
//Defino constantes para evitar repetir texto y hacer comodas las modificaciones
struct Empleado {
    long int ci;
    char apellido[11];
    char nombre[11];
    char departamento[14];
    char cargo[16];
    char fecha_ingreso[11];
    float sueldo;
}; //Utilizo un struct para manejar los datos de manera comoda

bool validar_fecha(char* fecha_revisar);
//Funcion para asegurar que la fecha escrita sea valida
void Agregar_Empleado(struct Empleado Empleado,FILE*aux_archivo);
//Agrega un empleado segun X estructura dada y Y archivo ejecutable
void Cargar_Empleados(struct Empleado Empleados[],int* tamano);
//Carga la lista de empleados de la constante predefinida de la main func
void Guardar_Empleados(struct Empleado Empleados[],int tamano_actual);
//Guarda a los empleados de la X estructura notese el plural eb el arch
void Mostrar_Pantalla_Empleado(struct Empleado Empleado);
//Printea X empleado dado
void Mostrar_Array_Empleados(struct Empleado Empleados[],int tamano_actual);
//Printea un array de empleados
int BuscarCedula(struct Empleado Empleados[],int tamano_actual, long int aux_cedula);
//Lista a un empleado segun su cedula dropeando su posicion
void AgregarEmpleados(struct Empleado Empleados[], int* tamano_actual);
//Agrega empleados al array a usar durante la main
void Modificar_Empleado(struct Empleado Empleados[],int tamano_actual);
//Modifica array donde se encontraba y lo dropea
void Eliminar_Empleado(struct Empleado Empleados[],int *tamano_actual);
//Elimina su casilla del array y la transcribe a extrabajadores con sus condiciones
void ArchivoDepartamento(struct Empleado Empleados[], int tamano_buscar);
//LIsta cant y sueldo convergente + listea en un txt con su nombre
void ArchivoCargo(struct Empleado Empleados[], int tamano_actual);
//Lo mismo que el de arriba2
void Salarios(struct Empleado Empleados[], int tamano_actual);
//Lista al que gana mas y el que gana menos
int main() {
struct Empleado Empleados[MAXIMO_EMPLEADOS]; //Declaro un array de struct para manipular los datos con facilidad
int tamano_actual=0;
int aux_c1;
long int aux_ci;
int menu=0,menu_c2,aux_decision=0;
int aux_c2=0;
printf("Cargando archivo...\n");
Cargar_Empleados(Empleados,&tamano_actual);
system(limpiar);
printf("Bienvenido usuario.\n\n\n");
printf("Este codigo fue hecho por:\n\nMiguel Mendez V-29864734\nEliakny Mirabal V-30913458\n\n");
printf("Presione enter para continuar.\n");
getchar();
system(limpiar);
do {
printf("Menu principal\n\n[1]Ingresar\n[2]Consultar\n[3]Modificar\n[4]Eliminar\n[5]Salir\n");
scanf("%d",&menu);
system(limpiar);
switch(menu) {
case 1:
do {
AgregarEmpleados(Empleados,&tamano_actual);
Guardar_Empleados(Empleados,tamano_actual);
system(limpiar);
printf("Escriba el numero 1 si desea agendar otro empleado\n");
scanf("%d",&aux_c1);
system(limpiar);
}while(aux_c1==1);
break;
case 2:
printf("Elija modulo a consultar:\n");
printf("[1]Cedula\n[2]Departamento\n[3]Cargo\n[4]Sueldo\n");
scanf("%d",&menu_c2);

switch(menu_c2) {
    case 1: //Si encuentra la cedula lo printea, si no ofrece registrarla al user
        printf("Ingrese cedula a buscar:\n");
        scanf("%ld",&aux_ci);
        aux_c2=BuscarCedula(Empleados,tamano_actual,aux_ci);
        if (aux_c2!= -5) {
            Mostrar_Pantalla_Empleado(Empleados[aux_c2]);
        } else {
            do {
            printf("La cedula no se encuentra en el registro. Desea registrarla?\n[1]Si\n[2]No\n");
            scanf("%d",&aux_decision);
            if((aux_decision!= 1) || (aux_decision!=2)) {
                printf("\n\nIngrese una opcion valida\n\n");
                }else if(aux_decision=1) {
                   AgregarEmpleados(Empleados,&tamano_actual);
                   Guardar_Empleados(Empleados,tamano_actual);
                    } else {
                    }
            }while((aux_decision<1) || (aux_decision>2));
        }
        break;
    case 2:
        ArchivoDepartamento(Empleados,tamano_actual);
        break;
    case 3:
        ArchivoCargo(Empleados,tamano_actual);
        break;
    case 4:
        Salarios(Empleados,tamano_actual);
        break;
    default:
        printf("\nIngrese una opcion valida.\n");
        break;
}
break;
case 3:
    Modificar_Empleado(Empleados, tamano_actual);
    Guardar_Empleados(Empleados,tamano_actual);
break;
case 4:
    Eliminar_Empleado(Empleados,&tamano_actual);
    Guardar_Empleados(Empleados,tamano_actual);
break;
case 5:
    return 0;
break;
default:
printf("Escriba una orden correcta.");
}
}while(menu!=5);
}

bool validar_fecha(char* fecha_revisar) {
int dia, mes, ano;
int num_leidos = sscanf(fecha_revisar, "%d/%d/%d", &dia, &mes, &ano);
    if (num_leidos != 3) {
        return false;
    }
    // Verificar que el mes esté en un rango válido (entre 1 y 12)
    if (mes < 1 || mes > 12) {
        return false;
    }
    //Declaro dos array uno para bisiesto y otro para no bisiesto
int dias_por_mes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //Arrau segun los dias de cada mes
if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) {
dias_por_mes[2] = 29; //Array 2 bisiesto es modificado
}
if (dia < 1 || dia > dias_por_mes[mes]) {
return false;
}
return true;
}

void Agregar_Empleado(struct Empleado Empleado,FILE*aux_archivo) {

fprintf(aux_archivo,"%ld %s %s %s %s %.2f %s\n",Empleado.ci,Empleado.nombre,Empleado.apellido,Empleado.departamento,Empleado.cargo,Empleado.sueldo,Empleado.fecha_ingreso);
}

void Cargar_Empleados(struct Empleado Empleados[], int* tamano_actual) {
    FILE* archivo_cargar;
    archivo_cargar = fopen(archivo_principal, "r");

    if (archivo_cargar != NULL) {
        *tamano_actual = 0;
        char linea[256]; // Tamaño máximo de una línea en el archivo

        while (fgets(linea, sizeof(linea), archivo_cargar) != NULL) {
            if (sscanf(linea, "%ld %10s %10s %13s %15s %f %10s",
                       &Empleados[*tamano_actual].ci, Empleados[*tamano_actual].nombre,
                       Empleados[*tamano_actual].apellido, Empleados[*tamano_actual].departamento,
                       Empleados[*tamano_actual].cargo, &Empleados[*tamano_actual].sueldo,
                       Empleados[*tamano_actual].fecha_ingreso) == 7) {
                (*tamano_actual)++;
            }
        }
    } else {
        printf("Error al abrir archivo principal.\n");
    }

    fclose(archivo_cargar);
}


void Guardar_Empleados(struct Empleado Empleados[],int tamano_actual) {
FILE* archivo_guardar;
int i=0;
archivo_guardar=fopen(archivo_principal,"w");

for (i=0;i<tamano_actual;i++) {
Agregar_Empleado(Empleados[i],archivo_guardar);
}
fclose(archivo_guardar);
}

void Mostrar_Pantalla_Empleado(struct Empleado Empleado) {
    printf("\n%ld\n", Empleado.ci);
    printf("%s %s\n", Empleado.nombre, Empleado.apellido);
    printf("%s\n", Empleado.departamento);
    printf("%s\n", Empleado.cargo);
    printf("%.2f\n", Empleado.sueldo);
    printf("%s\n\n", Empleado.fecha_ingreso);
}

void Mostrar_Array_Empleados(struct Empleado Empleados[],int tamano_actual) {
int i;
for (i=0;i<tamano_actual;i++) {
        printf("Empleado numero %d:\n",i+1);
        //i+1 porque si no al principio dira  empleado 0 y se ve feo
        Mostrar_Pantalla_Empleado(Empleados[i]);
}
}

int BuscarCedula(struct Empleado Empleados[],int tamano_actual, long int aux_cedula) {
int i; //Mis planes iniciales era usar tamano_actual para ahorrar recursos pero soltaba muchos errores
//Asi que decidi usar la constante
for(i=0;i<MAXIMO_EMPLEADOS;i++) {
    if (Empleados[i].ci==aux_cedula) {
        return i;
        }
}
return -5;
}

void AgregarEmpleados(struct Empleado Empleados[], int* tamano_actual){

    if (*tamano_actual >= MAXIMO_EMPLEADOS) {
        printf("La capacidad ha llegado a su maximo, no se pueden agregar mas empleados.\n");
        return; //Avisa si alcanzo su maximo de memoria
    }
struct Empleado NuevoEmpleado;
int tipo_departamento=0,tipo_cargo=0,verificarcedula=0;
char aux_fecha[11]; //Array struct auxiliar
long int aux_cedula;
do {
    printf("Introduzca cedula:\n");
    scanf("%ld",&aux_cedula);
verificarcedula= BuscarCedula(Empleados,tamano_actual,aux_cedula);
if (verificarcedula!=-5) {
    printf("\nHa ingresado una cedula que ya existe, intente nuevamente.\n\n");
}
}while (verificarcedula!=-5);
    NuevoEmpleado.ci=aux_cedula;
    system(limpiar);
    printf("Introduzca apellido(Maximo 10 caracteres):\n"); //Primero pido el apellido para que el user sepa que es nombre y apellido por separado
    scanf("%s",NuevoEmpleado.apellido);
    system(limpiar);
    printf("Introduzca nombre(Maximo 10 caracteres):\n");
    scanf("%s",NuevoEmpleado.nombre);
    system(limpiar);
    do {
        printf("Ingrese el numero segun el departamento correspondiente:\n");
        printf("\n[1]RRHH\n[2]Consultoria\n[3]Diseno\n[4]Produccion\n[5]Calidad\n[6]Distribucion\n\n");
        scanf("%d",&tipo_departamento);
        if (tipo_departamento <1 || tipo_departamento >6) {
                printf("Error, ingrese un dato valido.");
        }
    }while (tipo_departamento<1 || tipo_departamento>6);

switch(tipo_departamento) {
//Uso de strcpy para anular la libertad del usuario al escribir la palabra y asi evitar bugs mas adelante
    case 1:
     strcpy(NuevoEmpleado.departamento,"RRHH");
    break;
    case 2:
    strcpy(NuevoEmpleado.departamento,"Consultoria");
    break;
    case 3:
    strcpy(NuevoEmpleado.departamento,"Diseno");
    break;
    case 4:
    strcpy(NuevoEmpleado.departamento,"Produccion");
    break;
    case 5:
    strcpy(NuevoEmpleado.departamento,"Calidad");
    break;
    case 6:
    strcpy(NuevoEmpleado.departamento,"Distribucion");
    break;
}
system(limpiar);
do {
        printf("Ingrese el numero segun el cargo correspondiente:\n\n");
        printf("\n[1]Gerente\n[2]Supervisor\n[3]Analista\n[4]Disenador\n[5]Desarrollador\n[6]Auditor\n\n");
        scanf("%d",&tipo_cargo);
        if (tipo_cargo <1 || tipo_cargo >6) {
                printf("Error, ingrese un dato valido.");
        }
}while (tipo_cargo<1 || tipo_cargo>6);

switch(tipo_cargo) {
    case 1:
    strcpy(NuevoEmpleado.cargo,"Gerente");
    break;
    case 2:
    strcpy(NuevoEmpleado.cargo,"Supervisor");
    break;
    case 3:
    strcpy(NuevoEmpleado.cargo,"Analista");
    break;
    case 4:
    strcpy(NuevoEmpleado.cargo,"Disenador");
    break;
    case 5:
    strcpy(NuevoEmpleado.cargo,"Desarrollador");
    break;
    case 6:
    strcpy(NuevoEmpleado.cargo,"Auditor");
    break;
    }
    system(limpiar);
    printf("Introduzca salario (en formato n.dec)\n");
    printf("Ejemplo: 1291.12\n");
    scanf("%f",&NuevoEmpleado.sueldo);
    system(limpiar);

    do {
        printf("Introduzca fecha de ingreso a la empresa en formato DD/MM/YYYY\n");
        printf("Ejemplo: 05/02/2012\n");
        scanf("%s",aux_fecha);
        if (validar_fecha(aux_fecha)==true) {
                strcpy(NuevoEmpleado.fecha_ingreso,aux_fecha);
        } else {
            printf("\nHas ingresado una fecha invalida.\n\n");
            }
    }while((validar_fecha(aux_fecha)!=true));

    Empleados[*tamano_actual] = NuevoEmpleado;
    (*tamano_actual)++;
}

void Modificar_Empleado(struct Empleado Empleados[],int tamano_actual) {
int aux_opciones,tipo_cargo,tipo_departamento;
long int aux_ci;
int verificar;
char aux_fecha[11];
struct Empleado EmpleadoModificado;
printf("Ingrese cedula del empleado a modificar:\n");
scanf("%ld",&aux_ci);
verificar= BuscarCedula(Empleados,tamano_actual,aux_ci);
if(verificar==-5) {
        printf("No se encontro un empleado con esa CI.\n");
        return;
    }
EmpleadoModificado= Empleados[verificar]; //Uso de Array de registros aux
printf("\nEstos son los datos actuales del empleado:\n\n");
Mostrar_Pantalla_Empleado(EmpleadoModificado); //Printea los datos actuales del empleado para comodidad del usuario
do {
printf("Ingrese que desea modificar:\n[1]Nombre\n[2]Departamento\n[3]Cargo\n[4]Salario\n[5]Fecha\n[6]Todas\n");
scanf("%d",&aux_opciones);
system(limpiar);
switch(aux_opciones) {
    case 1:
        printf("Ingrese nuevo apellido:\n");
        scanf("%s",EmpleadoModificado.apellido);
        printf("Ingrese nuevo nombre:\n");
        scanf("%s",EmpleadoModificado.nombre);
        break;
    case 2:
        do {
        printf("\nIngrese nuevo departamento:\n");
        printf("\n[1]RRHH\n[2]Consultoria\n[3]Diseno\n[4]Produccion\n[5]Calidad\n[6]Distribucion\n");
        scanf("%d",&tipo_departamento);
        if (tipo_departamento <1 || tipo_departamento >6) {
                printf("Error, ingrese un dato valido.");
        }
        }while (tipo_departamento<1 || tipo_departamento>6);

        switch(tipo_departamento) {
            case 1:
                strcpy(EmpleadoModificado.departamento,"RRHH");
            break;
            case 2:
                strcpy(EmpleadoModificado.departamento,"Consultoria");
            break;
            case 3:
                strcpy(EmpleadoModificado.departamento,"Diseno");
            break;
            case 4:
                strcpy(EmpleadoModificado.departamento,"Produccion");
            break;
            case 5:
                strcpy(EmpleadoModificado.departamento,"Calidad");
            break;
            case 6:
                strcpy(EmpleadoModificado.departamento,"Distribucion");
            break;
    }
    break;

    case 3:
        do {
        printf("Ingrese nuevo cargo:\n\n");
        printf("\n[1]Gerente\n[2]Supervisor\n[3]Analista\n[4]Disenador\n[5]Desarrollador\n[6]Auditor\n\n");
        scanf("%d",&tipo_cargo);
        if (tipo_cargo <1 || tipo_cargo >6) {
                printf("Error, ingrese un dato valido.");
        }
        }while (tipo_cargo<1 || tipo_cargo>6);

        switch(tipo_cargo) {
            case 1:
                strcpy(EmpleadoModificado.cargo,"Gerente");
            break;
            case 2:
                strcpy(EmpleadoModificado.cargo,"Supervisor");
            break;
            case 3:
                strcpy(EmpleadoModificado.cargo,"Analista");
            break;
            case 4:
                strcpy(EmpleadoModificado.cargo,"Disenador");
            break;
            case 5:
                strcpy(EmpleadoModificado.cargo,"Desarrollador");
            break;
            case 6:
                strcpy(EmpleadoModificado.cargo,"Auditor");
            break;
    }
    break;
    case 4:
        printf("Introduzca nuevo salario (en formato n.dec)\n");
        printf("Ejemplo: 1291.12\n");
        scanf("%f",&EmpleadoModificado.sueldo);
    break;
    case 5:
        do {
        printf("Introduzca fecha de ingreso a la empresa en formato DD/MM/YYYY/n");
        printf("Ejemplo: 05/02/2012");
        scanf("%s",aux_fecha);
        if (validar_fecha(aux_fecha)==true) {
                strcpy(EmpleadoModificado.fecha_ingreso,aux_fecha);
        } else {
            printf("Has ingresado una fecha invalida.\n\n");
            }
        }while((validar_fecha(aux_fecha)!=true));
    break;
    case 6:
        printf("Ingrese nuevo apellido:\n");
        scanf("%s",EmpleadoModificado.apellido);
        system(limpiar);
        printf("Ingrese nuevo nombre:\n");
        scanf("%s",EmpleadoModificado.nombre);
        system(limpiar);
        do {
        printf("\nIngrese nuevo departamento:\n");
        printf("\n[1]RRHH\n[2]Consultoria\n[3]Diseno\n[4]Produccion\n[5]Calidad\n[6]Distribucion\n");
        scanf("%d",&tipo_departamento);
        if (tipo_departamento <1 || tipo_departamento >6) {
                printf("Error, ingrese un dato valido.");
        }
        }while (tipo_departamento<1 || tipo_departamento>6);

        switch(tipo_departamento) {
            case 1:
                strcpy(EmpleadoModificado.departamento,"RRHH");
            break;
            case 2:
                strcpy(EmpleadoModificado.departamento,"Consultoria");
            break;
            case 3:
                strcpy(EmpleadoModificado.departamento,"Diseno");
            break;
            case 4:
                strcpy(EmpleadoModificado.departamento,"Produccion");
            break;
            case 5:
                strcpy(EmpleadoModificado.departamento,"Calidad");
            break;
            case 6:
                strcpy(EmpleadoModificado.departamento,"Distribucion");
            break;
        }
        system(limpiar);
        do {
        printf("Ingrese nuevo cargo:\n\n");
        printf("\n[1]Gerente\n[2]Supervisor\n[3]Analista\n[4]Disenador\n[5]Desarrollador\n[6]Auditor\n\n");
        scanf("%d",&tipo_cargo);
        if (tipo_cargo <1 || tipo_cargo >6) {
                printf("Error, ingrese un dato valido.");
        }
        }while (tipo_cargo<1 || tipo_cargo>6);

        switch(tipo_cargo) {
            case 1:
                strcpy(EmpleadoModificado.cargo,"Gerente");
            break;
            case 2:
                strcpy(EmpleadoModificado.cargo,"Supervisor");
            break;
            case 3:
                strcpy(EmpleadoModificado.cargo,"Analista");
            break;
            case 4:
                strcpy(EmpleadoModificado.cargo,"Disenador");
            break;
            case 5:
                strcpy(EmpleadoModificado.cargo,"Desarrollador");
            break;
            case 6:
                strcpy(EmpleadoModificado.cargo,"Auditor");
            break;
        }
        system(limpiar);
        printf("Introduzca nuevo salario (en formato n.dec)\n");
        printf("Ejemplo: 1291.12\n");
        scanf("%f",EmpleadoModificado.sueldo);
        system(limpiar);
        do {
        printf("Introduzca fecha de ingreso a la empresa en formato DD/MM/YYYY/n");
        printf("Ejemplo: 05/02/2012");
        scanf("%s",aux_fecha);
        if (validar_fecha(aux_fecha)==true) {
                strcpy(EmpleadoModificado.fecha_ingreso,aux_fecha);
        } else {
            printf("Has ingresado una fecha invalida.\n\n");
            }
        }while((validar_fecha(aux_fecha)!=true));
    break;
    default:
        printf("\nIngrese opcion valida\n");
    break;
}
}while((aux_opciones<1) || (aux_opciones>7));

Empleados[verificar]= EmpleadoModificado;

printf("Empleado modificado.\n"); //Printea su exito en la resolucion
}

void Eliminar_Empleado(struct Empleado Empleados[],int *tamano_actual) {
int verificar,decision,aux_despido;
long int aux_ci;
struct Empleado EmpleadoEliminado;
char despido[12],aux_fecha[11],fecha_outgreso[11];
printf("Ingrese cedula del empleado a eliminar:\n");
scanf("%ld",&aux_ci);
verificar= BuscarCedula(Empleados,*tamano_actual,aux_ci);
if(verificar==-15) {
        printf("No se encontro un empleado con esa CI.\n");
        return;
    }
    EmpleadoEliminado=Empleados[verificar];
    system(limpiar);
    printf("\nDatos del empleado:\n");
    Mostrar_Pantalla_Empleado(EmpleadoEliminado);

    printf("Seguro que desea eliminarlo?\n[1]Si\n[2]No\n");
    scanf("%d",decision);
    if (decision=1) {
        FILE* extrabajadores=fopen(archivo_extrabajadores,"a+"); //a++ porque como comente en el doc no guardamos registro de ellos
           if (extrabajadores == NULL) {
            printf("Error al abrir el arcivo.\n");
            return;
        }
    do {
    printf("Ingrese motivo de despido:\n[1]Traslado\n[2]Renuncia\n[3]Otro\n\n");
    scanf("%d",&aux_despido);
    switch(aux_despido) {
    case 1:
        strcpy(despido,"Traslado");
    break;
    case 2:
        strcpy(despido,"Renuncia");
    break;
    case 3:
        strcpy(despido,"Otro");
    break;
    default:
        printf("\nIngrese opcion valida\n");
    break;
    }
    }while((aux_despido<1) || (aux_despido>3));
     do {
        printf("Introduzca fecha de salida de la empresa en formato DD/MM/YYYY/n");
        printf("Ejemplo: 05/02/2012");
        scanf("%s",aux_fecha);
        if (validar_fecha(aux_fecha)==true) {
                strcpy(fecha_outgreso,aux_fecha);
        } else {
            printf("Has ingresado una fecha invalida.\n\n");
            }
        }while((validar_fecha(aux_fecha)!=true));
fprintf(extrabajadores,"%ld %s %s %s %s %.2f %s %s %s\n",EmpleadoEliminado.ci,EmpleadoEliminado.nombre,EmpleadoEliminado.apellido,EmpleadoEliminado.departamento,EmpleadoEliminado.cargo,EmpleadoEliminado.sueldo,EmpleadoEliminado.fecha_ingreso,despido,fecha_outgreso);
//Lo imprimo sin los \t porque a la hora de escribir sera imposible hacerlo sin generar problemas en el archivo
fclose(extrabajadores);
//elimino al empleado del array de empleados
        for (int i = verificar; i < *tamano_actual - 1; i++) {
            Empleados[i] = Empleados[i + 1];
        }

        (*tamano_actual)--;
system(limpiar);
printf("Empleado eliminado.\n");
} else {
    printf("Eliminacion cancelada.\n");
}
}


void ArchivoDepartamento(struct Empleado Empleados[], int tamano_buscar){
    char depar[16];
    int tipo_departamento;
    int ContadorEmpleados= 0;
    float SalarioEmpleados= 0.0;
system(limpiar);
    do {
        printf("\n[1]RRHH\n[2]Consultoria\n[3]Diseno\n[4]Produccion\n[5]Calidad\n[6]Distribucion\n");
        scanf("%d",&tipo_departamento);
        if (tipo_departamento <1 || tipo_departamento >6) {
                printf("Error, ingrese un dato valido.");
        }
        }while (tipo_departamento<1 || tipo_departamento>6);

        switch(tipo_departamento) {
            case 1:
                strcpy(depar,"RRHH");
            break;
            case 2:
                strcpy(depar,"Consultoria");
            break;
            case 3:
                strcpy(depar,"Diseno");
            break;
            case 4:
                strcpy(depar,"Produccion");
            break;
            case 5:
                strcpy(depar,"Calidad");
            break;
            case 6:
                strcpy(depar,"Distribucion");
            break;
        }
//Mismo problema que al buscar cedula decidimos usar la constante
    for (int i = 0; i < MAXIMO_EMPLEADOS; i++) {
    if (strcmp(Empleados[i].departamento, depar) == 0) {
        ContadorEmpleados++;
        SalarioEmpleados += Empleados[i].sueldo;
    }
    }
system(limpiar);
    printf("Número de trabajadores en el departamento: %d\n\n", ContadorEmpleados);
    printf("\nTotal de sueldos devengados: %.3f\n\n", SalarioEmpleados);

    FILE* departamentoarchivo = fopen(archivo_departamento, "w");
    if (departamentoarchivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < tamano_buscar; i++) {
        if (strcmp(Empleados[i].departamento, depar) == 0) {
fprintf(departamentoarchivo,"%ld %s %s %s %s %.2f %s\n",Empleados[i].ci,Empleados[i].nombre,Empleados[i].apellido,Empleados[i].departamento,Empleados[i].cargo,Empleados[i].sueldo,Empleados[i].fecha_ingreso);
}
    }
fclose(departamentoarchivo);
}

void ArchivoCargo(struct Empleado Empleados[], int tamano_actual){
    char cargo[16];
    int tipo_cargo;
    int ContadorEmpleados= 0;
    float SalarioEmpleados= 0.0;
system(limpiar);
    do {
        printf("\n[1]Gerente\n[2]Supervisor\n[3]Analista\n[4]Disenador\n[5]Desarrollador\n[6]Auditor\n\n");
        scanf("%d",&tipo_cargo);
        if (tipo_cargo <1 || tipo_cargo >6) {
                printf("Error, ingrese un dato valido.");
        }
        }while (tipo_cargo<1 || tipo_cargo>6);

        switch(tipo_cargo) {
            case 1:
                strcpy(cargo,"Gerente");
            break;
            case 2:
                strcpy(cargo,"Supervisor");
            break;
            case 3:
                strcpy(cargo,"Analista");
            break;
            case 4:
                strcpy(cargo,"Disenador");
            break;
            case 5:
                strcpy(cargo,"Desarrollador");
            break;
            case 6:
                strcpy(cargo,"Auditor");
            break;
        }

    for (int i = 0; i < MAXIMO_EMPLEADOS; i++) {
    if (strcmp(Empleados[i].cargo, cargo) == 0) {
        ContadorEmpleados++;
        SalarioEmpleados += Empleados[i].sueldo;
    }
    }
system(limpiar);
    printf("Número de trabajadores con este cargo: %d\n", ContadorEmpleados);
    printf("\nTotal de sueldos devengados: %.3f\n\n", SalarioEmpleados);
    FILE* cargoarchivo = fopen(archivo_cargo, "w");
    if (cargoarchivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < tamano_actual; i++) {
        if (strcmp(Empleados[i].cargo, cargo) == 0) {
fprintf(cargoarchivo,"%ld %s %s %s %s %.2f %s\n",Empleados[i].ci,Empleados[i].nombre,Empleados[i].apellido,Empleados[i].departamento,Empleados[i].cargo,Empleados[i].sueldo,Empleados[i].fecha_ingreso);
}
    }
fclose(cargoarchivo);
}


void Salarios(struct Empleado Empleados[], int tamano_actual){
    float SalarioMayor = Empleados[0].sueldo;
    float SalarioMenor = Empleados[0].sueldo;
     int BanderaMax = 0;
    int BanderaMin = 0;

    for (int i = 1; i < tamano_actual; i++) {
        if (Empleados[i].sueldo > SalarioMayor) {
            SalarioMayor = Empleados[i].sueldo;
            BanderaMax = i;
        }
        if (Empleados[i].sueldo < SalarioMenor) {
            SalarioMenor = Empleados[i].sueldo;
            BanderaMin = i;
        }
    }
    printf("Trabajador con el mayor sueldo:\n");
    Mostrar_Pantalla_Empleado(Empleados[BanderaMax]);
    printf("\nTrabajador con el menor sueldo:\n");
    Mostrar_Pantalla_Empleado(Empleados[BanderaMin]);
}
