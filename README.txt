Tanner Degenkolb
Doug Miller

The system call was implemented based on the existing detail in the vm_event code, 
and manual searches through each page utilizing the active and inactive lists in 
each zone.

    Active and Inactive page totals were aquired by a simple count of each page in 
    the active or inactive list of each zone.

    Active Refferenced and Inactive Refferenced pages were found on the same pass by 
    incrementing the counter only when the referenced bit for the page was set.

    Evicted and Moved pages were taken from the global vm_stat variable.

For each frame we added an extra variable tracing reference count. This was incremented 
by a timed function call the every 100 Jiffies checked if the reference bit on each 
page had been set and incremented it otherwise.  To avoid overflow a maximum cap was 
placed on these counters.  These modifications were made separately for the individual 
checks in the active and inactive lists.

There were two test cases constructed.  The first to modify active referenced, and 
inactive referenced counts and the second to test all other counts.
    The first worked by memory mapping a file and then reading from it.  This results 
    in the pages alocated to the file being marked as refferenced, and epending on the 
    frequency of the reads they can be in either the active or inactive lists when marked.

    The second worked by reoeaatedly mallocing memory untill the kernel had to make it 
    inactive, and then eventually evict it.

