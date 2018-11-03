#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cacheutils.h"

#include <unistd.h>
#include <stdlib.h>

// My processor 
//  L1 I-Cache :8-way   128-set  32 KiB     
//  L1 D-Cache :8-way   64-set   32 KiB 
//  L2 Cache   :8-way   512-set 256 KiB
//  L3 Cache   :16-way  4096-set  4 MiB 
////////////////////////////////////////////////////////////////////////

#define BYTES_PER_GB (1024*1024*1024LL)

#define GIGABYTES_RAM 8

#define CACHE_LINE 64

#define LLC_BYPASS 1024

////////////////////////////////////////////////////////////////////////
// This fragment of code tries to occupy the bandwidth by trying to 
// stress the different banks of the DRAM by keeping a particular Row loaded
// into the memory buffer so that the memory access from the DRAM Faces latency
// and hence reduces the Request Service Rate.
////////////////////////////////////////////////////////////////////////

static char array[GIGABYTES_RAM*BYTES_PER_GB];

void bypass_access()
{
    unsigned int i,j,k,x;
    volatile unsigned int s;
    
    unsigned long int a;
    bool check = true;
    long int d1=0,d2=0,d3=0,f=0,t=1;

    while (t--){
        
        for(long int i = 0;i <GIGABYTES_RAM*BYTES_PER_GB;i=i+(4)){
            if(i>400*100){break;}
            a = gettime();
            s = array[i];
            long int time =  gettime() - a;
            
            //printf("address : %d, delay : %lu\n", i, time);
            if(time > 230 && time<500){
             printf("address : %ld, delay : %lu\n", i-d1, time);
             d1=i;  
             f=1;             
            }
            else if(time > 500 && time<3500){
             printf("address : %ld, delay : %lu\n", i-d2, time);
             d2=i;  
             f=1;             
            }
            else if(time > 3500){
             printf("address : %ld, delay : %lu\n", i-d3, time);
             d3=i;  
             f=1;                
            }
 
            
        }

 /*
        for (j=0; j<128,check==true; j++){

            for (k=0; k<=7,check==1; k++){ 
                x = (j+k<<7+i) << 6;
                if( x < 8*BYTES_PER_GB){
                    a = gettime();
                    s = array[(j+k<<7+i)<<6];
                    printf("address : %u, delay : %lu\n", x, gettime() - a);
                }
                else{
                    check = false;            
                    break;
                }
            }
        }

    
        i+=128*8;*/
}


}

int main()
{
    //while (1) {
        bypass_access();  
        printf("hello\n");
    //}
    return 0;
}
