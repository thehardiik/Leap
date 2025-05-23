#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 65536 
#define MAX_SEQ_LEN 256     

typedef struct {
    unsigned char *sequence;
    int length;
} DictEntry;

DictEntry dictionary[MAX_DICT_SIZE];
int dictSize = 1;  

void freeDictionary() {
    for (int i = 1; i < dictSize; i++) {
        free(dictionary[i].sequence);
    }
}

int decompress(const char *inputPath, const char *outputPath) {
    FILE *input = fopen(inputPath, "rb");
    FILE *output = fopen(outputPath, "wb");

    if (!input || !output) {
        perror("File error");
        return 1;
    }

    while (1) {
        unsigned short index;
        unsigned char nextChar;

        if (fread(&index, sizeof(unsigned short), 1, input) != 1) break;
        if (fread(&nextChar, sizeof(unsigned char), 1, input) != 1) break;

        if (index >= dictSize || (index != 0 && dictionary[index].sequence == NULL)) {
            fprintf(stderr, "Invalid dictionary index: %d\n", index);
            fclose(input);
            fclose(output);
            freeDictionary();
            return 1;
        }

        unsigned char *newSeq = malloc(MAX_SEQ_LEN);
        int newLen = 0;

        if (index == 0) {
            newSeq[0] = nextChar;
            newLen = 1;
        } else {
            int prefixLen = dictionary[index].length;
            if (prefixLen + 1 > MAX_SEQ_LEN) {
                fprintf(stderr, "Sequence too long\n");
                free(newSeq);
                continue;
            }
            memcpy(newSeq, dictionary[index].sequence, prefixLen);
            newSeq[prefixLen] = nextChar;
            newLen = prefixLen + 1;
        }

        fwrite(newSeq, 1, newLen, output);

        if (dictSize < MAX_DICT_SIZE) {
            dictionary[dictSize].sequence = malloc(newLen);
            memcpy(dictionary[dictSize].sequence, newSeq, newLen);
            dictionary[dictSize].length = newLen;
            dictSize++;
        }

        free(newSeq);
    }

    fclose(input);
    fclose(output);
    freeDictionary();
    return 0;
}
