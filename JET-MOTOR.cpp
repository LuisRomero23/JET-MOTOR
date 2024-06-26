#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

using namespace std;

void gotoxy(int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void barra() {
    int segundo = 2, i;
    gotoxy(50, 25);
    printf("====== CARGANDO ===== \n");

    gotoxy(4, 26);
    for (i = 0; i <= 112; i++) {
        printf("|");
        Sleep(segundo * 1000 / 80);
    }
    system("CLS");
}

struct fecha {
    int dia, mes, anio;
};

struct garantia {
    char concepto[20];
    float cobertura;
};

struct vehiculo {
    char serial[20], marca[20], modelo[20], color[20];
    struct fecha ffab, fent;
    float precio;
    int ngarant;
    struct garantia g[3];
} vehi;

bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int convertirADias(struct fecha f) {
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int totalDias = f.dia;

    for (int i = 0; i < f.mes - 1; ++i) {
        totalDias += diasPorMes[i];
    }

    if (f.mes > 2 && esBisiesto(f.anio)) {
        totalDias += 1;
    }

    for (int i = 1; i < f.anio; ++i) {
        totalDias += esBisiesto(i) ? 366 : 365;
    }

    return totalDias;
}

bool validarfecha(int dia, int mes, int anio) {
    if (anio < 0) {
        return false;
    }

    if (mes < 1 || mes > 12) {
        return false;
    }

    if (dia < 1) {
        return false;
    }

    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (dia > 31) return false;
            break;
        case 4: case 6: case 9: case 11:
            if (dia > 30) return false;
            break;
        case 2:
            if (esBisiesto(anio)) {
                if (dia > 29) return false;
            } else {
                if (dia > 28) return false;
            }
            break;
        default:
            return false;
    }

    return true;
}

char sel;

char menu() {
    char y;
    system("CLS");

    gotoxy(10, 2);  printf("   $$$$$| $$$$$$$$$ $$$$$$$$$|      $$       $$   $$$$$$  $$$$$$$$ |  $$$$$$   $$$$$$$    $$$$$$   ");
    gotoxy(10, 3);  printf("   $__$$ |$$  _____|$__$$  __|      $$$     $$$ |$$  __$$ |__$$  __|$$  __$$  $$  __$$  $$  __$$  ");
    gotoxy(10, 4);  printf("      $$ |$$ |         $$ |         $$$$   $$$$ |$$ |  $$ |  $$ |   $$ |  $$ |$$ |  $$ |$$ |  __|");
    gotoxy(10, 5);  printf("      $$ |$$$$$$       $$ |         $$ $$ $$ $$ |$$ |  $$ |  $$ |   $$ |  $$ |$$$$$$$  | $$$$$$   ");
    gotoxy(10, 6);  printf("$$$   $$ |$$  __|      $$ |         $$  $$$  $$ |$$ |  $$ |  $$ |   $$ |  $$ |$$  __$$<  $____$$  ");
    gotoxy(10, 7);  printf("$$ |  $$ |$$ |         $$ |         $$ | $  $ $ |$$ |  $$ |  $$ |   $$ |  $$ |$$ |  $$ |$$    $$ |");
    gotoxy(10, 8);  printf("$$$$$$$  |$$$$$$$$$    $$ |         $$ | |_| $$ | $$$$$$  |  $$ |    $$$$$$  |$$ |  $$ | $$$$$$  |");
    gotoxy(10, 9);  printf(" $______$ $________|   $__|         |__|     |__| $______$   |__|    $______$|__ |  |__| $______$ ");

    gotoxy(35, 14); printf("Menu de Opciones");

    gotoxy(35, 16); printf("1.- Incluir Registros");
    gotoxy(35, 18); printf("2.- Consultar Registros");
    gotoxy(35, 20); printf("3.- Modificar Registros");
    gotoxy(35, 22); printf("4.- Eliminar Registros");
    gotoxy(35, 24); printf("5.- Reportes");
    gotoxy(35, 26); printf("6.- Salida");

    gotoxy(50, 28); printf("Seleccion: ");

    y = getchar();
    return y;
}

void conversor(float total, float tasa) {
    if (tasa <= 0) {
        printf("Tasa de conversion invalida.\n");
        return;
    }
    float endolar = total / tasa;
    printf("El valor en USD es %.2f $\n", endolar);
}

char submenu() {
    system("CLS");
    barra();
    system("CLS");
    char y;
    system("CLS");

    gotoxy(40, 6);  printf("Sub-Menu");
    gotoxy(30, 8);  printf("1.- Modelo por periodo");
    gotoxy(30, 10); printf("2.- Total por marca");
    gotoxy(30, 12); printf("3.- Cobertura a Color");
    gotoxy(30, 14); printf("4.- Consultar por Garantia");
    gotoxy(30, 16); printf("5.- Menu principal");
    gotoxy(50, 20); printf("Seleccion: ");

    y = getchar();
    return y;
}

int busqueda(char serialbus1[20]) {
    int band = 0;
    int z;
    FILE* arch1;

    arch1 = fopen("JETMOTORSG11.dat", "rb");

    if (arch1 == NULL) {
        printf("Error al abrir el archivo.\n");
        return 0;
    }

    while ((band == 0) && (fread(&vehi, sizeof(vehi), 1, arch1) == 1)) {
        if (strcmp(vehi.serial, serialbus1) == 0) {
            band = 1;
        }
    }
    if (band == 0)
        z = 0;
    else
        z = 1;

    fclose(arch1);
    return z;
}

void busqueda2(char modbus1[20]) {
    system("CLS");
    barra();
    system("CLS");
    fflush(stdin);
    int band = 0;
    struct fecha f1, f2;
    int diasfecha1, diasfecha2, diasfechaE;
    bool fechavalida1, fechavalida2;
    float total = 0;
    char rial[2];
    FILE* arch1;

    arch1 = fopen("JETMOTORSG11.dat", "rb");

    if (arch1 == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    do {
        printf("Ingrese el rango de fechas en el que desea buscar\n");
        printf("Ingrese la primera fecha\n");
        printf("Dia: "); cin >> f1.dia;
        printf("Mes: "); cin >> f1.mes;
        printf("Ano: "); cin >> f1.anio;

        fechavalida1 = validarfecha(f1.dia, f1.mes, f1.anio);
        if (!fechavalida1) {
            printf("Fecha invalida, intente nuevamente\n");
        }
    } while (!fechavalida1);

    fflush(stdin);

    do {
        printf("Ingrese la segunda fecha: \n");
        printf("Dia: "); cin >> f2.dia;
        printf("Mes: "); cin >> f2.mes;
        printf("Ano: "); cin >> f2.anio;

        fechavalida2 = validarfecha(f2.dia, f2.mes, f2.anio);
        if (!fechavalida2) {
            printf("Fecha invalida, intente nuevamente\n");
        } else {
            diasfecha1 = convertirADias(f1);
            diasfecha2 = convertirADias(f2);

            if (diasfecha2 < diasfecha1) {
                printf("Rango de fechas invalido, intente nuevamente\n");
            }
        }
    } while (!fechavalida2 || diasfecha2 < diasfecha1);

    fflush(stdin);

    while ((fread(&vehi, sizeof(vehi), 1, arch1) == 1)) {
        if (strcmp(vehi.modelo, modbus1) == 0) {
            if (convertirADias(vehi.fent) > diasfecha1 && convertirADias(vehi.fent) < diasfecha2) {
                cout << "\nSerial " << vehi.serial << ":\n";
                cout << "Marca del vehiculo: " << vehi.marca;
                cout << "\nFecha de entrada del vehiculo al inventario ";
                cout << "\nDia de entrada: " << vehi.fent.dia;
                cout << "\nMes de entrada: " << vehi.fent.mes;
                cout << "\nAnio de entrada: " << vehi.fent.anio;
                printf("\nPrecio del vehiculo:%.2f Bs.\n", vehi.precio);
                total += vehi.precio;
            }
        }
    }
    if (total == 0) {
        printf("No se encontro este modelo, intente nuevamente");
    } else {
        fflush(stdin);
        printf("Desea su total expresado en USD?(SI/NO.):"); gets(rial);

        if (strcmp(rial, "Si") == 0 || strcmp(rial, "si") == 0 || strcmp(rial, "SI") == 0) {
            float tasa;
            do {
                printf("Ingrese la tasa de conversion (Bs.-> $): ");
                scanf("%f", &tasa);
                if (tasa <= 0) {
                    printf("Tasa de conversion invalida. Intente nuevamente.\n");
                }
            } while (tasa <= 0);
            conversor(total, tasa);
        } else {
            printf("El total acumulado es %.2f Bs.", total);
        }
    }

    fclose(arch1);
}

void busqueda3(char colorbus1[20]) {
    system("CLS");
    barra();
    system("CLS");
    fflush(stdin);
    int band = 0;
    char rial[2];
    float total = 0;

    FILE* arch1;
    arch1 = fopen("JETMOTORSG11.dat", "rb");

    if (arch1 == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; colorbus1[i]; i++) {
        colorbus1[i] = tolower(colorbus1[i]);
    }

    while (fread(&vehi, sizeof(vehi), 1, arch1) == 1) {
        char colorLower[20];
        strcpy(colorLower, vehi.color);
        for (int j = 0; colorLower[j]; j++) {
            colorLower[j] = tolower(colorLower[j]);
        }

        if (strcmp(colorLower, colorbus1) == 0) {
            printf("\nModelo del vehiculo: %s", vehi.modelo);
            for (int i = 0; i < vehi.ngarant; i++) {
                cout << "\nConcepto de la garantia #" << i + 1 << ": " << vehi.g[i].concepto;
                cout << "\nPorcentaje de la garantia #" << i + 1 << ": " << vehi.g[i].cobertura << "%";
            }
            printf("\nPrecio del vehiculo: %.2f Bs.\n", vehi.precio);
            total += vehi.precio;
            band++;
        }
    }

    if (band == 0) {
        printf("No se encontraron vehiculos del color indicado\n");
    } else {
        fflush(stdin);
        printf("Desea su total expresado en USD?(SI/NO.):"); gets(rial);

        if (strcmp(rial, "Si") == 0 || strcmp(rial, "si") == 0 || strcmp(rial, "SI") == 0) {
            float tasa;
            do {
                printf("Ingrese la tasa de conversion (Bs.-> $): ");
                scanf("%f", &tasa);
                if (tasa <= 0) {
                    printf("Tasa de conversion invalida. Intente nuevamente.\n");
                }
            } while (tasa <= 0);

            rewind(arch1);
            while (fread(&vehi, sizeof(vehi), 1, arch1) == 1) {
                char colorLower[20];
                strcpy(colorLower, vehi.color);
                for (int j = 0; colorLower[j]; j++) {
                    colorLower[j] = tolower(colorLower[j]);
                }
                if (strcmp(colorLower, colorbus1) == 0) {
                    float endolar = vehi.precio / tasa;
                    printf("El precio del vehiculo modelo %s en USD es %.2f $\n", vehi.modelo, endolar);
                }
            }
        } else {
            printf("El total acumulado es %.2f Bs.", total);
        }
    }

    fclose(arch1);
}

void incluir() {
    system("CLS");
    barra();
    system("CLS");
    char serialbus[20];
    bool fechavalida1, fechavalida2;

    int m, i, diasfecha1, diasfecha2;
    system("CLS");
    char posee[2];

    fflush(stdin);
    printf("NO DEJE ESPACIO AL FINAL DE LOS DATOS\n");
    printf("Ingrese el serial del vehiculo: "); gets(serialbus);

    m = busqueda(serialbus);

    if (m == 0) {
        strcpy(vehi.serial, serialbus);

        printf("Ingrese la marca del vehiculo: "); gets(vehi.marca);
        printf("Ingrese el modelo del vehiculo: "); gets(vehi.modelo);

        do {
            printf("Ingrese la fecha de fabricacion del vehiculo\n");
            printf("Dia: "); cin >> vehi.ffab.dia;
            printf("Mes: "); cin >> vehi.ffab.mes;
            printf("Ano: "); cin >> vehi.ffab.anio;

            fechavalida1 = validarfecha(vehi.ffab.dia, vehi.ffab.mes, vehi.ffab.anio);
            if (!fechavalida1) {
                printf("Fecha invalida, intente nuevamente\n");
            }

        } while (!fechavalida1);

        fflush(stdin);

        do {
            printf("Ingrese la fecha de entrada al inventario\n");
            printf("Dia: "); cin >> vehi.fent.dia;
            printf("Mes: "); cin >> vehi.fent.mes;
            printf("Ano: "); cin >> vehi.fent.anio;

            fechavalida2 = validarfecha(vehi.fent.dia, vehi.fent.mes, vehi.fent.anio);
            if (!fechavalida2) {
                printf("Fecha invalida, intente nuevamente\n");
            } else {
                diasfecha1 = convertirADias(vehi.ffab);
                diasfecha2 = convertirADias(vehi.fent);

                if (diasfecha2 < diasfecha1) {
                    printf("Fecha de entrada al inventario invalida, intente nuevamente\n");
                }
            }
        } while (!fechavalida2 || diasfecha2 < diasfecha1);

        fflush(stdin);
        printf("Ingrese el color del vehiculo: "); gets(vehi.color);
        fflush(stdin);

        do {
            fflush(stdin);
            printf("Ingrese el precio del vehiculo: "); scanf("%f", &vehi.precio);
            fflush(stdin);

            if (vehi.precio < 0) {
                printf("Precio invalido, intente nuevamente");
            }

        } while (vehi.precio < 0);

        printf("El vehiculo posee garantia?(SI/NO):"); gets(posee);

        if (strcmp(posee, "Si") == 0 || strcmp(posee, "si") == 0 || strcmp(posee, "SI") == 0) {
            fflush(stdin);
            printf("Ingrese el numero de garantias: "); cin >> vehi.ngarant;

            if (vehi.ngarant < 0 || vehi.ngarant > 3) {
                printf("Error numero de garantias invalido, intente nuevamente: ");
            } else {
                for (i = 0; i < vehi.ngarant; i++) {
                    printf("Ingrese los datos de la garantia #%d\n", i + 1);
                    fflush(stdin);
                    printf("Concepto de la garantia #%d: ", i + 1); gets(vehi.g[i].concepto);
                    fflush(stdin);
                    do {
                        printf("Ingrese el porcentaje cubierto por la garantia #%d: ", i + 1); scanf("%f", &vehi.g[i].cobertura);
                        if (vehi.g[i].cobertura < 0 || vehi.g[i].cobertura > 100) {
                            printf("Porcentaje de cobertura invalido. Intente nuevamente.\n");
                        }
                    } while (vehi.g[i].cobertura < 0 || vehi.g[i].cobertura > 100);
                }
            }
        } else if (strcmp(posee, "No") == 0 || strcmp(posee, "no") == 0 || strcmp(posee, "No") == 0) {
            printf("El vehiculo no posee garantia");
            vehi.ngarant = 0;
        }

        FILE* arch1;
        arch1 = fopen("JETMOTORSG11.dat", "ab+");

        if (arch1 == NULL) {
            printf("Error al abrir el archivo.\n");
            return;
        }

        if (fwrite(&vehi, sizeof(vehi), 1, arch1) != 1) {
            printf("Error al escribir en el archivo.\n");
        }
        fclose(arch1);

        printf("\nRegistro Insertado");
    } else {
        printf("\nSerial Ya Ingresado");
    }
    getch();
}

void consultar() {
    system("CLS");
    barra();
    system("CLS");
    fflush(stdin);
    int m, i;
    system("CLS");

    fflush(stdin);
    char serialcomp[20];
    cout << "Ingrese el serial del vehiculo: "; gets(serialcomp);

    m = busqueda(serialcomp);

    if (m == 1) {
        cout << "\nDatos adjuntados del serial " << serialcomp << ":\n";
        cout << "\nMarca del vehiculo: " << vehi.marca;
        cout << "\nModelo del vehiculo: " << vehi.modelo;
        cout << "\nColor de vehiculo: " << vehi.color;
        fflush(stdin);
        printf("\nPrecio del vehiculo:%.2f Bs.", vehi.precio);
        cout << "\nFecha de fabricacion del vehiculo ";
        cout << "\nDia de fabricacion: " << vehi.ffab.dia;
        cout << "\nMes de fabricacion: " << vehi.ffab.mes;
        cout << "\nAnio de fabricacion: " << vehi.ffab.anio;
        cout << "\nFecha de entrada del vehiculo al inventario ";
        cout << "\nDia de entrada: " << vehi.fent.dia;
        cout << "\nMes de entrada: " << vehi.fent.mes;
        cout << "\nAnio de entrada: " << vehi.fent.anio;
        cout << "\nNumero de garantias: " << vehi.ngarant;

        if (vehi.ngarant <= 0) {
            cout << "\nEl vehiculo no posee garantias";
        } else {
            for (int i = 0; i < vehi.ngarant; i++) {
                cout << "\nConcepto de la garantia #" << i + 1 << ": " << vehi.g[i].concepto;
                cout << "\nPorcentaje de la garantia #" << i + 1 << ": " << vehi.g[i].cobertura << "%";
            }
        }
    } else {
        cout << "\nNo se encontro el vehiculo con este serial.";
    }
    getche();
}

void modificar() {
    system("CLS");
    barra();
    system("CLS");
    fflush(stdin);
    bool fechavalida1, fechavalida2;
    char serialbus[20], posee[2];
    int m, i, diasfecha1, diasfecha2;
    system("CLS");

    printf("Ingrese el serial del vehiculo que desea modificar:");
    fflush(stdin);
    gets(serialbus);

    m = busqueda(serialbus);

    if (m == 1) {
        FILE* arch1;
        arch1 = fopen("JETMOTORSG11.dat", "rb");

        if (arch1 == NULL) {
            printf("Error al abrir el archivo.\n");
            return;
        }

        FILE* arch2;
        arch2 = fopen("temp.dat", "wb");

        if (arch2 == NULL) {
            printf("Error al abrir el archivo temporal.\n");
            fclose(arch1);
            return;
        }

        while (fread(&vehi, sizeof(vehi), 1, arch1) == 1) {
            if (strcmp(vehi.serial, serialbus) == 0) {
                printf("Ingrese la marca del vehiculo:"); gets(vehi.marca);
                printf("Ingrese el modelo del vehiculo:"); gets(vehi.modelo);

                do {
                    printf("Ingrese la fecha de fabricacion del vehiculo:\n");
                    printf("Dia:"); cin >> vehi.ffab.dia;
                    printf("Mes:"); cin >> vehi.ffab.mes;
                    printf("Ano:"); cin >> vehi.ffab.anio;

                    fechavalida1 = validarfecha(vehi.ffab.dia, vehi.ffab.mes, vehi.ffab.anio);
                    if (!fechavalida1) {
                        printf("Fecha invalida, intente nuevamente\n");
                    }

                } while (!fechavalida1);

                fflush(stdin);

                do {
                    printf("Ingrese la fecha de entrada al inventario:\n");
                    printf("Dia:"); cin >> vehi.fent.dia;
                    printf("Mes:"); cin >> vehi.fent.mes;
                    printf("Ano:"); cin >> vehi.fent.anio;

                    fechavalida2 = validarfecha(vehi.fent.dia, vehi.fent.mes, vehi.fent.anio);
                    if (!fechavalida2) {
                        printf("Fecha invalida, intente nuevamente\n");
                    } else {
                        diasfecha1 = convertirADias(vehi.ffab);
                        diasfecha2 = convertirADias(vehi.fent);

                        if (diasfecha2 < diasfecha1) {
                            printf("Fecha de entrada al inventario invalida, intente nuevamente\n");
                        }
                    }
                } while (!fechavalida2 || diasfecha2 < diasfecha1);

                fflush(stdin);
                printf("Ingrese el color del vehiculo: "); gets(vehi.color);
                fflush(stdin);

                do {
                    fflush(stdin);
                    printf("Ingrese el precio del vehiculo: "); scanf("%f", &vehi.precio);
                    fflush(stdin);

                    if (vehi.precio < 0) {
                        printf("Precio invalido, intente nuevamente");
                    }

                } while (vehi.precio < 0);

                printf("El vehiculo posee garantia?(SI/NO):"); gets(posee);

                if (strcmp(posee, "Si") == 0 || strcmp(posee, "si") == 0 || strcmp(posee, "SI") == 0) {
                    printf("Ingrese el numero de garantias:"); cin >> vehi.ngarant;

                    if (vehi.ngarant < 0 || vehi.ngarant > 3) {
                        printf("Error numero de garantias invalido, intente nuevamente:");
                    } else {
                        for (i = 0; i < vehi.ngarant; i++) {
                            printf("Ingrese los datos de la garantia #%d\n", i + 1);
                            fflush(stdin);
                            printf("Concepto de la garantia #%d:", i + 1); gets(vehi.g[i].concepto);
                            fflush(stdin);
                            do {
                                printf("Ingrese el porcentaje cubierto por la garantia #%d:", i + 1); scanf("%f", &vehi.g[i].cobertura);
                                if (vehi.g[i].cobertura < 0 || vehi.g[i].cobertura > 100) {
                                    printf("Porcentaje de cobertura invalido. Intente nuevamente.\n");
                                }
                            } while (vehi.g[i].cobertura < 0 || vehi.g[i].cobertura > 100);
                        }
                    }
                } else if (strcmp(posee, "No") == 0 || strcmp(posee, "no") == 0 || strcmp(posee, "No") == 0) {
                    printf("El vehiculo no posee garantia");
                    vehi.ngarant = 0;
                }
            }

            fwrite(&vehi, sizeof(vehi), 1, arch2);
        }
        fclose(arch1);
        fclose(arch2);
        remove("JETMOTORSG11.dat");
        rename("temp.dat", "JETMOTORSG11.dat");
        printf("\nRegistro modificado");
    } else {
        printf("\nSerial no encontrado");
    }
    getche();
}

void eliminar() {
    system("CLS");
    barra();
    system("CLS");
    fflush(stdin);
    int m, i;
    system("CLS");
    char serialbus[20];

    printf("Ingrese el serial del vehiculo:"); gets(serialbus);

    m = busqueda(serialbus);

    if (m == 1) {
        FILE* arch1;
        arch1 = fopen("JETMOTORSG11.dat", "rb");

        if (arch1 == NULL) {
            printf("Error al abrir el archivo.\n");
            return;
        }

        FILE* arch2;
        arch2 = fopen("temp.dat", "wb");

        if (arch2 == NULL) {
            printf("Error al abrir el archivo temporal.\n");
            fclose(arch1);
            return;
        }

        while (fread(&vehi, sizeof(vehi), 1, arch1) == 1) {
            if (strcmp(vehi.serial, serialbus) != 0) {
                fwrite(&vehi, sizeof(vehi), 1, arch2);
            }
        }
        fclose(arch1);
        fclose(arch2);
        remove("JETMOTORSG11.dat");
        rename("temp.dat", "JETMOTORSG11.dat");
        printf("\nRegistro eliminado");
    } else {
        printf("\nSerial no encontrado");
    }
    getche();
}

void modeloporperiodo(struct vehiculo vehi) {
    system("CLS");
    barra();
    system("CLS");
    fflush(stdin);
    system("CLS");
    char modbus[20];

    fflush(stdin);
    printf("Ingrese el modelo del vehiculo:"); gets(modbus);

    busqueda2(modbus);

    getche();
}

void totalpormarca(struct vehiculo vehi) {
    system("CLS");
    barra();
    system("CLS");
    fflush(stdin);
    system("CLS");
    int band = 0, i;
    FILE* arch1;
    float totalmarca = 0, totalgral = 0;
    struct vehiculo arre[50];
    int numreg = 0;

    arch1 = fopen("JETMOTORSG11.dat", "rb");

    if (arch1 == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    while ((fread(&vehi, sizeof(vehi), 1, arch1) == 1)) {
        arre[numreg] = vehi;
        numreg++;
    }

    int cambio = 0;
    struct vehiculo aux;
    do {
        cambio = 0;
        for (int i = 0; i < numreg - 1; i++) {
            if (strcmp(arre[i].marca, arre[i + 1].marca) > 0) {
                aux = arre[i];
                arre[i] = arre[i + 1];
                arre[i + 1] = aux;
                cambio = 1;
            }
        }

    } while (cambio == 1);

    char marca[20];
    char rial[2];
    float tasa = 0;

    for (int i = 0; i < numreg; i++) {
        if (i == 0) {
            strcpy(marca, arre[i].marca);
        }
        if (strcmp(marca, arre[i].marca) != 0) {
            cout << endl << endl << "Total de " << marca << ": " << totalmarca << " Bs." << endl;
            totalmarca = 0;
            strcpy(marca, arre[i].marca);
        }

        totalmarca += arre[i].precio;
        totalgral += arre[i].precio;
        cout << "\n-----------------------------------------------------";
        printf("\nSerial del vehiculo:%s", arre[i].serial);
        printf("\nModelo del vehiculo:%s", arre[i].modelo);
        printf("\nMarca del vehiculo:%s", arre[i].marca);
        cout << "\nFecha de fabricacion del vehiculo ";
        cout << "\nDia de fabricacion: " << arre[i].ffab.dia;
        cout << "\nMes de fabricacion: " << arre[i].ffab.mes;
        cout << "\nAnio de fabricacion: " << arre[i].ffab.anio;
        printf("\nPrecio del vehiculo:%.2f Bs.", arre[i].precio);
        printf("\nColor del vehiculo:%s\n", arre[i].color);
        cout << "\n-----------------------------------------------------";
    }
    cout << endl << "Total de " << marca << ": " << totalmarca << " Bs." << endl;
    cout << "=====================================================================" << endl;
    cout << endl << "Total General: " << totalgral <<" Bs."<< endl;
    cout << "======================================================================";

    fflush(stdin);
    printf("\nDesea su total expresado en USD?(SI/NO.):"); gets(rial);

    if (strcmp(rial, "Si") == 0 || strcmp(rial, "si") == 0 || strcmp(rial, "SI") == 0) {
        do {
            printf("\nIngrese la tasa de conversion (Bs.-> $): ");
            scanf("%f", &tasa);
            if (tasa <= 0) {
                printf("Tasa de conversion invalida. Intente nuevamente.\n");
            }
        } while (tasa <= 0);

        for (int i = 0; i < numreg; i++) {
            if (i == 0) {
                strcpy(marca, arre[i].marca);
            }
            if (strcmp(marca, arre[i].marca) != 0) {
                cout << endl << endl << "Total de " << marca << ": " << totalmarca / tasa << " USD" << endl;
                totalmarca = 0;
                strcpy(marca, arre[i].marca);
            }
            float endolar = arre[i].precio / tasa;
            totalmarca += arre[i].precio;
            totalgral += arre[i].precio;
            cout << "\n-----------------------------------------------------";
            printf("\nSerial del vehiculo:%s", arre[i].serial);
            printf("\nModelo del vehiculo:%s", arre[i].modelo);
            printf("\nMarca del vehiculo:%s", arre[i].marca);
            cout << "\nFecha de fabricacion del vehiculo ";
            cout << "\nDia de fabricacion: " << arre[i].ffab.dia;
            cout << "\nMes de fabricacion: " << arre[i].ffab.mes;
            cout << "\nAnio de fabricacion: " << arre[i].ffab.anio;
            printf("\nPrecio del vehiculo:%.2f Bs. o %.2f USD", arre[i].precio, endolar);
            printf("\nColor del vehiculo:%s\n", arre[i].color);
            cout << "\n-----------------------------------------------------";
        }
        cout << endl << "Total de " << marca << ": " << totalmarca / tasa << " USD" << endl;
        cout << "=====================================================================" << endl;
        cout << endl << "Total General: " << totalgral / tasa <<" USD"<< endl;
        cout << "======================================================================";
    }

    fclose(arch1);
    getche();
}

void coberturacolor(struct vehiculo vehi) {
    system("CLS");
    barra();
    system("CLS");
    fflush(stdin);
    system("CLS");
    int m;
    char color[20];

    printf("Ingrese el color que desea buscar:"); gets(color);

    busqueda3(color);

    getche();
}

void consultaporgrantia() {
    system("CLS");
    barra();
    fflush(stdin);
    system("CLS");

    char conceptobus[20];
    float maxMonto = 0.0;
    bool found = false;
    struct vehiculo vehiMaxMonto;

    printf("Ingrese el concepto de la garantia que desea buscar: ");
    gets(conceptobus);

    for (int i = 0; conceptobus[i]; i++) {
        conceptobus[i] = tolower(conceptobus[i]);
    }

    FILE* arch1 = fopen("JETMOTORSG11.dat", "rb");

    if (arch1 == NULL) {
        printf("No se pudo abrir el archivo.\n");
        getch();
        return;
    }

    while (fread(&vehi, sizeof(vehi), 1, arch1) == 1) {
        for (int i = 0; i < vehi.ngarant; i++) {
            char conceptolower[20];
            strcpy(conceptolower, vehi.g[i].concepto);
            for (int j = 0; conceptolower[j]; j++) {
                conceptolower[j] = tolower(conceptolower[j]);
            }
            if (strcmp(conceptolower, conceptobus) == 0) {
                float monto = vehi.g[i].cobertura * vehi.precio / 100;
                if (monto > maxMonto) {
                    maxMonto = monto;
                    vehiMaxMonto = vehi;
                    found = true;
                }
            }
        }
    }

    fclose(arch1);

    char currency[4];
    float tasa = 0.0;

    printf("\nDesea el monto en Bs. o USD? (Bs/USD): ");
    gets(currency);

    for (int i = 0; currency[i]; i++) {
        currency[i] = tolower(currency[i]);
    }

    if (strcmp(currency, "usd") == 0) {
        printf("\nIngrese la tasa de conversion (Bs. -> $): ");
        do {
            scanf("%f", &tasa);
            if (tasa <= 0) {
                printf("Tasa de conversion invalida. Intente nuevamente.\n");
            }
        } while (tasa <= 0);
        maxMonto /= tasa;
    }

    if (found) {
        printf("\nVehiculo con mayor monto por cobertura \"%s\":\n", conceptobus);
        printf("Serial del vehiculo: %s\n", vehiMaxMonto.serial);
        printf("Marca del vehiculo: %s\n", vehiMaxMonto.marca);
        printf("Modelo del vehiculo: %s\n", vehiMaxMonto.modelo);
        printf("Color del vehiculo: %s\n", vehiMaxMonto.color);
        printf("Fecha de fabricacion: %02d/%02d/%04d\n", vehiMaxMonto.ffab.dia, vehiMaxMonto.ffab.mes, vehiMaxMonto.ffab.anio);
        printf("Fecha de entrada al inventario: %02d/%02d/%04d\n", vehiMaxMonto.fent.dia, vehiMaxMonto.fent.mes, vehiMaxMonto.fent.anio);
        printf("Precio del vehiculo: %.2f Bs.\n", vehiMaxMonto.precio);
        if (strcmp(currency, "usd") == 0) {
            printf("Monto de cobertura: %.2f USD\n", maxMonto);
        } else {
            printf("Monto de cobertura: %.2f Bs.\n", maxMonto);
        }
    } else {
        printf("No se encontraron vehiculos con el concepto de garantia \"%s\".\n", conceptobus);
    }

    getche();
}

void reportes() {
    fflush(stdin);
    system("CLS");
    do {
        sel = submenu();
        switch (sel) {
            case '1': modeloporperiodo(vehi); break;
            case '2': totalpormarca(vehi); break;
            case '3': coberturacolor(vehi); break;
            case '4': consultaporgrantia(); break;
        }
    } while (sel != '5');
}

int main() {
    barra();
    do {
        sel = menu();
        switch (sel) {
            case '1': incluir(); break;
            case '2': consultar(); break;
            case '3': modificar(); break;
            case '4': eliminar(); break;
            case '5': reportes(); break;
        }
    } while (sel != '6');
}
