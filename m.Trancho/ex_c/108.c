#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct Vecture2d{
    double x;
    double y;
}v;
v translation(v V, v T);
v agrandissement(v V, v C, double alpha);
v Rotation (v V, v C, double delta);
int main(){
v V;
v C;
v T;
double alpha=0.4;
double delta=0.9;
v v_tr= translation(V,T);
v v_ag=agrandissement(V,C,alpha);
v v_rot=Rotation(V,C,delta);
printf("%2.lf %2.lf",v_tr.x,v_tr.y);
printf("%2.lf %2.lf",v_ag.x,v_ag.y);
printf("%2.lf %2.lf",v_rot.x, v_rot.y);
}
v translation(v V, v T) {
    v result;
    result.x = V.x + T.x;
    result.y = V.y + T.y;
    return result;
}
v agrandissement(v V, v C, double alpha) {
    v result;
    result.x = alpha * (V.x - C.x) + C.x;
    result.y = alpha * (V.y - C.y) + C.y;
    return result;
}
v Rotation (v V, v C, double delta){
    v result;
    double cos_delta=cos(delta);
    double sin_delta=sin(delta);
    result.x= cos_delta*(V.x+C.x)-sin_delta*(V.y-C.y)+C.x;
    result.y= sin_delta*(V.x+C.x)+cos_delta*(V.y-C.y)+C.y;
    return result;
}