#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a patient node
typedef struct Patient {
    char name[100];
    char priority[20];
    struct Patient* next;
} Patient;

// Define the order of priority
const char *priorityOrder[] = {"Red", "Orange", "Yellow", "Green", "Black"};

// Function to create a new patient node
Patient* createPatient(const char* name, const char* priority) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    if (newPatient == NULL) {
        printf("Memory allocation failed. Unable to add the patient.\n");
        return NULL;
    }

    strcpy(newPatient->name, name);
    strcpy(newPatient->priority, priority);
    newPatient->next = NULL;

    return newPatient;
}

// Function to add a patient to the triage queue
Patient* addPatient(Patient* triageQueue, const char* name, const char* priority) {
    Patient* newPatient = createPatient(name, priority);
    if (newPatient == NULL) {
        return triageQueue;
    }

    if (triageQueue == NULL || strcmp(priority, triageQueue->priority) < 0) {
        newPatient->next = triageQueue;
        return newPatient;
    }

    Patient* current = triageQueue;
    while (current->next != NULL && strcmp(priority, current->next->priority) >= 0) {
        current = current->next;
    }

    newPatient->next = current->next;
    current->next = newPatient;

    return triageQueue;
}

// Function to remove and treat the highest-priority patient
Patient* treatPatient(Patient* triageQueue) {
    if (triageQueue == NULL) {
        printf("No patients in the triage queue.\n");
        return NULL;
    }

    for (int i = 0; i < 5; i++) {
        Patient* current = triageQueue;
        Patient* prev = NULL;

        // Find the first patient with the highest-priority in the current order
        while (current->next != NULL && strcmp(current->priority, priorityOrder[i]) != 0) {
            prev = current;
            current = current->next;
        }

        if (strcmp(current->priority, priorityOrder[i]) == 0) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                triageQueue = current->next;
            }

            printf("Patient treated and removed from the queue.\n");
            free(current);
            return triageQueue;
        }
    }

    return triageQueue; // If no patients were found with the current priority
}

// Function to print the current triage queue
// Function to print the current triage queue in the specified order
void printTriageQueue(Patient* triageQueue) {
    if (triageQueue == NULL) {
        printf("Triage queue is empty.\n");
        return;
    }

    printf("Triage Queue:\n");

    // Traverse the priority order
    for (int i = 0; i < 5; i++) {
        Patient* current = triageQueue;

        // Print patients with the current priority
        while (current != NULL) {
            if (strcmp(current->priority, priorityOrder[i]) == 0) {
                printf("Name: %s, Priority: %s\n", current->name, current->priority);
            }
            current = current->next;
        }
    }
}


int main() {
    Patient* triageQueue = NULL;

    printf("LifeSaver Triage: Optimizing Patient Prioritization in Emergencies\n\n\n");
    printf("Priority Order followed:\nImmediate (Red): Patients in critical condition who require immediate attention and potentially life-saving interventions.\nUrgent (Orange): Patients with serious but not immediately life-threatening conditions.\nDelayed (Yellow): Patients with non-urgent conditions that do not require immediate attention.\nMinimal (Green): Patients with minor injuries or illnesses that can typically wait longer for treatment.\nExpectant (Black): Patients whose injuries or conditions are so severe that survival is unlikely.\n\n");

    int choice;
    char name[100];
    char priority[20];

    do {
        printf("\nOptions:\n");
        printf("1. Add a patient to triage\n");
        printf("2. Treat the highest-priority patient\n");
        printf("3. Print triage queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter patient's name: ");
                scanf(" %[^\n]", name);
                printf("Enter patient's priority (Red, Orange, Yellow, Green, Black): ");
                scanf(" %[^\n]", priority);
                triageQueue = addPatient(triageQueue, name, priority);
                break;
            case 2:
                triageQueue = treatPatient(triageQueue);
                break;
            case 3:
                printTriageQueue(triageQueue);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    // Clean up memory (free any remaining patients)
    while (triageQueue != NULL) {
        Patient* nextPatient = triageQueue->next;
        free(triageQueue);
        triageQueue = nextPatient;
    }

    return 0;
}
