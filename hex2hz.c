//
// File: hex2hz.c
// Language: C99 standard
// Author: Roland Sanford <ras9841@rit.edu>
//         Dakota Williams 
// Description:
//      Takes in a binary file and outputs a song. Each byte is
//      mapped to a single note. The first nibble represents the
//      duration and rhythm of the note and the second represents
//      the pitch.
// // // // // // // // // // // // // // // // // // // // // // // // // // 

//
// Includes
//
#include <stdio.h>


//
// Defines
//
#define EXIT_SUCCESS 1
#define EXIT_FAILURE 0

int main(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, "Usage: hex2hz inputFile \n");
        return EXIT_FAILURE;
    }
    
    // Open the file
    FILE *file = fopen(argv[1], "rb");
    if (!file){
        fprintf(stderr,
        "Failed to open input file: no such file or directory");
        return EXIT_FAILURE;
    }

    // Check for empty file
    fseek(file, 0, SEEK_END);
    long num_bytes;
    if (!(num_bytes = ftell(file))){
        fprintf(stderr, "Error: input file is empty.");
        return EXIT_FAILURE;
    }   
    fseek(file, 0, SEEK_SET);
    
    printf("File %s has %ld bytes.\n", argv[1], num_bytes);
    
    fclose(file);
    return 0;
}
