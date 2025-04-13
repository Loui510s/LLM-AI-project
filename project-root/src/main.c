#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Include math.h for isnan and isinf
#include "matrix.h"
#include "model.h"
#include "training_accuracy.h"
#include "graph.h" // Include graph.h for saving accuracy data
#include "loss.h"

#define MAX_EPOCHS 10000

// XOR training data
float inputs[4][2] = {
    {0, 0}, {0, 1}, {1, 0}, {1, 1}
};
float targets[4][1] = {
    {0}, {1}, {1}, {0}
};

int main() {
    printf("Starting program...\n");

    srand(42);  // for reproducibility

    int input_size = 2;
    int hidden_size = 4;
    int output_size = 1;

    Model* model = create_model(input_size, hidden_size, output_size);

    printf("Model created. Starting training...\n");

    int epochs[MAX_EPOCHS];
    int accs[MAX_EPOCHS];

    int correct_predictions = 0; // Track correct predictions for accuracy

    for (int epoch = 0; epoch < MAX_EPOCHS; ++epoch) {
        printf("Starting epoch %d...\n", epoch);
        correct_predictions = 0; // Reset correct predictions for each epoch
    
        for (int i = 0; i < 4; ++i) {
            Matrix* input = create_matrix(1, input_size);
            Matrix* target = create_matrix(1, output_size);
    
            input->data[0] = inputs[i][0];
            input->data[1] = inputs[i][1];
            target->data[0] = targets[i][0];
    
            // Forward pass
            Matrix* logits = model_forward(model, input); // Raw logits from the model
            float probabilities[output_size];
            softmax(logits->data, probabilities, output_size); // Apply softmax to logits
    
            // Debugging: Print logits and probabilities
            printf("Logits: ");
            for (int j = 0; j < output_size; j++) {
                printf("%f ", logits->data[j]);
            }
            printf("\n");
    
            printf("Probabilities: ");
            for (int j = 0; j < output_size; j++) {
                printf("%f ", probabilities[j]);
            }
            printf("\n");
    
            // Calculate loss
            int correct_label = (int)target->data[0]; // Assuming target is a one-hot encoded matrix
            float loss = cross_entropy_loss(probabilities, correct_label, output_size);
            if (isnan(loss) || isinf(loss)) {
                printf("Invalid loss detected: %f\n", loss);
                exit(1);
            }
            printf("Epoch %d, Sample %d, Loss: %f\n", epoch, i, loss);
    
            // Calculate accuracy
            int predicted_class = (probabilities[0] >= 0.5) ? 1 : 0; // Threshold at 0.5
            printf("Sample %d: Predicted = %d, Correct = %d\n", i, predicted_class, correct_label);
            if (predicted_class == correct_label) {
                correct_predictions++;
            }
    
            // Backward pass and update
            model_backward(model, input, target);
            model_update(model, 0.001f); // Reduced learning rate
    
            free_matrix(logits);
            free_matrix(input);
            free_matrix(target);
        }
    
        // Calculate and print accuracy for the epoch
        float accuracy = (float)correct_predictions / 4 * 100; // 4 samples in XOR dataset
        printf("Epoch %d: Correct Predictions = %d, Accuracy = %.2f%%\n", epoch, correct_predictions, accuracy);
    
        // Save accuracy for plotting
        epochs[epoch] = epoch;
        accs[epoch] = (int)accuracy;
    
        // Early stopping
        if (accuracy >= 99.99f) { // Use tolerance for floating-point comparison
            printf("Early stopping at epoch %d: Accuracy = %.2f%%\n", epoch, accuracy);
            break;
        }
    }
    
}