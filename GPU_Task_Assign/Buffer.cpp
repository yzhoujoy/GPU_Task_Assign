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
    int out_num;                               //number of tasks should be sent
    map<int, double> tasks;
    int num_drop;
    double output_arr[20];
    
    /*provide number of empty slot*/
    int buffer_empty_slot(){
        int num_task=0;
        num_task=20-(int)tasks.size();         //number of empty items in buffer
        if (num_task<10) num_drop=10-num_task; 
        else num_task=10;
        return num_task;                       //number of task can be store into buffer
    }
    
    /*store tasks from CPU to buffer*/
    void buffer_input(double *task, int size){
        for (int n=0; n<size ; n++) {
            cout<<"input array $$$$$$= "<<*task<<endl;
            tasks[task_ctr]=*task;
            task++;
            task_ctr++;
        }
        map<int,double>::iterator iter_t=tasks.begin();
        for (iter_t; iter_t !=tasks.end(); iter_t++) {
            cout<<"^^^^^^^^^^^"<<iter_t->second<<endl;
        }
    }
    
    /*caculate size of output array*/
    double * buffer_output(int num_output){
        out_num=0;               
        cout<<"used buffer size = "<<(int)tasks.size()<<endl;
        cout<<"number of ready GPUs = "<< num_output<<endl;
        
        //assign size of output array
        if (tasks.size()<num_output) out_num=(int)tasks.size();
        else out_num=num_output;
        map<int, double>::iterator iter_temp=tasks.begin();
        int n_temp=0;
        for (iter_temp; iter_temp !=tasks.end(); iter_temp++) {
            cout<<"buffer"<<n_temp<<" = "<<iter_temp->second<<endl;
            n_temp++;
        }
        
        double *output_pt=output_arr;
        map<int, double>::iterator iter;
        for (int n=0; n<out_num; n++) {
            iter=tasks.begin();
            *output_pt=iter->second;
            output_pt++;
            tasks.erase(iter);
        }
        if (tasks.empty()) {
            cout<<"it's empty!"<<endl;
        }else
            cout<<"it's not empty!"<<endl;
        
        int n_temp2=0;
        map<int, double>::iterator iter_erase=tasks.begin();
        for (iter_erase; iter_erase !=tasks.end(); iter_erase++) {
            cout<<"buffer after erase"<<n_temp2<<" = "<<iter_temp->second<<endl;
            n_temp2++;
        }
        cout<<"size of output array = "<< out_num<<endl;
        for (int i=0; i<out_num; i++) {
            cout<<"output task = "<<output_arr[i]<<endl;
        }
        return output_arr;
    }
    
    int drop_cost(int num_of_drop){
        sum += num_of_drop*5;
        return sum;
    }
    
    
};