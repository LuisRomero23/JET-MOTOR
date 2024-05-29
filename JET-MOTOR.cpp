#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include<windows.h>

using namespace std;

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
  }


struct fecha{
	int dia,mes,anio;
};

struct garantia{
	char concepto[20];
	float cobertura;
};


struct vehiculo{
	char serial[20],marca[20],modelo[20],color[20];
	struct fecha ffab, fent;
	float precio;
	int ngarant;
	struct garantia g[3];
}vehi;


bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}//funcion para validar un año bisiesto



// Función para convertir una fecha a días desde una fecha base (por ejemplo, 01/01/0001)
int convertirADias(struct fecha f) {
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int totalDias = f.dia;

    // Agregar los días de los meses completos del año actual
    for (int i = 0; i < f.mes - 1; ++i) {
        totalDias += diasPorMes[i];
    }

    // Agregar un día extra si el año es bisiesto y el mes es después de febrero
    if (f.mes > 2 && esBisiesto(f.anio)) {
        totalDias += 1;
    }

    // Agregar los días de los años completos anteriores
    for (int i = 1; i < f.anio; ++i) {
        totalDias += esBisiesto(i) ? 366 : 365;
    }

    return totalDias;
}














bool validarfecha(int dia, int mes, int anio){
	
	if (anio < 0) {
        return false;
    }
	
	if(mes<1||mes>12){
		
		return false;
	}
	
	if(dia<1){
		
		return false;
	}
	
	switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (dia > 31) 
            return false;
            break;
        case 4: case 6: case 9: case 11:
            if (dia > 30) 
            return false;
            break;
        case 2:
            if (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0)) {
                if (dia > 29) 
                return false;
            	
            } else {
                if (dia > 28) 
                return false;
        	}
            break;
        default:
            return false;
    }

    return true;
}

char sel;

char menu(){ 
char y; system("CLS");

gotoxy(30,6);printf("Menu de Opciones");

gotoxy(30,8);printf("1.- Incluir Registros");

gotoxy(30,10);printf("2.- Consultar Registros");

gotoxy(30,12);printf("3.- Modificar Registros");

gotoxy(30,14);printf("4.- Eliminar Registros");

gotoxy(30,16);printf("5.- Registros");

gotoxy(30,18);printf("6.- Salida");

gotoxy(50,20);printf("Seleccion = ");

y = getchar();
return (y); }




int busqueda(char serialbus1[20]){
	int band=0;
	int z;
	FILE*arch1;
	
	arch1=fopen("JETMOTORSG11.dat","r");
	
	while((band==0)&&(fread(&vehi,sizeof(vehi),1,arch1)==1)){
		if(strcmp(vehi.serial,serialbus1)==0){
			band=1;
		}
	}if(band==0)
	z=0;
	else
	z=1;
	
	fclose(arch1);
	return(z);
}



void incluir(){
char serialbus[20];
bool fechavalida1, fechavalida2;

int m,i,diasfecha1,diasfecha2; system("CLS");
char posee[2];

fflush(stdin);
printf("Ingrese el serial del vehiculo: ");gets(serialbus);

m = busqueda(serialbus);

if (m==0) {
strcpy(vehi.serial,serialbus);

printf("Ingrese la marca del vehiculo:"); gets(vehi.marca);

printf("Ingrese el modelo del vehiculo:");gets(vehi.modelo);



do{
	printf("Ingrese la fecha de fabricacion del vehiculo:\n");
	/*gotoxy(0,4);*/printf("Dia:");cin>>vehi.ffab.dia;
	/*gotoxy(10,4);*/printf("Mes:");cin>>vehi.ffab.mes;
	/*gotoxy(20,4);*/printf("Ano:");cin>>vehi.ffab.anio;

	fechavalida1=validarfecha(vehi.ffab.dia,vehi.ffab.mes,vehi.ffab.anio);
	if(!fechavalida1){
		printf("Fecha invalida, intente nuevamente\n");
	}
	
}while(!fechavalida1);

fflush(stdin);


do{
	printf("Ingrese la fecha de entrada al inventario:\n");
	/*gotoxy(0,6);*/printf("Dia:");cin>>vehi.fent.dia;
	/*gotoxy(10,6);*/printf("Mes:");cin>>vehi.fent.mes;
	/*gotoxy(20,6);*/printf("Ano:");cin>>vehi.fent.anio;

	fechavalida2=validarfecha(vehi.fent.dia,vehi.fent.mes,vehi.fent.anio);
	if(!fechavalida2){
		printf("Fecha invalida, intente nuevamente\n");
	}else 
	convertirADias(vehi.ffab);convertirADias(vehi.fent);
	
	diasfecha1=convertirADias(vehi.ffab);
	diasfecha2=convertirADias(vehi.fent);
	
	if(diasfecha2<diasfecha1){
		printf("Fecha de entrada al inventario invalida, intente nuevamente\n");
	}
	
	
	
}while(!fechavalida2||diasfecha2<diasfecha1);


fflush(stdin);





printf("Ingrese el color del vehiculo: ");gets(vehi.color);
fflush(stdin);

do{
	fflush(stdin);
	printf("Ingrese el precio del vehiculo: ");scanf("%.2f",&vehi.precio);
	fflush(stdin);
	
	if (vehi.precio<0){
	printf("Precio invalido, intente nuevamente");
	}

}while(vehi.precio<0);//validacion de precio


printf("El vehiculo posee garantia?(SI/NO):");gets(posee);

if(strcmp(posee,"Si")==0||strcmp(posee,"si")==0||strcmp(posee,"SI")==0){
	printf("Ingrese el numero de garantias:");cin>>vehi.ngarant;
	
	if (vehi.ngarant<0||vehi.ngarant>3){
		printf("Error numero de grarantias invalido, intente nuevamente:");	
	}else

	for(i=0;i<vehi.ngarant;i++){
		printf("Ingrese los datos de la grantia #%d\n",i+1);
		fflush(stdin);
		printf("Concepto de la garantia #%d:",i+1);gets(vehi.g[i].concepto);
		fflush(stdin);
		printf("Ingrese el porcentaje cubierto por la grantia #%d:",i+1);scanf("%f",&vehi.g[i].cobertura);
	}

}else if(strcmp(posee,"No")==0||strcmp(posee,"no")==0||strcmp(posee,"No")==0){
	printf("El vehiculo no posee garantia");//validacion de garantia
	vehi.ngarant=0;
}




FILE *arch1;

arch1 = fopen("JETMOTORSG11.dat","at+");

fwrite(&vehi,sizeof(vehi),1,arch1);

fclose(arch1);

printf("\n Registro Insertado");

}else
printf("\n Serial Ya Ingresado");
getch();
};


void consultar(){
	fflush(stdin);
int m,i; system("CLS");

fflush(stdin);

char serialcomp[20]; //una variable para comparar la serial ingresada con las seriales en los registros
	cout<<"Ingrese el serial del vehiculo: "; gets(serialcomp);
	
	m= busqueda(serialcomp);
	
	if(m==1){ //if que busca si ambas seriales son iguales y muestre sus datos 
		cout<<"\nDatos adjuntados del serial " << serialcomp <<":\n";
		cout<<"\nMarca del vehiculo: "<< vehi.marca;
		cout<<"\nModelo del vehiculo: "<< vehi.modelo;
		cout<<"\nColor de vehiculo: "<< vehi.color;
		fflush(stdin);
		printf("\nPrecio del vehiculo:%f",vehi.precio);
		cout<<"\nFecha de fabriacion del vehiculo ";
		cout<<"\nDia de fabricacion: "<< vehi.ffab.dia;
		cout<<"\nMes de fabriacion: "<< vehi.ffab.mes;
		cout<<"\nAnio de fabriacion: "<< vehi.ffab.anio;
		cout<<"\nFecha de entrada del vehiculo al inventario "; 
		cout<<"\nDia de entrada: "<< vehi.fent.dia;
		cout<<"\nMes de entrada: "<< vehi.fent.mes;
		cout<<"\nAnio de entrada: "<< vehi.fent.anio;
		cout<<"\nNumero de garantias: "<<vehi.ngarant;
		
		if (vehi.ngarant <=0){ //if para validar si tiene garantias o no, si no tiene, no se muestra la info de las garantias
			cout<<"\nEl vehiculo no posee garantias";
		} else {
		for (int i = 0 ; i < vehi.ngarant ; i++){
			cout<<"\nConcepto de la garantia #"<<i+1<<": " <<vehi.g[i].concepto;
			cout<<"\nPorcentaje de la garantia #"<<i+1<<": " <<vehi.g[i].cobertura<<"%";
			}
		}
	} else {
		cout<<"\nNo se encontro el vehiculo con este serial.";
	}
	getche();
};




void modificar();

void eliminar();

void reportes();


int main(){
struct vehiculo vehi;
do{
sel = menu();
switch (sel){ 

case '1': incluir();
break; 

case '2': consultar();
break; 

/*case '3': modificar();
break; 

case '4': eliminar();
break; 

case '5': reportes();
break; */
}

} while (sel != '6');

	
	
	
}
