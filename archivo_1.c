#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct Asiento {
    int numero;
    int ocupado; // 0: Libre, 1: Ocupado
    char lugar;  
} Asiento;

void continuar() {
    printf("Presione una tecla para continuar\n\n");
    getch();
}

void verificar_archivo() {
    FILE *archivo;
    archivo = fopen("asientos.dat", "rb");

    if (archivo != NULL) {
        printf("El archivo ya existe\n");
        fclose(archivo);
    } else {
        
        archivo = fopen("asientos.dat", "wb");
        if (archivo == NULL) {
            printf("Error al crear el archivo\n");
            exit(1);
        }
        printf("Archivo creado!\n");
        fclose(archivo);
    }
    continuar();
}

void inicializar_asientos() {
    Asiento asiento;
    FILE *archivo;
    archivo = fopen("asientos.dat", "a+b");

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
                asiento.ocupado = 0; 
                impar += 2; 
            } else {
                asiento.lugar = 'p';
                asiento.numero = par;
                asiento.ocupado = 0; 
                par += 2;   
            }
            fwrite(&asiento, sizeof(Asiento), 1, archivo); 
        }
    }

    fclose(archivo);
}

void reinicializar_asientos() {
    Asiento asiento;
    FILE *archivo;
    archivo = fopen("asientos.dat", "wb");

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
                asiento.ocupado = 0; 
                impar += 2; 
            } else {
                asiento.lugar = 'p';
                asiento.numero = par;
                asiento.ocupado = 0; 
                par += 2;   
            }
            fwrite(&asiento, sizeof(Asiento), 1, archivo); 
        }
    }

    fclose(archivo);
    printf("Los asientos han sido reinicializados a sus valores originales.\n");
    continuar();
}

void comprar_asiento() {
    FILE *archivo;
    archivo = fopen("asientos.dat", "r+b");

    if (archivo == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(1);
    }

    printf("Ingrese el numero de asiento a comprar: ");
    int numero;
    scanf("%d", &numero);

    Asiento asiento;
    int existe = 0;

    while (fread(&asiento, sizeof(Asiento), 1, archivo)) {
        if (numero == asiento.numero) {
            if (asiento.ocupado == 1) {
                printf("El asiento %d esta ocupado.\n", asiento.numero);
            } else {
                printf("El asiento %d esta libre. Comprando...\n", asiento.numero);
                asiento.ocupado = 1; 
                int pos=ftell(archivo)-sizeof(Asiento);
                fseek(archivo,pos,SEEK_SET);
                fwrite(&asiento, sizeof(Asiento), 1, archivo);
                printf("Asiento %d comprado exitosamente.\n", asiento.numero);
            }
            existe = 1;
            break;
        }
    }

    if (existe==0) {
        printf("No existe un asiento con ese numero.\n");
    }

    fclose(archivo);
    continuar();
}

void Imprimir_Croquis(){
    system("cls");
    FILE *archivo;
    archivo = fopen("asientos.dat", "rb");

    if (archivo == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(1);
    }

    Asiento asientos[20]; 
    fread(asientos, sizeof(Asiento), 20, archivo);

    int impar = 1;
    int par = 2;
    int i, j;
    
    printf("+--------------------------------------+\n");
    printf("|         Croquis del Omnibus          |\n");
    printf("+--------------------------------------+\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            int asiento_num;

            if (i == 0 || i == 3) {
                asiento_num = impar;
                impar += 2;
            } else {
                asiento_num = par;
                par += 2;
            }

            int ocupado = 0;
            int k;
            for (k = 0; k < 20; k++) {
                if (asientos[k].numero == asiento_num) {
                    if (asientos[k].ocupado == 1) {
                        ocupado = 1;
                    }
                    break;
                }
            }

            if (ocupado==1) {
                printf("| x ");
            } else {
                printf("|%2d ", asiento_num);
            }

        }
        printf("\n");
    }

    printf("+--------------------------------------+\n");
    fclose(archivo);
}

void mostrar_asientos() {
    FILE *archivo;
    archivo = fopen("asientos.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(1);
    }

    Asiento asiento;
    int contador_asientos = 0;

    printf("+--------+-------+----------+\n");
    printf("| Numero | Lugar | Estado   |\n");
    printf("+--------+-------+----------+\n");

    while (fread(&asiento, sizeof(Asiento), 1, archivo) == 1 && contador_asientos < 20){
        char estado[10];
        if (asiento.ocupado == 1) {
            sprintf(estado,"Ocupado");

        } else {
            sprintf(estado,"Libre");
        }

        printf("| %6d | %5c | %-8s |\n", asiento.numero, asiento.lugar, estado);
        contador_asientos++;
    }

    printf("+--------+-------+----------+\n");

    fclose(archivo);

    continuar();
}

void consulta_asiento() {
    FILE *archivo;
    archivo = fopen("asientos.dat", "rb");

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
            if(asiento.ocupado==1){
                printf("Numero: %d, Lugar: %c, Estado: Ocupado\n", asiento.numero, asiento.lugar);
            }else{
                printf("Numero: %d, Lugar: %c, Estado: Libre\n", asiento.numero, asiento.lugar);
            }
            
            existe = 1;
            break;
        }
        fread(&asiento, sizeof(Asiento), 1, archivo);
    }
    if (existe==0)
        printf("No existe un asiento con ese numero\n");
    fclose(archivo);
    continuar();
}

void liberar_asiento() {
    FILE *archivo;
    archivo = fopen("asientos.dat", "r+b");

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
                printf("El asiento ya esta libre!.\n");
            }
            break;
        }
    }

    if (existe==0) {
        printf("No existe un asiento con ese numero o ya esta libre!.\n");
    }

    fclose(archivo);
    continuar();
}

int main() {
    int opcion;
    do {
        system("cls");
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
                system("cls");
                verificar_archivo(); 
                inicializar_asientos();
                reinicializar_asientos();
                break;
            case 2: 
                Imprimir_Croquis();
                comprar_asiento(); 
                break;
            case 3: 
                Imprimir_Croquis();
                mostrar_asientos(); 
                break;
            case 4: 
                Imprimir_Croquis();
                consulta_asiento(); 
                break;
            case 5: 
                Imprimir_Croquis();
                liberar_asiento(); 
                break;
        }
    } while (opcion != 6);
    return 0;
}













