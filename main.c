#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "treemap.h"
#include "heap.h"
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

//Prototipo de crear Ruta
void crearRuta(List* E)
{
Ruta* new=(Ruta*) malloc(sizeof(Ruta));
new->listaruta=createList();
int px,py,v,tam,cont,v1;
printf("Favor ingrese sus coordenadas actuales\n");
printf("Posicion en el eje x: ");
scanf("%d",&px);
printf("Posicion en el eje y: ");
scanf("%d",&py);
tam=size(E);
float distancias[2][tam];
float min;
int id,p;
List* aux=createList();
List* orden=createList();   
Entrega* a= malloc(sizeof(Entrega));
a->y=py;
a->x=px;
Entrega* eaux=firstList(E),*eaux2;
pushFront(aux,eaux);
nextList(aux);
v=0;
//Ciclo que copia la lista de entregas a la auxiliar y crea un arreglo con sus id y distancias.
while(eaux){
    distancias[0][v]=distancia(a,eaux);
    distancias[1][v]=eaux->id;
    eaux=nextList(E);
    pushCurrent(aux,eaux);
    nextList(aux);
    v++;
}
p=0;
cont=0;
//Pone en orden de menor a mayor las entregas en la lista orden.
while(eaux){
    min=0;
    id=0;
    for(v=0;v<tam;v++){
        if(min==0 && distancias[0][v]!= 0){
            min=distancias[0][v];
            id=distancias[1][v];
            p=v;
        } else if(min>distancias[0][v] && distancias[0][v]!=0){
            min=distancias[0][v];
            id=distancias[1][v];
            p=v;
        }
    }
    distancias[0][p]=0;
    distancias[1][p]=0;
    eaux=firstList(aux);
    while(eaux){
        if((eaux->id==id) && (cont=0)){
            pushFront(orden,eaux);
            nextList(orden);
            popCurrent(aux);
            break;
        }else if(eaux->id==id){
            pushCurrent(orden,eaux);
            nextList(orden);
            popCurrent(aux);
            break;
        }
        eaux=nextList(aux);
    }
    cont++;
}  
//imprime y permite la seleccion de la primera entrega
eaux=firstList(orden);
printf("Entregas pendientes:\n");
for(v=0;v<tam;v++){
    min=distancia(a,eaux);
    printf("Id:%d Distancia:%f\n",eaux->id,min);
    eaux=nextList(orden);
}
printf("Favor indicar inicio de ruta\n");
scanf("%d",&id);
eaux=firstList(orden);
cont=0;
while(eaux){
    if(eaux->id==id){
        min=distancia(a,eaux);
        new->distancia+=min;
        pushFront(new->listaruta,eaux);
        nextList(new->listaruta);
        eaux2=eaux;
        popCurrent(orden);
        break;
    }else{
        eaux=nextList(orden);
        cont++;
        if(cont==tam-1){
            printf("La id ingresada no es valida\n");
            return;
        }
    }
}
//Ciclo de seleccion de las entregas pasada la primera.
for(v=1;v<tam;v++){
    eaux=firstList(orden);
    printf("Entregas pendientes:\n");
    for(v1=0;v1<tam-v;v1++){
        min=distancia(eaux2,eaux);
        printf("Id:%d Distancia:%f\n",eaux->id,min);
        eaux=nextList(orden);
    }
    printf("Favor elija la siguiente entrega de la ruta\n");
    scanf("%d",&id);
    eaux=firstList(orden);
    cont=0;
    while(eaux){
        if(eaux->id==id){
            min=distancia(eaux2,eaux);
            new->distancia+=min;
            pushCurrent(new->listaruta,eaux);
            nextList(new->listaruta);
            eaux2=eaux;
            popCurrent(orden);
            break;
        }else{
            eaux=nextList(orden);
            cont++;
            if(cont==tam-1){
                printf("La id ingresada no es valida\n");
                return;
            }
        }
    }
}
printf("La ruta creada es la siguiente: \n");
eaux=firstList(new->listaruta);
cont=0;
//Ciclo que imprime la ruta
while(eaux){
    printf("%d",eaux->id);
    cont++;
    eaux=nextList(new->listaruta);
    if(cont==tam)break;
    printf(" - ");
}
printf("\n Favor ingrese el nombre de la ruta");
scanf("%s",&new->nombre);
return;
}

void entregasCercanas(List* E)
{
    Entregas *d;
    if(size(E) ==0)
    {
        printf("NO EXISTEN SUFICIENTES ENTREGAS\n");
    }
    else
    {
        int px,py;
        printf("Favor ingrese sus coordenadas actuales\n");
        printf("Posicion en el eje x: ");
        scanf("%d",&px);
        printf("Posicion en el eje y: ");
        scanf("%d",&py);
        Entrega *e1,*e2,*e3,*e4,*aux,*a;
        float dist=0,distaux,d1,d2,d3;
        a = malloc(sizeof(Entrega));
        a->y = py;
        a->x = px;
        aux = firstList(E);
        e1 = aux;
        e2 = aux;
        e3 = aux;
        dist = distancia(a,aux);
        printf("-----------------------------------------------------------------------\n");
        printf("                      Las entregas son: \n");
        printf("-----------------------------------------------------------------------\n");
        while (aux)
        {
            distaux = distancia(a,aux);
            if(dist>distaux && dist != 0 && distaux!=0)
            {
                dist = distaux;
                e1 = aux;
            }
            aux = nextList(E);
        }
        d1 = dist;
        //printf("ID: %d, Distancia: %f \n",e1->id,dist);
        distaux = 0;
        
        aux = firstList(E);
        dist = distancia(a,aux);
        while (aux)
        {
            distaux = distancia(a,aux);
            if(dist>distaux && dist != 0 && distaux!=0 && aux->id != e1->id)
            {
                dist = distaux;
                e2 = aux;
            }
            aux = nextList(E);
        }
        d2=dist;
        //printf("ID: %d, Distancia: %f \n",e2->id,dist);
        
        distaux = 0;
        aux = firstList(E);
        dist = distancia(a,aux);
        while (aux)
        {
            distaux = distancia(a,aux);
            if(dist>distaux && dist != 0 && distaux!=0 && aux->id != e2->id && aux->id != e1->id)
            {
                dist = distaux;
                e3 = aux;
            }
            aux = nextList(E);
        }
        d3=dist;
        if(d2 == d1 &&d1 ==d3)
        {
            printf("ID: %d, Distancia: %f \n",e3->id,dist);
        }
        else
        {
            printf("ID: %d, Distancia: %f \n",e1->id,d1);
            printf("ID: %d, Distancia: %f \n",e2->id,d2);
            printf("ID: %d, Distancia: %f \n",e3->id,d3);
        }
        printf("-----------------------------------------------------------------------\n");
    }
    //tarea3_tsp
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
int rutaAleatoria(List* E, Ruta* r, Entregas *x, TreeMap*map, Heap *pq)
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
    printf("\nEscriba el nombre de la Ruta\n");
    scanf("%s",&r->nombre);
    printf("-----------------------------------------------------------------------\n");
    printf("***** La distancia de la ruta %s es : %f *****\n",r->nombre,r->distancia);
    printf("-----------------------------------------------------------------------\n\n");
    x->Numentregas++;
    insertTreeMap(map,&r->distancia,r);
    heap_push(pq,r,r->distancia);
    printf("\n");
 
}
//ERROR : Muestra solo la ultima entrega guardada
void mostraRutas(Entregas *e, TreeMap *map, Heap *pq)
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
        int i;
        Ruta *r = firstTreeMap(map);
        printf("Nombre: %s ,Distancia: %f\n",r->nombre,r->distancia);
        //if(nextTreeMap(map)==NULL) printf("NULL");
        /*
        while(heap_top(pq)){
            r = heap_top(pq);
            printf("Nombre: %s, Distancia: %f\n",r->nombre,r->distancia);
            heap_pop(pq);
        }*/
        
    }
    printf("-----------------------------------------------------------------------\n");
}
void mostrarentregas(List*E, TreeMap *map)
{
    int i,p,q;
    Ruta *r = firstTreeMap(map);
    printf("La distancia de la ruta %s es %f\n",r->nombre,r->distancia);
    int tamano = size(r->listaruta);
    Entrega *e = firstList(r->listaruta);
    printf("ID     X        Y\n");
    while (e)
    {
        printf("[%d] = (%d , %d)\n",e->id,e->x,e->y);
        e = nextList(r->listaruta);
    }
    printf("Seleccione mediante el id, la ruta que desea cambiar: ");
    scanf("%d",&p);
    e = firstList(r->listaruta);
    while (e)
    {
        if(p == e->id)break;
        e = nextList(r->listaruta);
    }
    int w = rand() % (tamano-2)+1;
    int x,y,auxid;
    Entrega *e2 = firstList(r->listaruta);
    while (e2)
    {
        if(w == e2->id)break;
        e2 = nextList(r->listaruta);
    }
    /*
    x = e->x;
    e->x = e2->x;
    e2->x = x;
    y = e->y;
    e->y = e2->y;
    e2->y = y;
    auxid = e->id;
    e->id = e2->id;
    e2->id = auxid;*/
    printf("\nLa ruta seguida es: \n");
    Entrega *e1;
    e = firstList(r->listaruta);
    while (e)
    {
        if(p == e->id)
        { 
            printf("ENTRODENTRO\n");
            e1 = e;
            e = e2;
            e2 = e1;
        }
        e = nextList(r->listaruta);
    }
    
    int j=0;
    float dist=0;
    //for(i=0 ; i<tamano ; i++)
    //{
    e = firstList(r->listaruta);
    e2 = e;
    while(e)
    {
            //if( == e->id)
            //{
            printf("[%d] ",e->id);
                //pushBack(r->listaruta,e);
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
           // }
        e = nextList(r->listaruta);
    }
    printf("\nDistancia: %f\n",dist);
}

void mejorRuta(List * E){
    if(size(E)==0){
        printf("No hay entregas suficientes.\n");
        return;
    }
    int px,py;
    printf("Ingresa posicion x: ");
    scanf("%d",&px);
    printf("Ingresa posicion y: ");
    scanf("%d",&py);

    
}

/* Función para comparar claves de tipo string */
int lower_than_string(void* key1, void* key2){
    float k1=*(float*) key1;
    float k2=*(float*) key2;
    if(k1<k2) return 1;
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
    Heap*pq = createHeap();
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
            case 3:entregasCercanas(E);break;
            case 4:printf("No implementada\n");break;
            case 5:rutaAleatoria(E,r,x,map,pq);break;
            case 6:mostrarentregas(E,map);break;
            case 7:mostraRutas(x,map,pq);break;
            case 8:crearRuta(E);break;
        }
    }
    return 0;
}