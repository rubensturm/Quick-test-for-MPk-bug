#define _GNU_SOURCE
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>
#include <errno.h>

const int stack_size = 4096*4096;

extern void asm_signal_entry(int signo);
int main(){
    struct sigaction act_user1 = {};
    act_user1.sa_handler = asm_signal_entry;
    //act_user1.sa_flags |= SA_ONSTACK;
    assert(sigaction(SIGUSR1, &act_user1, NULL) == 0);
    printf("start\n");
    asm volatile(
        "xorl %%ecx, %%ecx\n\t"
        "xorl %%edx, %%edx\n\t"
        "movq $11, %%rax\n\t"
        "wrpkru\n\t"
        "movq $62, %%rax\n\t" /*kill syscall number*/
        "movq $0, %%rdi\n\t"
        "movq $10, %%rsi\n\t" /*SIGUSR1*/
        "syscall\n\t"
        "xorl %%ecx, %%ecx\n\t"
        "xorl %%edx, %%edx\n\t"
        "movq $0, %%rax\n\t"
        "wrpkru\n\t"
        :
        :
        :"rax", "rcx", "rdx", "rdi", "rsi"
    );
    printf("end\n");
    return 0;
}