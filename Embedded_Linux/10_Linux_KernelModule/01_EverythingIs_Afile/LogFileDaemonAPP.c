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

    // Open and seek to the end of /dev/kmsg
    kmsg_fd = OpenAndSeek_Kmsg(KMSG_PATH);
    // Open the logfile
    logfile_fd = OpenLogFile(LOGFILE_PATH);
    
    while(1)
    {
        // Read latest data from /dev/kmsg
        int BytesRead = Readkmsg_LatestData(kmsg_fd,buffer);       
        // Write latest data to the logfile
        Wtitelogfile_LatestData(logfile_fd,buffer,BytesRead);
        // Check if the logfile has reached maximum lines
        if ( Checklogfile_MaxLines(LOGFILE_PATH,10) == 1 )
        {
            // Empty the logfile
            Emptylogfile(LOGFILE_PATH,logfile_fd);
            // Reopen the logfile
            logfile_fd = OpenLogFile(LOGFILE_PATH);
            // Toggle the CapsLock LED           
            Toggle_CapsLock_Led();
        }

        // Sleep for 10 seconds
        sleep(10);
        // Clear the buffer
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

    // Open the CapsLock LED file
    CapsLockLED_fd = open("/sys/class/leds/input3::capslock/brightness", O_RDWR);
    if ( CapsLockLED_fd < 0 )
    {
        printf("[LOG]: Failed to open CapsLock LED file\n");
        return -1;
    }

    // Read the current CapsLock LED state
    errno = read(CapsLockLED_fd, &CapsLock_Val, 1);
    if ( errno <= 0 )
    {
        printf("[LOG]: Failed to read CapsLock LED state\n");
        close(CapsLockLED_fd);
        return -1;
    }

    // Toggle the CapsLock LED state
    CapsLock_Val = (CapsLock_Val == '0') ? '1' : '0';

    // Write the new CapsLock LED state
    errno = write(CapsLockLED_fd, &CapsLock_Val, 1);
    if ( errno <= 0 )
    {
        printf("[LOG]: Failed to write CapsLock LED state\n");
        close(CapsLockLED_fd);
        return -1;
    }

    // Close the CapsLock LED file
    close(CapsLockLED_fd);    
}

int OpenAndSeek_Kmsg(const char *Filename)
{
    int kmsg_fd;

    // Open /dev/kmsg
    kmsg_fd = open(Filename, O_RDONLY);
    if ( kmsg_fd < 0 )
    {
        printf("[LOG]: Failed to open /dev/kmsg\n");
        return -1;
    }

    // Seek to the end of /dev/kmsg
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

    // Open the logfile
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

    // Read data from /dev/kmsg
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

    // Write data to the logfile
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

    // Open the logfile With read/write permisson
    fileptr = fopen(Filename,"r+");
    if ( fileptr == NULL ) 
    {
        printf("[LOG]: Failed to open file");
        return -1; 
    }   

    // Count the number of lines in the logfile
    while ( fgets(line, sizeof(line), fileptr) != NULL )
     {
        line_count++;
       
        if ( line_count >= MaxLines )
        {           
            fclose(fileptr);
            return 1;
        }
    }

    // Close the logfile
    fclose(fileptr); 

    return 0;        
}

int Emptylogfile(const char *Filename,int logfile_fd)
{
    FILE *fileptr;

    // Open the logfile With read/write permisson
    fileptr = fopen(Filename,"r+");
    if ( fileptr == NULL ) 
    {
        printf("[LOG]: Failed to open file");
        return -1; 
    } 

    // Truncate the logfile to 0 bytes
    if (truncate(Filename, 0) == -1) 
    {
        printf("[LOG]: Failed to truncate file");
        fclose(fileptr);
        return 0;
    }

    // Close the logfile
    fclose(fileptr);
    // Close the logfile file descriptor
    close(logfile_fd);

    return 1;
}
