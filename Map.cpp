// function to calculate induced charge at a ring (radius r) with
// step_size width induced by an electron placed at a distance h from anode.
double sigma(double h, double r){
  double sigma = 0.;
  double term = 1.;
  int k=Nsum;
  if(h<0.2) k = 10*Nsum;
  for(int n=1;n<k;n++){
    term   = 1.;
    term  *= TMath::BesselK0(n*pi*r/grid_anode_distance)*n ;
    term  *= TMath::Sin     (n*pi*h/grid_anode_distance);
    sigma += term;
  }
  sigma   *= 2.*pi*r*step_size / pow(grid_anode_distance,2);
  return sigma;
}

int MapR(){
// Create maps of charge and currtent for thin rings (width=step_size)
//  arount zero point/ This map will be later used to create a
//  current mup with a givaen anode segmentetion
  std::cout << "STATUS : Creating induced charge distribution\n";

  int    Nch = 0;
  double current_time=0;
  int    Nr;

  for(double h=10.; h>0 ; h-=drift_velocity*channel_width ){
    std::cout << "\t Channel=" << Nch << "   Time=" << current_time
              << "   h=" << h << std::endl;
    Nr=0;
    for(double r=step_size*0.5; r<r_map; r+=step_size ){
      charge[Nr][Nch] = sigma(h,r);
      Nr++;
    }

    c_time[Nch] = current_time;
    current_time += channel_width;
    Nch++;
  }


  for(int bin=0;bin<Nch-1;bin++){
    i_time[bin] = 0.5*(c_time[bin]+c_time[bin+1]);
    for(int rbin=0;rbin<Nr;rbin++){
      current[rbin][bin] = (charge[rbin][bin+1] - charge[rbin][bin]) / channel_width;
    }
  }

  return Nch;

}

void WriteMapR(int Nch){
  ofstream file_charge;
  file_charge.open ("CHARGE_MapR.txt");
  file_charge << Nch                  << "\n";
  file_charge << r_map                << "\n";
  file_charge << step_size            << "\n";
  file_charge << channel_width        << "\n";
  file_charge << grid_anode_distance  << "\n";
  file_charge << drift_velocity       << "\n";

  for(int bin=0;bin<Nch;bin++){
    file_charge << c_time[bin];
    for(int rbin=0;rbin<N_R;rbin++){
      file_charge << " " << charge[rbin][bin] ;
    }
    file_charge << "\n";
  }
  file_charge.close();
}

int ReadMapR(){

  std::ifstream file_charge("CHARGE_MapR.txt" , std::ios::in);
  int    Nch                   ; file_charge >> Nch ;
  double f_r_map               ; file_charge >> f_r_map               ;
  double f_step_size           ; file_charge >> f_step_size           ;
  double f_channel_width       ; file_charge >> f_channel_width       ;
  double f_grid_anode_distance ; file_charge >> f_grid_anode_distance ;
  double f_drift_velocity      ; file_charge >> f_drift_velocity      ;

  bool AbortIt = false;
  if (f_r_map != r_map) AbortIt = true ;
  if (f_step_size != step_size) AbortIt = true ;
  if (f_channel_width != channel_width) AbortIt = true ;
  if (f_grid_anode_distance != grid_anode_distance) AbortIt = true ;
  if (f_drift_velocity != drift_velocity) AbortIt = true ;
  if( AbortIt ){
    std::cout << "ABORTED: Parameters in CHARGE_MapR.txt DON'T FIT ones in Parameters.h\n";
    gSystem->Exit(1);
  }

  for(int bin=0;bin<Nch;bin++){
    file_charge >> c_time[bin];
    for(int rbin=0;rbin<N_R;rbin++){
      file_charge >> charge[rbin][bin] ;
    }
  }
  file_charge.close();

  for(int bin=0;bin<Nch-1;bin++){
    i_time[bin] = 0.5*(c_time[bin]+c_time[bin+1]);
    for(int rbin=0;rbin<N_R;rbin++){
      current[rbin][bin] = (charge[rbin][bin+1] - charge[rbin][bin]) / channel_width;
    }
  }

  return Nch;
}

void DrawMapR(int Nch, int to_draw=0){

  TGraph* gr = new TGraph(Nch  , c_time, charge [ to_draw ] );
  TGraph* gc = new TGraph(Nch-1, i_time, current[ to_draw ] );

  gr->SetMarkerStyle(20);
  gc->SetMarkerStyle(24);

  gr->SetMinimum(0);

  gr->SetTitle(" ");
  gc->SetTitle(" ");

  gr->GetXaxis()->SetTitle("time, ns");
  gc->GetXaxis()->SetTitle("time, ns");

  gr->GetYaxis()->SetTitle("induced charge, a.u.");
  gc->GetYaxis()->SetTitle("current, a.u.");

  TCanvas* canv = new TCanvas("canv","canv",800,800);
  gr->Draw("APL");
  canv->Print("TEMP.png");
  gc->Draw("APL");
  canv->Print("TEMP2.png");
  canv->Close();
}
