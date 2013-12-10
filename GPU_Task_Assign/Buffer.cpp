//
//  main.cpp
//  GPU_Task_Assign
//
//  Created by YING ZHOU on 12/9/13.
//  Copyright (c) 2013 YING ZHOU. All rights reserved.
//


#include "Buffer.h"
#include <map>

using namespace std;

class Buffer{
public:
    int task_ctr=0;
    int sum=0;
    map<int, double> tasks;
    int num_drop;
    double output_arr[20];
    int buffer_empty_slot(){
        int num_task=0;
        num_task=20-(int)tasks.size();  //number of empty items in buffer
        if (num_task<10) {
            num_drop=10-num_task;
        }else{
            num_task=10;
        }
        return num_task;
    }
    
    void buffer_input(double *task, int size){
        for (int n=0; n<size ; n++) {
            tasks[task_ctr]=*task;
            task++;
            task_ctr++;
        }
    }
    
    double * buffer_output(int num_output){
        
        //double output_arr[num_output];
        double *output_pt=output_arr;
        map<int, double>::iterator iter;
        for (int n=0; n<num_output; n++) {
            iter=tasks.begin();
            *output_pt=iter->second;
            output_pt++;
            tasks.erase(iter);
        }
        for (int i=0; i<num_output; i++) {
            cout<<"output = "<<output_arr[i]<<endl;
            //cout<<"output == "<<*output_arr<<endl;
            
        }
        
       // double *out_arr=output_arr;
        return output_arr;
    }
    
    int drop_cost(int num_of_drop){
        sum += num_of_drop*5;
        return sum;
    }
    
    
    
};