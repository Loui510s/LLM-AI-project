#include <stdio.h>

void save_accuracy_csv(const char* filename, int* epochs, int* accuracies, int num_epochs) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    // Write CSV header
    fprintf(file, "Epoch,Accuracy\n");

    // Write data
    for (int i = 0; i < num_epochs; i++) {
        fprintf(file, "%d,%d\n", epochs[i], accuracies[i]);
    }

    fclose(file);
    printf("Accuracy data saved to %s\n", filename);
}