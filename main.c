#include<fcntl.h>
#include<sys/stat.h>
#include<tlpi_hdr.h>
#include<ctype.h>
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
int main(int argc, char *argv[])
{
/*	size_t len;
	off_t offset;
	int fd, ap, j;
	char *buf;
	ssize_t numRead, numWrite;*/
	int inputFd, outputFd,openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE];
	printf("%d\n",argc);
	printf("%s\n",argv[0]);
	printf("%s\n",argv[1]);
	printf("%s\n",argv[2]);
	if (argc != 3 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("%s old-file new-file\n", argv[0]);
	}
	inputFd = open(argv[1], O_RDONLY);
	if(inputFd == -1)
		errExit("opening file %s", argv[1]);
	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	outputFd = open(argv[2], openFlags, filePerms);
	if(outputFd == -1)
		errExit("opening file %s\n", argv[2]);
	while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
		if(write(outputFd, buf, numRead) != numRead)
			fatal("couldn't write whole buffer");
	if(numRead == -1)
		errExit("read");
	if(close(inputFd) == -1)
		errExit("close input");
	if(close(outputFd) == -1)
		errExit("close output");	

	exit(EXIT_SUCCESS);
}
