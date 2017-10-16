1.

	3) 
		* gcc -c statique.c -o statique.o
		* ar rcs libstatique.a statique.o

	4) Convention de nommage : .so pour lib dynamique, .a pour lib statique et la lib name doit se nommer libname

	5) nm libstatique.a 

		statique.o:
				             U printf
		0000000000000000 T test1
		0000000000000015 T test2

	6) OK

	7) Oui

2.

	1) gcc -c -Wall -Werror -fpic statique.c // compilation lib dynamic
		 gcc -shared -o libdynamic.so statique.o // création lib dynamic
		 gcc -L. -Wall -o exoDynamic exoDynamic.c -ldynamic // compilation executable avec lib dynamic

	2) ldd exoDynamic
		linux-vdso.so.1 =>  (0x00007ffff53c2000)
		libdynamic.so => /users/etudiant/c/ca404826/Documents/master1ifi/archios/TP1/libdynamic.so (0x00007f090ba26000)
		libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f090b639000)
		/lib64/ld-linux-x86-64.so.2 (0x00007f090bc2b000)


	3) nm libdynamic.so 
		0000000000201038 B __bss_start
		0000000000201038 b completed.6973
				             w __cxa_finalize@@GLIBC_2.2.5
		0000000000000600 t deregister_tm_clones
		0000000000000670 t __do_global_dtors_aux
		0000000000200e08 t __do_global_dtors_aux_fini_array_entry
		0000000000201030 d __dso_handle
		0000000000200e18 d _DYNAMIC
		0000000000201038 D _edata
		0000000000201040 B _end
		000000000000070c T _fini
		00000000000006b0 t frame_dummy
		0000000000200e00 t __frame_dummy_init_array_entry
		00000000000007c8 r __FRAME_END__
		0000000000201000 d _GLOBAL_OFFSET_TABLE_
				             w __gmon_start__
		0000000000000598 T _init
				             w _ITM_deregisterTMCloneTable
				             w _ITM_registerTMCloneTable
		0000000000200e10 d __JCR_END__
		0000000000200e10 d __JCR_LIST__
				             w _Jv_RegisterClasses
				             U puts@@GLIBC_2.2.5
		0000000000000630 t register_tm_clones
		00000000000006e5 T test1
		00000000000006f7 T test2
		0000000000201038 d __TMC_END__

	4)
		*   8550	octets	exoDynamic
		* 877358	octets	exoStatic

	5) OK

3.

	1) OK

	2) gcc -c -fPIC dyntime.c
		 gcc -shared -o libdyntime.so dyntime.o
		 gcc -L. -o testTime testTime.c -ldyntime



