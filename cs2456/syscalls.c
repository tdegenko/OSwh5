#include <linux/kernel.h>
#include <linux/mmzone.h>
#include <linux/slab.h>
#include <asm-x86/uaccess_32.h>
struct mem_stats{
    long active,inactive,ref_active,ref_inactive,moved,evcted;
};
asmlinkage long sys_cs2456_memstat(struct mem_stats * stat){
    struct mem_stats * stats;
    struct zone * pointer;
    stats=kmalloc(sizeof(struct mem_stats),GFP_USER);
    for_each_zone(pointer){
    }
    if(copy_to_user(stat,stats,sizeof(struct mem_stats))!=0){
        return 1;
    }
    return 0;
}
