#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "list.h"
//Lo deje como idea

typedef struct
{
    int x;
    int y;
    int id;
}Entrega;

typedef struct{
    List* entregas;
}Entregas;

Entrega* createEntrega(int id,int x,int y){
    Entrega* new = (Entrega*) malloc(sizeof(Entrega));
    new->id=id;
    new->x=x;
    new->y=y;
    return new;
}

//Conversor de char a int
int conversorInt(char * cadena){
    int i=cadena[0]-'0';
    if(cadena[1]-'0'>=0){
        i=i*10;
        i+=cadena[1]-'0';
    }
    return i;
}

void importar(List *E){

    printf("-----------------------------------------------------------------------\n");
    char nameFile[101];
    FILE *file;
    gets(nameFile);
    //Abrimos el archivo ingresado por el usuario
    do{
        printf("\nIngrese el nombre del archivo sin extension (.txt):");
        gets(nameFile);
        strcat(nameFile,".txt");
        file = fopen (nameFile, "r" ); 
        printf("-----------------------------------------------------------------------\n");
    }while(!file);
        // Cadena para guardar la linea completa del archivo txt
        char linea[1024];
        int numEn,cont=1;
        printf("Ingrese el numero de entregas a ingresar: ");
        scanf("%d",&numEn);
        printf("\n%d este es el total de entregas a solicitar\n",numEn);

        while (fgets (linea, 1023, file) != NULL) { 
            int x,y,id,j=0;
            bool next=true,first=false;
            char auxX[10],auxY[10];
            id=cont;
            for(int i=0;i<strlen(linea);i++){
                if(linea[i]==' '){
                    if(first)next=false;
                }
                else{
                    if(next){
                        auxX[i]=linea[i];
                        first=true;
                    }
                    else{
                        auxY[j]=linea[i];
                        j++;
                    }
                }
            }
            x=conversorInt(auxX);
            y=conversorInt(auxY);
            Entrega* entrega=createEntrega(id,x,y);
            pushBack(E,entrega);

            if(cont==numEn)break;
            cont++;
        }

        fclose(file);
    printf("-----------------------------------------------------------------------\n");
    printf("***************  Las entregas se cargaron exitosamente  ***************\n");
    printf("-----------------------------------------------------------------------\n");
    printf("\n");
}


int main()
{
    List* E=createList();

    printf("-----------------------------------------------------------------------\n");
    printf("                          MENU DE RUTAS                                \n");
    printf("-----------------------------------------------------------------------\n");
    int op=2;
    while(op!=0)
    {
        printf("1.Importar archivo de coordenadas\n");
        printf("2.Distancia entre entregas\n");
        printf("3.Mostrar 3 entregas mas cercanas a las coordenadas ingresadas\n");
        printf("4.Crear ruta\n");
        printf("5.Generar ruta aleatoria\n");
        printf("6.Mejorar ruta\n");
        printf("7.Mostrar rutas\n");
        printf("8.Mejor ruta\n");
        printf("0.Salir\n");
        scanf("%d",&op);
        switch (op)
        {
            case 1:importar(E);break;
            case 2:printf("No Implementada\n");break;
            case 3:printf("No Implementada\n");break;
            case 4:printf("No Implementada\n");break;
            case 5:printf("No Implementada\n");break;
            case 6:printf("No Implementada\n");break;
            case 7:printf("No Implementada\n");break;
            case 8:printf("No Implementada\n");break;
        }
    }
    return 0;
}