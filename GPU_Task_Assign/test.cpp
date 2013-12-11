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
    double task_temp[10];
    double task_arr [500];
    int task_counter=0;
    for (int n=0; n<300; n++) {
        task_arr[n]=1;
    }

    
    Buffer *obj = new Buffer();
    int num_task=0;
    double *input_arr=NULL;
    
    
    for (int i=0; i<16; i++) {                    //for duration
        cout<<"$$$$$$$$$$$$$$$$$ "<<i<<endl;
        
        //empty buffer size
        num_task = obj->buffer_empty_slot();
        
        //assign CPU output task array
        if (num_task>=10) {
            int ctr_temp1=0;
            for (int n=task_counter; n<task_counter+10; n++) {
                task_temp[ctr_temp1]=task_arr[n];
                ctr_temp1++;
            }
            input_arr=task_temp;
            num_task=10;
            task_counter+=10;
            cout<<"task counter = "<<task_counter<<endl;
        }else{
            cout<<"not 10 tasks"<<endl;
            int ctr_temp2=0;
            double input_arr2[num_task];
            for (int n=task_counter; n<task_counter+num_task; n++) {
                cout<<"in CPU array "<<task_arr[n]<<endl;
                input_arr2[ctr_temp2]=task_arr[n];
                ctr_temp2++;
            }
            task_counter+=num_task;
            input_arr=input_arr2;
            cout<<"pointer = "<<input_arr<<endl;
            double *input_arr_t=input_arr;
            for (int m=0; m<num_task; m++) {
                cout<<"######"<<*input_arr_t<<endl;
                input_arr_t++;
            }
            cout<<"task counter = "<<task_counter<<endl;
        }
        
        //CPU input to Bbuffer
        cout<<"number of task to input to buffer: "<<num_task<<endl;
        double *input_arr_tt=input_arr;
        cout<<"pointer = "<<input_arr<<endl;
        for (int m=0; m<num_task; m++) {
            cout<<"!!!!!!!!"<<*input_arr_tt<<endl;
            input_arr_tt++;
        }
        obj->buffer_input(input_arr, num_task);
        int cost_dp = obj->drop_cost(obj->num_drop);
        cout<<"cost from dropped jobs: "<<cost_dp<<endl;
        
        //check ready number of GPUs
        int ready_ctr=controller->parse(gpus);
        cout<<"number of ready GPUs: "<<ready_ctr<<endl;

        //buffer output array for GPUs
        double *output_arr = obj->buffer_output(ready_ctr);        
        
        //assign tasks to GPUs
        controller->assign_task(gpus, output_arr,obj->out_num);
        map<int,int>::iterator iter_contr = controller->GPU_assign.begin();

        for (int ctr=0; ctr<16; ctr++) {
            cout<<"gpu id = "<< ctr << " idle =" << gpus[ctr]->f_idle<< " ready=" << gpus[ctr]->f_ready<<" hot ="<<gpus[ctr]->hot<<endl;

        }
        
        //cost from buffer toggling
        int cost_tg = controller->sum_per_iter();
        cout<<"sum of toggling buffer ="<<cost_tg<<endl;
        
    }
    

    
    return 0;
 
}