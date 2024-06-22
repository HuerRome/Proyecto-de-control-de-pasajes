#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct Asiento {
    int numero;
    int ocupado; // 0: Libre, 1: Ocupado
    char lugar;  // 'v': para ventanilla y 'p': para pasillo
} Asiento;

void continuar() {
    printf("Presione una tecla para continuar\n\n");
    getch();
}

void verificar_archivo() {
    FILE *arch = fopen("asientos.dat", "rb");
    if (arch != NULL) {
        // El archivo ya existe
        printf("El archivo ya existe\n");
        fclose(arch);
    } else {
        // El archivo no existe, asï¿½ que lo creamos
        arch = fopen("asientos.dat", "wb");
        if (arch == NULL) {
            printf("Error al crear el archivo\n");
            exit(1);
        }
        printf("Archivo creado!\n");
        fclose(arch);
    }
    continuar();
}

void inicializar_asientos() {
    Asiento asiento;
    FILE *archivo = fopen("asientos.dat", "a+b");
    if (archivo == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(1);
    }

    int impar = 1; 
    int par = 2;   
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (i == 0 || i == 3) {
                asiento.lugar = 'v';
                asiento.numero = impar;
                asiento.ocupado = 0; // Por defecto, el asiento estÃ¡ libre
                impar += 2; // Incrementar por 2 para obtener el siguiente nÃºmero impar
            } else {
                asiento.lugar = 'p';
                asiento.numero = par;
                asiento.ocupado = 0; // Por defecto, el asiento estÃ¡ libre
                par += 2;   // Incrementar por 2 para obtener el siguiente nÃºmero par
            }
            fwrite(&asiento, sizeof(Asiento), 1, archivo); // Escribir el asiento en el archivo dentro del bucle
        }
    }

    fclose(archivo);
}

/*
void comprar_asiento(){
    FILE *archivo = fopen("asientos.dat", "r+b");
    if (archivo == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(1);
    }

    printf("Ingrese el numero de asiento a modificar: ");
    int numero;
    scanf("%d", &numero);

    Asiento asiento;
    int existe = 0;
    fread(&asiento, sizeof(Asiento), 1, archivo);
    while (!feof(archivo)) {
        if (numero == asiento.numero){
            if(asiento.ocupado==1){
                printf("Numero: %d, Lugar: %c, Estado: Ocupado\n", asiento.numero, asiento.lugar);
            }else{
                printf("Numero: %d, Lugar: %c, Estado: Libre\n", asiento.numero, asiento.lugar);
            }
            printf("Modificando el estado del asiento a Ocupado.\n");
            asiento.ocupado = 1;
            //fseek(archivo, -sizeof(Asiento), SEEK_CUR);
            int pos=ftell(archivo)-sizeof(Asiento);
            fseek(archivo,pos,SEEK_SET);
            fwrite(&asiento, sizeof(Asiento), 1, archivo);
            existe = 1;
            break;
        }
        fread(&asiento, sizeof(Asiento), 1, archivo);
    }
    if (!existe)
        printf("No existe un asiento con ese numero\n");
    fclose(archivo);
    continuar();
}
*/
void comprar_asiento() {
    FILE *archivo = fopen("asientos.dat", "r+b");
    if (archivo == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(1);
    }

    printf("Ingrese el numero de asiento a comprar: ");
    int numero;
    scanf("%d", &numero);

    Asiento asiento;
    int existe = 0;

    // Leer cada registro de asiento del archivo
    while (fread(&asiento, sizeof(Asiento), 1, archivo)) {
        if (numero == asiento.numero) {
            if (asiento.ocupado == 1) {
                printf("El asiento %d esta ocupado.\n", asiento.numero);
            } else {
                printf("El asiento %d esta libre. Comprando...\n", asiento.numero);
                asiento.ocupado = 1; // Marcar el asiento como ocupado
                int pos=ftell(archivo)-sizeof(Asiento);
                fseek(archivo,pos,SEEK_SET);
                fwrite(&asiento, sizeof(Asiento), 1, archivo);
                printf("Asiento %d comprado exitosamente.\n", asiento.numero);
            }
            existe = 1; // Marcar que se encontrÃ³ el asiento
            break;
        }
    }

    if (!existe) {
        printf("No existe un asiento con ese numero.\n");
    }

    fclose(archivo);
    continuar();
}



void listado() {
    FILE *archivo = fopen("asientos.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(-1);
    }

    Asiento asiento;
    fread(&asiento, sizeof(Asiento), 1, archivo);
    while (!feof(archivo)) {
        if(asiento.ocupado==1){
            printf("Numero: %d, Lugar: %c, Estado: Ocupado\n", asiento.numero, asiento.lugar);
        }else{
            printf("Numero: %d, Lugar: %c, Estado: Libre\n", asiento.numero, asiento.lugar);
        }
        fread(&asiento, sizeof(Asiento), 1, archivo);
    }
    fclose(archivo);
    continuar();
}

void consulta_asiento() {
    FILE *archivo = fopen("asientos.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(1);
    }

    printf("Ingrese el numero de asiento: ");
    int numero;
    scanf("%d", &numero);

    Asiento asiento;
    int existe = 0;
    fread(&asiento, sizeof(Asiento), 1, archivo);
    while (!feof(archivo)) {
        if (numero == asiento.numero) {
            printf("Numero: %d, Lugar: %c, Estado: %s\n", asiento.numero, asiento.lugar, asiento.ocupado ? "Ocupado" : "Libre");
            existe = 1;
            break;
        }
        fread(&asiento, sizeof(Asiento), 1, archivo);
    }
    if (!existe)
        printf("No existe un asiento con ese numero\n");
    fclose(archivo);
    continuar();
}

void liberar_asiento() {
    FILE *archivo = fopen("asientos.dat", "r+b");
    if (archivo == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(1);
    }

    printf("Ingrese el numero de asiento para reembolso: ");
    int numero;
    scanf("%d", &numero);

    Asiento asiento;
    int existe = 0;

    while (fread(&asiento, sizeof(Asiento), 1, archivo)) {
        if (numero == asiento.numero) {
            if(asiento.ocupado==1){
                printf("Numero: %d, Lugar: %c, Estado: Ocupado\n", asiento.numero, asiento.lugar);
            }else{
                printf("Numero: %d, Lugar: %c, Estado: Libre\n", asiento.numero, asiento.lugar);
            }
            
            if (asiento.ocupado == 1) {
                printf("Modificando el estado del asiento a Libre.\n");
                asiento.ocupado = 0;
                int pos=ftell(archivo)-sizeof(Asiento);
                fseek(archivo,pos,SEEK_SET);
                fwrite(&asiento, sizeof(Asiento), 1, archivo);
                existe = 1;
            } else {
                printf("El asiento ya estÃ¡ libre.\n");
            }
            break;
        }
    }

    if (!existe) {
        printf("No existe un asiento con ese numero o ya estÃ¡ libre.\n");
    }

    fclose(archivo);
    continuar();
}

int main() {
    int opcion;
    do {
        printf("1 - Crear un archivo binario llamado \"asientos.dat\"\n");
        printf("2 - Comprar asiento\n");
        printf("3 - Listado completo de asientos\n");
        printf("4 - Consultar asiento\n");
        printf("5 - Liberar asiento reembolso\n");
        printf("6 - Finalizar\n\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: 
                inicializar_asientos();
                verificar_archivo(); 
                break;
            case 2: 
                comprar_asiento(); 
                break;
            case 3: 
                listado(); 
                break;
            case 4: 
                consulta_asiento(); 
                break;
            case 5: 
                liberar_asiento(); 
                break;
        }
    } while (opcion != 6);
    return 0;
}
