//
//  main.cpp
//  GPU_Task_Assign
//
//  Created by YING ZHOU on 12/9/13.
//  Copyright (c) 2013 YING ZHOU. All rights reserved.
//


#include "GPU.h"
using namespace std;

class GPU {

public:
    int hot,busy,k,counter,f_idle,f_ready;//time;
    double array[10];
    
    GPU(){
        hot = 0;
        busy= 0;
        k=3;
        counter=0;
        f_idle=0;
        f_ready=1;
        //time=0;
        for(int i=0; i<10;i++)
        {
            array[i] = 0.0;
        }
    }
   
    void update(double time){
        double sum=0;
        int ctr = counter%10;
        double avg =0;
        array[ctr] = time;
        if(ctr>=9)
        {
            for(ctr;ctr>ctr-9;ctr--)
            {
                sum +=array[ctr];
                
            }
        
        }
        avg = sum/10;
        if(avg > 0.5)
        {
            f_idle=1;
            passive_idle();
            //hot=1;
            //busy=0;
        }
        else
        {
            f_ready=0;
            ready();
        }
        counter++;
    }

    void passive_idle(){
        hot=1;
        busy=1;
        if(k>0)k--;
        else f_idle=0;
    }
    
    void ready(){
        hot=0;
        busy=0;
        f_idle=0;
    }

};