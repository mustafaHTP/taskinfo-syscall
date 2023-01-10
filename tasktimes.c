/**
 * @file tasktimes.c
 * @author Mustafa Hatipoğlu
 * 
 * @brief prints process info 
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define _GNU_SOURCE_
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h> 
#include <errno.h>
#include <sys/types.h>

#define SYS_TASK_TIME_INFO 451

int main(int argc, char* argv[]){
    long res;
    char buf[256];

    if(argc == 1){
        res = syscall(SYS_TASK_TIME_INFO, -1, (void*)buf, sizeof(buf));
    }else if(argc == 2){
        pid_t pid = atoi(argv[1]);
        res = syscall(SYS_TASK_TIME_INFO, pid, (void*)buf, sizeof(buf));
    }else{
        printf("Up to 1 argument can be given...\n");
        return -1;
    }

    if(res == -1){
        fprintf(stderr, "sys_task_time_info failed, errno = %d\n", errno);
    }else{
        if(argc == -1)
            printf("process has the biggest running times\n");
        printf("%s\n", buf);
    }
}