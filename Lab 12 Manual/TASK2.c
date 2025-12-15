#include <stdio.h>
#include <stdlib.h>

typedef struct Bed {
    int occupied;
    char patient[50];
    int daysAdmitted;
} Bed;
// Recursive function 
int countOccupied(Bed *beds, int n) {
    if(n == 0) return 0;
    return beds[n-1].occupied + countOccupied(beds, n-1);
}
int main() {
    int wardCount, i, j;
    printf("Number of wards: ");
    scanf("%d", &wardCount);
    Bed **wards = malloc(wardCount * sizeof(Bed*));
    int *bedsPerWard = malloc(wardCount * sizeof(int));
    // Input number of beds per ward
    for(i = 0; i < wardCount; i++) {
        printf("Beds in ward %d: ", i+1);
        scanf("%d", &bedsPerWard[i]);
        wards[i] = calloc(bedsPerWard[i], sizeof(Bed));
    }
    // Occupy a bed
    int selectedWard, selectedBed;
    printf("\nSelect ward to occupy: "); scanf("%d", &selectedWard);
    printf("Select bed: "); scanf("%d", &selectedBed);
    printf("Patient name: "); scanf("%s", wards[selectedWard-1][selectedBed-1].patient);
    printf("Days admitted: "); scanf("%d", &wards[selectedWard-1][selectedBed-1].daysAdmitted);
    wards[selectedWard-1][selectedBed-1].occupied = 1;
    printf("\nOccupied beds in ward %d = %d\n",
           selectedWard, countOccupied(wards[selectedWard-1], bedsPerWard[selectedWard-1]));
    // Save state to file
    FILE *file = fopen("hospital_state.txt", "w");
    if(file) {
        fprintf(file, "%d\n", wardCount);
        for(i = 0; i < wardCount; i++) {
            fprintf(file, "%d\n", bedsPerWard[i]);
            for(j = 0; j < bedsPerWard[i]; j++)
                fprintf(file, "%d %s %d\n",
                        wards[i][j].occupied,
                        wards[i][j].patient,
                        wards[i][j].daysAdmitted);
        }
        fclose(file);
    }
     // state from file
    file = fopen("hospital_state.txt", "r");
    if(file) {
        int fileWardCount;
        fscanf(file, "%d", &fileWardCount);
        for(i = 0; i < fileWardCount; i++) {
            int bedCount;
            fscanf(file, "%d", &bedCount);
            for(j = 0; j < bedCount; j++)
                fscanf(file, "%d %s %d",
                       &wards[i][j].occupied,
                       wards[i][j].patient,
                       &wards[i][j].daysAdmitted);
        }
        fclose(file);
    }
    printf("State saved and loaded successfully.\n");
    for(i = 0; i < wardCount; i++) free(wards[i]);
    free(wards);
    free(bedsPerWard);

    return 0;
}


