#include <stdbool.h>

typedef struct fecha {
  int dia;
  int mes;
  int ano;
} Fecha;

bool Bisiesto(Fecha f);

bool FechaValida(Fecha f);
