#include<sys/syscall.h>
#include<linux/unistd.h>
#include<stddef.h>
#define __NR_hide_user_processes 454
int main(int argc,char*argv[]){
    syscall(__NR_hide_user_processes, atoi(argv[1]), argv[2]);
    return 0;
}