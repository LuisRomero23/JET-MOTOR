#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>
using namespace std;

struct fecha {
	int dia, mes, anio;
};

struct garantia{
	char concepta
	float porcentaje
};

struct carro{
	char serial[10], marca[20], modelo[20], color[15];
	float precio;
	struct fecha fab; //fabricacion
	struct fecha ent; //entrada al inventario
	struct garantia garant[3];
};

int main(){
	struct carro c; // c = carro
	cargar(//la estructura);
	int n; 
	do {
		cout<<"aqui van las opciones"
		cin>>n;
		if(n ==1){
			funcion1(estructura);
		} else if (n == 2){
			funcion2(estructura);
		} else if (n == 3){
			funcion3(estructura);
		} else if (n == 4){
			funcion4(estructura);
		} else if (n == 5){
			cout<<"cerrando el programa"
		} else {
			cout<<"error opcion no valida";
		}
		getch();
	} while (n != 5);
	return 0;
}
