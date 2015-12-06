#Semaphore
 \- Used for synchronization  
 \- Synchronize multi process tasks  
 \- Used for synchronize access to shared memory  
 

###1) semget system call
Create semaphore, or access to semaphore that already exist.

```
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semget(key_t key, int nsems, int semflag);
	return semid if OK, -1 on Error
```
 \- nsems : number of semaphores  
 \- semflag : same as msq flag

###2) semop system call
Operate for semaphore sets

```
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semop(int semid, struct sembuf **opsptr, unsigend int nops);
	return 0 if OK, -1 on Error
```
 \- opsptr :    
 
```
 struct sembuf {
 	ushort sem_num;		/* semaphore # */
 	short sem_op;		/* operation */
 	short sem_flg;
 };
```
 \- sem_op :  
 
sem_op > 0 : Increase sem_val and if there's waiting ps, wake them up.  
sem_op = 0 : Wait for sem_val is 0.  
sem_op < 0 : Decrease sem_val and if not enough, sleep.


###3) semctl system call
```
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semctl(int semid, int semnum, int cmd, union semun arg);
	return 0 if OK, -1 on Error
```
 \- arg :
 
```
union semun {
	int val;				// SETVAL
	struct semid_ds *buff;		// IPC_STAT, IPC_SET
	ushort *array;			// IPC_GETALL, IPC_SETALL
```
 \- cmd :  
IPC_RMID : Remove semaphore  
GETALL : Get sem_val from semaphore  
SETALL : Set sem_val to semaphore  

##All of these operations are atomic.