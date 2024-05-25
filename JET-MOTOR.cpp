#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>
using namespace std;

struct fecha {
	int dia, mes, anio;
};

struct garantia{
	char concepto;
	float porcentaje;
};

struct carro{
	char serial[10], marca[20], modelo[20], color[15], g[20];
	float precio;
	int nrogarant;
	struct fecha fab; //fabricacion
	struct fecha ent; //entrada al inventario
	struct garantia garant[3];
}k;

bool busqueda (char serial[10]){
	bool v = false;
	FILE *busca;
	busca = fopen("archivo.dat","r");
	while (v == false && fread(&k,sizeof(k), 1, busca)==1)
		if (strcmp(serial,k.serial)==0){
			v = true;
			break;
		}
	fclose(busca);
	return(v);
}

void incluir(){
	char g[2];
	cout<<"\nIngrese la serial del vehiculo: "; gets(k.serial);
	if(busqueda(k.serial)==true){
		cout<<"\nLa serial ya esta en el sistema";
	} else {
		cout<<"\nIngrese el modelo del vehiculo: "; gets(k.modelo);
		cout<<"\nIngrese el color de vehiculo: "; gets(k.color);
		cout<<"\nIngrese marca del vehiculo: "; gets(k.marca);
		do {
			cout<<"\nIngrese precio del vehiculo: "; cin>>k.precio;
		} while (k.precio < 0);
		cout<<"\nIngrese fecha de fabriacion del vehiculo ";
		cout<<"\nDia de fabricacion: "; cin>>k.fab.dia;
		cout<<"\nMes de fabriacion: "; cin>>k.fab.mes;
		cout<<"\nAnio de fabriacion: "; cin>>k.fab.anio;
		cout<<"\nIngrese fecha de entrada del vehiculo al inventario "; 
		cout<<"\nDia de entrada: "; cin>>k.ent.dia;
		cout<<"\nMes de entrada: "; cin>>k.ent.mes;
		cout<<"\nAnio de entrada: "; cin>>k.ent.anio;
		do {
			cout<<"\nEl vehiculo tiene garantia? (si o no): "; gets(k.g);			
		} while (k.g=="si"||k.g=="no");
		if (strcmp(k.g,"si")==0){
			do {
			cout<<"\nIngrese cuantas garantias tiene su vehiculo(maximo 3): "; cin>>k.nrogarant;
		} while (k.nrogarant < 0 || k.nrogarant >=3);
			for (int i = 0 ; i < k.nrogarant ; i++){
				cout<<"\nIngrese el concepto de su garantia #" <<i+1<<": "; gets(k.garant[i].concepto);
				cout<<"\nIngrese el porcentaje del precio cubierto de la garantia #" <<i+1<<": "; cin>>k.garant[i].porcentaje;
			}
		} else {
			k.nrogarant = 0;
		}
		FILE *registro; //para que todo lo que se este metiendo a k se ponga en un archivo.
		registro = fopen("archivo.dat","at+");
		fclose(registro);
	}
}

void consultar(){
	char serialcomp[20];
	cout<<"\nIngrese la serial del vehiculo: "; gets(serialcomp);
	if(busqueda(serialcomp)==true){
		cout<<"\nDatos adjuntados de de la serial" << serialcomp <<": \n";
		cout<<"\nModelo del vehiculo: "<< k.modelo;
		cout<<"\nColor de vehiculo: "<< k.color;
		cout<<"\nMarca del vehiculo: "<< k.marca;
		cout<<"\nPrecio del vehiculo: "<< k.precio;
		cout<<"\nFecha de fabriacion del vehiculo ";
		cout<<"\nDia de fabricacion: "<< k.fab.dia;
		cout<<"\nMes de fabriacion: "<< k.fab.mes;
		cout<<"\nAnio de fabriacion: "<< k.fab.anio;
		cout<<"\nFecha de entrada del vehiculo al inventario "; 
		cout<<"\nDia de entrada: "<< k.ent.dia;
		cout<<"\nMes de entrada: "<< k.ent.mes;
		cout<<"\nAnio de entrada: "<< k.ent.anio;
		cout<<"\nNumero de garantias: "<<k.nrogarant;
		for (int i = 0 ; i < k.nrogarant ; i++){
			cout<<"\nConcepto de la garantia #"<<i+1<<": " <<k.garant[i].concepto;
			cout<<"\nPorcentaje de la garantia #"<<i+1<<": " <<k.garant[i].porcentaje;
		}
	}
}

void modificar(){
	
}

void eliminar(){
	
}

void salir(){
	
}
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
