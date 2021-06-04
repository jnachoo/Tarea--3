#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "treemap.h"
//Lo deje como idea

typedef struct{
    int x;
    int y;
    int id;
}Entrega;

typedef struct{
    float distancia;
    char nombre[50];
    List *listaruta;
}Ruta;

typedef struct{
    List *entregas;
    int Numentregas;
}Entregas;

Entrega* createEntrega(int id,int x,int y){
    Entrega* new = (Entrega*) malloc(sizeof(Entrega));
    new->id=id;
    new->x=x;
    new->y=y;
    return new;
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
            int x=0,y=0,id,j=0,contX=1,contY=1;
            bool next=true,first=false;
            id=cont;
            for(int i=0;i<strlen(linea);i++){
                if(linea[i]==' '){
                    if(first)next=false;
                }
                else{
                    if(next){
                        x=x*contX;
                        x+=linea[i]-'0';
                        first=true;
                        contX=10;
                    }
                    else{
                        if(linea[i]=='\n')break;
                        y=y*contY;
                        y+=linea[i]-'0';
                        contY=10;
                        j++;
                    }
                }
            }
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

float distancia(Entrega * entrega1, Entrega * entrega2){
    float x,y,d;
    x=fabs(entrega1->x - entrega2->x);
    y=fabs(entrega1->y - entrega2->y);
    //printf("este es x %d\n",entrega1->x);
   // printf("este es x %f\n",y);
    x=pow(x,2);
    y=pow(y,2);

    d=sqrt(x+y);
    return d;
}

void distanciaEntreEntregas(List * E){
    int id1,id2;
    float d;
    if(vacio(E)){
        printf("Aun no se han ingresado entregas, pruebe cargando un archivo\n");
        return;
    }
    printf("Ingrese el numero de las entregas para calcular distancia:\n");
    printf("Entrega 1:");
    scanf("%d",&id1);
    printf("Entrega 2:");
    scanf("%d",&id2);
    Entrega* e1;
    Entrega* e2;
    Entrega* e=firstList(E);
    while(e){
        if(e->id==id1){
            e1=e;
        }
        if(e->id==id2){
            e2=e;
        }
        e=nextList(E);
    }
    d=distancia(e1,e2);
    printf("la distancia entre la entrega %d y %d es %f\n",id1,id2,d);
    printf("\n-----------------------------------------------------------------------\n");
}
int solucionador(int *a, int tamano)
{
    int i,j,aux,k=0;

    for(i=1 ; i<tamano ; i++)
    {
        aux = i;
        for(j=0 ; j<tamano ; j++)
        {
            if(a[j]==aux)
            {
                k=0;
                break;
            }
            else
            {
                k++;
            }
        }
        if(k!=0)
        {
            return aux;
        }
    }
}
//Falla entregando Entregas repetidas
int rutaAleatoria(List* E, Ruta* r, Entregas *x, TreeMap*map)
{
    int i,j,cont=0,tamano,numero,*a,*b,aux;
    float dist=0;
    Entrega *e,*e2,*e1;
    tamano = size(E);
    a = malloc (sizeof(int)*tamano);
    b = malloc (sizeof(int)*tamano);
    for (i=0 ; i < tamano ; i++)
    {
        a[i] = -1;
        b[i]  = -1;
    }
    for(i=0 ; i<tamano ; i++)
    {
        numero = rand() % (tamano-2)+1;
        a[i] = numero;
    }
    for(i=0 ; i<tamano ; i++)
    {
        aux = a[i];
        for ( j = 0; j < tamano; j++)
        {
            if(j != i && aux == a[j])
            {
                a[j] = -1;
            }
        }
          
    }
    for(i=0 ; i<tamano ; i++)
    {
        if(a[i]==-1)
        {
            a[i] = solucionador(a,tamano);
        }
    }
    printf("\nLa ruta seguida es: ");
    j=0;
    for(i=0 ; i<tamano ; i++)
    {
        e = firstList(E);
        e2 = e;
        while(e)
        {
            if(a[i] == e->id)
            {
                printf("[%d] ",e->id);
                pushBack(r->listaruta,e);
                if(j==0)
                {
                    e1 = e;
                    j++;
                }
                else
                {
                    if(j==1)
                    {
                        e2 = e;
                        
                        dist += distancia(e1,e2);
                        e1 = e2;
                    }
                }
            }
            e = nextList(E);
        }
    }
    r->distancia = dist;
    // i = rand() % 100;
    printf("\nEscriba el nombre de la Ruta\n");
    scanf("%s",&r->nombre);
    printf("-----------------------------------------------------------------------\n");
    printf("***** La distancia de la ruta %s es : %f *****\n",r->nombre,r->distancia);
    //printf("***** La distancia de la ruta %s es : %d ***o**\n",r->nombre,i);
    printf("-----------------------------------------------------------------------\n\n");
    x->Numentregas++;
   //char cad[30];
    //sprintf( cad, "%f" , r->distancia);
   // i = *((int*)dist);
   if(!r)printf("NULL;\n");
   if(r != NULL)printf("NO-NULL;\n");
    insertTreeMap(map,&r->distancia,r);
   // insertTreeMap(map,&i,r);
    pushBack(x->entregas,r);
    printf("\n");
}
//ERROR : Muestra solo la ultima entrega guardada
void mostraRutas(Entregas *e, TreeMap *map)
{
    if(e->Numentregas==0) 
    {
        printf("-----------------------------------------------------------------------\n");
        printf("                 No hay rutas Almacenadas\n");
    }
    else
    {
        printf("-----------------------------------------------------------------------\n");
        printf("************************* SUS RUTAS SON *******************************\n");
        printf("-----------------------------------------------------------------------\n");
        Ruta *r = firstList(e->entregas); 
        while(r)
        {
            printf("La distancia recorrida de la ruta %s es : %f\n",r->nombre,r->distancia);
            r = nextList(e->entregas);
        }
        r = firstTreeMap(map); 
        while(r)
        {
            printf("La distancia recorrida de la ruta en el MAPA %s es : %f\n",r->nombre,r->distancia);
            r = nextTreeMap(map);
        }
    }
    printf("-----------------------------------------------------------------------\n");
}
/* Función para comparar claves de tipo string */
int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
    return 0;
}
int main()
{
    TreeMap* map = createTreeMap(lower_than_string);
    List* E=createList();
    Ruta* r = malloc(sizeof(Ruta));
    r->listaruta = createList();
    r->distancia =0;
    Entregas *x = malloc(sizeof(Entregas));
    x->Numentregas = 0;
    x->entregas = createList();

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
            case 2:distanciaEntreEntregas(E);break;
            case 3:printf("No Implementada\n");break;
            case 4:printf("No Implementada\n");break;
            case 5:rutaAleatoria(E,r,x,map);break;
            case 6:printf("No Implementada\n");break;
            case 7:mostraRutas(x,map);break;
            case 8:printf("No Implementada\n");break;
        }
    }
    return 0;
}