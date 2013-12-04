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

    The second worked by repeatedly mallocing memory untill the kernel had to make it 
    inactive, and then eventually evict it.

We combined these two tests into one program, which we used to compare the overall efficacy
of our methodology vs the original kernel code.

The output using the original kernel code is as follows:




Active: 1972
Inactive:       1324
Refferenced Active:     1254
Refferenced Inactive:   467
Moved:  0
Evicted:        79766

after reading 1MB from file
Active: 1976
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 0 MBs
Active: 2228
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 1 MBs
Active: 2494
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 2 MBs
Active: 2746
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 3 MBs
Active: 2998
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 4 MBs
Active: 3264
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 5 MBs
Active: 3516
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 6 MBs
Active: 3768
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 7 MBs
Active: 4034
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 8 MBs
Active: 4286
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 9 MBs
Active: 4538
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 10 MBs
Active: 4804
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 11 MBs
Active: 5056
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 12 MBs
Active: 5322
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 13 MBs
Active: 5574
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 14 MBs
Active: 5826
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 15 MBs
Active: 6092
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 16 MBs
Active: 6344
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 17 MBs
Active: 6596
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 18 MBs
Active: 6862
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 19 MBs
Active: 7114
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 20 MBs
Active: 7366
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 21 MBs
Active: 7632
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 22 MBs
Active: 7884
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 23 MBs
Active: 8136
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 24 MBs
Active: 8402
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 25 MBs
Active: 8654
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 26 MBs
Active: 8920
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 27 MBs
Active: 9172
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 28 MBs
Active: 9424
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 29 MBs
Active: 9690
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 30 MBs
Active: 9942
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 31 MBs
Active: 10194
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 32 MBs
Active: 10460
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 33 MBs
Active: 10712
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 34 MBs
Active: 10964
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 35 MBs
Active: 11230
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 36 MBs
Active: 11482
Inactive:       1572
Refferenced Active:     1258
Refferenced Inactive:   715
Moved:  0
Evicted:        79766

Malloced and accessed 37 MBs
Active: 11132
Inactive:       1980
Refferenced Active:     707
Refferenced Inactive:   1213
Moved:  655
Evicted:        79982

Malloced and accessed 38 MBs
Active: 11123
Inactive:       1994
Refferenced Active:     519
Refferenced Inactive:   1332
Moved:  917
Evicted:        80228

Malloced and accessed 39 MBs
Active: 11375
Inactive:       1714
Refferenced Active:     512
Refferenced Inactive:   1188
Moved:  925
Evicted:        80515

Malloced and accessed 40 MBs
Active: 11641
Inactive:       1458
Refferenced Active:     512
Refferenced Inactive:   1140
Moved:  925
Evicted:        80768

Malloced and accessed 41 MBs
Active: 11968
Inactive:       1140
Refferenced Active:     512
Refferenced Inactive:   952
Moved:  925
Evicted:        81012

Malloced and accessed 42 MBs
Active: 12309
Inactive:       820
Refferenced Active:     306
Refferenced Inactive:   528
Moved:  1053
Evicted:        81258

Malloced and accessed 43 MBs
Active: 12007
Inactive:       1160
Refferenced Active:     0
Refferenced Inactive:   389
Moved:  1616
Evicted:        81540

Malloced and accessed 44 MBs
Active: 12085
Inactive:       1112
Refferenced Active:     0
Refferenced Inactive:   244
Moved:  1792
Evicted:        81822

Malloced and accessed 45 MBs
Active: 11501
Inactive:       1683
Refferenced Active:     0
Refferenced Inactive:   110
Moved:  2640
Evicted:        82129

Malloced and accessed 46 MBs
Active: 10739
Inactive:       2447
Refferenced Active:     0
Refferenced Inactive:   13
Moved:  3652
Evicted:        82414

Malloced and accessed 47 MBs
Active: 9867
Inactive:       3350
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  4801
Evicted:        82684

Malloced and accessed 48 MBs
Active: 9141
Inactive:       4039
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  5784
Evicted:        82982

Malloced and accessed 49 MBs
Active: 9109
Inactive:       4206
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  6068
Evicted:        83099

Malloced and accessed 50 MBs
Active: 8583
Inactive:       4719
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  6848
Evicted:        83367

Malloced and accessed 51 MBs
Active: 8181
Inactive:       5096
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  7515
Evicted:        83657

Malloced and accessed 52 MBs
Active: 7801
Inactive:       5422
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  8154
Evicted:        83971

Malloced and accessed 53 MBs
Active: 7725
Inactive:       5537
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  8487
Evicted:        84189

Malloced and accessed 54 MBs
Active: 7689
Inactive:       5575
Refferenced Active:     1
Refferenced Inactive:   2
Moved:  8781
Evicted:        84448

Malloced and accessed 55 MBs
Active: 7565
Inactive:       5668
Refferenced Active:     1
Refferenced Inactive:   2
Moved:  9162
Evicted:        84738

Malloced and accessed 56 MBs
Active: 7505
Inactive:       5745
Refferenced Active:     1
Refferenced Inactive:   2
Moved:  9479
Evicted:        84978

Malloced and accessed 57 MBs
Active: 7381
Inactive:       5835
Refferenced Active:     1
Refferenced Inactive:   2
Moved:  9847
Evicted:        85256

Malloced and accessed 58 MBs
Active: 7307
Inactive:       5923
Refferenced Active:     1
Refferenced Inactive:   2
Moved:  10189
Evicted:        85510

Malloced and accessed 59 MBs
Active: 7316
Inactive:       5853
Refferenced Active:     1
Refferenced Inactive:   2
Moved:  10439
Evicted:        85830

Malloced and accessed 60 MBs
Active: 7279
Inactive:       5916
Refferenced Active:     1
Refferenced Inactive:   2
Moved:  10736
Evicted:        86061

Malloced and accessed 61 MBs
Active: 7241
Inactive:       5939
Refferenced Active:     1
Refferenced Inactive:   2
Moved:  11031
Evicted:        86333

Malloced and accessed 62 MBs
Active: 7247
Inactive:       5934
Refferenced Active:     1
Refferenced Inactive:   2
Moved:  11282
Evicted:        86589

Malloced and accessed 63 MBs
Active: 7252
Inactive:       5930
Refferenced Active:     1
Refferenced Inactive:   2
Moved:  11534
Evicted:        86845

Malloced and accessed 64 MBs
Active: 7359
Inactive:       5824
Refferenced Active:     1
Refferenced Inactive:   2
Moved:  11684
Evicted:        87101




The output from the tests with our changes is:



// DOUGS_MODE=y, DOUGS_MAX_USE_COUNT=100

Active: 1830
Inactive:       10658
Refferenced Active:     47
Refferenced Inactive:   3
Moved:  1943
Evicted:        150379
pointer 0xb7e7c000
after reading 1MB from file
Active: 1833
Inactive:       10718
Refferenced Active:     2
Refferenced Inactive:   52
Moved:  1945
Evicted:        150575

Malloced and accessed 0 MBs
Active: 2083
Inactive:       10472
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  1949
Evicted:        150840

Malloced and accessed 1 MBs
Active: 2334
Inactive:       10161
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  1958
Evicted:        151170

Malloced and accessed 2 MBs
Active: 2579
Inactive:       10005
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  1962
Evicted:        151336

Malloced and accessed 3 MBs
Active: 2825
Inactive:       9641
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  1982
Evicted:        151729

Malloced and accessed 4 MBs
Active: 3063
Inactive:       9490
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  1991
Evicted:        151896

Malloced and accessed 5 MBs
Active: 3282
Inactive:       9218
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2039
Evicted:        152224

Malloced and accessed 6 MBs
Active: 3500
Inactive:       9096
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2077
Evicted:        152391

Malloced and accessed 7 MBs
Active: 3650
Inactive:       8916
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2185
Evicted:        152688

Malloced and accessed 8 MBs
Active: 3853
Inactive:       8670
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2227
Evicted:        152981

Malloced and accessed 9 MBs
Active: 4054
Inactive:       8514
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2295
Evicted:        153208

Malloced and accessed 10 MBs
Active: 4238
Inactive:       8387
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2360
Evicted:        153401

Malloced and accessed 11 MBs
Active: 4392
Inactive:       8202
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2463
Evicted:        153694

Malloced and accessed 12 MBs
Active: 4594
Inactive:       8004
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2521
Evicted:        153952

Malloced and accessed 13 MBs
Active: 4833
Inactive:       7708
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2545
Evicted:        154274

Malloced and accessed 14 MBs
Active: 5067
Inactive:       7528
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2557
Evicted:        154467

Malloced and accessed 15 MBs
Active: 5327
Inactive:       7281
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2566
Evicted:        154729

Malloced and accessed 16 MBs
Active: 5559
Inactive:       7081
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2590
Evicted:        154956

Malloced and accessed 17 MBs
Active: 5785
Inactive:       6697
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2622
Evicted:        155377

Malloced and accessed 18 MBs
Active: 6022
Inactive:       6580
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2633
Evicted:        155508

Malloced and accessed 19 MBs
Active: 6264
Inactive:       6346
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2655
Evicted:        155767

Malloced and accessed 20 MBs
Active: 6529
Inactive:       6090
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2655
Evicted:        156023

Malloced and accessed 21 MBs
Active: 6792
Inactive:       5802
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2655
Evicted:        156315

Malloced and accessed 22 MBs
Active: 7046
Inactive:       5578
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2655
Evicted:        156542

Malloced and accessed 23 MBs
Active: 7302
Inactive:       5354
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2655
Evicted:        156769

Malloced and accessed 24 MBs
Active: 7566
Inactive:       5066
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2655
Evicted:        157049

Malloced and accessed 25 MBs
Active: 7831
Inactive:       4714
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2655
Evicted:        157408

Malloced and accessed 26 MBs
Active: 8080
Inactive:       4554
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2655
Evicted:        157572

Malloced and accessed 27 MBs
Active: 8344
Inactive:       4362
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2655
Evicted:        157772

Malloced and accessed 28 MBs
Active: 8594
Inactive:       4106
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2655
Evicted:        158035

Malloced and accessed 29 MBs
Active: 8862
Inactive:       3786
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2655
Evicted:        158357

Malloced and accessed 30 MBs
Active: 9113
Inactive:       3563
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2656
Evicted:        158584

Malloced and accessed 31 MBs
Active: 9371
Inactive:       3308
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2657
Evicted:        158844

Malloced and accessed 32 MBs
Active: 9629
Inactive:       3084
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2657
Evicted:        159067

Malloced and accessed 33 MBs
Active: 9892
Inactive:       2764
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2657
Evicted:        159390

Malloced and accessed 34 MBs
Active: 10136
Inactive:       2540
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2657
Evicted:        159622

Malloced and accessed 35 MBs
Active: 10403
Inactive:       2348
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2657
Evicted:        159822

Malloced and accessed 36 MBs
Active: 10642
Inactive:       2104
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2669
Evicted:        160086

Malloced and accessed 37 MBs
Active: 10901
Inactive:       1849
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2669
Evicted:        160354

Malloced and accessed 38 MBs
Active: 11087
Inactive:       1665
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2744
Evicted:        160624

Malloced and accessed 39 MBs
Active: 11352
Inactive:       1442
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2776
Evicted:        160857

Malloced and accessed 40 MBs
Active: 11482
Inactive:       1311
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  2965
Evicted:        161125

Malloced and accessed 41 MBs
Active: 11291
Inactive:       1625
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  3496
Evicted:        161380

Malloced and accessed 42 MBs
Active: 10373
Inactive:       2557
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  4875
Evicted:        161701

Malloced and accessed 43 MBs
Active: 10422
Inactive:       2620
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  5130
Evicted:        161975

Malloced and accessed 44 MBs
Active: 10436
Inactive:       2706
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  5568
Evicted:        162208

Malloced and accessed 45 MBs
Active: 6453
Inactive:       6418
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  22178
Evicted:        162777

Malloced and accessed 46 MBs
Active: 4289
Inactive:       8051
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24657
Evicted:        163597

Malloced and accessed 47 MBs
Active: 4541
Inactive:       8051
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24657
Evicted:        163597

Malloced and accessed 48 MBs
Active: 4793
Inactive:       8051
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24657
Evicted:        163597

Malloced and accessed 49 MBs
Active: 5059
Inactive:       8051
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24657
Evicted:        163597

Malloced and accessed 50 MBs
Active: 5213
Inactive:       7955
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24758
Evicted:        163791

Malloced and accessed 51 MBs
Active: 5478
Inactive:       7715
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24758
Evicted:        164026

Malloced and accessed 52 MBs
Active: 5738
Inactive:       7441
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24758
Evicted:        164295

Malloced and accessed 53 MBs
Active: 5996
Inactive:       7120
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24763
Evicted:        164620

Malloced and accessed 54 MBs
Active: 6254
Inactive:       6873
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24763
Evicted:        164866

Malloced and accessed 55 MBs
Active: 6501
Inactive:       6701
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24765
Evicted:        165040

Malloced and accessed 56 MBs
Active: 6761
Inactive:       6445
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24765
Evicted:        165295

Malloced and accessed 57 MBs
Active: 7012
Inactive:       6124
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24770
Evicted:        165621

Malloced and accessed 58 MBs
Active: 7276
Inactive:       5804
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24775
Evicted:        165937

Malloced and accessed 59 MBs
Active: 7544
Inactive:       5554
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24775
Evicted:        166174

Malloced and accessed 60 MBs
Active: 7806
Inactive:       5287
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24776
Evicted:        166442

Malloced and accessed 61 MBs
Active: 7979
Inactive:       5106
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24860
Evicted:        166709

Malloced and accessed 62 MBs
Active: 8234
Inactive:       4869
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24862
Evicted:        166948

Malloced and accessed 63 MBs
Active: 8491
Inactive:       4670
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24862
Evicted:        167153

Malloced and accessed 64 MBs
Active: 8749
Inactive:       4366
Refferenced Active:     0
Refferenced Inactive:   0
Moved:  24862
Evicted:        167456




Looking at the differences between these two, we can see some general observations:
- Our code is much more aggressive in its moving and evicting of pages that are not
     frequently referenced; in some cases, the referenced bit is never incremented
     after the initial setting, and so the page very quickly finds its way to the
     inactive list, and then to eviction. The kernel, on the other hand, does not
     evict or move any pages until a significant amount of memory has been taken.
- Our code tends to hang for a bit when it tries to allocate memory in the case of
     contention, as it has to wait until the reference counts go all the way down to
     zero before the pages are moved/evicted, whereas the original kernel implementation
     could move/evict pages as soon as page_referenced was returning 0 (that is, there
     were no current references). Thus, in our code, pages that were once frequently
     used have much more staying power, and it is harder to get new memory.
