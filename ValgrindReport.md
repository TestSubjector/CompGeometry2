$ valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all ./run_daa
==12354== Memcheck, a memory error detector
==12354== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==12354== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==12354== Command: ./run_daa
==12354==
Enter input file path: /home/testsubjector/code/github_c++/CompGeom2/test/testcase3.txt
==12354==
==12354== HEAP SUMMARY:
==12354==     in use at exit: 72,704 bytes in 1 blocks
==12354==   total heap usage: 10 allocs, 9 frees, 92,453 bytes allocated
==12354==
==12354== 72,704 bytes in 1 blocks are still reachable in loss record 1 of 1
==12354==    at 0x4C2DB8F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==12354==    by 0x4EC3EFF: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
==12354==    by 0x40106C9: call_init.part.0 (dl-init.c:72)
==12354==    by 0x40107DA: call_init (dl-init.c:30)
==12354==    by 0x40107DA: _dl_init (dl-init.c:120)
==12354==    by 0x4000C69: ??? (in /lib/x86_64-linux-gnu/ld-2.23.so)
==12354==
==12354== LEAK SUMMARY:
==12354==    definitely lost: 0 bytes in 0 blocks
==12354==    indirectly lost: 0 bytes in 0 blocks
==12354==      possibly lost: 0 bytes in 0 blocks
==12354==    still reachable: 72,704 bytes in 1 blocks
==12354==         suppressed: 0 bytes in 0 blocks
==12354==
==12354== For counts of detected and suppressed errors, rerun with: -v
==12354== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Note that the reachable block is not a case of leak, more is discussed here - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66339