#include <fstream>
#include <iostream>
#include <iomanip>

#include "TSystem.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TRandom.h"

#include "Parameters.h"
#include "Map.cpp"

#include "AnodeLib.cpp"
#include "AreaCalc.cpp"
#include "ChargeCalc.cpp"

int Run(){

  int Nch = MapR();
  DrawMapR( Nch , 0 );

  //FullArea();
  // Area(0,51);

  ChargeCurrent( 0, 0, Nch );
  DrawAnodes( Nch );

  gSystem->Exit(0);
  return 0;
}
