#include "cordic.cpp"


int main(){
    DUT dut;
    int divisor=8;//x
    int dividend=41;//y

    dut.cordic(divisor,dividend,0,1,1);//rot_mode=1,cordic_mode=1

    return 1;
}
