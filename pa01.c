#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*=============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Vigenere cipher
|
| Author: Sunidhi Mistry
| Language: c, c++, Java, go, python
|
| To Compile: javac pa01.java
| gcc -o pa01 pa01.c
| g++ -o pa01 pa01.cpp
| go build pa01.go
| python pa01.py
|
| To Execute: java -> java pa01 kX.txt pX.txt
| or c++ -> ./pa01 kX.txt pX.txt
| or c -> ./pa01 kX.txt pX.txt
| or go -> ./pa01 kX.txt pX.txt
| or python -> python pa01.py kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Fall 2022
| Instructor: McAlpin
| Due Date: per assignment
|
+=============================================================================*/

#define BUFFER_SIZE 1000000

int main(int argc, char ** argv) {

    // How to open any file in c
    FILE *keyFile;
    FILE *plaintextFile;

    // Open the key file using the first command line argument
    char * keyFileName = argv[1];
    char * plaintextFileName = argv[2];

    // Open the key file
    keyFile = fopen(keyFileName, "r");

    // Open the plaintext file
    plaintextFile = fopen(plaintextFileName, "r");

    // Allocate memory for the key and plaintext
    char key[BUFFER_SIZE];
    char plaintext[BUFFER_SIZE];

    // Allocate memory for the key without spaces and plaintext without spaces
    char key_woSpace[512];
    char plaintext_woSpace[512];

    // Read the key file and store it in the key array
    int key_len = 0;
    while(fscanf(keyFile, "%c", &key[key_len]) != EOF) {
        key_len++;
    }

    // Read the plaintext file and store it in the plaintext array
    int plaintext_len = 0;
    while(fscanf(plaintextFile, "%c", &plaintext[plaintext_len]) != EOF) {
        plaintext_len++;
    }
    
    // Remove any non alphabetic characters from key and plaintext
    for(int i = 0, j = 0; i < key_len; i++) {
        // Remove any non alphabetic characters from key
        if(isalpha(key[i]) != 0) {
            key_woSpace[j] = tolower(key[i]);
            j++;
        }
    }

    // Remove any non alphabetic characters from the rest of the plaintext
    for(int i = 0, k = 0; i < plaintext_len && k < 512; i++) {
        if(isalpha(plaintext[i]) != 0) {
            plaintext_woSpace[k] = tolower(plaintext[i]);
            k++;
        }
    }   

    // New length of plaintext
    plaintext_len = strlen(plaintext_woSpace);

    // Add X's to the end of the plaintext as a reference for padding
    for(int i = plaintext_len; i < 512; i++) {
        plaintext_woSpace[i] = 'x';
    }

    // New length of key
    key_len = strlen(key_woSpace);

    // New length of plaintext
    plaintext_len = strlen(plaintext_woSpace);
    
    // key int array
    int * key_int = (int *)calloc(sizeof(int), key_len);
    // plaintext int array
    int * plaintext_int = (int *)calloc(sizeof(int), plaintext_len);

    // Convert key to int array
    for(int x = 0; x < key_len; x++) {
        key_int[x] = key_woSpace[x] - 97;
    }

    // Convert plaintext to int array
    for(int x = 0; x < plaintext_len; x++) {
        plaintext_int[x] = plaintext_woSpace[x] - 97;
    }

    // ciphertext int array
    int * ciphertext_int = (int *)calloc(sizeof(int), 512);
    // ciphertext array
    char * ciphertext_char = (char *)calloc(sizeof(char), 512);

    // Encrypt
    for(int x = 0, y = 0; x < 512; x++, y++) {

        // If y is greater than the length of the key, reset y to 0
        if(y == key_len ) {
            y = 0;
        }

        // If the plaintext is a space, add a space to the ciphertext
        ciphertext_int[x] = (plaintext_int[x] + key_int[y]) % 26;
    }

    // Convert ciphertext_int to ciphertext_char
    for(int x = 0; x < 512; x++) {
        ciphertext_char[x] = ciphertext_int[x] + 97;
    }

    // Print ciphertext finally!!!
    for(int x = 0, y = 0; x < 512; x++, y++) {
        if(y == 80) {
            printf("\n");
            y = 0;
        }
        printf("%c", ciphertext_char[x]);
    }
    printf("\n");

}

/*=============================================================================
| I Sunidhi Mistry (su358025) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/