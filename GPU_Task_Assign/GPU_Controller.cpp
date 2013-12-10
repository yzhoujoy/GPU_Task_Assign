//
//  main.cpp
//  GPU_Task_Assign
//
//  Created by YING ZHOU on 12/9/13.
//  Copyright (c) 2013 YING ZHOU. All rights reserved.
//

#include "GPU_Controller.h"
#include "GPU.h"
#include "GPU.cpp"
#include <map>
using namespace std;

class GPU_Controller{

public:
    map<int,int> GPU_map;//map<GPU_id,flag>
    map<int,int> GPU_assign;//assigned GPU
    int ready_ctr,sum_buf;
    
    GPU_Controller(){
        ready_ctr=0;
        sum_buf=0;
    }
    
    int parse(GPU *gpu_16[]){
        for (int counter=0; counter<16; counter++) {
            if(gpu_16[counter]->f_ready==1){
                GPU_map[counter]=0;//ready
                ready_ctr++;
            }else{
                GPU_map[counter]=1;  //passive_idle
            }
        }
        return ready_ctr;     //inform how many task should be sent
    }
    
    
    void assign_task(GPU *gpu_16[],double *task){
        int counter =0;
        map<int,int>::iterator iter2 = GPU_assign.begin();
        for (iter2; iter2 !=GPU_assign.end(); iter2++) {
            iter2->second=0;
        }
        map<int, int>::iterator iter = GPU_map.begin();
        for (iter; iter != GPU_map.end(); iter++) {
            if(iter->second==0){
                gpu_16[iter->first]->update(task[counter]);
                GPU_assign[iter->first]=1;
            }
            counter++;
        }
        
    }
    
     int sum_per_iter(){
        int num_tog_buf=11;
        for (int ctr=0; ctr<15; ctr=ctr+2) {
            if ((GPU_assign[ctr]==1)||(GPU_assign[++ctr]==1)) {
                num_tog_buf +=3;
            }
        }
        sum_buf += num_tog_buf;
        return sum_buf;
    }
    
};






















