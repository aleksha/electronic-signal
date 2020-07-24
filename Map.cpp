// function to calculate induced charge at a ring (radius r) with
// step_size width induced by an electron placed at a distance h from anode.
double sigma(double h, double r){
  double sigma = 0.;
  double term = 1.;
  for(int n=1;n<Nsum;n++){
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
    std::cout << "\t Channel=" << Nch << "   Time=" << current_time << std::endl;
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
