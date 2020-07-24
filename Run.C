
#include <fstream>
#include <iostream>
#include <iomanip>

#include "TSystem.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "Parameters.h"
#include "Map.cpp"


int Run(){

  int Nch = MapR();
  DrawMapR( Nch , 5 );

  gSystem->Exit(0);
  return 0;
}
