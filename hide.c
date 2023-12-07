#include<sys/syscall.h>
#include<linux/unistd.h>
#include<stdio.h>
#define __NR_hide 453
int main(int argc,char*argv[]){
    syscall(__NR_hide, atoi(argv[1]), 1); // hide the process whose pid is argv[1]
    return 0;
}