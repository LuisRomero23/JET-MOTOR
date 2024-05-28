#include <iostream>
#include <stdio.h>
#include <string.h>
/*
  Usar fgets() en lugar de gets().
  Este el ultimo ha sido reemplazado en versiones futuras de C
*/
#include <conio.h>

#include "fecha.h"
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
    do {
      cout << "\nEl vehiculo tiene garantia? (si o no): ";
      gets(k.g);
    } while (k.g != "si" || k.g != "no");
    if (strcmp(k.g, "si") == 0) {
      do {
        cout << "\nIngrese cuantas garantias tiene su vehiculo(maximo 3): ";
        cin >> k.nroGarantias;
      } while (k.nroGarantias < 0 || k.nroGarantias >= 3);
      for (int i = 0; i < k.nroGarantias; i++) {
        cout << "\nIngrese el concepto de su garantia #" << i + 1 << ": ";
        gets(k.garantias[i].concepto);
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
  gets(serialcomp);
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
  struct carro c; // c = carro
        cargar(//la estructura);
	int n; 
	do {
    cout << "aqui van las opciones" cin >> n;
    if (n == 1) {
      funcion1(estructura);
    } else if (n == 2) {
      funcion2(estructura);
    } else if (n == 3) {
      funcion3(estructura);
    } else if (n == 4) {
      funcion4(estructura);
    } else if (n == 5) {
      cout << "cerrando el programa"
    } else {
      cout << "error opcion no valida";
    }
    getch();
	} while (n != 5);
	return 0;
}
