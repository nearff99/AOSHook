#include "hook.h"
#include <android/log.h>


static struct hook_t eph;

int hook_func(int p0,int p1,int p2,int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12, int p13, int p14, int p15)
{
    int (*orig_func)(int p0,int p1,int p2,int p3,int p4,int p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12, int p13, int p14, int p15);

    orig_func = (void*)eph.proto;
    
    LOGD("before orig\n");

    int ret = orig_func(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15);
    //int ret = orig_func("/data/local/tmp/test2",p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15);

    LOGD("after orig\n");

    return ret; 
}

int init_func(char * str){
    LOGD("%s, hook in pid = %d\n", str, getpid());

    long target_addr = 0;

    //if target func is thumb, be sure to add 0x1 to the func addr.
    target_addr = 0x22138; //strcmp;
    //target_addr = 0x20e78; //nanosleep;
    //target_addr = 0x2dfcf; //sleep;
    //target_addr = 0x20afc; //lstat;
    hook_by_addr(&eph, "libc.so", target_addr, hook_func);
    
    //hook_by_name(&eph_sendto, "libc.so", "sendto", sendto_thumb, sendto_arm);

    return 0;
}
    
