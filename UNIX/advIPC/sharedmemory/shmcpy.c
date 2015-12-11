#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHMKEY1 (key_t) 0x10
#define SHMKEY2 (key_t) 0x15
#define SEMKEY (key_t) 0x20

#define BUFSIZE 4096
#define ERR ((struct databuf *)-1)
struct databuf {
	int d_nread;
	char d_buf[BUFSIZE];
};

typedef union _semun {
	int val;
	struct semid_ds *buf;
	ushort *array;
} semun;

static int shmid1, shmid2, semid;

void getseg(struct databuf **p1, struct databuf **p2) {
	if ((shmid1 = shmget(SHMKEY1, sizeof(struct databuf),
					0600 | IPC_CREAT | IPC_EXCL)) == -1)
		perror("shmget");
	if ((shmid2 = shmget(SHMKEY2, sizeof(struct databuf),
					0600 | IPC_CREAT | IPC_EXCL)) == -1)
		perror("shmget");

	if ((*p1 = (struct databuf *)shmat(shmid1, 0, 0)) == ERR)
		perror("shmat");
	if ((*p2 = (struct databuf *)shmat(shmid2, 0, 0)) == ERR)
		perror("shmat");

}

int getsem() {
	semun x;
	x.val = 0;

	if ((semid = semget(SEMKEY, 2, 0600 | IPC_CREAT | IPC_EXCL)) == -1)
		perror("semget");

	if (semctl(semid, 0, SETVAL, x) == -1)
		perror("semctl");
	if (semctl(semid, 1, SETVAL, x) == -1)
		perror("semctl");

	return semid;
}

void rmobj() {
	if (shmctl(shmid1, IPC_RMID, NULL) == -1)
		perror("shmctl");
	if (shmctl(shmid2, IPC_RMID, NULL) == -1)
		perror("shmctl");
	if (shmctl(semid, IPC_RMID, NULL) == -1)
		perror("shmctl");
}

struct sembuf p1 = {0, -1, 0}, p2 = {1, -1, 0};
struct sembuf v1 = {0, 1, 0}, v2 = {1, 1, 0};

void reader(int semid, struct databuf *buf1, struct databuf *buf2) {
	for (;;) {
		/* read into buf1 */
		buf1->d_nread = read(0, buf1->d_buf, BUFSIZE);

		/* synchronization */
		semop(semid, &v1, 1);
		semop(semid, &p2, 1);

		/* avoid writer sleeping */
		if (buf1->d_nread <= 0)
			return;

		buf2->d_nread = read(0, buf2->d_buf, BUFSIZE);

		semop(semid, &v1, 1);
		semop(semid, &p2, 1);

		if (buf2->d_nread <= 0)
			return;
	}
}

void writer(int semid, struct databuf *buf1, struct databuf *buf2) {
	for (;;) {
		semop(semid, &p1, 1);
		semop(semid, &v2, 1);

		if (buf1->d_nread <= 0)
			return;

		write(1, buf1->d_buf, buf1->d_nread);

		semop(semid, &p1, 1);
		semop(semid, &v2, 1);

		if (buf2->d_nread <= 0)
			return;

		write(1, buf2->d_buf, buf2->d_nread);
	}
}

int main() {
	struct databuf *buf1, *buf2;
	int semid = getsem();

	getseg(&buf1, &buf2);

	reader(semid, buf1, buf2);
	writer(semid, buf1, buf2);

	rmobj();
}
