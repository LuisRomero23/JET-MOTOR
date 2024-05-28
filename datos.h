// #include "fecha.h"

typedef struct fecha {
  int dia;
  int mes;
  int ano;
} Fecha;

bool Bisiesto(Fecha f) {
  return f.ano % 400 == 0 || (f.ano % 4 == 0 && f.ano % 100 != 0);
}

bool FechaValida(Fecha f) {
  if (f.ano < 0) {
    return false;
  }

  switch (f.mes) {
  case 2: {
  	int dias_febrero = 28;
    if (Bisiesto(f)) {
      ++dias_febrero;
    }
	if (f.dia > dias_febrero) {
      return false;
    }
    break;
  }
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    if (f.dia > 31) {
      return false;
    }
    break;
  case 4:
  case 6:
  case 9:
  case 11:
    if (f.dia > 30) {
      return false;
    }
    break;
  default:
    return false;
    break;
  }
  return true;
}

typedef struct garantia {
  char concepto[50];
  float cobertura;		/* Valor porcentual */
} Garantia;

typedef struct carro {
  char serial[10];
  char marca[20];
  char modelo[20];
  char color[15];

  float precio;
  
  bool garantia;
  int nroGarantias;
  Garantia garantias[3];

  Fecha fabricacion;
  Fecha entrada;
} Carro;
