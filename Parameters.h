#include "TMath.h"

double pi = TMath::Pi();


double grid_anode_distance = 10.    ; // mm     ; Grid-Anode distance
double drift_velocity      = 0.0075 ; // mm/ns  ; Dirift velosity
double step_size           = 0.1    ; // mm     ; step size for calculation of induced charge
double channel_width       = 40     ; // ns     ; Flash ADC channel width

double r_map               = 50.    ; // mm  <--- To fix later!!!

int Nsum = 100000 ;
int Nphi =   10000 ;
