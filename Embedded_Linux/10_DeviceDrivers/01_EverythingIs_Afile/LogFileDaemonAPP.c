#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


#define MAX_BUFFER_SIZE 4096

#define KMSG_PATH "/dev/kmsg"
#define LOGFILE_PATH "/home/abdelaziz/NTI_WS/Linux_Workspace/DeviceDrivers/SystemCalls/logfile.txt"

int Toggle_CapsLock_Led();
int Readkmsg_LatestData(int kmsg_fd, char* ReadBuffer);
int OpenLogFile(const char *Filename);
int OpenAndSeek_Kmsg(const char *Filename);
int Wtitelogfile_LatestData(int kmsg_fd, char* ReadBuffer,int Data_ToRead);
int Checklogfile_MaxLines(const char *Filename,int MaxLines);
int Emptylogfile(const char *Filename,int logfile_fd);

int main(int argc, int *argv[])
{
    int kmsg_fd ,logfile_fd; 
    
    char buffer[MAX_BUFFER_SIZE];   

    kmsg_fd = OpenAndSeek_Kmsg(KMSG_PATH);
    logfile_fd = OpenLogFile(LOGFILE_PATH);
    
    while(1)
    {
        int BytesRead = Readkmsg_LatestData(kmsg_fd,buffer);

        Wtitelogfile_LatestData(logfile_fd,buffer,BytesRead);

        if ( Checklogfile_MaxLines(LOGFILE_PATH,10) == 1 )
        {
            Emptylogfile(LOGFILE_PATH,logfile_fd);

            logfile_fd = open(LOGFILE_PATH, O_RDWR);
            if ( logfile_fd < 0 )
            {
                printf("Failed to open logfile\n");
                return -1;
            }  
                      
            Toggle_CapsLock_Led();
        }
        sleep(10);

        for ( int i = 0 ; i < MAX_BUFFER_SIZE ; i++ )
        {
            buffer[i] = '\0';
        }
    }
    return 0;
}

int Toggle_CapsLock_Led()
{ 
    int CapsLockLED_fd ,errno = 0;
    char  CapsLock_Val;

    CapsLockLED_fd = open("/sys/class/leds/input3::capslock/brightness", O_RDWR);
    if ( CapsLockLED_fd < 0 )
    {
        printf("[LOG]: Failed to open CapsLock LED file\n");
        return -1;
    }

    errno = read(CapsLockLED_fd, &CapsLock_Val, 1);
    if ( errno <= 0 )
    {
        printf("[LOG]: Failed to read CapsLock LED state\n");
        close(CapsLockLED_fd);
        return -1;
    }

    CapsLock_Val = (CapsLock_Val == '0') ? '1' : '0';

    errno = write(CapsLockLED_fd, &CapsLock_Val, 1);
    if ( errno <= 0 )
    {
        printf("[LOG]: Failed to write CapsLock LED state\n");
        close(CapsLockLED_fd);
        return -1;
    }

    close(CapsLockLED_fd);    
}

int OpenAndSeek_Kmsg(const char *Filename)
{
    int kmsg_fd;

    kmsg_fd = open(Filename, O_RDONLY);
    if ( kmsg_fd < 0 )
    {
        printf("[LOG]: Failed to open /dev/kmsg\n");
        return -1;
    }

    off_t offset = lseek(kmsg_fd, 0, SEEK_END);
    if ( offset == (off_t) -1 )
    {
        printf("[LOG]: Failed to get offset on /dev/kmsg data\n");
        close(kmsg_fd);
        return -1;
    } 

    return kmsg_fd;
}

int OpenLogFile(const char *Filename)
{
    int logfile_fd; 

    logfile_fd = open(Filename, O_RDWR);
    if ( logfile_fd < 0 )
    {
        printf("[LOG]: Failed to open logfile\n");
        return -1;
    }

    return logfile_fd;
}

int Readkmsg_LatestData(int kmsg_fd,char* ReadBuffer)
{
    int BytesRead;

    BytesRead = read(kmsg_fd, ReadBuffer, MAX_BUFFER_SIZE);
    if ( BytesRead <= 0 )
    {
        printf("[LOG]: Failed to read /dev/kmsg data\n");
        close(kmsg_fd);
        return -1;
    } 

    return BytesRead; 
}

int Wtitelogfile_LatestData(int logfile_fd, char* ReadBuffer,int Data_ToRead)
{
    int errno;

    errno = write(logfile_fd, ReadBuffer, Data_ToRead);
    if ( errno <= 0 )
    {
        printf("[LOG]: Failed to write to logfile\n");
        close(logfile_fd);
        return -1;
    }
}

int Checklogfile_MaxLines(const char *Filename,int MaxLines)
{
    FILE *fileptr;
    char line[1024]; 
    int line_count = 0;

    fileptr = fopen(Filename,"r+");
    if ( fileptr == NULL ) 
    {
        printf("[LOG]: Failed to open file");
        return -1; 
    }   
   
    while ( fgets(line, sizeof(line), fileptr) != NULL )
     {
        line_count++;
       
        if ( line_count >= MaxLines )
        {           
            fclose(fileptr);
            return 1;
        }
    }

    fclose(fileptr); 

    return 0;        
}

int Emptylogfile(const char *Filename,int logfile_fd)
{
    FILE *fileptr;

    fileptr = fopen(Filename,"r+");
    if ( fileptr == NULL ) 
    {
        printf("[LOG]: Failed to open file");
        return -1; 
    } 

    if (truncate(Filename, 0) == -1) 
    {
        printf("[LOG]: Failed to truncate file");
        fclose(fileptr);
        return 0;
    }

    fclose(fileptr);

    close(logfile_fd);

    return 1;
}
