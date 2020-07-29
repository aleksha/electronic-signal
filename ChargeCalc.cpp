void ClearAnodes(){
  for(int a=0; a<N_ANODES;a++){
    for(int jj=0;jj<N_TIME;jj++){
      anode_xy_charge [a][jj]=0.;
      anode_xy_current[a][jj]=0.;
//      for(int ii=0;ii<3500;ii++){
//        anode_charge [a][ii][jj]=0.;
//        anode_current[a][ii][jj]=0.;
//      }
    }
  }

  std::cout << "STATUS : Charge and currents are set to zero for all anodes\n";
}

void ChargeCurrent(double x, double y, int Nch){

  std::cout << "STATUS : Calculating charge with Map for each anode\n";
  std::cout << "       : Nch=" << Nch << "  x=" << x << "  y=" << y << "\n";
  int num;
  double d_phi = 2.*pi/ float(Nphi);
  double dC;

  ClearAnodes();

  int Nr   = 0;
  for(int tt=0;tt<Nch;tt++){
    Nr=0;
    for(double r=step_size*0.5; r<r_map; r+=step_size ){
      for(double phi=0; phi<2.*pi; phi+=d_phi){
        dC = d_phi*charge[Nr][tt]/(2.*pi);
        num = get_pad_number(x+r*TMath::Cos(phi),y+r*TMath::Sin(phi));
        if( num>=0 && num<N_ANODES){
          anode_xy_charge[num][tt] += dC;
        }
      }
      Nr++;
    }
  }

  for(int a=0;a<N_ANODES;a++){
    for(int bin=0;bin<Nch-1;bin++){
      anode_xy_current[a][bin] = (anode_xy_charge[a][bin+1] - anode_xy_charge[a][bin]) / channel_width;
    }
  }

}


void DrawAnodes( int Nch ){

  TCanvas* canv = new TCanvas("canv","canv",800,800);
  canv->Divide(3,3);

  TGraph* gr[N_ANODES];
  TGraph* gc[N_ANODES];

  for(int a=0;a<N_ANODES;a++){
    gr[a] = new TGraph(Nch, c_time, anode_xy_charge[a] );
    gr[a]->SetMarkerStyle(20);
    gr[a]->SetTitle(" ");
    gr[a]->GetXaxis()->SetTitle("time, ns");
    gr[a]->GetYaxis()->SetTitle("charge, a.u.");
    canv->cd(a+1);
    gr[a]->Draw("APL");
  }

  canv->Print("TEMP3.png");
  canv->Print("TEMP3.C");

  for(int a=0;a<N_ANODES;a++){
    gc[a] = new TGraph(Nch-1, i_time, anode_xy_current[a] );
    gc[a]->SetMarkerStyle(24);
    gc[a]->SetTitle(" ");
    gc[a]->GetXaxis()->SetTitle("time, ns");
    gc[a]->GetYaxis()->SetTitle("current, a.u.");
    canv->cd(a+1);
    gc[a]->Draw("APL");
  }

  canv->Print("TEMP4.png");
  canv->Print("TEMP4.C");

  canv->Close();
}
