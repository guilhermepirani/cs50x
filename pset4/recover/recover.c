#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Each file is saved in Blocks of 512KB (FAT32)
#define BLOCKSIZE 512

// This is an int from 0 to 255
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensuring user enters a file
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    // Opening prompted file
    FILE *inptr = fopen(argv[1], "r");
    
    // Buffer to store jpeg data, filename saves sprintf results, imgcount also used in sprintf, outptr is the temporary new file(saved as ###.jpg)
    BYTE buffer[BLOCKSIZE];
    char filename[8];
    int imgCount = 0;
    FILE *outptr = NULL;
    
    // While not final of file (feof returns >0 when file ends)
    while (fread(buffer, sizeof(BYTE), BLOCKSIZE, inptr) || feof(inptr) == 0)
    {
        // Checks 4 Starting Bytes from buffer to see if they match jpeg pattern, then procceed to create copies of those
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // NULL means no jpeg found, so no need to close an open file, we just create a new one
            if (outptr == NULL)
            {
                sprintf(filename, "%03i.jpg", imgCount);
                outptr = fopen(filename, "w");
                imgCount++;
            }
            // Now we DO need to close an open file, and then open a new one
            else if (outptr != NULL)
            {
                fclose(outptr);
                sprintf(filename, "%03i.jpg", imgCount);
                outptr = fopen(filename, "w");
                imgCount++;         
            }
        }
        // Outside jpeg check, means we have an open file and are ready to write on it.
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCKSIZE, outptr);
        }
    }
    // Make sure to close everything
    fclose(outptr);
    fclose(inptr);
}

/* sprintf -> (filename) from the string variable created before, we saved space for 8 Bytes: 0 0 0 . j p g \0
              "%03i.jpg" means that we want to save ###.jpg as filename, next paramenter defines ###
              imgCount is the number that goes in ### always with 3 digits e.g. 1st one is 000.
 size_t fread(
   void *buffer,
   size_t size,
   size_t count,
   FILE *stream);
   
Parameters:
buffer
Storage location for data.
size
Item size in bytes.
count
Maximum number of items to be read.
stream
Pointer to FILE structure. */