#include "fecha.h"

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

  int nroGarantias;

  Garantia garantias[3];

  Fecha fabricacion;
  Fecha entrada;
} Carro;
