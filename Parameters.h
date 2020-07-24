#include "TMath.h"
const int N_ANODES = 9;
double pi = TMath::Pi();


double grid_anode_distance = 10.    ; // mm     ; Grid-Anode distance
double drift_velocity      = 0.0075 ; // mm/ns  ; Dirift velosity
double step_size           = 0.1    ; // mm     ; step size for calculation of induced charge
double channel_width       = 40     ; // ns     ; Flash ADC channel width

double r_map               = 50.    ; // mm  <--- To fix later!!!

int Nsum = 100000 ;
int Nphi =   10000 ;


double c_time[100];  // time-stamps for induced charge map
double i_time[100];  // time-stamps for current map (in the center btw time-stamps for charge)

// first index = map size
// MUST FIT r_map/step_size
double  charge[500][100];
double current[500][100];

double anode_area_of_overlap[N_ANODES];

long long int Nmc=1000000000;
double anode_area_mc_estimation[N_ANODES];
