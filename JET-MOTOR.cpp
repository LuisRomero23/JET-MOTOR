#include <iostream>
#include <stdio.h>
#include <string.h>
/*
  Usar fgets() en lugar de gets().
  Este el ultimo ha sido reemplazado en versiones futuras de C
*/

#include "datos.h"

using namespace std;

bool busqueda(char serial[10], Carro k) {
  bool v = false;
  FILE *busca;
  busca = fopen("archivo.dat", "r");
  while (v == false && fread(&k, sizeof(k), 1, busca) == 1)
    if (strcmp(serial, k.serial) == 0) {
      v = true;
      break;
    }
  fclose(busca);
  return (v);
}

void incluir() {
  Carro k;

  char g[2];
  cout << "\nIngrese la serial del vehiculo: ";
  fgets(k.serial, 10, stdin);
  if (busqueda(k.serial, k) == true) {
    cout << "\nLa serial ya esta en el sistema";
  } else {
    cout << "\nIngrese el modelo del vehiculo: ";
    fgets(k.modelo, 20, stdin);
    cout << "\nIngrese el color de vehiculo: ";
    fgets(k.color, 15, stdin);
    cout << "\nIngrese marca del vehiculo: ";
    fgets(k.marca, 20, stdin);
    do {
      cout << "\nIngrese precio del vehiculo: ";
      cin >> k.precio;
    } while (k.precio < 0);
    cout << "\nIngrese fecha de fabriacion del vehiculo ";
    cout << "\nDia de fabricacion: ";
    cin >> k.fabricacion.dia;
    cout << "\nMes de fabriacion: ";
    cin >> k.fabricacion.mes;
    cout << "\nAnio de fabriacion: ";
    cin >> k.fabricacion.ano;
    cout << "\nIngrese fecha de entrada del vehiculo al inventario ";
    cout << "\nDia de entrada: ";
    cin >> k.entrada.dia;
    cout << "\nMes de entrada: ";
    cin >> k.entrada.mes;
    cout << "\nAnio de entrada: ";
    cin >> k.entrada.ano;

    char seleccion[3];
    do {
      cout << "\nEl vehiculo tiene garantia? (si o no): ";
      scanf("%s", seleccion);
      getc(stdin);
    } while (strcmp(seleccion, "si") != 0 && strcmp(seleccion, "no") != 0);
    if (strcmp(seleccion, "si") == 0) {
      k.garantia = true;
      do {
        cout << "\nIngrese cuantas garantias tiene su vehiculo(maximo 3): ";
        cin >> k.nroGarantias;
      } while (k.nroGarantias < 0 || k.nroGarantias >= 3);
      for (int i = 0; i < k.nroGarantias; i++) {
        cout << "\nIngrese el concepto de su garantia #" << i + 1 << ": ";
        fgets(k.garantias[i].concepto, 50, stdin);
        cout << "\nIngrese el porcentaje del precio cubierto de la garantia #"
             << i + 1 << ": ";
        cin >> k.garantias[i].cobertura;
      }
    } else {
      k.nroGarantias = 0;
    }
    FILE *registro; // para que todo lo que se este metiendo a k se ponga en un
                    // archivo.
    registro = fopen("archivo.dat", "at+");
    fclose(registro);
  }
}

void consultar() {
  Carro k;
  char serialcomp[20];
  cout << "\nIngrese la serial del vehiculo: ";
  fgets(serialcomp, 20, stdin);
  if (busqueda(serialcomp, k) == true) {
    cout << "\nDatos adjuntados de de la serial" << serialcomp << ": \n";
    cout << "\nModelo del vehiculo: " << k.modelo;
    cout << "\nColor de vehiculo: " << k.color;
    cout << "\nMarca del vehiculo: " << k.marca;
    cout << "\nPrecio del vehiculo: " << k.precio;
    cout << "\nFecha de fabriacion del vehiculo ";
    cout << "\nDia de fabricacion: " << k.fabricacion.dia;
    cout << "\nMes de fabriacion: " << k.fabricacion.mes;
    cout << "\nAnio de fabriacion: " << k.fabricacion.ano;
    cout << "\nFecha de entrada del vehiculo al inventario ";
    cout << "\nDia de entrada: " << k.entrada.dia;
    cout << "\nMes de entrada: " << k.entrada.mes;
    cout << "\nAnio de entrada: " << k.entrada.ano;
    cout << "\nNumero de garantias: " << k.nroGarantias;
    for (int i = 0; i < k.nroGarantias; i++) {
      cout << "\nConcepto de la garantia #" << i + 1 << ": "
           << k.garantias[i].concepto;
      cout << "\nPorcentaje de la garantia #" << i + 1 << ": "
           << k.garantias[i].cobertura;
    }
  }
}

void modificar() {}

void eliminar() {}

void salir() {}

int main() {
  Carro c; // c = carro
  // cargar(la estructura);
  bool salir = false;
  char n;

  while (!salir) {
    cout << "aqui van las opciones";
    cin >> n;
    switch (n) {
    case '1':
    //  funcion1(estructura);
    incluir();
      break;
    case '2':
    // funcion2(estructura);
      break;
    case '3':
    //  funcion3(estructura);
      break;
    case '4':
    //  funcion4(estructura);
      break;
    case '5':
      cout << "cerrando el programa" << endl;
      salir = !salir;
      break;
    default:
      cout << "error opcion no valida";
    }
  }

  return 0;
}
