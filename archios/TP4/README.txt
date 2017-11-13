1.
    cat /proc/cpuinfo | grep siblings => siblings : 2
    cat /proc/cpuinfo | grep "cpu cores" => cpu cores   : 2
    Donc hyprthreading désactivé

    COEUR
    cat /sys/devices/system/cpu/cpu1/topology/core_id => 1
    cat /sys/devices/system/cpu/cpu0/topology/core_id => 0

    SOCKET
    cat /sys/devices/system/cpu/cpu0/topology/physical_package_id => 0
    cat /sys/devices/system/cpu/cpu1/topology/physical_package_id => 0

    ls /sys/devices/system/cpu
    cpu0  cpuidle     microcode  offline  possible  present
    cpu1  kernel_max  modalias   online   power uevent

    Le cpu0 partage son index2 (cache L2) avec le CPU 1
    cat /sys/devices/system/cpu/cpu0/cache/index2/shared_cpu_list => 0-1

/usr/local/likwid/bin/likwid-topology -g

Graphical:
*************************************************************
Socket 0:
+-------------------+
| +------+ +------+ |
| |   0  | |   1  | |
| +------+ +------+ |
| +------+ +------+ |
| | 32kB | | 32kB | |
| +------+ +------+ |
| +---------------+ |
| |      2MB      | |
| +---------------+ |
+-------------------+

