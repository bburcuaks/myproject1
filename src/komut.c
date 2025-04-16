#include "komut.h"

void processInputFile(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        handleError("Giris dosyasi acilamadi.");
        return;
    }

    FILE *outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        fclose(inputFile);
        handleError("Cikis dosyasi acilamadi.");
        return;
    }

    char line[1024];
    char outputBuffer[1024] = {0};
    int outputIndex = 0;

    while (fgets(line, sizeof(line), inputFile)) {
        char *command = strtok(line, ":");
        char *content = strtok(NULL, "\n");

        if (strcmp(command, "yaz") == 0) {
            char *token = strtok(content, " ");
            while (token != NULL) {
                int num = atoi(token);
                token = strtok(NULL, " ");
                for (int i = 0; i < num; i++) {
                    if (token[0] == '\\') {
                        outputBuffer[outputIndex++] = (token[1] == 'b' ? ' ' : '\n');
                    } else {
                        outputBuffer[outputIndex++] = token[0];
                    }
                }
                token = strtok(NULL, " ");
            }
        } else if (strcmp(command, "sil") == 0) {
            int num = atoi(strtok(content, " "));
            char charToFind = *strtok(NULL, " ");

            int i = 0, j = 0;
            while (i < outputIndex) {
                if (outputBuffer[i] == charToFind && num > 0) {
                    num--;
                } else {
                    outputBuffer[j++] = outputBuffer[i];
                }
                i++;
            }
            outputIndex = j; // güncellenen index değeri
            while (j < i) { // tampon sonunu temizle
                outputBuffer[j++] = '\0';
            }
        } else if (strcmp(command, "sonagit") == 0) {
            // currentPosition güncellemesi gerekmez
        } else if (strcmp(command, "dur") == 0) {
            break;
        }
    }

    fprintf(outputFile, "%s", outputBuffer);

    fclose(inputFile);
    fclose(outputFile);
}

void handleError(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}
