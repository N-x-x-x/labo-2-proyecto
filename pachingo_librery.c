#include<stdio.h>
#include<time.h>
#include<string.h>

int esNumero(char coso){// si esta funcion devuelve un 1 lo que ingreso es un numero
    if( (coso<48 || coso>57) )//si coso esta entre el rago de lo que es un numero sigo
    {
        printf("Tipo de dato invalido: Ingreso caracter no entero\n");
        return 0;
    }else {
        return 1;
    }//si no metio cual quier cosa
}

void obtenerFecha(char cadena[])//obtengo fecha
{
    time_t tiempo_ahora= time(0);
    struct tm *mi_tiempo=localtime(&tiempo_ahora);
    int numero;
    char array[40];
    char temp[10];

    numero = mi_tiempo->tm_mday;
    sprintf(temp, "%d", numero);
    strcpy(array,temp);

    fflush(stdin);

    strcat(array,"-");

    numero = mi_tiempo->tm_mon+1;
    sprintf(temp, "%d", numero);
    strcat(array,temp);

    strcat(array,"-");

    numero = mi_tiempo->tm_year+1900;
    sprintf(temp, "%d", numero);
    strcat(array,temp);

    fflush(stdin);

    //printf("fecha: %s\n", array);

    strcpy(cadena,array);
}

int dataTypeId(char cadena[])
{
    int i,flag=0;

    if(cadena[0]=='\n')
    {
        printf("Tipo de dato invalido: Dejo el campo vacio\n\n");
        flag=1;
    }

    for(i=0;cadena[i]!='\n';i++)
    {
        if( (cadena[i]<48 || cadena[i]>57) && flag==0)
        {
            printf("Tipo de dato invalido: Ingreso numero no entero o negativo\n\n");
            flag=1;
        }
    }
    return flag;
}

int dataTypeString(char cadena[])
{
    int i,flag=0;
    for(i=0;cadena[i]!='\0';i++)
    {
        if(cadena[i]>47 && cadena[i]<58 && flag==0)
        {
            printf("Tipo de dato invalido: Ingreso entero o flotante\n");
            flag=1;
        }else if(cadena[0]=='\n' && flag==0)
        { /**MOD**/
            printf("Tipo de dato invalido: Dejo el campo vacio\n");
            flag=1;
        }
    }
    return flag;
}

int dataTypeInt(char cadena[])
{
    int i,flag=0;

    if(cadena[0]==48 || cadena[0]=='\n')
    {
        printf("Tipo de dato invalido: Dejo el campo vacio\n");
        flag=1;
    }

    for(i=0;cadena[i]!='\n';i++)
    {
        if( (cadena[i]<48 || cadena[i]>57) && flag==0)
        {
            printf("Tipo de dato invalido: Ingreso numero no entero o negativo\n");
            flag=1;
        }
    }
    return flag;
}

int datatTypeFloat(char cadena[])
{
    int i,flag=0;

    if(cadena[0]==48 || cadena[0]=='\n')
    {
        printf("Tipo de dato invalido: Dejo el campo vacio\n");
        flag=1;
    }

    for(i=0;cadena[i]!='\n';i++)
    {
        if((cadena[i]>57 || cadena[i]<48) && cadena[i]!='.' && flag==0)
        {
            printf("Tipo de dato invalido: Ingeso caracter no entero ni flotante\n");
            flag=1;
        }
    }
    return flag;
}

int dataValidation2Int(char cadena[])
{
    int i,flag=0;

    if(cadena[1]!='\n') {
        printf("ERROR: El dato ingresado no concuerda con las opciones dadas\n");
        flag=1;
        return flag;
    }

    if(cadena[0]==48 || cadena[0]=='\n')
    {
        printf("Tipo de dato invalido: Dejo el campo vacio\n");
        flag=1;
    }

    for(i=0;cadena[i]!='\n';i++)
    {
        if(cadena[i]!=49 && cadena[i]!=50 && flag==0)
        {
            printf("Tipo de dato invalido\n");
            flag=1;
        }
    }
    return flag;
}

int dataValidation3Int(char cadena[])
{
    int i,flag=0;

    if(cadena[1]!='\n') {
        printf("ERROR: El dato ingresado no concuerda con las opciones dadas\n");
        flag=1;
        return flag;
    }

    if(cadena[0]==48 || cadena[0]=='\n')
    {
        printf("Tipo de dato invalido: Dejo el campo vacio\n");
        flag=1;
    }

    for(i=0;cadena[i]!='\n';i++)
    {
        if(cadena[i]!=49 && cadena[i]!=50 && cadena[i]!=51 && flag==0)
        {
            printf("Tipo de dato invalido\n");
            flag=1;
        }
    }
    return flag;
}

void formatS(char cadena[])
{
    int i;
    int flag1=0;

    for(i=0;cadena[i]!='\0';i++)
    {
        if(((cadena[i]>96 && cadena[i]<123) || (cadena[i]>64 && cadena[i]<91)) && flag1==0)
        {
                if(cadena[i]>96 && cadena[i]<123)
                {
                    cadena[i]-=32;
                }

                flag1=1;
                continue;
        }

        if(cadena[i]==32 || cadena[i]=='.')
        {
            flag1=0;
        }

        if(cadena[i]>64 && cadena[i]<91 && flag1==1)
        {
            cadena[i]+=32;
        }
    }
}

void clearBuffer(char cadena[],int dim)
{
    int i;

    for(i=0;i<dim;i++)
    {
        cadena[i]='\0';
    }
}

void cutEnter(char cadena[])
{
    int i;

    for(i=0;cadena[i]!='\0';i++)
    {
        if(cadena[i]=='\n') cadena[i]='\0';
    }
}

void FconfirmacionMod(int *estado)
{
    char opcion;
    do {///posible funcion -> de que?
        scanf(" %c", &opcion);
        fflush(stdin);

        if (opcion == 'a' || opcion == 'A') {
                *estado = 1;//estado de modificacion
        } else if (opcion == 'r' || opcion == 'R') {
            //fmod(arch, reg);///posible error
            *estado = 2;//estado de salida
        } else {
            *estado = 0;//estado de control de errores
            printf("------------------------------------------------------------\n");
            printf("Opci%cn inv%clida, ingrese a para continuar / r para volver: \n",162,160);
            printf("------------------------------------------------------------\n");
        }
    }while (*estado == 0);
}



