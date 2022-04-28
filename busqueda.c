#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "travel.h"

long int searchIdo(int index);

void searchMeanTime(int ido, int idd, int hod, char *time);

int main()
{
    int ido, idd, hod;
    double meanTime;
    char strMeanTime[8];

    int fd1;

    // FIFO file path
    char *myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);

    char str1[10], str2[20];

    // First open in read only and read
    fd1 = open(myfifo, O_RDONLY);
    read(fd1, str1, 10);

    // Print the read string and close
    ido = atoi(str1);
    read(fd1, str1, 10);

    // Print the read string and close
    idd = atoi(str1);
    read(fd1, str1, 10);

    // Print the read string and close
    hod = atoi(str1);
    close(fd1);

    // get time is exist
    char *time;
    time = malloc(8*sizeof(char));
    searchMeanTime(ido, idd, hod,time);
    //snprintf(strMeanTime, 8, "%f", meanTime);
    if(strcmp(time,"-1") == 0) {
        strcpy(time, "NA");
    }
    printf("%s\n",time);
    // Now open in write mode and write
    // string taken from user.
    fd1 = open(myfifo, O_WRONLY);
    write(fd1, time, strlen(time) + 1);
    close(fd1);
    free(time);

    return 0;
}

long int searchIdo(int ido)
{/*funcion que busca la posicion almacenada en la hashTable, del ido. Devuelve la posicion del ido en la lista principal

*/
    long auxNum;
    char *auxChar;
	auxChar = malloc(11*sizeof(char));
    FILE *file;
    file = fopen("hashTable.txt", "r");
	if (file==NULL) { fputs ("File error",stderr); exit (1);}
	else{
		fseek(file, 11 * ido, SEEK_SET);
		//fread(&auxChar, 1, 10, file);
		if(fgets(auxChar,11,file)){
			//printf("solo char %s\n",auxChar);
			auxNum = atoi(auxChar);
			//printf("en char %s  en numero %d\n",auxChar,auxNum);
			free(auxChar);
		}else{
			printf("%s", "error de lectura \n");
		}
		
	}
    fclose(file);

    return auxNum;
}

void searchMeanTime(int ido, int idd, int hod,char *time)
{/*funcion que busca en la lista los datos del viaje, recibe los datos a comparar
    recibe un puntero donde almacenara el tiempo encontrado, si no encuentra tiempo 
    retornara una cadena con "-1"
*/
    const char *filename = "lista.txt";             //archivo donde buscamos
    FILE *file = fopen(filename, "r");
    if (!file)
        printf("%s", "No se pudo abrir el archivo");

    char *contents = malloc(50*sizeof(char));       //asigna memoria a la cadena donde almacenamos las filas
    
    int end = 0;
    Travel tr;                                      //estructura que nos ayuda a separar y almacenar los datos de cada fila
    fseek(file, searchIdo(ido-1), SEEK_SET);
    while (end == 0 && fgets(contents, 50, file))
    {
        // Se extraen las variables de cada renglon

        tr.ido = strtok(contents, ",");
        tr.idd = strtok(NULL,",");
        tr.hora = strtok(NULL,",");
        tr.tiempo = strtok(NULL,",");
       
        // Se busca tiempo medio
        if (ido == atoi(tr.ido))
        {
            if (idd == atoi(tr.idd))
            {
                if (hod == atoi(tr.hora))
                {
                    end = 1;
                }
            }
        }
        else
        {
            tr.tiempo = "-1";
            end = 1;
        }
    }
    strcpy(time,tr.tiempo);
    free(contents);
    fclose(file);
    
}