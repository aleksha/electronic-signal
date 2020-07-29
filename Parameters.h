#include "TMath.h"
const int N_ANODES = 9;
const int N_R      = 5000;
const int N_TIME   = 200;
double pi = TMath::Pi();

bool read_from_db = false ;

double grid_anode_distance = 10.    ; // mm     ; Grid-Anode distance
double drift_velocity      = 0.0075 ; // mm/ns  ; Dirift velosity
double channel_width       = 40     ; // ns     ; Flash ADC channel width

double r_map     = 50.  ; // mm
double step_size = 0.01 ; // mm

int Nsum = 100000 ;
int Nphi =   10000 ;


double c_time[N_TIME];  // time-stamps for induced charge map
double i_time[N_TIME];  // time-stamps for current map (in the center btw time-stamps for charge)

// first index = map size
// MUST FIT r_map/step_size
double  charge[N_R][N_TIME];
double current[N_R][N_TIME];

double anode_area_of_overlap[N_ANODES];

long long int Nmc=1000000000;
double anode_area_mc_estimation[N_ANODES];

//double anode_charge [N_ANODES][3500][N_TIME];
//double anode_current[N_ANODES][3500][N_TIME];

double anode_xy_charge [N_ANODES][N_TIME];
double anode_xy_current[N_ANODES][N_TIME];
