
#include <fstream>
#include <iostream>
#include <iomanip>

#include "TSystem.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "Parameters.h"
#include "Map.cpp"

#include "AnodeLib.cpp"

int get_pad_number(double x, double y){
// This functions returns pad number from a
// coordinate on the anode (x,y)-plane.
// You can use per-defined (in AnodeLib) ones.

    return get_pad_number_Rings(x,y);
}


int Run(){

  int Nch = MapR();
  DrawMapR( Nch , 5 );

  gSystem->Exit(0);
  return 0;
}
