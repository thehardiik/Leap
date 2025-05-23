
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printLogo() {
    printf(
        " _    _          _ _    _____ _                                   \n"
        "| |  | |        (_) |  / ____| |                                  \n"
        "| |__| | __ _ ___ _| | | (___ | |__   __ _ _ __  _ __   ___  _ __   \n"
        "|  __  |/ _` |/ __| | | \\___ \\| '_ \\ / _` | '_ \\| '_ \\ / _ \\| '_ \\  \n"
        "| |  | | (_| | (__| | | ____) | | | | (_| | | | | | | | (_) | | | | \n"
        "|_|  |_|\\__,_|\\___|_|_| |_____/|_| |_|\\__,_|_| |_|_| |_|\\___/|_| |_| \n\n"
        "\"Information is the resolution of uncertainty\" - Claude Shannon\n"
        "Lempel-Ziv Compression Tool - Honoring the Father of Information Theory\n"
        "Entropy Encoder v1.0 | Dedicated to Digital Compression Pioneers\n\n"
    );
}

// Function declarations
int compress(const char *inputFile, const char *outputFile);
int decompress(const char *inputFile, const char *outputFile);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <compress|decompress> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    printLogo();

    if (strcmp(argv[1], "compress") == 0) {
        return compress(argv[2], argv[3]);
    } else if (strcmp(argv[1], "decompress") == 0) {
        return decompress(argv[2], argv[3]);
    } else {
        fprintf(stderr, "Invalid operation: %s\n", argv[1]);
        return 1;
    }
}
