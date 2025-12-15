#include <stdio.h>
#include <stdlib.h>

// Recursive function to calculate total attendees
int totalAttendees(int *arr, int n) {
    if (n == 0) return 0;
    return arr[n - 1] + totalAttendees(arr, n - 1);
}

int main() {
    int *attendance, gates, extraGates, i;
    
    printf("Enter number of gates: ");
    scanf("%d", &gates);
    attendance = (int*) malloc(gates * sizeof(int));
    for (i = 0; i < gates; i++) {
        printf("Gate %d attendees: ", i + 1);
        scanf("%d", &attendance[i]);
    }
    printf("Add more gates? ");
    scanf("%d", &extraGates);
    if (extraGates > 0) {
        attendance = (int*) realloc(attendance, (gates + extraGates) * sizeof(int));
        for (i = gates; i < gates + extraGates; i++) {
            printf("Gate %d attendees: ", i + 1);
            scanf("%d", &attendance[i]);
        }
        gates += extraGates;
    }
    // Find max gate
    int max = attendance[0], maxGate = 1;
    for (i = 1; i < gates; i++) {
        if (attendance[i] > max) {
            max = attendance[i];
            maxGate = i + 1;
        }
    }
    int total = totalAttendees(attendance, gates);
    printf("\nTotal attendees: %d\n", total);
    printf("Gate with highest attendance: Gate %d (%d people)\n", maxGate, max);
    // Save to file
    FILE *f = fopen("attendance.txt", "w");
    for (i = 0; i < gates; i++)
        fprintf(f, "Gate %d: %d\n", i + 1, attendance[i]);
    fprintf(f, "Total attendees: %d\n", total);
    fprintf(f, "Highest attendance: Gate %d (%d)\n", maxGate, max);
    fclose(f);

    free(attendance);
    return 0;
}
