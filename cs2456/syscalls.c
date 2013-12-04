#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/mmzone.h>
#include <linux/mm_types.h>
#include <linux/slab.h>
#include <linux/rmap.h>
#include <asm-x86/uaccess_32.h>
struct mem_stats{
    long active,inactive,ref_active,ref_inactive,moved,evicted;
};
long moved, evicted;
asmlinkage long sys_cs2456_memstat(struct mem_stats * stat){
    struct mem_stats * stats;
    struct zone * pointer;
    struct page * pos;
    int returns=0;
    stats=kmalloc(sizeof(struct mem_stats),GFP_USER);
    stats->active=0;
    stats->inactive=0;
    stats->ref_active=0;
    stats->ref_inactive=0;
    stats->moved=0;
    stats->evicted=0;
    for_each_zone(pointer){
        spin_lock_irq(pointer->lru_lock);
        list_for_each_entry(pos,&pointer->active_list,lru){
            stats->active++;
            if(PageReferenced(pos)){
                stats->ref_active++;
            }
        }
        list_for_each_entry(pos,&pointer->inactive_list,lru){
            stats->inactive++;
            if(PageReferenced(pos)){
                stats->ref_inactive++;
            }
        }
        spin_unlock_irq(pointer->lru_lock);
    }
    stats->moved=moved;
    stats->evicted=evicted;
    if(copy_to_user(stat,stats,sizeof(struct mem_stats))!=0){
        returns=1;
    }
    kfree(stats);
    return returns;
}
