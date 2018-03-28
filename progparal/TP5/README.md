# TP5 (MPI)

## MPI ?

### Une norme implémentée dans plein de bibliothèques

* Une API
* des outils pour compiler/exécuter

Une application MPI == un unique exécutable démarré sur plusieurs machines

### Exemple

#### Initialisation 

```C
#include <mpi.h>

void main(int argc, char* argv[]){
    int numprocs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

}

```

#### Méthodes de communication

```C
int MPI_Send(void *buf, int count, MPI_Datatype type, int dest, int tag, MPI_Comm com);
```

* __`void *buf`__ : pointeur vers les données à envoyer
* __`int count`__ : nombre d'éléments
* __`MPI_Datatype type`__ : type de données
* __`int dest`__ : destination
* __`int tag`__ : identifiant de message
* __`MPI_Comm com`__ : portée
* __valeur de retour__ : statut d'erreur, par exemple ->
    * __MPI_SUCCESS__
    * __MPI_ERR_RANK__ 

```C
int MPI_Recv(void *buf, int count, MPI_Datatype type, int source, int tag, MPI_Comm com, MPI_Status *status);
```

* __`void *bud`__ : le malloc doit avoir été fait **AVANT**
* __`int count`__ : nombre d'éléments
* __`MPI_Datatype type`__ : type de données
* __`int source`__ : source
* __`int tag`__ : identifiant de message (permet de régler le pb si deux processes envoient un même msg), on peut mettre **MPI_Any**
* __`MPI_Comm com`__ : portée
* __`MPI_Status status`__ : 

```C
void MPI_Finalize();
```

* A faire obligatoirement à la fin du prog

### Compilation & éxecution

Pour compiler il faut utiliser la syntaxe suivante : __`mpicc -o exo1 -lm`__

Pour éxecuter : __`mpirun ./exo1`__

## Hello world en MPI 

1. 
    * Sans préciser de processus :
    ```
    $ mpirun ./hello_world
    Mon rang est : 1
    Mon rang est : 0
    ```

    * Avec 4 processus :
    ```
    $ mpirun -np 4 ./hello_world
    Mon rang est : 0
    Mon rang est : 1
    Mon rang est : 2
    Mon rang est : 3
    ``` 

    * Avec 10 processus :
    ```
    $ mpirun -np 10 ./hello_world
    Mon rang est : 7
    Mon rang est : 8
    Mon rang est : 4
    Mon rang est : 9
    Mon rang est : 3
    Mon rang est : 6
    Mon rang est : 2
    Mon rang est : 5
    Mon rang est : 1
    Mon rang est : 0
    ```

2. Comme on a pu le voir sur les éxecutions précedentes, le rang n'est pas forément respecté, il peut être aléatoire. On a donc l'effet suivant avec plus de 2 processus :
    ```
    $ mpirun -np 10 ./hello_world
    Hello !
    Bye !!

    $ mpirun -np 10 ./hello_world
    Bye !!
    Hello !
    ```

## Ping Pong

1. Exercice 1 :
    ```C
    #include <mpi.h>
    #include <stdio.h>
    #include <stdlib.h>

    void main(int argc, char* argv[]){
        int numprocs, rank;
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if(rank == 0){
            int data = 4;
            MPI_Send(&data, sizeof(int), MPI_INT, 1, 0, MPI_COMM_WORLD);
        } else if (rank == 1) {
            int* data = malloc(sizeof(int));
            MPI_Status status;
            MPI_Recv(data, sizeof(int), MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            printf("Received : %d !!\n", *data);
        }

        MPI_Finalize();

    }
    ```
    Après compilation et éxecution : 
    ```
    $ mpirun ./ping_pong
    Received : 4 !!
    ```

2. Exercice 2 :
    ```
    $ mpirun -np 10 ./ping_pong
    Proc 7 deceived : 4 !!
    Proc 2 deceived : 4 !!
    Proc 3 deceived : 4 !!
    Proc 1 deceived : 4 !!
    Proc 9 deceived : 4 !!
    Proc 6 deceived : 4 !!
    Proc 5 deceived : 4 !!
    Proc 4 deceived : 4 !!
    Proc 8 deceived : 4 !!
    ```

## Pipeline
 