int get_pad_number_Rings(double x, double y){

    // central pad R = 10 mm
    // other rinrs with width = 40 mm
    // numberinf inner-to-outer

    double l;
    l = sqrt(x*x+y*y);

    if( l>290 && l<=330) return  8;
    if( l>250 && l<=290) return  7;
    if( l>210 && l<=250) return  6;
    if( l>170 && l<=210) return  5;
    if( l>130 && l<=170) return  4;
    if( l> 90 && l<=130) return  3;
    if( l> 50 && l<= 90) return  2;
    if( l> 10 && l<= 50) return  1;
    if( l<=10)           return  0;

    return -1;
}

int get_pad_number(double x, double y){
// This functions returns pad number from a
// coordinate on the anode (x,y)-plane.
// You can use per-defined (in AnodeLib) ones.

    return get_pad_number_Rings(x,y);
}
