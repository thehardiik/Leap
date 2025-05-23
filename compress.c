#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10007 // Prime Number for Hash Table
#define MAX_DICT_SIZE 65536 // 16 bit index, so total possible entries are 65536


// Hash Table Entry
typedef struct Entry {
    unsigned char sequence[16];
    unsigned char length;
    int index;
    struct Entry *next;
} Entry;

// Hash Table for Dictionary
Entry* dict[HASH_SIZE] = {0};  
int nextIndex = 1;             


// Hash Function
unsigned int hash(unsigned char *sequence, unsigned char length) {
    unsigned int hash = 5381;
    for (int i = 0; i < length; i++) {
        hash = ((hash << 5) + hash) + sequence[i];
    }
    return hash % HASH_SIZE;
}


// Hash Table Lookup
int searchDictionary(unsigned char *sequence, unsigned char length) {
    unsigned int index = hash(sequence, length);
    Entry *entry = dict[index];
    while (entry != NULL) {
        if (entry->length == length && memcmp(entry->sequence, sequence, length) == 0) {
            return entry->index;
        }
        entry = entry->next;
    }
    return -1;  // not found
}


// Add to Hash Table
void addToDictionary(unsigned char *sequence, unsigned char length) {
    if (nextIndex >= MAX_DICT_SIZE) return;
    unsigned int h = hash(sequence, length);
    Entry* newEntry = malloc(sizeof(Entry));
    memcpy(newEntry->sequence, sequence, length);
    newEntry->length = length;
    newEntry->index = nextIndex++;
    newEntry->next = dict[h];
    dict[h] = newEntry;
}


// Main Compress Function
int compress(const char *inputPath, const char *outputPath) {
    FILE *file = fopen(inputPath, "rb");
    FILE *output = fopen(outputPath, "wb");
    if (file == NULL || output == NULL) {
        perror("Error opening file");
        return 1;
    }

    unsigned char sequence[16];
    int seq_len = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        sequence[seq_len++] = (unsigned char)c;
        int index = searchDictionary(sequence, seq_len);

        if (index != -1 && seq_len < 16) {
            continue;
        }

        int prefixIndex = 0;
        unsigned char newChar = sequence[seq_len - 1];

        if (seq_len > 1) {
            prefixIndex = searchDictionary(sequence, seq_len - 1);
        }

        fwrite(&prefixIndex, sizeof(short), 1, output);
        fwrite(&newChar, sizeof(unsigned char), 1, output);
        addToDictionary(sequence, seq_len);

        seq_len = 0;
    }

    if (ferror(file)) {
        perror("Error reading file");
        fclose(file);
        fclose(output);
        return 1;
    }

    fclose(file);
    fclose(output);
    return 0;
}

