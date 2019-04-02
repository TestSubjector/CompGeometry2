$ valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all ./run_daa k
==20921== Memcheck, a memory error detector
==20921== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==20921== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==20921== Command: ./run_daa k
==20921==
Enter input file path: /home/testsubjector/code/github_c++/CompGeom2/test/testcase3.txt
==20921==
==20921== HEAP SUMMARY:
==20921==     in use at exit: 72,704 bytes in 1 blocks
==20921==   total heap usage: 8 allocs, 7 frees, 83,709 bytes allocated
==20921==
==20921== 72,704 bytes in 1 blocks are still reachable in loss record 1 of 1
==20921==    at 0x4C2DB8F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==20921==    by 0x4EC3EFF: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
==20921==    by 0x40106C9: call_init.part.0 (dl-init.c:72)
==20921==    by 0x40107DA: call_init (dl-init.c:30)
==20921==    by 0x40107DA: _dl_init (dl-init.c:120)
==20921==    by 0x4000C69: ??? (in /lib/x86_64-linux-gnu/ld-2.23.so)
==20921==    by 0x1: ???
==20921==    by 0xFFEFFFF9A: ???
==20921==    by 0xFFEFFFFA4: ???
==20921==
==20921== LEAK SUMMARY:
==20921==    definitely lost: 0 bytes in 0 blocks
==20921==    indirectly lost: 0 bytes in 0 blocks
==20921==      possibly lost: 0 bytes in 0 blocks
==20921==    still reachable: 72,704 bytes in 1 blocks
==20921==         suppressed: 0 bytes in 0 blocks
==20921==
==20921== For counts of detected and suppressed errors, rerun with: -v
==20921== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Note that the reachable block is not a case of leak, more is discussed here - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66339