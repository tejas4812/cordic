#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<algorithm>
#include<numeric>
#include<cmath>
#include<string>

using namespace std;
#define QRES 15
class DUT {
 public:
     DUT(){
      cout<<"DUT default constructor"<<endl;
     }
     void cordic(int x,int y,int z, int rot_mode,int cordic_mode);
     int theta(int,int);

     int x1,y1,z1;
};



void DUT::cordic(int x,int y,int z, int rot_mode,int cordic_mode){
 //(rot_mode= 0 for circular) (rot_mode=1 for linear)// (cordic_mode=1 for vectorizing and 0 for rotation)
 //QRES=10 defined in the header file not yet included int he psuedo code
 int i=0;
 int d=0;
 int u;
 int x_temp=0; 
 int y_temp=0;
 int z_temp=0;
 int z2;

 int shiftDen = 0;
    while (y>= 2*x) {
        x *= 2;
        shiftDen++;
    }

 cout<<"shiftDen="<<shiftDen<<endl;
 x1=x<<QRES;//Q9.QRES 
 y1=y<<QRES;//Q9.QRES
 z1=z<<QRES;//Q7.QRES
 u=(rot_mode==0)?1:(rot_mode==1)?0:-1;
     while(i!=(16)){
        if(cordic_mode==0) {
            d=(z1<0)?-1:1;//d=sign(z)
        }
        else if(cordic_mode==1){
            d=(y1<0)?1:-1;
        }
        cout<<"x1="<<x1<<endl;
        cout<<"y1="<<y1<<endl;
        cout<<"z1="<<z1<<endl;
        cout<<"i="<<i<<endl;
       if(d<0){
        x_temp=x1+u*(y1>>i);
        y_temp=y1-(x1>>i);
        z_temp=z1+theta(i,rot_mode);
       }
       else {
        x_temp=x1-u*(y1>>i);
        y_temp=y1+(x1>>i);
        z_temp=z1-theta(i,rot_mode);
       }
       x1=x_temp;
       y1=y_temp;
       z1=z_temp;
         i++;
     }
 x1=x1>>(QRES+shiftDen);
 
 y1=y1>>QRES;
 if(cordic_mode==1 && rot_mode==1){//(y/x)
    z1 = z1<<(shiftDen); 
    z2=(z1)>>(QRES-3);//3 bits for fractional remainder
    
 }
        cout<<"x1="<<x1<<endl;
        cout<<"y1="<<y1<<endl;
        cout<<"Quotient="<<(z2/8)<<endl;
        cout<<"Remainder="<<(z2&7)<<endl;
        cout<<"i="<<i<<endl;
}


int DUT::theta(int i,int mode)
{
    if(mode==0) {   
    //Q6.4//QRES different than 4 needs modifcation in the table
       switch(i) {
       case 0: return 720;//45;
       case 1: return 425;//26.6;
       case 2: return 224;//14;
       case 3: return 113;//7.1;
       case 4: return 57;//3.6;
       case 5: return 28; //1.8;
       case 6: return 14;//0.9;
       case 7: return 6;//0.4;
       case 8: return 3;//0.2;
       case 9: return 1;//0.1;
       default: return 0;
       }
    }
    else if (mode==1){
    //Q6.QRES
       return 1<<(QRES-i);
    }
    else{
       return 0;
    }
}
