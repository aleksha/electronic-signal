void FullArea(){
  int num;
  double x,y;
  double Ntot = double(Nmc);
  double MaxSize = 330.; // <--- THIS MUST BE IN AGREEMENT WITH get_pad_number
  std::cout << "STATUS : Estmation of full areas for each anode\n";
  for(int a=0; a<N_ANODES;a++){
     anode_area_mc_estimation[a]=0.;
  }
  for(int hit=0;hit<Nmc;hit++){
    x = (2.*gRandom->Rndm()-1.)*MaxSize;
    y = (2.*gRandom->Rndm()-1.)*MaxSize;
      num = get_pad_number(x,y);
      if( num>=0 && num<N_ANODES){
        anode_area_mc_estimation[num] += 1.;
      }
  }
  for(int a=0; a<N_ANODES;a++){
     anode_area_mc_estimation[a] = anode_area_mc_estimation[a]*pow(MaxSize*2.,2)/Ntot;
  }
  std::cout << "RESULT : Anode area estimation (!!!) using MC integration\n";
  std::cout << "       : MaxSize=" <<MaxSize <<"   Nmc=" << Nmc << "\n";
  for(int a=0; a<N_ANODES;a++){
    std::cout << "       : Anode=" << a << "  full_area=" << anode_area_mc_estimation[a] << " mm^2\n" ;
  }
}

void Area(double x, double y){

  std::cout << "STATUS : Calculating area of overlap with Map for each anode\n";
  std::cout << "         for x=" << x << ", y=" << y <<" point\n";

  int Nr,num;
  double d_phi = 2.*pi/ float(Nphi);
  double calc_area = 0.;
  double dS;

  for(int a=0; a<N_ANODES;a++){
     anode_area_of_overlap[a]=0.;
  }

  for(double r=step_size*0.5; r<r_map; r+=step_size ){
    for(double phi=0; phi<2.*pi; phi+=d_phi){
      dS = d_phi*r*step_size;
      calc_area += dS;
      num = get_pad_number(x+r*TMath::Cos(phi),y+r*TMath::Sin(phi));
      if( num>=0 && num<N_ANODES){
        anode_area_of_overlap[num] += dS;
      }
    }
    Nr++;
  }

  std::cout << "CHECK  : Map  area = " << pi*pow(r_map,2) << " mm^2\n";
  std::cout << "       : Calc area = " << calc_area       << " mm^2\n";
  std::cout << "RESULT : Anode area of overlap\n";
  for(int a=0; a<N_ANODES;a++){
    std::cout << "       : Anode=" << a << "  area=" << anode_area_of_overlap[a] << " mm^2" ;
    std::cout << "\t\tfull_area=" << anode_area_mc_estimation[a] << " mm^2\n" ;
  }
}
