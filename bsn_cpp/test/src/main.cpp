#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	char const* name = "ba";
	int length = 4096;
	int FILE_MODE = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	int flags = O_RDWR | O_CREAT;
	auto fd =  shm_open(name, flags, FILE_MODE);
	if (fd == -1)
	{
		printf("shm_open error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
	}

	auto ptr = mmap(NULL, length*2, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED) {
        printf("mmap error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
	printf("mmap ptr: %p\n", ptr);

	if (ftruncate(fd, length) == -1) {
        printf("ftruncate error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

	auto ptr1 = mmap(ptr, length, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_SHARED, fd, 0);
	if (ptr1 == MAP_FAILED) {
        printf("mmap error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
	printf("mmap ptr1: %p\n", ptr1);

	auto ptr2 = mmap((char*)ptr + length, length, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_SHARED, fd, 0);
	if (ptr2 == MAP_FAILED) {
        printf("mmap error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
	printf("mmap ptr2: %p\n", ptr2);

	if (shm_unlink(name) == -1) {
        printf("shm_unlink error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (close(fd) == -1) {
        printf("close error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

	char* pW = (char*)ptr;
	sprintf(pW, "pW=%p ptr=%p %s", pW, ptr, "abc1");
	pW = (char*)ptr + length;
	sprintf(pW, "pW=%p ptr=%p %s", pW, ptr, "abc2");

	
	printf("pW: %s\n", (char*)pW);
	printf("ptr: %s\n", (char*)ptr);
	printf("ptr1: %s\n", (char*)ptr1);
	printf("ptr2: %s\n", (char*)ptr2);

	pW = (char*)ptr + length-2;
	sprintf(pW, "%s", "abcd");
	printf("a: %s\n", (char*)ptr2);
	
    exit(EXIT_SUCCESS);
}
