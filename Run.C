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

double x2check = 12.;
double y2check = 18.;

int Run(){

  int Nch;
  if( read_from_db ){
    Nch =0;
    Nch = ReadMapR();
  }
  else{
    Nch = MapR();
    DrawMapR( Nch , 0 );
    WriteMapR( Nch );
  }

  //FullArea();
  // Area(0,51);

  ChargeCurrent( x2check, y2check, Nch );
  std::cout << "STATUS : Anode " << GetFiredAnode(Nch) << " is fired\n";
  RescaleAnodeCurrents( Nch );
  DrawAnodes( Nch );

  gSystem->Exit(0);
  return 0;
}
