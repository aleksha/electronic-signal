#include "TMath.h"
const int N_ANODES = 9;
const int N_TIME   = 200;
double pi = TMath::Pi();


double grid_anode_distance = 10.    ; // mm     ; Grid-Anode distance
double drift_velocity      = 0.0075 ; // mm/ns  ; Dirift velosity
double step_size           = 0.1    ; // mm     ; step size for calculation of induced charge
double channel_width       = 10     ; // ns     ; Flash ADC channel width

double r_map               = 50.    ; // mm  <--- To fix later!!!

int Nsum = 100000 ;
int Nphi =   10000 ;


double c_time[N_TIME];  // time-stamps for induced charge map
double i_time[N_TIME];  // time-stamps for current map (in the center btw time-stamps for charge)

// first index = map size
// MUST FIT r_map/step_size
double  charge[500][N_TIME];
double current[500][N_TIME];

double anode_area_of_overlap[N_ANODES];

long long int Nmc=1000000000;
double anode_area_mc_estimation[N_ANODES];

//double anode_charge [N_ANODES][3500][N_TIME];
//double anode_current[N_ANODES][3500][N_TIME];

double anode_xy_charge [N_ANODES][N_TIME];
double anode_xy_current[N_ANODES][N_TIME];
