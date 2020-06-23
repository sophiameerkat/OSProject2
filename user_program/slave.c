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

int main (int argc, char* argv[])
{
    char buf[BUF_SIZE];
    int i, dev_fd;// the fd for the device and the fd for the input file
    size_t r, file_size = 0, data_size = -1, offs;
    char number[20];
    int num;
    char method[20];
    char ip[20];
    char file_name_o[50], file_name[MAX][50];
    int file_fd[MAX];
    struct timeval start;
    struct timeval end;
    double trans_time; //calulate the time between the device is opened and it is closed
    char *kernel_add, *file_add;

    strcpy(number, argv[1]);
    num = atoi(number);
    strcpy(file_name_o, argv[2]);

    for (int i = 0; i < num; i++)
      sprintf(file_name[i], "%s_%d", file_name_o, i + 1);

    strcpy(method, argv[3]);
    strcpy(ip, argv[4]);


    if( (dev_fd = open("/dev/slave_device", O_RDWR)) < 0) {//should be O_RDWR for PROT_WRITE when mmap()
        perror("failed to open /dev/slave_device\n");
        return 1;
    }
    gettimeofday(&start ,NULL);
    for (int i = 0; i < num; i++) {
        if( (file_fd[i] = open (file_name[i], O_RDWR | O_CREAT | O_TRUNC)) < 0) {
            perror("failed to open input file\n");
            return 1;
        }
    }

    for (int i = 0; i < num; i++) {
        if(ioctl(dev_fd, 0x12345677, ip) == -1){	//0x12345677 : connect to master in the device
            perror("ioclt create slave socket error\n");
            return 1;
        }

        //write(1, "ioctl success\n", 14);

        switch(method[0])
        {
            case 'f'://fcntl : read()/write()
            do {
                r = read(dev_fd, buf, sizeof(buf)); // read from the the device
                write(file_fd[i], buf, r); //write to the input file
                file_size += r;
            }while(r > 0);
                break;
            case 'm'://mmap
                offs = 0;
                int flag = 1;
                while (flag == 1) {
                    r = ioctl(dev_fd, 0x12345678);
                    if (r == 0) {
                        file_size += offs;
                        flag = 0;
                        break;
                    }
                    posix_fallocate(file_fd[i], offs, r);
                    file_add = mmap(NULL, r, PROT_WRITE, MAP_SHARED, file_fd[i], offs);
                    kernel_add = mmap(NULL, r, PROT_READ, MAP_SHARED, dev_fd, offs);
                    memcpy(file_add, kernel_add, r);
                    munmap(file_add, r);
                    munmap(kernel_add, r);
                    offs = offs + r;
                }
                ioctl(dev_fd, 0x12345680); //default
                break;
        }

        if(ioctl(dev_fd, 0x12345679) == -1) {// end receiving data, close the connection
            perror("ioclt client exits error\n");
            return 1;
        }
    }

    gettimeofday(&end, NULL);
    trans_time = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)*0.0001;
    printf("Transmission time: %lf ms, File size: %lu bytes\n", trans_time, file_size / 8);

    for (int i = 0; i < num; i++)
        close(file_fd[i]);
    close(dev_fd);
    return 0;
}
