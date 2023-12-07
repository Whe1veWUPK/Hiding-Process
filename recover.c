#include<sys/syscall.h>
#include<linux/unistd.h>
#include<stdio.h>
#define __NR_hide 453
int main(int argc,char*argv[]){
    syscall(__NR_hide, atoi(argv[1]), 0);
    return 0;
}