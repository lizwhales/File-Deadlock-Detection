#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct {
    int process;
    int locked;
    int requested;
} resource_t;

void detect(char *filename);
int member(int* array, int arr_len, int id);

int main(int argc, char **argv)
{
    /* command line parsing */    
    char *filename = NULL;
    int opt;
    while((opt = getopt(argc, argv, "f:ce")) != -1){
        switch(opt){
            case 'e':
                printf("option: %c\n", opt);
                break;
            case 'f':
                filename = optarg;
                break;
            default:
                printf("unknown option");
                break;
        }
    } 
    
    detect(filename);
    
    return 0;
}

void detect(char *filename){

    resource_t *resources = NULL;
    FILE *f;
    int i;
    int j;
    resource_t *new_res = NULL;
    size_t count = 0;
    size_t alloc = 0;

    f = fopen(filename, "r");
     
    /* reading in the files */ 
    while (1) {
        if (count >= alloc) {
            alloc += 1000;
            resources = realloc(resources,sizeof(resource_t) * alloc);
        }
        new_res = &resources[count];

        if (fscanf(f, "%d %d %d", &(new_res->process), &(new_res->locked), &(new_res->requested)) == EOF){
            break;

        }
        count++;
    }

    fclose(f);

    resources = realloc(resources,sizeof(resource_t) * count);

    
    new_res = resources;


    /* TASK 1: find no. processes and files */
    
    int * all_files = malloc(sizeof(int) * count*2);
    int curr_file = 1;
    int num_process = 0;

    for (int i = 0; i < count; i++)
    {
        num_process++;
        for (int j = 0; j < curr_file; j++)
        {
            if (!member(all_files, curr_file, new_res[i].locked))
            {   
                all_files[curr_file++] = new_res[i].locked;
            }
            if (!member(all_files, curr_file, new_res[i].requested))
            {
                all_files[curr_file++] = new_res[i].requested;
            }
        }
    }


    printf("\nProcesses %d", num_process);
    printf("\nFiles %d", curr_file - 1);


    /* TASK 2: find execution time */


    int mode = 1;


    for(i = 0; i < count; i++){
        if(new_res[i].requested == new_res[i+1].requested){
            mode++;
        }else{
            i++;
        }
    }

    int exe_time = mode + 1;
    printf("\nExecution time %d", exe_time);


    /* TASK 3: find deadlocks */

    int deadlock_cnt;

    for(i = 0; i < count; i++){
        for(j = 0; j < count; j++){
            if(new_res[i].locked == new_res[j].requested){
                deadlock_cnt++;       
        }else{
            deadlock_cnt = 0;
        }
    }

    if(deadlock_cnt > 0){
        printf("\nDeadlock detected"); 
        break;
    }else{
        printf("\nNo deadlocks");
        break;
    }       

    
    }

    /* TASK 4: find and terminate deadlocked processes */

    int * term_processes = malloc(sizeof(int) * count*2);

    for(i = 0; i < count; i++){
            for(j = 0; j < count; j++){
                if(new_res[i].locked == new_res[j].requested){
                    term_processes[i] = new_res[i].process;
            }
        }
    }


    /* finds the smallest process to terminate */

    int loc = 0;
    for(i = 0; i < count; i++){
        if(term_processes[i] < term_processes[loc]){
            loc = i;
        }
    }
    

    printf("\nTerminate %d", term_processes[loc]);
   

    /* free memory */
    free(all_files);
    free(term_processes);
    free(new_res);

}

 /* creates array of members of locked and requested files */

int member(int* array, int arr_len, int id)
{
    for (int i = 0; i < arr_len; i++)
    {
        if (array[i] == id)
        {
            return 1;
        }
    }
    return 0;
}

