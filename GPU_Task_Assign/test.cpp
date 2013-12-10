//
//  main.cpp
//  GPU_Task_Assign
//
//  Created by YING ZHOU on 12/9/13.
//  Copyright (c) 2013 YING ZHOU. All rights reserved.
//


#include "test.h"
#include "GPU_Controller.h"
#include "GPU_Controller.cpp"
#include "Buffer.h"
#include "Buffer.cpp"
#include <map>
using namespace std;

int main(){
    GPU *gpus[16];
    for (int i=0; i<16; i++) {
        gpus[i]=new GPU();
    }
    GPU_Controller *controller= new GPU_Controller();
    double task_arr [10];
    task_arr[0]=0.75;
    task_arr[1]=0.25;
    task_arr[2]=0.5;
    task_arr[3]=1;
    task_arr[4]=0.5;
    task_arr[5]=0.5;
    task_arr[6]=0.25;
    task_arr[7]=0.75;
    task_arr[8]=1;
    task_arr[9]=0.5;
    Buffer *obj = new Buffer();
    int num_task=0;
    double *input_arr=NULL;
    
    for (int i=0;i<1;i++) {
        num_task = obj->buffer_empty_slot();
        //cout<<"the number of empty items in buffer is "<< num_task<<endl;
        if (num_task>=10) {
            input_arr=task_arr;
            //cout<<"the number of empty items is more than 10"<<endl;
        }else{
            //cout<<"the number of empty items is less than 10"<<endl;
            double input_arr2[num_task];
            for (int n=0; n<num_task; n++) {
                input_arr2[n]=task_arr[n];
                //cout<<"input array element "<<input_arr2[n]<<endl;
            }
            input_arr=input_arr2;
        }
        
        //cout<<sizeof(*input_arr)/sizeof(double)<<endl;

        obj->buffer_input(input_arr, num_task);
        map<int, double>::iterator iter = obj->tasks.begin();
//        for (iter; iter != obj->tasks.end(); iter++) {
//            cout<<"task id = "<< iter->first<< " task value = "<< iter->second<<endl;
//        }
        int cost = obj->drop_cost(obj->num_drop);
        double *output_arr = obj->buffer_output(num_task);
        
        controller->parse(gpus);
        
        
        
       
    }
    
    
    
    
    return 0;
 
}