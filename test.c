#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/unistd.h>
#include <sys/syscall.h> 
#include <sys/mman.h>

#define _MEMSTAT_ 327

struct mem_stats{
    long active,inactive,ref_active,ref_inactive,moved,evicted;
};

int main(int argc, char *argv[])
{
    struct mem_stats * stat=malloc(sizeof(struct mem_stats));
    syscall(_MEMSTAT_, stat);
    printf("Active:\t%d\nInactive:\t%d\nRefferenced Active:\t%d\nRefferenced Inactive:\t%d\nMoved:\t%d\nEvicted:\t%d\n",stat->active,stat->inactive,stat->ref_active,stat->ref_inactive,stat->moved,stat->evicted);
    int fp;
    int i,j;
    fp = open("testfile", 0);
    if(fp==-1){
        exit(1);
    }
    char * a=mmap(NULL,1024*1024,PROT_READ,MAP_SHARED,fp,0);
    printf("pointer %p\n",a);
    //    perror("NOPE:");
    printf("after reading 1MB from file\n");
    for(i=0;i<1024*1024;i+=4096){
        j+=a[i];
    }
    
    syscall(_MEMSTAT_, stat);
    printf("Active:\t%d\nInactive:\t%d\nRefferenced Active:\t%d\nRefferenced Inactive:\t%d\nMoved:\t%d\nEvicted:\t%d\n",stat->active,stat->inactive,stat->ref_active,stat->ref_inactive,stat->moved,stat->evicted);
    char * tmp;
    for(i=0;i<65;i++){
        tmp = malloc(1024*1024);
        memset(tmp,1,1024*1024);
        for(j=0;j<1024*1024;j++){
            *(tmp+j)='c';
        }
        printf("\nMalloced and accessed %d MBs\n",i);
        
        syscall(_MEMSTAT_, stat);
        printf("Active:\t%d\nInactive:\t%d\nRefferenced Active:\t%d\nRefferenced Inactive:\t%d\nMoved:\t%d\nEvicted:\t%d\n",stat->active,stat->inactive,stat->ref_active,stat->ref_inactive,stat->moved,stat->evicted);
        }
    return 0;
}
   
