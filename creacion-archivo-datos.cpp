#include <iostream>
#include <conio.h>
using namespace std;
//CPP PARA CREACION DEL ARCHIVO DE DATOS PARA JET MOTOR
int main(){
	FILE *archivo; //creacion de archivo
	archivo = fopen("datos.dat", "w"); //la "w" sirve para abrir el archivo, pero si no existe, entonces lo va a crear
	cout<<"archivo creado";
	fclose(archivo); //para cerrar el archivo cada ves que se abre
	return 0;
}
