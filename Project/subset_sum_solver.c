#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BREAKLINES "\n\n"
#define maxStringSize 100

typedef char* String;
typedef char** StringArray;
typedef int* IntegerArray;

void sortArray(int* array);
void convertStringToIntegerArray(int* array, String toConvert) {
    // printf("Converting.\n");

    int *numbers = malloc(10 * sizeof(int));
    int capacity = 10;  // Keep track of allocated capacity
    int count = 0;      // Number of elements added so far

    // Split the string into tokens using strtok()
    char *token = strtok(toConvert, " ");
    while (token != NULL) {
        // Convert the token (string) to an integer
        int number = atoi(token);

        // Check if reallocation is needed (if count reaches capacity)
        if (count == capacity) {
        capacity *= 2;  // Double the capacity
        numbers = realloc(numbers, capacity * sizeof(int));
            if (numbers == NULL) {
                fprintf(stderr, "Memory allocation failed!\n");
                return;
            }
        }

        // Add the converted integer to the array
        numbers[count++] = number;

        // Get the next token
        token = strtok(NULL, " ");
    }
    numbers[count++] = 99999;
    array = numbers;

    int sum = 0;
    for(int j = 0; numbers[j]!=99999; j++) {
        printf(" %d\t", numbers[j]);
        sum += numbers[j];
    }
    printf(BREAKLINES);
}

int main() {
    int set_amount;
    int i, j;
    int target, number;

    int** set_of_number_arrays;
    String* string_inputs_array;

    printf("Welcome to the subset sum solver.\n");

    printf("Enter the amount of sets you want to evaluate: ");
    scanf("%d", &set_amount);

    printf(BREAKLINES);
    
    printf("Allocating space for %d integer arrays...\n", set_amount);
    set_of_number_arrays = (int**)malloc(sizeof(int*)*set_amount);
    printf("Successfully allocated integer arrays.\n");

    printf(BREAKLINES);

    printf("Allocating space for %d string arrays...\n", set_amount);
    string_inputs_array = (String*)malloc(sizeof(String)*set_amount);
    for(i = 0; i < set_amount; i++) {
        string_inputs_array[i] = (String)malloc(sizeof(char)*maxStringSize);
    }
    printf("Successfully allocated string arrays.\n");


    printf(BREAKLINES);

    printf("Allocating space for %d target array...\n", set_amount);
    int* targets_array = (int*)malloc(sizeof(int));
    printf("Successfully allocated target array.\n");

    printf(BREAKLINES);

    for(i = 0; i<set_amount; i++) {
        printf("Running %d time(s)\n", i+1);
        printf("Enter target and array number(s): %d\n", i+1);

        printf("Target: "); scanf(" %d", &target);

        targets_array[i] = target;
        
        printf("Enter numbers: ");
        scanf(" %[^\n]s",string_inputs_array[i]);
        printf(" %s", string_inputs_array[i]);
    }

    printf("Parsing input.\n");
    for(i = 0; i<set_amount; i++) {
        convertStringToIntegerArray(set_of_number_arrays[i], string_inputs_array[i]);
    }
    
    return 0;
}