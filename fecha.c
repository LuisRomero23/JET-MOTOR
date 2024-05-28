#include "fecha.h"

bool Bisiesto(Fecha f) {
  return f.ano % 400 == 0 || (f.ano % 4 == 0 && f.ano % 100 != 0);
}

bool FechaValida(Fecha f) {
  if (f.ano < 0) {
    return false;
  }

  switch (f.mes) {
  case 2:
    if (Bisiesto(f) && f.dia > 29) {
      return false;
    } else if (f.dia > 28) {
      return false;
    }
    break;
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
