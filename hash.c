#include "travel.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void createTableB();
void createHashTable();
void convertNumber(long pos,char *dir );

int main(){
    printf("Creando tabla de busquedas ordenada, espere un momento....\n");
    createTableB();
    printf("ejecutamos createHashTable");
    createHashTable();
    return 0;
}

void createTableB(){
/* en este arvhivo solo se crea la lista de lectura con los datos ordenados mediante un while.
se va a adicionar por indice y solo se usara el arvhivo de escritura y el archivo de lectura.
se cerrara el arvhivo en cada indice.

crea archovos modo append
busca el ido en orden ascendente
al encontrar escribe en otro archivo
cierra el archivo
aumenta el ido
abre el archivo datos desde el inicio modo read
sigue la busqueda
repite el proceso. */
    //abrimos el archivo original
    FILE *fr;
    fr = fopen("datos.csv","r");
    FILE *fa;
    Travel tr;
    char cadena[60];
    for(int i =1;i<=1160;i++){
        //buscamos todos los numeros, uno po uno
        while(fgets(cadena,50,fr)){  

            tr.ido = strtok(cadena,",");
            if(i == atoi(tr.ido)){                  //comparamos si el primer elemento coincide con el ido que estamos ordenando
                tr.idd = strtok(NULL,",");
                tr.hora = strtok(NULL,",");
                tr.tiempo = strtok(NULL,",");
                //abrimos o creamos e larchivo donde almacenamos los datos ordenados 
                fa = fopen("lista.txt","a+");
                if (fa==NULL) { fputs ("File error",stderr); exit (1);}
                else{ //escribimos datos en tabla de indices
                    fputs(tr.ido,fa);
                    fputs(",",fa);
                    fputs(tr.idd,fa);
                    fputs(",",fa);
                    fputs(tr.hora,fa);
                    fputs(",",fa);
                    fputs(tr.tiempo,fa);
                    fputs("\n",fa);
                    fclose(fa);
                }
            }
        }
        rewind(fr);         //reiniciamos el archivo para empezar la nueva busqeuda 
    }
    fclose(fr);
}

void createHashTable(){
/*
en este se usata la tabla creada por la funcion createTableB, y genera la tabla con indices a la primera tabla
guardando la posicion del primer ido en el archivo ya creado.
busca en la tabla ordenada el primer elemento de cada ido


abre tablaHash modo append
busca el ido iniciando desde cero
encuentra el primer elemento
guarda la posicion en la tabla hash
aumenta el ido
busca en la tabla ordenada 
guarda la posicion de la fila
repite la operacion hasta llegar al final
si no encuentra un ido guarda el valor -1 en la tabla hash
malloc
free    */
    printf("hasTable en ejecucion \n");
    FILE *fr;                       //puntero de nuestro archivo de lectura (lista)
    fr = fopen("lista.txt","r");    
    FILE *fa;                       //puntero de nuestro archivo de escritura hashTable  
    char cadena[50];                //almacenar la fila del archivo listas
    bool find = false;              //controlar si el indice es encontrado
    int index = 1;                  //indice que estamos buscanod
    long pos = 0;                      //variable que guardara la posicion del archivo
                     
    while(index<=1160){
        //printf("entra al while ");
        //printf("index = %i",index);
        find = false;
        while(fgets(cadena,50,fr) && !find){    ///si hay lineas que leer y no ha sido encontrado el indice
            char *ido;                          //almacena el ido en el archivo listas
            ido = strtok(cadena,",");           //separamos la primera columna de la fila
            if(atoi(ido)==index){               //compara si si el ido es el que buscamos 
                fa = fopen("hashTable.txt","a+");                           //SI: abrimos o creamos hashTable para adicionar la direccion
                if (fa==NULL) {fputs ("File error",stderr); exit (1);}
                else{
                    find = true;
                    char *dir;
                    dir = malloc(10*sizeof(char));
                    //enviamos puntero en que almacenamos el arreglo de ceros 
                    convertNumber(pos,dir);
                    fputs(dir,fa);
                    free(dir);
                    fputs("\n",fa);
                    fclose(fa);
                    index++;
                    rewind(fr); 
                }
               
            }
            pos = ftell(fr);
            //printf("no encontro %i",index);
        } 
        
        if(!find){  //en caso qeu no se encuentre el ido en la lista, almacenamos en la hashTable direccion -1
            fa = fopen("hashTable.txt","a+");
            if (fa==NULL) {fputs ("File error",stderr); exit (1);}
            else{   //si no hay lienas que leer
                fputs("-000000001",fa);
                fputs("\n",fa);
                fclose(fa);
                index++;
                rewind(fr);
            }
        }
        pos = ftell(fr); 
    }
}

void convertNumber(long pos,char *dir ){
 /*funcion que  convierte un numero a cadena de 10 posiciones, rellenando 
 los faltantes con ceros a la izquierda*/ 
	char *text;
	text = malloc(10*sizeof(char));         //asignamos memoria a la variable donde almacenaremos el numero en texto
    sprintf(text, "%li", pos);              //convertimos el dato numerico a cadena de texto
    int ceros = 10 - (int) strlen(text);    //calculamos cantidad de ceros con para rellenar la cadena de texto
    char *cerosc;
	cerosc = malloc(10*sizeof(char)); //asignamos memoria aa nuestro arreglo de 10 posiciones
    //concatenamos los ceros con los que rellenamos la cadena
    for (int i=0;i<ceros;i++){
        strcat(cerosc,"0");
    }
    strcat(cerosc,text);
	free(text);
    strcpy(dir,cerosc);
	free(cerosc);

}
