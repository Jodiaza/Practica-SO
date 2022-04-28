#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*
Este programa pide al usuario que ingrese el ido, idd y la hora.
Verifica que cada uno estè en los rangos antes de enviar el mensaje.
Espera por una respuesta y termina.
*/

int main()
{
    int fd;

    // FIFO file path
    char *myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);

    char arr1[20], arr2[10];

    // Open FIFO for write only
    fd = open(myfifo, O_WRONLY);

    // Take an input arr2ing from user.
    printf("1. Ingrese ID del origen, ingrese un número entre 1 y 1160:\n");
    fgets(arr2, 10, stdin);
    int val;
    val = atoi(arr2);
    while (val < 1 || val > 1160)
    {
        printf("Por favor ingrese un numero vàlido: \n");
        fgets(arr2, 10, stdin);
        val = atoi(arr2);
    }

    // Write the input arr2ing on FIFO
    // and close it

    write(fd, arr2, strlen(arr2) + 1);
    printf("2. Ingrese ID del destino, ingrese un número entre 1 y 1160: \n");
    fgets(arr2, 10, stdin);
    val = atoi(arr2);
    while (val < 1 || val > 1160)
    {
        printf("Por favor ingrese un numero vàlido: \n");
        fgets(arr2, 10, stdin);
        val = atoi(arr2);
    }

    // Write the input arr2ing on FIFO
    // and close it
    write(fd, arr2, strlen(arr2) + 1);
    printf("3. Ingrese hora del día, un nùmero entre 0 y 23: \n");
    fgets(arr2, 10, stdin);
    val = atoi(arr2);
    while (val < 0 || val > 23)
    {
        printf("Por favor ingrese un numero vàlido: \n");
        fgets(arr2, 10, stdin);
        val = atoi(arr2);
    }

    // Write the input arr2ing on FIFO
    // and close it
    write(fd, arr2, strlen(arr2) + 1);
    close(fd);

    // Open FIFO for Read only
    fd = open(myfifo, O_RDONLY);

    // Read from FIFO
    read(fd, arr1, sizeof(arr1));

    // Print the read message
    printf("El tiempo medio de viaje corresponde a: %s\n", arr1);
    close(fd);

    return 0;
}
