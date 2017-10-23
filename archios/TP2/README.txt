2.
    1) Mémoire dispo : 319416 kB
       Swap total    :  78852 kB

    2) Node 0, zone DMA     184   71 23 2 0 0 1 0 1 0 0
       Node 0, zone Normal  933 1116  1 2 0 0 0 0 0 1 0

    3) CommitLimit = Nombre max. de pages que Linux peut allouer
       Commited_AS = Valeur actuelle de la mémoire allouée dans tout le système

3.
    1) overcommit_memory =  0
       overcommit_ratio  = 50

    Selon les pages de manuels (manpage) de Linux, le paramètre overcommit_memory a trois options:

0: heuristique overcommit (valeur par défaut)

1: overcommit toujours, pas de vérification

2: toujours vérifier, pas d’overcommit

Dans le mode 2 (présent depuis la version 2.6 du noyau Linux), l’espace mémoire virtuel total qui peut être alloué (valeur de CommitLimit dans /proc/meminfo) est calculé avec la formule CommitLimit = (total_RAM - total_huge_TLB) * overcommit_ratio / 100 + total_swap

Par exemple, sur un système avec 16 Go de RAM, 16 Go de swap sur disque, sans espace dédié aux grandes pages (cadres), et un overcommit_ratio de 50, la formule donne une valeur de 24 Go. C’est la taille maximale de mémoire virtuelle que le système peut allouer.

Cela est bien décrit dans la page https://www.kernel.org/doc/Documentation/vm/overcommit-accounting

Lorsque le paramètre overcommit_memory est mis à 2, l’espace mémoire alloué ne peut pas dépasser la taille du swap + pourcentage de la RAM.

Exemple de crash système: si vous utilisez la machine virtuelle ubunto (version 12.04) que je vous ai fournie, si vous mettez le  paramètre overcommit à 2, alors probablement votre environnement graphique planterait. La raison est que le CommitLimit n’est pas suffiant (égal à taille de RAM * 50% + taille de swap). Et selon les pages manuel d’ubunto, les versions d’ubunto au delà de 11 utilisent un espace mémoire pour l’environnement graphique d’une taille de 2 Go.

Si l’environnement graphique de votre machine virtuelle plante, vous pouvez continuer à utiliser la machine virtuelle en ouvrant un terminal (Ctrl + Alt + F1) et changer le paramètre overcommit_ratio ((/proc/sys/vm/overcommit_ratio) à 100, et faire ainsi l’exercice courant pour désactiver l’overcommit.

    2) * Echec de malloc après 3056 MiB 
       * Killed à 147 MiB
       * Killed à 102 MiB

4.

    1) Le fichier /etc/fstab contient la liste de toutes les partitions montées par votre système. Vous y trouverez votre partition de swap initiale.
       aufs / aufs rw 0 0
       tmpfs /tmp tmpfs nosuid,nodev 0 0
      
       Le fichier /proc/swaps contient la liste des swap (partitions ou fichiers)
       /dev/ramzswap0 partition Size: 79852 Used: 13660 Priority: 100
    2)
