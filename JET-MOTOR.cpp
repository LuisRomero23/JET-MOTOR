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

//funcion para validar un anioo bisiesto
bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}


// Funcion para convertir una fecha a dias desde una fecha base (por ejemplo, 01/01/0001)
int convertirADias(struct fecha f) {
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int totalDias = f.dia;

    // Agregar los dias de los meses completos del anio actual
    for (int i = 0; i < f.mes - 1; ++i) {
        totalDias += diasPorMes[i];
    }

    // Agregar un dia extra si el anioo es bisiesto y el mes es despues de febrero
    if (f.mes > 2 && esBisiesto(f.anio)) {
        totalDias += 1;
    }

    // Agregar los dias de los anios completos anteriores
    for (int i = 1; i < f.anio; ++i) {
        totalDias += esBisiesto(i) ? 366 : 365;
    }

    return totalDias;
}

//Funcion para validar fecha
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

gotoxy(1,2);printf("		   $$$$$| $$$$$$$$$ $$$$$$$$$|      $$       $$   $$$$$$  $$$$$$$$ |  $$$$$$   $$$$$$$    $$$$$$   ");
gotoxy(1,3);printf("		   $__$$ |$$  _____|$__$$  __|      $$$     $$$ |$$  __$$ |__$$  __|$$  __$$  $$  __$$  $$  __$$  ");
gotoxy(1,4);printf("		      $$ |$$ |         $$ |         $$$$   $$$$ |$$ |  $$ |  $$ |   $$ |  $$ |$$ |  $$ |$$ |  __|");
gotoxy(1,5);printf("		      $$ |$$$$$$       $$ |         $$ $$ $$ $$ |$$ |  $$ |  $$ |   $$ |  $$ |$$$$$$$  | $$$$$$   ");
gotoxy(1,6);printf("		$$$   $$ |$$  __|      $$ |         $$  $$$  $$ |$$ |  $$ |  $$ |   $$ |  $$ |$$  __$$<  $____$$  ");
gotoxy(1,7);printf("		$$ |  $$ |$$ |         $$ |         $$ | $  $ $ |$$ |  $$ |  $$ |   $$ |  $$ |$$ |  $$ |$$    $$ |");
gotoxy(1,8);printf("		$$$$$$$  |$$$$$$$$$    $$ |         $$ | |_| $$ | $$$$$$  |  $$ |    $$$$$$  |$$ |  $$ | $$$$$$  |");
gotoxy(1,9);printf("		 $______$ $________|   $__|         |__|     |__| $______$   |__|    $______$|__ |  |__| $______$ ");

gotoxy(30,14);printf("Menu de Opciones");

gotoxy(30,16);printf("1.- Incluir Registros");

gotoxy(30,18);printf("2.- Consultar Registros");

gotoxy(30,20);printf("3.- Modificar Registros");

gotoxy(30,22);printf("4.- Eliminar Registros");

gotoxy(30,24);printf("5.- Reportes");

gotoxy(30,26);printf("6.- Salida");

gotoxy(50,28);printf("Seleccion: ");

y = getchar();
return (y); }

void conversor(float total){
	float tasa,endolar;
	
	printf("Ingrese la tasa de conversion (Bs.-> $)");
	scanf("%f",&tasa);
	
	endolar=total/tasa;
	
	printf("El valor en USD es %.2f $",endolar);
	
}

//el submenu para la funcion de reportes 
char submenu(){
	char y; system("CLS");

gotoxy(40,6);printf("Sub-Menu");

gotoxy(30,8);printf("1.- Modelo por periodo");

gotoxy(30,10);printf("2.- Total por marca");

gotoxy(30,12);printf("3.- Cobertura a Color");

gotoxy(30,14);printf("4.- Consultar por Garantia");

gotoxy(30,16);printf("5.- Menu principal");

gotoxy(50,20);printf("Seleccion: ");

y = getchar();
return (y);

}

//busqueda por serial
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

//busqueda por modelo, primera funcion de la opcion reportes
void busqueda2(char modbus1[20]){
	fflush(stdin);	
	int band=0;
	struct fecha f1,f2;
	int diasfecha1,diasfecha2,diasfechaE;
	bool fechavalida1, fechavalida2;
	float total=0;
	char rial[2];
	FILE*arch1;
	
	arch1=fopen("JETMOTORSG11.dat","r");
	
	
do{
	printf("Ingrese el rango de fechas en el que desea buscar\n");
	printf("Ingrese la primera fecha\n");
	printf("Dia: ");cin>>f1.dia;
	printf("Mes: ");cin>>f1.mes;
	printf("Ano: ");cin>>f1.anio;

	fechavalida1=validarfecha(f1.dia,f1.mes,f1.anio);
	if(!fechavalida1){
		printf("Fecha invalida, intente nuevamente\n");
					}	
}while(!fechavalida1);

fflush(stdin);

do{
	printf("Ingrese la segunda fecha: \n");
	printf("Dia: ");cin>>f2.dia;
	printf("Mes: ");cin>>f2.mes;
	printf("Ano: ");cin>>f2.anio;

	fechavalida2=validarfecha(f2.dia,f2.mes,f2.anio);
	if(!fechavalida2){
		printf("Fecha invalida, intente nuevamente\n");
					}else 
	convertirADias(f1);convertirADias(f2);
	diasfecha1=convertirADias(f1);
	diasfecha2=convertirADias(f2);
	
	if(diasfecha2<diasfecha1){
		printf("Rango de fechas invalido, intente nuevamente\n");
							}		
}while(!fechavalida2||diasfecha2<diasfecha1);
	
fflush(stdin);	
	
	while((band==0)&&(fread(&vehi,sizeof(vehi),1,arch1)==1)){
		if(strcmp(vehi.modelo,modbus1)==0){
			if(convertirADias(vehi.fent)>diasfecha1&&convertirADias(vehi.fent)<diasfecha2){
				
				cout<<"\nSerial " << vehi.serial <<":\n";
				cout<<"Marca del vehiculo: "<< vehi.marca;
				cout<<"\nFecha de entrada del vehiculo al inventario "; 
				cout<<"\nDia de entrada: "<< vehi.fent.dia;
				cout<<"\nMes de entrada: "<< vehi.fent.mes;
				cout<<"\nAnio de entrada: "<< vehi.fent.anio;
				//opcion para mostrar precio en verdes 
				printf("\nPrecio del vehiculo:%.2f Bs.\n",vehi.precio);
				//funcion para mostrar el precio en verdes 	;
				total+=vehi.precio;
				
			}	    
		}
	}
	if(total==0){
		printf("No se encontro este modelo, intente nuevamente");
	}else{
		fflush(stdin);			
	printf("Desea su total expresado en USD?(SI/NO.):");gets(rial);

if(strcmp(rial,"Si")==0||strcmp(rial,"si")==0||strcmp(rial,"SI")==0){
	conversor(total);
}else{
	printf("El total acumulado es %.2f Bs.",total);
}
	}

	fclose(arch1);
	
}

//busqueda por color,tercera funcion de la opcion reportes
void busqueda3 ( char colorbus1[20] ){
	fflush(stdin);
	int band=0;
	int i;
	char rial[2];
	
	FILE*arch1;
	arch1=fopen("JETMOTORSG11.dat","r");
	
	
	while ((fread (&vehi, sizeof(vehi),1,arch1)==1)){
		if ((strcmp(vehi.color,colorbus1)==0)&&vehi.ngarant>=2){
			
			printf("\nModelo del vehiculo: %s",vehi.modelo);
			
			for (int i = 0 ; i < vehi.ngarant; i++){
			cout<<"\nConcepto de la garantia #"<<i+1<<": " <<vehi.g[i].concepto;
			cout<<"\nPorcentaje de la garantia #"<<i+1<<": " <<vehi.g[i].cobertura<<"%";
			}
			
			printf("\nDesea el precio expresado en USD?(SI/NO):");gets(rial);
			
			if(strcmp(rial,"Si")==0||strcmp(rial,"si")==0||strcmp(rial,"SI")==0){
			conversor(vehi.precio);
			
			}else{
			printf("\nPrecio del vehiculo: %.2f Bs.\n ",vehi.precio);
			}
			
			}
				++band;
			} if(band==0){
	   	cout<<"No se encontraron vehiculos del color indicado y con mas de dos garantias"<<endl;
							}	
	fclose(arch1);
}


void incluir(){
char serialbus[20];
bool fechavalida1, fechavalida2;

int m,i,diasfecha1,diasfecha2; system("CLS");
char posee[2];

fflush(stdin);
printf("NO DEJE ESPACIO AL FINAL DE LOS DATOS\n");
printf("Ingrese el serial del vehiculo: ");gets(serialbus);

m = busqueda(serialbus);

if (m==0) {
strcpy(vehi.serial,serialbus);

printf("Ingrese la marca del vehiculo: "); gets(vehi.marca);

printf("Ingrese el modelo del vehiculo: ");gets(vehi.modelo);
do{
	printf("Ingrese la fecha de fabricacion del vehiculo\n");
	/*gotoxy(0,4);*/printf("Dia: ");cin>>vehi.ffab.dia;
	/*gotoxy(10,4);*/printf("Mes: ");cin>>vehi.ffab.mes;
	/*gotoxy(20,4);*/printf("Ano: ");cin>>vehi.ffab.anio;

	fechavalida1=validarfecha(vehi.ffab.dia,vehi.ffab.mes,vehi.ffab.anio);
	if(!fechavalida1){
		printf("Fecha invalida, intente nuevamente\n");
	}
	
}while(!fechavalida1);

fflush(stdin);


do{
	printf("Ingrese la fecha de entrada al inventario\n");
	/*gotoxy(0,6);*/printf("Dia: ");cin>>vehi.fent.dia;
	/*gotoxy(10,6);*/printf("Mes: ");cin>>vehi.fent.mes;
	/*gotoxy(20,6);*/printf("Ano: ");cin>>vehi.fent.anio;

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
	printf("Ingrese el precio del vehiculo: ");scanf("%f",&vehi.precio);
	fflush(stdin);
	
	if (vehi.precio<0){
	printf("Precio invalido, intente nuevamente");
	}

}while(vehi.precio<0);//validacion de precio


printf("El vehiculo posee garantia?(SI/NO):");gets(posee);

if(strcmp(posee,"Si")==0||strcmp(posee,"si")==0||strcmp(posee,"SI")==0){
	fflush(stdin);
	printf("Ingrese el numero de garantias: ");cin>>vehi.ngarant;
	
	if (vehi.ngarant<0||vehi.ngarant>3){
		printf("Error numero de grarantias invalido, intente nuevamente: ");	
	}else

	for(i=0;i<vehi.ngarant;i++){
		printf("Ingrese los datos de la garantia #%d\n",i+1);
		fflush(stdin);
		printf("Concepto de la garantia #%d: ",i+1);gets(vehi.g[i].concepto);
		fflush(stdin);
		printf("Ingrese el porcentaje cubierto por la garantia #%d: ",i+1);scanf("%f",&vehi.g[i].cobertura);
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
int m,i; system("CLS"); //system("CLS") es clean screen, para quitar todo de la pantalla

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
		printf("\nPrecio del vehiculo:%.2f Bs.",vehi.precio);
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


void modificar(){
	fflush(stdin);
	bool fechavalida1, fechavalida2;
	char serialbus[20],posee[2];
	int m,i,diasfecha1,diasfecha2; system("CLS");
	
	
	printf("Ingrese el serial del vehiculo que desea modificar:");
	fflush(stdin);
	gets(serialbus);
	
	m=busqueda(serialbus);
	
	
if(m==1){
	FILE*arch1;
	arch1=fopen("JETMOTORSG11.dat","r");
	
	FILE*arch2;
	arch2=fopen("temp.dat","at+");
	while((fread(&vehi,sizeof(vehi),1,arch1)==1)){
		
	if(strcmp(vehi.serial,serialbus)==0){
			
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
	printf("Ingrese el precio del vehiculo: ");scanf("%f",&vehi.precio);
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
				
		}
		
	fwrite(&vehi,sizeof(vehi),1,arch2);
	}
	fclose(arch1);
	fclose(arch2);
	remove("JETMOTORSG11.dat");
	rename("temp.dat","JETMOTORSG11.dat");
	printf("\nRegristro modificado");
}else{
	printf("\nSerial no encontrado");
};
getche();
};


void eliminar(){
	fflush(stdin);
	int m,i; system("CLS");
	char serialbus[20];
	
	printf("Ingrese el serial del vehiculo:");gets(serialbus);
	
	m=busqueda(serialbus);
	
	if(m==1){
		FILE*arch1;
		arch1=fopen("JETMOTORSG11.dat","r");
		FILE*arch2;
		arch2=fopen("temp.dat","at+");
		
	while((fread(&vehi,sizeof(vehi),1,arch1)==1)){
		if(strcmp(vehi.serial,serialbus)==1){
			fwrite(&vehi,sizeof(vehi),1,arch2);
		}
	}
	fclose(arch1);
	fclose(arch2);
	remove("JETMOTORSG11.dat");
	rename("temp.dat","JETMOTORSG11.dat");
	printf("\nRegistro eliminado");
	}
	else{
		printf("\nSerial no encontrado");
	}
	getche();
};


//lista
void modeloporperiodo(struct vehiculo vehi){	
fflush(stdin);
system("CLS");
char modbus[20];
	
fflush(stdin);	
printf("Ingrese el modelo del vehiculo:");gets(modbus);

busqueda2(modbus);

	getche();
};



void totalpormarca(struct vehiculo vehi){
	fflush(stdin);system("CLS");
	int band=0,i;
	FILE*arch1;
	float totalmarca = 0, totalgral = 0;
	struct vehiculo arre[50];
	int numreg=0;
	
	arch1=fopen("JETMOTORSG11.dat","r");
	
	while((band==0)&&(fread(&vehi,sizeof(vehi),1,arch1)==1)){
			arre[numreg]=vehi;
			numreg++;
		}
		
	//orden por marca (alfabeticamente)	
	int cambio=0;
	struct vehiculo aux;
		do{
			cambio=0;
			for(int i=0;i<numreg-1;i++){
				if(strcmp(arre[i].marca,arre[i+1].marca)>0){
					aux=arre[i];
					arre[i]=arre[i+1];
					arre[i+1]=aux;
					cambio=1;
				}
			}
			
		}while(cambio==1);
		
	char marca[20];
	
	for(int i=0;i<numreg;i++){
		
		if(i==0){
			strcpy(marca,arre[i].marca);
		}
		if(strcmp(marca,arre[i].marca)!=0){ //if para si encuentra dos marcas diferentes imprime el total por marca que ya encontramos para que continue con el siguiente
			cout<<endl<<endl<<"							Total de "<<marca<<": "<<totalmarca<<endl;
			totalmarca=0;
			strcpy(marca,arre[i].marca);
		}
		
		totalmarca+=arre[i].precio;
		totalgral+=arre[i].precio;
		cout<<"\n				-----------------------------------------------------";
		printf("\n							Serial del vehiculo:%s",arre[i].serial); //%s para mostrar char
		printf("\n							Modelo del vehiculo:%s",arre[i].modelo);
		printf("\n							Marca del vehiculo:%s",arre[i].marca);
		cout<<"\n							Fecha de fabricacion del vehiculo ";
		cout<<"\n							Dia de fabricacion: "<< arre[i].ffab.dia;
		cout<<"\n							Mes de fabriacion: "<< arre[i].ffab.mes;
		cout<<"\n							Anio de fabriacion: "<< arre[i].ffab.anio;
		printf("\n							Precio del vehiculo:%.2f Bs.",arre[i].precio);
		printf("\n							Color del vehiculo:%s\n",arre[i].color);
		cout<<"\n				-----------------------------------------------------";
	}	
		cout<<endl<<	"						Total de "<<marca<<": "<<totalmarca<<endl; //imprime el total de la ulti a marca
		cout<<"====================================================================="<<endl;
		cout<<endl<<"								Total General: "<<totalgral<<endl;
		cout<<"======================================================================";

	
	getche();
};


//lista
void coberturacolor(struct vehiculo vehi){
	fflush(stdin);system("CLS");
	int m;
	char color[20];
	
	printf("Ingrese el color que desea buscar:");gets(color);
	
	busqueda3(color);
	
	getche();
};


//función que muestre una consulta del vehículo que posee el monto más alto
//por concepto de cobertura ingresado por el usuario.
void consultaporgrantia() {
    fflush(stdin);
    system("CLS");

    char conceptobus[20];
    float maxMonto = 0.0;
    bool found = false;
    struct vehiculo vehiMaxMonto;

    // Pregunta al usuario para ingresar el concepto de la garantia.
    printf("Ingrese el concepto de la garantia que desea buscar: ");
    gets(conceptobus);

    // Convierte el concepto a minúsculas para evitar problemas relacionados a letras mayusculas y minúsculas durante la busqueda.
    for (int i = 0; conceptobus[i]; i++) {
        conceptobus[i] = tolower(conceptobus[i]);
    }

    // Abre el archivo en formato solo lectura "read".
    FILE* arch1 = fopen("JETMOTORSG11.dat", "r");

    // Validación de una apertura correcta del archivo.
    if (arch1 == NULL) {
        printf("No se pudo abrir el archivo.\n");
        getch ();
		return;
    }

    // Ciclo while entre todos los vehiculos guardados.
    while (fread(&vehi, sizeof(vehi), 1, arch1) == 1) {
        // Ciclo for para cada garantía.
        for (int i = 0; i < vehi.ngarant; i++) {
            char conceptolower[20];
            strcpy(conceptolower, vehi.g[i].concepto);
            // Convierte a minúsculas el concepto de garantía.
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

    // Cierra el archivo.
    fclose(arch1);

    // Preguntamos al usuario si desea su monton en Bs. ó en USD.
    char currency[4];
    float tasa = 0.0;

    printf("Desea el monto en Bs. o USD? (Bs/USD): ");
    gets(currency);

    // Convertimos la opción de la función currency a minúscula para evitar problemas.
    for (int i = 0; currency[i]; i++) {
        currency[i] = tolower(currency[i]);
    }

    if (strcmp(currency, "usd") == 0) {
        printf("Ingrese la tasa de conversion (Bs. -> $): ");
        scanf("%f", &tasa);
        maxMonto /= tasa;
    }

    // Mostrar resultados finales.
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

void reportes(){
	fflush(stdin);system("CLS");
	do{
sel = submenu();
switch (sel){ 

case '1': modeloporperiodo(vehi);
break; 

case '2': totalpormarca(vehi);
break; 

case '3': coberturacolor(vehi);
break; 

case '4': consultaporgrantia();
break;
	
}

} while (sel != '5');

};

int main(){
struct vehiculo vehi;
do{
sel = menu();
switch (sel){ 

case '1': incluir();
break; 

case '2': consultar();
break; 

case '3': modificar();
break; 

case '4': eliminar();
break; 

case '5': reportes();
break; 
}

} while (sel != '6');

	
	
	
}
