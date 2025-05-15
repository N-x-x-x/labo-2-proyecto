/**
Proyecto realizado por:
Paulo Gaston Meira Strazzolini
Carolina Villalba
Nelyer Jose Narvaez Briceño
Eros Khalil Berón
**/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "pachingo_librery.h"
#include "pachingo_librery.c"

struct registro
{
    int id;
    char fechaEntrada[15];
    char zona[30];
    char ciudad[30];
    int dormitorios;
    int banos; //baños
    float superficieTotal;
    float superficieCubierta;
    float precio;
    char moneda[10];
    char tipoPropiedad[20];
    char operacion[40];
    char fechaSalida[15];
    int activo;
};

void imprimoTodo(struct registro reg) //tras mucho trabajo al fin logre que printeara todo bien lindo //cabecera
{
    FILE*arch;
    arch = fopen("propiedades.dat","rb");

    printf("| ID | FECHA IN     | ZONA              | CIUDAD             | DORM | BA | SUP TOT    | SUP CUB       | PRECIO        | MONEDA | TIPO PROP       | OP                | FECHA OUT  | ACTIVO |\n");
    fseek(arch,0,SEEK_SET);
    fread(&reg,sizeof(struct registro),1,arch);//lectura previa

    while(!feof(arch))//repito hasta acabar el archivo
    {
        printf("|%-3d | %-12s |%-19s| %-18s | %4d | %2d | %-10.4f | %-13.4f | %-13.4f | %6s | %-15s | %-17s | %-10s | %6d |\n", reg.id, reg.fechaEntrada, reg.zona, reg.ciudad, reg.dormitorios, reg.banos, reg.superficieTotal, reg.superficieCubierta, reg.precio, reg.moneda, reg.tipoPropiedad, reg.operacion, reg.fechaSalida, reg.activo);
        //printf("|%-3d - %-12s - %-19s - %-18s - %4d - %2d - %-10.4f - %-13.4f - %-13.4f - %6s - %20s - %-15s - %-10s - %6d|\n",reg.id, reg.fechaEntrada, reg.zona, reg.ciudad, reg.dormitorios, reg.banos, reg.superficieTotal, reg.superficieCubierta, reg.precio, reg.moneda, reg.tipoPropiedad, reg.operacion, reg.fechaSalida, reg.activo);
        //printf("%s\n",reg.moneda);
        //printf("%s\n",reg.tipoPropiedad);
        //printf("| %s - %5s - %15s - %10s - %4s - %4s - %10s - %10s - %5s - %s - %15s - %8s - %5s - %s |\n",id,FECHA_IN,ZONA,CIUDAD,DORM,BAN,SUP_TOT,SUP_CUB,PRECIO,MONEDA,TIPO_PROP,OP,FEHCA_OUT,ACTIVO);
        fflush(stdin);
        fread(&reg,sizeof(struct registro),1,arch);
    }
    //printf("|ID -    FEHCA IN    -    ZONA    -    CIUDAD    - DORM  - BAN -    SUP TOT    -    SUP CUB    -    PRECIO    - MONEDA -       TIPO PROP       -       OP      -    FEHCA OUT    - ACTIVO|\n");
//    char id[]="ID";
//    char FECHA_IN[]="FECHA IN";
//    char ZONA[]="ZONA";
//    char CIUDAD[]="CIUDAD";
//    char DORM[]="DORM";
//    char BAN[]="BAN";
//    char SUP_TOT[]="SUP TOT";
//    char SUP_CUB[]="SUP CUB";
//    char PRECIO[]="PRECIO";
//    char MONEDA[]="MONEDA";
//    char TIPO_PROP []="TIPO PROP";
//    char OP[]="OP";
//    char FEHCA_OUT[]="FEHCA OUT";
//    char ACTIVO[]="ACTIVO";
    //printf("| %10s - %10s - %10s - %10s - %10s - %10s - %10s - %10s - %10s - %10s - %10s - %10s - %10s - %10s |\n",id,FECHA_IN,ZONA,CIUDAD,DORM,BAN,SUP_TOT,SUP_CUB,PRECIO,MONEDA,TIPO_PROP,OP,FEHCA_OUT,ACTIVO);
    //quiza descontar los espacios por lo que ocupa un caracter
}

void impresionEspecificaCabecera()
{
    printf("| ID | FECHA IN     | ZONA              | CIUDAD             | DORM | BA | SUP TOT    | SUP CUB       | PRECIO        | MONEDA | TIPO PROP       | OP                | FECHA OUT  | ACTIVO |\n");
}///fin impresionEspecificaCabecera

void impresionEspecifica(struct registro reg){
    printf("|%-3d | %-12s |%-19s| %-18s | %4d | %2d | %-10.4f | %-13.4f | %-13.4f | %6s | %-15s | %-17s | %-10s | %6d |\n", reg.id, reg.fechaEntrada, reg.zona, reg.ciudad, reg.dormitorios, reg.banos, reg.superficieTotal, reg.superficieCubierta, reg.precio, reg.moneda, reg.tipoPropiedad, reg.operacion, reg.fechaSalida, reg.activo);
}///fin imprecion_especifica

int listarActivos() {
    int flag=0;
    struct registro reg;
    FILE*arch;
    arch = fopen("propiedades.dat","rb");//solo voy a printar los campos activos

    if (arch == NULL)//control al abrir y si todo sale bien continuo con lo que quiero hacer
        {
            printf("ERROR 001: Archivo inexistente\n");
            fclose(arch);
            return 1;
        }

    fseek(arch,0,SEEK_SET);
    fread(&reg,sizeof(struct registro),1,arch);//lectura previa
    //impresionEspecificaCabecera();//preparo la cabecera

    while(!feof(arch))//repito hasta acabar el archivo
    {
        if(reg.activo == 1)
        {
            if(flag==0)//esto es un proceso para printear siempre la cabecera al inicio
            {
                impresionEspecificaCabecera();
                flag=1;
            }
            impresionEspecifica(reg);// si activo es 1 printo ahora si el reg con ese campo
//        }else
//        {
//            if(flag==0)
//            {
//                printf("\nNo hay propiedades activas en este momento\n");
//                flag=1;
//            }
//        }
        }
        fread(&reg,sizeof(struct registro),1,arch);//lectura previa
    }
    fclose(arch);
}

void apagoActivos(struct registro reg, FILE *archdo)
{
    fseek(archdo,-sizeof(struct registro),SEEK_CUR);
    reg.activo = 0;
    fwrite(&reg,sizeof(struct registro),1,archdo);//guardo toda la estructura en esa unica interacicion
    fclose(archdo);
}

int idCheck(int id,FILE * filePointer)
{
    struct registro aux;
    fseek(filePointer,sizeof(struct registro)*(id-1),SEEK_SET);
    fread(&aux,sizeof(struct registro),1,filePointer);


    if(id==0) {
        printf("Id no valido\n\n");
        return 1;
    }
    if(id==0 && aux.dormitorios>0) {
        printf("Este id ya esta en uso\n\n");
        return 1;
    } else if(aux.id==id && id!=0) {
        printf("Este id ya esta en uso\n\n");
        return 1;
    } else if(id>0) {
        printf("Id disponible\n");
        return 0;
    }
}

void archivoFisica(struct registro aux){
    char fechaActual[15];
    char nombreArchivo[35]="propiedades_bajas_";
    clearBuffer(fechaActual,15);
    obtenerFecha(fechaActual);

    strcat(nombreArchivo,(strcat(fechaActual,".xyz")));
    FILE *arch_do;
    arch_do=fopen(nombreArchivo , "ab+");
    fwrite(&aux,sizeof(struct registro),1,arch_do);
    fclose(arch_do);
}

int bajaFisica()
{
    int tamano=0;
    int estado;
    struct registro reg;
    struct registro aux;
    FILE*arch;
    arch = fopen("propiedades.dat","rb+");//rb+ para modificar

    if (arch == NULL)//control al abrir y si todo sale bien continuo con lo que quiero hacer
    {
        printf("ERROR 001: Archivo inexistente\n");
        fclose(arch);
        return 1;
    }
    printf("--------------------------------------------------------------\n");
    printf("Bienvenido a la Baja Fisica\n");
    printf("Ingrese 'a' para continuar y 'r' para cancelar, sepa que todos los campos con activo en 0 seran eliminados: ");
    FconfirmacionMod(&estado);
    //fflush(stdin);
    printf("--------------------------------------------------------------\n");

    if (estado == 1){ //continua proceso,//esto me costo un monton

        int currentId=1;

        fseek(arch,0,SEEK_SET); //primero, me pone el puntero al inicio, por si acaso

        while(!feof(arch)) {

            fseek(arch,sizeof(struct registro)*(currentId-1),SEEK_SET);

            fread(&reg,sizeof(struct registro),1,arch);


            if(reg.activo == 0 && reg.dormitorios > 0){ //veo si es uno cargado con activo en 0

            fseek(arch,sizeof(struct registro)*(currentId-1),SEEK_SET);

            //fseek(arch,-sizeof(struct registro),SEEK_CUR); //me posiciono la posicion anterior

            aux.id=reg.id;
            strcpy(aux.fechaEntrada,reg.fechaEntrada);
            strcpy(aux.zona,reg.zona);
            strcpy(aux.ciudad,reg.ciudad);
            aux.dormitorios=reg.dormitorios;
            aux.banos=reg.banos;
            aux.superficieTotal=reg.superficieTotal;
            aux.superficieCubierta=reg.superficieCubierta;
            aux.precio=reg.precio;
            strcpy(aux.moneda,reg.moneda);
            strcpy(aux.tipoPropiedad,reg.tipoPropiedad);
            strcpy(aux.operacion,reg.operacion);
            strcpy(aux.fechaSalida,reg.fechaSalida);
            aux.activo=0;

            reg.id=0;
            strcpy(reg.fechaEntrada,"");
            strcpy(reg.zona,"");
            strcpy(reg.ciudad,"");
            reg.dormitorios=0;
            reg.banos=0;
            reg.superficieTotal=0;
            reg.superficieCubierta=0;
            reg.precio=0;
            strcpy(reg.moneda,"");
            strcpy(reg.tipoPropiedad,"");
            strcpy(reg.operacion,"");
            strcpy(reg.fechaSalida,"");
            reg.activo=0;

            fwrite(&reg,sizeof(struct registro),1,arch); //escribo el struct

            fflush(stdin); //fflush random

            //fseek(arch,sizeof(struct registro),SEEK_CUR);//vuelvo poner el puntero adelante, para seguir leyendo el archivo

            //SEEK_CUR me mueve el puntero que lee el archivo y como me lo mueve donde quiero puedo ahcer eso

            archivoFisica(aux);//aqui paso a agregar algo al archivo o generarlo y guardarlo

            }
            currentId++;
        }

        /* ORIGINAl -> ERROR -> SOLO BAJA UNA PROPIEDAD POR MAS QUE HAYA VARIOS CON ACTIVO 0 (o no baja la propiedad final?)
        while(fread(&reg,sizeof(struct registro), 1, arch) == 1){//leo el struct

            if(reg.activo == 0 && reg.dormitorios > 0){//veo si es uno cargado con activo en 0
            fseek(arch,-sizeof(struct registro),SEEK_CUR);//me posiciono la posicion anterior

            aux.id=reg.id;
            strcpy(aux.fechaEntrada,reg.fechaEntrada);
            strcpy(aux.zona,reg.zona);
            strcpy(aux.ciudad,reg.ciudad);
            aux.dormitorios=reg.dormitorios;
            aux.banos=reg.banos;
            aux.superficieTotal=reg.superficieTotal;
            aux.superficieCubierta=reg.superficieCubierta;
            aux.precio=reg.precio;
            strcpy(aux.moneda,reg.moneda);
            strcpy(aux.tipoPropiedad,reg.tipoPropiedad);
            strcpy(aux.operacion,reg.operacion);
            strcpy(aux.fechaSalida,reg.fechaSalida);
            aux.activo=0;

            reg.id=0;
            strcpy(reg.fechaEntrada,"");
            strcpy(reg.zona,"");
            strcpy(reg.ciudad,"");
            reg.dormitorios=0;
            reg.banos=0;
            reg.superficieTotal=0;
            reg.superficieCubierta=0;
            reg.precio=0;
            strcpy(reg.moneda,"");
            strcpy(reg.tipoPropiedad,"");
            strcpy(reg.operacion,"");
            strcpy(reg.fechaSalida,"");
            reg.activo=0;
            fwrite(&reg,sizeof(struct registro),1,arch);//escribo el struct
            fseek(arch,sizeof(struct registro),SEEK_CUR);//vuelvo poner el puntero adelante, para seguir leyendo el archivo
            //SEEK_CUR me mueve el puntero que lee el archivo y como me lo mueve donde quiero puedo ahcer eso

            archivoFisica(aux);//aqui paso a agregar algo al archivo o generarlo y guardarlo

            }
        }
        */

        //fclose(arch);//termino y cierro
        listarActivos();
    } else if(estado == 2){//cancela proceso
        fclose(arch);
        printf("Saliendo...\n\n\n");
    }
}

int bajaLogica()
{
    int flag=1;
    int baja_logica_id;
    int confirmacion = 9999;
    struct registro reg;
    FILE*arch;
    arch = fopen("propiedades.dat","rb+");

    if (arch == NULL) //control al abrir y si todo sale bien continuo con lo que quiero hacer
    {
        printf("ERROR 001: Archivo inexistente\n");
        fclose(arch);
        return 1;
    }

    printf("---------------------------------------------------------------------------------------------\n");
    printf("Bienvenido a la baja logica\n");
    printf("Ingrese el ID de la propiedad a la que quiere dar de baja: ");
    scanf("%d",&baja_logica_id);
    fflush(stdin);

    while(flag==1)
    {
        if (baja_logica_id <= 0) //si es 0 (pq no hay id 0 pq me da la gana) o si es un numero negativo
        {
            printf("El ID que ingreso es invalido, vuelva a ingresarlo: ");
            scanf("%d",&baja_logica_id);
        }else{flag = 0;}
    }

    int senorita_flag=1;

    ///
    fseek(arch,sizeof(struct registro)*(baja_logica_id-1),SEEK_SET);
    fread(&reg,sizeof(struct registro),1,arch);
    if(reg.id==0 || reg.activo==0) {
        printf("\nERROR 004: El registro no existe o ya se encuentra dado de baja\n");
        fclose(arch);
        return 1;
    }
    fseek(arch,0,SEEK_SET);
    ///

    while((fread(&reg,sizeof(struct registro),1,arch)==1) && (senorita_flag==1)) //mientras exista info que se pueda leer y la confirmacion sea 0
    {
        if(reg.id == baja_logica_id)//si mientras se lee el archivo se detecta el id sigo
        {
            if(reg.activo==0)//me pregunto si el campo tiene activo en 0, que lo tengo significa que ya fue dado de baja logica
            {
                printf("El registro ya posee baja realizada o no se encuentra cargado\n");
                senorita_flag = 0;
            }
            else ///si no hay fecha de salida
            {
                printf("Esta seguro de que quiere dar de baja esta propiedad?\n");

                if(baja_logica_id == 0 && reg.dormitorios == 0){//para salvar el 0 cuando este lleno y evitar letras
                    printf("Error presiono una letra o busco un id 0 sin campos\n");
                    fclose(arch);
                    return 1;//remina la funcion
                }

                impresionEspecificaCabecera();
                impresionEspecifica(reg);

                printf("Para cancelar la operacion presione 1 y para continuar con la operacion presione 0 \n");
                scanf("%d",&confirmacion);
                fflush(stdin);

                while(confirmacion != 1 && confirmacion!= 0)
                {
                    printf("Selecciono una opcion invalida\n");
                    printf("Para cancelar la operacion presione 1 y para continuar con el proceso presione 0 \n");
                    scanf("%d",&confirmacion);
                    fflush(stdin);
                }

                if (confirmacion == 0)
                {
                    //lo copie de lo de ros posiacaso pongo todo
                    char fechaActual[15];
                    clearBuffer(fechaActual,15);
                    clearBuffer(reg.fechaSalida,15);
                    obtenerFecha(fechaActual);
                    strcpy(reg.fechaSalida,fechaActual);
                    strcat(reg.fechaSalida,"\0");

                    apagoActivos(reg,arch);

                    listarActivos();

                    printf("La baja se ha realizado con exito\n");
                }else
                {
                printf("Se cancelo la baja logica de la propiedad con exito :)\n");
                }
            }
        }
     }
    fclose(arch);
}

int alta()
{
    printf("-------------------------------------------\n");

    struct registro aux;
    char buffer[30];

    FILE *fptr;
    fptr=fopen("propiedades.dat","rb+");

    if (fptr == NULL){
        printf("ERROR 001: Archivo inexistente\n");
        fclose(fptr);
        return 1;
    }

    aux.id=999;

    fflush(stdin);
    clearBuffer(buffer,30);

    do
    { /**VALIDACION DEL ID**/
        do
        {
            printf("Ingrese el numero de ID de la nueva propiedad\n");
            fgets(buffer,30,stdin);
            fflush(stdin);
        } while(dataTypeId(buffer)!=0);

        sscanf(buffer,"%d",&aux.id);
    } while(idCheck(aux.id,fptr)!=0);

    printf("id->%d\n",aux.id);

    clearBuffer(buffer,30);

    char fechaActual[15]; /**FECHA DE INGRESO**/
    clearBuffer(fechaActual,15);
    clearBuffer(aux.fechaEntrada,15);
    obtenerFecha(fechaActual);
    strcpy(aux.fechaEntrada,fechaActual);
    strcat(aux.fechaEntrada,"\0");
    printf("\nFecha ingreso %s\n",aux.fechaEntrada);
    clearBuffer(buffer,30);

    do
    { /**VALIDACION CAMPO ZONA**/
        printf("\nIngrese Zona de la propiedad\n");
        fgets(buffer,30,stdin);
        fflush(stdin);
    } while(dataTypeString(buffer)!=0);

    formatS(buffer);
    cutEnter(buffer);
    strcpy(aux.zona,buffer);

    do
    { /**VALIDACION CAMPO CIUDAD**/
        printf("\nIngrese ciudad o barrio de la propiedad\n");
        fgets(buffer,30,stdin);
        fflush(stdin);
    } while(dataTypeString(buffer)!=0);

    formatS(buffer);
    cutEnter(buffer);
    strcpy(aux.ciudad,buffer);

    clearBuffer(buffer,30);

    do
    { /**VALIDACION CAMPO DORMITORIOS**/
        printf("\nIngrese cantidad de dormitorios de la propiedad\n");
        fgets(buffer,30,stdin);
        fflush(stdin);
    } while(dataTypeInt(buffer)!=0);

    sscanf(buffer,"%d",&aux.dormitorios);

    clearBuffer(buffer,30);

    do
    { /**VALIDACION CAMPO BAÑOS**/
        printf("\nIngrese cantidad de ba%cos de la propiedad\n",164);
        fgets(buffer,30,stdin);
        fflush(stdin);
    } while(dataTypeInt(buffer)!=0);

    sscanf(buffer,"%d",&aux.banos);

    clearBuffer(buffer,30);

    do
    { /**VALIDACION CAMPO SUPERFICIE TOTAL**/
        printf("\nIngrese superficie total de la propiedad\n");
        fgets(buffer,30,stdin);
        fflush(stdin);
    } while(datatTypeFloat(buffer)!=0);

    sscanf(buffer,"%f",&aux.superficieTotal);

    clearBuffer(buffer,30);

    do {
        do
        { /**VALIDACION CAMPO SUPERFICIE CUBIERTA**/
            printf("\nIngrese superficie cubierta de la propiedad\n");
            fgets(buffer,30,stdin);
            fflush(stdin);
        } while(datatTypeFloat(buffer)!=0);

        sscanf(buffer,"%f",&aux.superficieCubierta);
        if(aux.superficieCubierta>aux.superficieTotal) {
            printf("ERROR: La superifie ingresada es mayor a la superficie total\n");
        }
    } while(aux.superficieCubierta>aux.superficieTotal);

    clearBuffer(buffer,30);

    do
    { /**VALIDACION CAMPO PRECIO**/
        printf("\nIngrese precio de la propiedad\n");
        fgets(buffer,30,stdin);
        fflush(stdin);
    }while(datatTypeFloat(buffer)!=0);

    sscanf(buffer,"%f",&aux.precio);

    clearBuffer(buffer,30);

    int temp;

    do
    { /**VALIDACION CAMPO MONEDA**/
        printf("\nElija tipo de moneda PESOS(1) o USD(2) con el que se valua la propiedad\n");
        fgets(buffer,30,stdin);
        fflush(stdin);
    } while(dataValidation2Int(buffer)!=0);

    sscanf(buffer,"%d",&temp);

    switch(temp)
    {
        case 1: strcpy(aux.moneda,"PESOS\0");
        break;
        case 2: strcpy(aux.moneda,"USD\0");
    }

    clearBuffer(buffer,30);

    do
    { /**VALIDACION CAMPO TIPO PROPIEDAD**/
        printf("\nIngrese tipo de propiedad CASA(1), DEPARTAMENTO(2) o PH(3)\n");
        fgets(buffer,30,stdin);
        fflush(stdin);
    } while(dataValidation3Int(buffer)!=0);

    sscanf(buffer,"%d",&temp);

    switch(temp)
    {
        case 1: strcpy(aux.tipoPropiedad,"Casa\0");
        break;
        case 2: strcpy(aux.tipoPropiedad,"Departamento\0");
        break;
        case 3: strcpy(aux.tipoPropiedad,"PH\0");
    }

    clearBuffer(buffer,30);

    do
    { /**VALIDACION CAMPO OPERACION**/
        printf("\nIngrese tipo de operaci%cn VENTA(1), ALQUILER(2) o ALQUILER TEMPORAL(3)\n",162);
        fgets(buffer,30,stdin);
        fflush(stdin);
    } while(dataValidation3Int(buffer)!=0);

    sscanf(buffer,"%d",&temp);

    switch(temp)
    {
        case 1: strcpy(aux.operacion,"Venta\0");
        break;
        case 2: strcpy(aux.operacion,"Alquiler\0");
        break;
        case 3: strcpy(aux.operacion,"Alquiler temporal\0");
    }

    ///LA FECHA DE SALIDA SE INGRESA LUEGO?SI->CAMPO FECHA SALIDA DEBE SER TIPO STRING

    strcpy(aux.fechaSalida," \0"); ///warnig

    aux.activo=1;

    ///FALTA->???->EN LOS CAMPOS ZONA Y CIUDAD CONSULTAR QUE TIPOS DE DATOS SE VAN A PODER INGRESAR (SOLO LETRAS Y PUNTOS O ALGUN NUMERO TMB?)

    impresionEspecificaCabecera();
    impresionEspecifica(aux);

    fseek(fptr,sizeof(struct registro)*(aux.id-1),SEEK_SET);
    fwrite(&aux,sizeof(struct registro),1,fptr);

    fclose(fptr);
}

void crearArchivo(int *banderaFCrea)
{
    printf("Hola! Se esta creando el archivo\n");
    struct registro reg;
    int flag = 2;
    FILE*arch;
    arch = fopen("propiedades.dat","rb");
    while(flag != 0 && flag != 1){
        if(arch != NULL){ // si al leer el archivo existe, pregunto si lo quiero crear de nuevo
            printf("El proyecto ya cuenta con un archivo de propiedades.dat, presione 1 para continuar y 0 para salir \n");
            scanf("%d",&flag);
            fflush(stdin);
            while(flag != 0 && flag != 1){//verifico que lo que me meta sea una de las 2 opciones
                printf("Vuelva a ingresar su opcion, ya que la anterior no fue valida\n");
                scanf("%d",&flag);
                fflush(stdin);
            }
        } else {//si no, es pq no existe
            flag = 1;// para que se cree pase de una a donde lo crea
        }
        if(flag == 1) {
        arch = fopen("propiedades.dat","wb"); ///creo el archivo principal
        printf("\nYa se cre%c el archivo\n",162);
        fclose(arch);
        flag = 1;
        }
        if(flag == 0){
            printf("Saliendo...\n");
            flag = 0;
        }
    }
    fclose(arch);//
}

int modificarFechaSalida() {
    printf("----------------------------------------\n");

    struct registro aux;

    FILE *fptr;
    fptr=fopen("propiedades.dat","rb+");

    if(fptr==NULL) {
        printf("ERROR: Archivo inexistente\n");
        fclose(fptr);
        return 1;
    }

    int id;
    int a,b,c;

    printf("Ingrese id de la propiedad que desea modificar: ");

    scanf("%d",&id);
    fflush(stdin);

    if(id<=0) {
        printf("ERROR: Id ingresado no valido\n");
        fclose(fptr);
        return 1;
    }

    fseek(fptr,0,SEEK_SET);
    fseek(fptr,sizeof(struct registro)*(id-1),SEEK_CUR);
    fread(&aux,sizeof(struct registro),1,fptr);

    if(aux.id==0) {
        printf("ERROR: La propiedad del id %d no existe\n",id);
        fclose(fptr);
        return 1;
    }

    if(aux.activo==0 || aux.activo!=1) {
        printf("ERROR 008: La propiedad no existe o no esta activa\n");
        fclose(fptr);
        return 1;
    }

    impresionEspecifica(aux);

    printf("\nIngrese la fecha de salida no menor a la fecha de entrada o mayor a la fecha actual\n");

    printf("Ingrese dia: ");
    scanf("%d",&a);
    fflush(stdin);
    printf("Ingrese mes: ");
    scanf("%d",&b);
    fflush(stdin);
    printf("Ingrese a%co: ",164);
    scanf("%d",&c);
    fflush(stdin);

    if(a==0 || b==0 || c==0) { ///VALIDACION DE FECHA PARA CALENDARIO GREGORIANO
        printf("ERROR: La fecha ingresada no es valida :/\n");
        fclose(fptr);
        return 1;
    } else if((b==1 || b==3 || b==5 || b==7 || b==8 || b==10 || b==12) && (a>31 || a<1)) {
        printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
        fclose(fptr);
        return 1;
    } else if((b==4 || b==6 || b==9 || b==11) && (a>30 || a<1)) {
        printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
        fclose(fptr);
        return 1;
    } else if(b==2) {
        if(c%4==0) {
            if(c%100!=0 && (a>29 || a<1)) {
                printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
                fclose(fptr);
                return 1;
            } else if(c%100==0 && c%400==0 && (a>29 || a<1)) {
                printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
                fclose(fptr);
                return 1;
            } else if(a>29 || a<1) {
                printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
                fclose(fptr);
                return 1;
            }
        } else if(a>28 || a<1) {
            printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
            fclose(fptr);
            return 1;
        }
    } else if(b>12 || b<1) {
        printf("ERROR: La fecha ingresada no es valida, mes o a%co exceden :/\n",164);
        fclose(fptr);
        return 1;
    }

    int dia1,mes1,anio1;
    int dia2,mes2,anio2;

    char fechaActual[15];

    sscanf(aux.fechaEntrada,"%d-%d-%d",&dia1,&mes1,&anio1);
    fflush(stdin);

    obtenerFecha(fechaActual);
    sscanf(fechaActual,"%d-%d-%d",&dia2,&mes2,&anio2);
    fflush(stdin);

    if(c<anio1 || c>anio2) {
        printf("ERROR: El a%co ingresado no se encuentra en el rango de la propiedad (entre fecha ingreso y fecha actual)\n",164);
        fclose(fptr);
        return 1;
    }

    if(anio1==anio2) {
        if(mes1==mes2) {
            if(a<dia1 || a>dia2) {
                printf("ERROR: El dia ingresado no se encuentra en el rango de la propiedad (entre fecha ingreso y fecha actual)\n");
                fclose(fptr);
                return 1;
            }
        }
        if(b<mes1 || b>mes2) {
            printf("ERROR: El mes ingresado no se encuentra en el rango de la propiedad (entre fecha ingreso y fecha actual)\n");
            fclose(fptr);
            return 1;
        }
    }

    if(c==anio1 && b>mes1 && a>dia1) {
        printf("ERROR: La fecha ingresada es menor a la fecha de entrada\n");
        fclose(fptr);
        return 1;
    }

    if(c==anio2 && b<mes2 && a<dia2) {
        printf("ERROR: La fecha ingresada es mayor a la fecha de hoy\n");
        fclose(fptr);
        return 1;
    }

    char dia[3];
    char mes[3];
    char anio[5];

    sprintf(dia,"%d",a);
    sprintf(mes,"%d",b);
    sprintf(anio,"%d",c);

    strcpy(aux.fechaSalida,dia);
    strcat(aux.fechaSalida,"-");
    strcat(aux.fechaSalida,mes);
    strcat(aux.fechaSalida,"-");
    strcat(aux.fechaSalida,anio);

    aux.activo=0;

    printf("|%-3d | %-12s |%-19s| %-18s | %4d | %2d | %-10.4f | %-13.4f | %-13.4f | %6s | %-15s | %-17s | %-10s | %6d |\n", aux.id, aux.fechaEntrada, aux.zona, aux.ciudad, aux.dormitorios, aux.banos, aux.superficieTotal, aux.superficieCubierta, aux.precio, aux.moneda, aux.tipoPropiedad, aux.operacion, aux.fechaSalida, aux.activo);

    fseek(fptr,0,SEEK_SET);
    fseek(fptr,sizeof(struct registro)*(id-1),SEEK_CUR);
    fwrite(&aux,1,sizeof(struct registro),fptr);

    fclose(fptr);
}

int modificarCiudad() { ///controlar que no deje mod una propeidad que este de baja
    struct registro reg;
    int posi;
    int estado = 0; ///voy a manejar 3 estados -> flag
    char opcion;
    char ciudadNueva[40];
    FILE * arch;
    arch = fopen("propiedades.dat","rb+");

    if(arch!=NULL)
    {
        printf("---------------------------------------------------------\n");
        printf("Ingrese el id de la propiedad que quiere modificar: ");
        scanf("%d",&posi);
        fflush(stdin);
        printf("---------------------------------------------------------\n");

        if(posi==0) {
            printf("ERROR: Id ingresado no valido\n");
            fclose(arch);
            return 1;
        }

        fseek(arch,0,SEEK_SET);
        fseek(arch,(posi-1)*sizeof(struct registro),SEEK_CUR);
        fread(&reg, sizeof(struct registro),1,arch);

        if(reg.id<=0 || reg.activo==0) {
            printf("ERROR 005: Esta propiedad no existe o no esta activa\n");
            fclose(arch);
            return 1;
        }

        impresionEspecificaCabecera();
        impresionEspecifica(reg);
        printf("---------------------------------------------------------------------------------\n");
        printf("Est%c seguro que quiere modificar este archivo? - a para continuar / r para volver \n",160);
        printf("---------------------------------------------------------------------------------\n");

        FconfirmacionMod(&estado);
        fflush(stdin);

        //a partir de este punto -> modificacion efectiva

        if (estado == 1) { //estado de modificacion true, el control del error se hace en la FconfirmacionMod
            printf("-------------------------------------------\n");

            do {
            printf("Ingrese ciudad/barrio nuevo: ");
            fflush(stdin);
            gets(ciudadNueva);
            fflush(stdin);
            printf("\n");
            } while(dataTypeString(ciudadNueva)!=0);

            printf("-------------------------------------------\n");

            formatS(ciudadNueva);
            strcpy(reg.ciudad, ciudadNueva);

            fseek(arch,-sizeof(struct registro), SEEK_CUR);
            fwrite(&reg,sizeof(struct registro), 1, arch);

            printf("-------------------------------------------\n");
            printf("Ciudad/barrio modificad@ correctamente!\n");
            fclose(arch);
        } else if (estado == 2) {
            fclose(arch);
            return 0;
        }
    } else {
        printf("-------------------------------------------\n");
        printf("ERROR 001: Archivo inexistente\n");
        printf("-------------------------------------------\n");
        fclose(arch);
    }
}

int modificarPrecio() {
    struct registro reg;
    int posi;
    int estado = 0; ///flag que maneja 3 estado
    char opcion;
    float precioNuevo;
    FILE * arch;
    arch = fopen("propiedades.dat","rb+");

    if(arch !=NULL) {
        printf("---------------------------------------------------------\n");
        printf("Ingrese el id de la propiedad que quiere modificar: ");
        scanf("%d",&posi);
        fflush(stdin);
        printf("---------------------------------------------------------\n");

        if(posi<=0) {
            printf("ERROR: El id ingresado no es valido\n");
            fclose(arch);
            return 1;
        }

        fseek(arch,0,SEEK_SET);
        fseek(arch,(posi-1)*sizeof(struct registro),SEEK_SET);
        fread(&reg, sizeof(struct registro),1,arch);

        if(reg.activo==0) {
            printf("ERROR 007: La propiedad del id ingresado no existe o no esta activa\n");
            fclose(arch);
            return 1;
        }


        impresionEspecificaCabecera();
        impresionEspecifica(reg);
        printf("---------------------------------------------------------------------------------\n");
        printf("Est%c seguro que quiere modificar este archivo? - a para continuar / r para volver \n",160);
        printf("---------------------------------------------------------------------------------\n");

        FconfirmacionMod(&estado);

        ///a partir de este punto -> modificacion

        if (estado == 1) { //estado de modificacion true
            do{
                printf("-------------------------------------------\n");
                printf("Ingrese precio nuevo: ");
                fflush(stdin);
                scanf("%f",&precioNuevo);
                fflush(stdin);
                printf("-------------------------------------------\n");
            }while(precioNuevo <= 0);
            //fflush(stdin);
            reg.precio = precioNuevo;
            fseek(arch,-sizeof(struct registro), SEEK_CUR);
            fwrite(&reg,sizeof(struct registro), 1, arch);
            printf("-------------------------------------------\n");
            printf("Precio modificad@ correctamente!\n");
            fclose(arch);
        }
    } else {
        printf("-------------------------------------------\n");
        printf("ERROR 001: Archivo inexistente\n");
        printf("-------------------------------------------\n");
        fclose(arch);
    }
}

int opcionModificar(int *opciones) {

    FILE *fptr;
    fptr=fopen("propiedades.dat","rb");

    if(fptr==NULL) {
        printf("ERROR 001: Archivo inexistente\n");
        fclose(fptr);
        return 1;
    }

    fflush(stdin);
    scanf("%i", opciones);
    fflush(stdin);
    switch(*opciones){
        case 1: modificarCiudad();
        break;
        case 2: modificarFechaSalida();
        break;
        case 3: modificarPrecio();
        break;
        case 0: printf("Saliendo...\n");
        break;
        default: printf("Opci%cn inv%clida\n",162,160);
        break;
    }
}

int menuModificar() {

    FILE * fptr;
    fptr=fopen("propiedades.dat","rb");

    if(fptr==NULL) {
        printf("ERROR 001: Archivo inexistente\n");
        fclose(fptr);
        return 1;
    }
    fclose(fptr);

    int opciones=999;

    while(opciones!=0) {
        printf("-------------------------------------------\n");
        printf("Seleccione que quiere modificar\n");
        printf("1. Ciudad / barrio\n");
        printf("2. Fecha de salida\n");
        printf("3. Precio\n");
        printf("0. Volver al men%c principal\n", 163);
        printf("-------------------------------------------\n");
        opcionModificar(&opciones);
    }
}

void listarBajas() {

    FILE*arch;

    struct registro aux;
    char nombreArchivo[35]="propiedades_bajas_";
    char inputFecha[6];

    printf("-------------------------------------------\n");
    printf("Ingrese la fecha cuando se realizaron las bajas de las propiedades que deses ver:\n");

    printf("D%ca: ",161);
    fflush(stdin);
    gets(inputFecha);
    strcat(nombreArchivo, (strcat(inputFecha, "-")));

    printf("Mes: ");
    fflush(stdin);
    gets(inputFecha);
    strcat(nombreArchivo, (strcat(inputFecha, "-")));

    printf("A%co: ", 164);
    fflush(stdin);
    gets(inputFecha);
    printf("-------------------------------------------\n");
    strcat(nombreArchivo, inputFecha);
    strcat(nombreArchivo, ".xyz");

    //printf("\n%s\n" , nombreArchivo);

    arch = fopen(nombreArchivo,"rb");

    if(arch!=NULL) {
        printf("\n\n");
        impresionEspecificaCabecera();
        fseek(arch,0,SEEK_SET);
        fread(&aux,sizeof(struct registro),1,arch);//lectura previa

        while(!feof(arch))//repito hasta acabar el archivo
        {
            impresionEspecifica(aux);
            fflush(stdin);
            fread(&aux,sizeof(struct registro),1,arch);
        }
        printf("\n\n");
        fclose(arch);
    } else {
        printf("El archivo de la fecha ingresada no existe\n");
        printf("-------------------------------------------\n");
    }
}

int listarTipoPropiedad() {
    char inputOpereta[30], inputProp[30];
    int opcion;
    int flag=0;

    for(int i=0;i<30;i++)
    {
        inputOpereta[i]='\0';
        inputProp[i]='\0';
    }

    struct registro reg;
    FILE*arch;
    arch = fopen("propiedades.dat","rb");//solo voy a printar los campos activos

    if (arch == NULL) { //control al abrir y si todo sale bien continuo con lo que quiero hacer
        printf("ERROR 001: Archivo inexistente\n");
        fclose(arch);
        return 1;
    }

    do {
        printf("-------------------------------------------\n");
        printf("Ingrese tipo de propiedad:\n");
        printf("1. Casa\n");
        printf("2. Departamento\n");
        printf("3. PH\n");
        printf("0. Volver\n");
        printf("-------------------------------------------\n");
        scanf("%d" ,& opcion);
        fflush(stdin);

        if(opcion!=0 && opcion!=1 && opcion!=2 && opcion!=3) {// si no marco una opcion valida
            printf("--AVISO--\n");
            printf("Opci%cn inv%clida\n", opcion,162,160);

        } else { // si marco una opcion valida
            printf("Procesando...\n");
        }
    } while(opcion!=0 && opcion!=1 && opcion!=2 && opcion!=3);

    switch(opcion) {
        case 0:
            fclose(arch);
            return 0;
        break;
        case 1:
            strcpy(inputProp,"Casa");
        break;
        case 2:
            strcpy(inputProp,"Departamento");
        break;
        case 3:
            strcpy(inputProp,"PH");
        break;
        default:

        break;
    }

    printf("-------------------------------------------\n");

    fseek(arch,0,SEEK_SET);

    while(!feof(arch)) {
        fread(&reg,sizeof(struct registro),1,arch);
        if(strcmp(reg.tipoPropiedad, inputProp) == 0 && !feof(arch)) {
            if(flag==0) {
                impresionEspecificaCabecera();
                flag=1;
            }
            impresionEspecifica(reg);
        }
    }

    if(flag == 0 ) { // si nunca en toda la lectura del archivo se encuentra
            printf("No hay activos cargados\n");
    }
    fclose(arch);
}

int listarTodo()
{
    struct registro reg;
    FILE*arch;
    arch = fopen("propiedades.dat","rb");

    if (arch == NULL) //Control al abrir y si todo sale bien continuo con lo que quiero hacer
        {
            printf("ERROR 001: Archivo inexistente\n");
            fclose(arch);
            return 1;
        }

    fclose(arch);//vuelvo a cerrar
    imprimoTodo(reg);
}

int listarRangoFecha() {
    printf("------------------------------\n");

    struct registro aux;

    int minDD,minMM,minYY;
    int maxDD,maxMM,maxYY;

    int a,b,c;

    FILE *fptr;
    fptr=fopen("propiedades.dat","rb");

    if (fptr == NULL){
        printf("ERROR 001: Archivo inexistente\n");
        fclose(fptr);
        return 1;
    }

    printf("Para realizar la busqueda ingrese una fecha minima y maxima.\n");

    printf("\nIngrese fecha minima\n\n");
    fflush(stdin);
    printf("Ingrese dia: ");
    scanf("%d",&minDD);
    fflush(stdin);
    printf("Ingrese mes: ");
    scanf("%d",&minMM);
    fflush(stdin);
    printf("Ingrese a%co: ",164);
    scanf("%d",&minYY);
    fflush(stdin);

    if(minDD==0 || minMM==0 || minYY==0) { ///VALIDACION DE FECHA PARA CALENDARIO GREGORIANO
        printf("ERROR: La fecha ingresada no es valida :/\n");
        fclose(fptr);
        return 1;
    } else if((minMM==1 || minMM==3 || minMM==5 || minMM==7 || minMM==8 || minMM==10 || minMM==12) && (minDD>31 || minDD<1)) {
        printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
        fclose(fptr);
        return 1;
    } else if((minMM==4 || minMM==6 || minMM==9 || minMM==11) && (minDD>30 || minDD<1)) {
        printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
        fclose(fptr);
        return 1;
    } else if(minMM==2) {
        if(minYY%4==0) {
            if(minYY%100!=0 && (minDD>29 || minDD<1)) {
                printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
                fclose(fptr);
                return 1;
            } else if(minYY%100==0 && minYY%400==0 && (minDD>29 || minDD<1)) {
                printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
                fclose(fptr);
                return 1;
            } else if(minDD>29 || minDD<1) {
                printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
                fclose(fptr);
                return 1;
            }
        } else if(minDD>28 || minDD<1) {
            printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
            fclose(fptr);
            return 1;
        }
    } else if(minMM>12 || minMM<1) {
        printf("Error: La fecha ingresada no es valida, mes o a%co exceden :/\n",164);
        fclose(fptr);
        return 1;
    }

    printf("\nIngrese fecha maxima\n\n");
    fflush(stdin);
    printf("Ingrese dia: ");
    scanf("%d",&maxDD);
    fflush(stdin);
    printf("Ingrese mes: ");
    scanf("%d",&maxMM);
    fflush(stdin);
    printf("Ingrese a%co: ",164);
    scanf("%d",&maxYY);
    fflush(stdin);


    /* VALIDACION DE FECHA PARA AÑO COMERCIAL
    if(maxDD==0 || maxMM==0 || maxYY==0) {
        printf("Error: La fecha ingresada no es valida :/\n");
        return 1;
    } else if(maxDD>30 || maxDD<1 || maxMM>12 || maxMM<1) {
        printf("Error: La fecha ingresada no es valida, mes o a%co exceden :/\n",164);
        return 1;
    }*/

    if(maxDD==0 || maxMM==0 || maxYY==0) { ///VALIDACION DE FECHA PARA CALENDARIO GREGORIANO
        printf("ERROR 006: La fecha ingresada no es valida :/\n");
        fclose(fptr);
        return 1;
    } else if((maxMM==1 || maxMM==3 || maxMM==5 || maxMM==7 || maxMM==8 || maxMM==10 || maxMM==12) && (maxDD>31 || maxDD<1)) {
        printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
        fclose(fptr);
        return 1;
    } else if((maxMM==4 || maxMM==6 || maxMM==9 || maxMM==11) && (maxDD>30 || maxDD<1)) {
        printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
        fclose(fptr);
        return 1;
    } else if(maxMM==2) {
        if(maxYY%4==0) {
            if(maxYY%100!=0 && (maxDD>29 || maxDD<1)) {
                printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
                fclose(fptr);
                return 1;
            } else if(maxYY%100==0 && maxYY%400==0 && (maxDD>29 || maxDD<1)) {
                printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
                fclose(fptr);
                return 1;
            } else if(maxDD>29 || maxDD<1) {
                printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
                fclose(fptr);
                return 1;
            }
        } else if(maxDD>28 || maxDD<1) {
            printf("ERROR 006: La fecha ingresada no es valida, dia excede\n");
            fclose(fptr);
            return 1;
        }
    } else if(maxMM>12 || maxMM<1) {
        printf("Error: La fecha ingresada no es valida, mes o a%co exceden :/\n",164);
        fclose(fptr);
        return 1;
    }

    if(minYY>maxYY) {
        printf("ERROR: A%co minimo mayor a a%co maximo\n",164,164);
        fclose(fptr);
        return 1;
    } else if(minYY==maxYY && minMM>maxMM) {
        printf("ERROR: Mes minimo mayor a mes maximo\n");
        fclose(fptr);
        return 1;
    } else if(minYY==maxYY && minMM==maxMM && minDD>maxDD) {
        printf("ERROR: Dia minimo mayor a dia maximo\n");
        fclose(fptr);
        return 1;
    }

    /*
    char placeHolder[15];
    obtenerFecha(placeHolder);
    printf("%s\n",placeHolder);

    fflush(stdin);
    sscanf(placeHolder,"%d-%d-%d",&a,&b,&c);
    printf("%d %d %d\n",a,b,c);
    */

    fseek(fptr,0,SEEK_SET);

    printf("\nLas propiedades registradas entre el %d-%d-%d y el %d-%d-%d son:\n\n",minDD,minMM,minYY,maxDD,maxMM,maxYY);

    while(!feof(fptr)) {
        a=0;
        b=0;
        c=0;
        fread(&aux,sizeof(struct registro),1,fptr);
        fflush(stdin);
        sscanf(aux.fechaEntrada,"%d-%d-%d",&a,&b,&c);

        /*
        if(c==minYY && b>=minMM) {
            if(b==minMM && a>=minDD) {
                if(a==minDD) {
                    printf();
                }
            }
        }*/

        if(c==minYY && c==maxYY) {
            if(b==minMM && b==maxMM) {
                if(a>=minDD && a<=maxDD) {
                    impresionEspecifica(aux);
                    continue;
                }
            } else if(b==minMM && a>=minDD) {
                impresionEspecifica(aux);
                continue;
            } else if(b==maxMM && a<=maxDD) {
                impresionEspecifica(aux);
                continue;
            } else if(b!=minMM && b!=maxMM) {
                impresionEspecifica(aux);
                continue;
            }
        } else if(c==minYY && b>=minMM && !feof(fptr)) {
            if(b==minMM && a>=minDD) {
                printf("|%-3d | %-12s |%-19s| %-18s | %4d | %2d | %-10.4f | %-13.4f | %-13.4f | %6s | %-15s | %-17s | %-10s | %6d |\n", aux.id, aux.fechaEntrada, aux.zona, aux.ciudad, aux.dormitorios, aux.banos, aux.superficieTotal, aux.superficieCubierta, aux.precio, aux.moneda, aux.tipoPropiedad, aux.operacion, aux.fechaSalida, aux.activo);
                continue;
            }
        } else if(c==maxYY && b<=maxMM && !feof(fptr)) {
            if(b==maxMM && a<=maxDD) {
                printf("|%-3d | %-12s |%-19s| %-18s | %4d | %2d | %-10.4f | %-13.4f | %-13.4f | %6s | %-15s | %-17s | %-10s | %6d |\n", aux.id, aux.fechaEntrada, aux.zona, aux.ciudad, aux.dormitorios, aux.banos, aux.superficieTotal, aux.superficieCubierta, aux.precio, aux.moneda, aux.tipoPropiedad, aux.operacion, aux.fechaSalida, aux.activo);
                continue;
            }
        } else if(minYY<c && c<maxYY && !feof(fptr)) {
            printf("|%-3d | %-12s |%-19s| %-18s | %4d | %2d | %-10.4f | %-13.4f | %-13.4f | %6s | %-15s | %-17s | %-10s | %6d |\n", aux.id, aux.fechaEntrada, aux.zona, aux.ciudad, aux.dormitorios, aux.banos, aux.superficieTotal, aux.superficieCubierta, aux.precio, aux.moneda, aux.tipoPropiedad, aux.operacion, aux.fechaSalida, aux.activo);
        }
    }
    fclose(fptr);
    printf("\n-------------------------------\n");
}

int switchLista(int opcion)
 {
    switch(opcion)
    {
        case 1:
            listarTodo();
        break;

        case 2:
            listarActivos();
        break;

        case 3:
            listarTipoPropiedad();
        break;

        case 4:
            listarRangoFecha();
        break;

        case 5:
            listarBajas();
        break;
        case 0:
            printf("Saliendo :) ...\n"); //menuPrincipal();
        break;
        default:
            printf("Opci%cn inv%clida\n", 162,160);
        break;
    }
 }

void abreSubMenu()
{
    int opcion=-1;

    while(opcion!=0)
    {
        opcion=-1;
        printf("-------------------------------\n");
        printf("Selecione la opci%cn: \n",162); //ponerlo lindo
        printf("1. Listar todo \n");
        printf("2. Listar campos activos\n"); //mostrar solo campos activos
        printf("3. Listar por tipo de propiedad\n");
        printf("4. Listar por tiempo de ingreso\n");
        printf("5. Listar bajas \n");
        printf("0. Salir del submen%c \n", 163);
        printf("-------------------------------\n");
        scanf("%d",&opcion);
        fflush(stdin);
        switchLista(opcion); //funciona pq la funcion solo evalua que hago despues siempre vuelve a aqui asi salto
    }
}

int buscar()
{
    struct registro reg;
    FILE*arch;
    arch = fopen("propiedades.dat","rb");

    if (arch == NULL){
        printf("ERROR 001: Archivo inexistente\n");
        fclose(arch);
        return 1;
    }

    int opcion;
    int inputID, flag=0;
    char inputOpereta[30], inputProp[30];

    do//Menu para saber de que modo quiere buscar la propiedad
    {
        printf("-------------------------------------------\n");
        printf("1. Buscar por ID\n");
        printf("2. Buscar por operaci%cn\n", 162);
        printf("0. Volver\n");
        printf("-------------------------------------------\n");
        scanf("%d",&opcion);
        fflush(stdin);
        if(opcion!=0 && opcion!=1 && opcion!=2)
        {// si no marco una opcion valida
            printf("--AVISO--\n");
            printf("ERROR 003: Opci%cn de busqueda inv%clida\n",162,160);
        }else
        {// si marco una opcion valida
            printf("-------------------------------------------\n");
            printf("Procesando...\n");
        }
    }while(opcion!=0 && opcion!=1 && opcion!=2);// si no marco una opcion valida

    //Menu si quiere buscar por ID
    if(opcion==1)
    {
        printf("-------------------------------------------\n");
        printf("Ingrese ID: ");
        scanf("%d" , &inputID);
        fflush(stdin);
        printf("-------------------------------------------\n\n");

        if(inputID==0) {
            printf("ERROR: El id ingresado no es valido\n\n");
            fclose(arch);
            return 1;
        }

        while( flag==0 && (fread(&reg,sizeof(struct registro), 1, arch) == 1))
        {
            //Muestro las propiedad con ese id
            if(reg.id == inputID && reg.banos != 0)
            {
                impresionEspecificaCabecera();
                impresionEspecifica(reg);
                flag=1;
            }
        }
        //Mensaje al no encontrar propiedad con ID solicitado
        if(flag==0)// ete if e nuevo
        {
            printf("No se han encontrado propiedad con campo solicitado (busco un ID que no existe)\n\n");
        }
    }

    //Menu de busqueda por operacion
    if(opcion==2)
    {
        do
        {
            printf("-------------------------------------------\n");
            printf("Ingrese tipo de operaci%cn:\n",162);
            printf("1. Venta\n");
            printf("2. Alquiler\n");
            printf("3. Alquiler temporal\n");
            printf("0. Volver\n");
            printf("-------------------------------------------\n");
            scanf("%d" ,& opcion);
            fflush(stdin);

            if(opcion!=0 && opcion!=1 && opcion!=2 && opcion!=3)
            {// si no marco una opcion valida
                    printf("--AVISO--\n");
                    printf("%d Opcion invalida\n", opcion);
            }else
            {// si marco una opcion valida
                printf("-------------------------------------------\n");
                printf("Procesando...\n");
            }
        }while(opcion!=0 && opcion!=1 && opcion!=2 && opcion!=3);// si no marco una opcion valida

        //Cargo un array con la opcion de operacion elegida
        switch(opcion)
        {
            case 1:
                strcpy(inputOpereta,"Venta");
                break;
            case 2:
                strcpy(inputOpereta,"Alquiler");
                break;
            case 3:
                strcpy(inputOpereta,"Alquiler temporal");
                break;
            default:
                break;
        }

        //Menu para seleccionar tipo de propiedad
        if(!opcion==0)//Si opcion es 0 lo manda al menu principal
        {
            do
            {
                printf("-------------------------------------------\n");
                printf("Ingrese tipo de propiedad:\n");
                printf("1. Casa\n");
                printf("2. Departamento\n");
                printf("3. PH\n");
                printf("0. Volver\n");
                printf("-------------------------------------------\n");
                scanf("%d" ,& opcion);
                fflush(stdin);

                if(opcion!=0 && opcion!=1 && opcion!=2 && opcion!=3)
                {// si no marco una opcion valida
                    printf("--AVISO--\n");
                    printf("%d Opcion invalida\n", opcion);
                    //printf("Opcion invalida\n");
                }else
                {// si marco una opcion valida
                    printf("-------------------------------------------\n");
                    printf("Procesando...\n");
                }
            }while(opcion!=0 && opcion!=1 && opcion!=2 && opcion!=3);// si no marco una opcion valida

            //Cargo un array con la opcion de tipo de propiedad elegida
            switch(opcion)
            {
                case 1:
                    strcpy(inputProp,"Casa");
                    break;
                case 2:
                    strcpy(inputProp,"Departamento");
                    break;
                case 3:
                    strcpy(inputProp,"PH");
                    break;
                default:
                    break;
            }

            printf("-------------------------------------------\n");
            while(!opcion==0 && fread(&reg,sizeof(struct registro), 1, arch) == 1)
            {
                //Muestra las propiedades con la operacion y tipo de propiedad solicitada
                if((strcmp(reg.operacion, inputOpereta)==0) && strcmp(reg.tipoPropiedad, inputProp)==0)
                {
                    //printf("\n");
                    if(flag != 1){
                        impresionEspecificaCabecera();
                    }
                    impresionEspecifica(reg);
                    flag=1;
                }
            }

            //Mensaje si no encuentra ninguna propiedad con los campos solicitados
            if(!opcion==0 && flag==0)//ete tmb
            {
                printf("No se han encontrado propiedad con campo solicitado\n");
            }
        }
    }
    fclose(arch);
}

int menuPrincipal() {
    int opcion=999;
    printf("-------------------------------------------\n");
    printf("--------MEN%c PRINCIPAL DE OPCIONES---------\n", 163);
    printf("-----------Ingrese una opci%cn--------------\n",162);
    printf("1. Buscar\n");
    printf("2. Listar \n");
    printf("3. Modificar\n");
    printf("4. Crear archivo\n");
    printf("5. Alta de nueva propiedad\n");
    printf("6. Baja l%cgica\n",162);
    printf("7. Baja f%csica\n",161);
    printf("0. Salir\n");
    printf("-------------------------------------------\n");
    scanf("%d",&opcion);
    fflush(stdin);
    return opcion;
}

int main()
{
    int banderaFCrea=0;
    int opcion=1;

    /* CARGAR FECHAS EN EL ARCHIVO

     FILE *arch;
    arch=fopen("propiedades.dat","r+b");

    int i;
    int dim=5;
    struct registro aux[dim];

    for(i=1;i<dim;i++) {
        aux[i].id=i;
    }

    strcpy(aux[1].fechaEntrada,"1-1-2000");
    strcpy(aux[2].fechaEntrada,"10-9-2023");
    strcpy(aux[3].fechaEntrada,"11-5-2011");
    strcpy(aux[4].fechaEntrada,"25-3-2024");
    strcpy(aux[5].fechaEntrada,"1-1-2050");

    fseek(arch,0,SEEK_SET);
    fwrite(&aux,dim,sizeof(struct registro),arch);

    fclose(arch);
    */

    while(opcion!=0)
    {
        opcion = menuPrincipal();

        switch(opcion)
        {
            case 1:
                buscar();
            break;

            case 2:
                abreSubMenu();
            break;

            case 3:
                menuModificar();
            break;

            case 4:
                crearArchivo(&banderaFCrea);
            break;

            case 5:
                alta();
            break;

            case 6:
                bajaLogica();
            break;

            case 7:
                bajaFisica();
            break;

            case 0:
                opcion = 0;
            break;
            default:
                printf("ERROR 002: Opci%cn inv%clida (fuera del men%c)\n",162,160,163);
            break;
        }
    }
    return 0;
}
