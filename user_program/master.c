#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

#define MAX 100
#define PAGE_SIZE 4096
#define BUF_SIZE 512
#define MAP_SIZE PAGE_SIZE

size_t get_filesize(const char* filename);//get the size of the input file

int main (int argc, char* argv[])
{
	char buf[BUF_SIZE];
	int i, dev_fd, file_fd;// the fd for the device and the fd for the input file
	size_t ret, file_size, offset = 0, tmp;
	char file_name[MAX][50], method[20];
	char *kernel_address = NULL, *file_address = NULL;
	struct timeval start;
	struct timeval end;
	double trans_time; //calulate the time between the device is opened and it is closed

	int N = atoi(argv[1]);
	for(i = 0; i < N; i++)
		strcpy(file_name[i], argv[2 + i]);

	strcpy(method, argv[2 + N]);

	if( (dev_fd = open("/dev/master_device", O_RDWR)) < 0)
	{
		perror("failed to open /dev/master_device\n");
		return 1;
	}

  unsigned long int total_file_size = 0;
	gettimeofday(&start ,NULL);


	for(i = 0; i < N; i++) {
		if(ioctl(dev_fd, 0x12345677) == -1) //0x12345677 : create socket and accept the connection from the slave
		{
			perror("ioclt server create socket error\n");
			return 1;
		}
		if( (file_fd = open(file_name[i], O_RDWR)) < 0 )
		{
			perror("failed to open input file\n");
			return 1;
		}

		if( (file_size = get_filesize(file_name[i])) < 0)
		{
			perror("failed to get filesize\n");
			return 1;
		}

		total_file_size += file_size;

		switch(method[0])
		{
			case 'f': //fcntl : read()/write()
			do
			{
					ret = read(file_fd, buf, sizeof(buf)); // read from the input file
					write(dev_fd, buf, ret);//write to the the device
			}while(ret > 0);
			break;

			case 'm' : // mmap()
			offset = 0;
			while (offset < file_size) {
				if ((file_address = mmap(NULL, MAP_SIZE, PROT_READ, MAP_SHARED, file_fd, offset)) < 0) {
					perror("file mapping error\n");
					_exit(0);
				}
				if ((kernel_address = mmap(NULL, MAP_SIZE, PROT_WRITE, MAP_SHARED, dev_fd, offset)) < 0) {
					perror("device mapping error");
					_exit(0);
				}
				size_t len = (offset + MAP_SIZE > file_size)? (file_size - offset) : MAP_SIZE;
				memcpy(kernel_address, file_address, len);
				offset += len;
			  ioctl(dev_fd, 0x12345678, len); //master_IOCTL_MMAP
			}
			ioctl(dev_fd, 0x12345680); //default
			munmap(file_address, MAP_SIZE);
			break;
		}

		if(ioctl(dev_fd, 0x12345679) == -1) // end sending data, close the connection
		{
			perror("ioclt server exits error\n");
			return 1;
		}
	}
	
	gettimeofday(&end, NULL);
	trans_time = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)*0.0001;
	printf("Transmission time: %lf ms, File size: %lu bytes\n", trans_time, total_file_size / 8);

	close(file_fd);
	close(dev_fd);

	return 0;
}

size_t get_filesize(const char* filename)
{
	struct stat st;
	stat(filename, &st);
	return st.st_size;
}
