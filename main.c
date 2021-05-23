#include<stdio.h>
#include<stdlib.h>
#include <math.h>
//Lo deje como idea
/*
typedef struct
{
    int x;
    int y;
    int id;
}Coordenadas;

typedef struct 
{
    Coordenadas **Entrega;
}Entregas;
*/
int main()
{

    printf("-----------------------------------------------------------------------\n");
    printf("                          MENU DE RUTAS                                \n");
    printf("-----------------------------------------------------------------------\n");
    int op=2;
    while(op!=0)
    {
        printf("1.Importar archivo de coordenadas\n");
        printf("2.Distancia entre entregas\n");
        printf("3.Mostrar 3 entregas más cercanas a las coordenadas ingresadas\n");
        printf("4.Crear ruta\n");
        printf("5.Generar ruta aleatoria\n");
        printf("6.Mejorar ruta\n");
        printf("7.Mostrar rutas\n");
        printf("8.Mejor ruta\n");
        printf("0.Salir\n");
        scanf("%d",&op);
        switch (op)
        {
            case 1:printf("No Implementada\n");break;
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