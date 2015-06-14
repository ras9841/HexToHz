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

void hex_print(unsigned char byte);

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
    
    // Read each byte
    unsigned char byte;
    for (size_t i = 0; (long)i < num_bytes; i++){
        fread(&byte, 1, 1, file);
        hex_print(byte);
    }


    fclose(file);
    return 0;
}


// For the byte AB, 0->A and 1->B
size_t get_nibble(size_t byte, size_t number){
    if (!number){
        return (byte & 0xf0) >> 4;
    }
    else {
        return (byte & 0xf);
    }
}

void hex_print(unsigned char byte){
    size_t first = get_nibble(byte,0) ;     
    size_t second = get_nibble(byte,1);
    printf("Byte 0x%X (%u)\n", (unsigned short)byte, (unsigned short)byte);
    printf("First Nibble: 0x%zx (%zu)\n", first);
    printf("Second Nibble: 0x%zx (%zu)\n", second);
}


