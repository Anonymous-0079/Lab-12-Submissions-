#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, j, z, i;
    printf("Number of users: ");
    scanf("%d", &n);
    char **names = malloc(n * sizeof(char*));
    int **units = malloc(n * sizeof(int*));
    int *days = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        names[i] = malloc(50 * sizeof(char));
        printf("\nName of user %d: ", i + 1);
        scanf("%s", names[i]);
        printf("Days recorded: ");
        scanf("%d", &days[i]);
        units[i] = malloc(days[i] * sizeof(int));
        for (j = 0; j < days[i]; j++) {
            printf("Units day %d: ", j + 1);
            scanf("%d", &units[i][j]);
        }
        // Extend days
        char ext;
        printf("Extend days? (y/n): ");
        scanf(" %c", &ext);
        if (ext == 'y' || ext == 'Y') {
            int extra;
            printf("Extra days: ");
            scanf("%d", &extra);
            units[i] = realloc(units[i], (days[i] + extra) * sizeof(int));
            for (z = days[i]; z < days[i] + extra; z++) {
                printf("Units day %d: ", z + 1);
                scanf("%d", &units[i][z]);
            }
            days[i] += extra;
        }
    }
    FILE *fp = fopen("bill_summary.txt", "w");
    if (!fp) return 1;
    fprintf(fp, "Electricity Bill Summary\n");
    for (i = 0; i < n; i++) {
        int total = 0;
        for (j = 0; j < days[i]; j++) total += units[i][j];
        float avg = (float)total / days[i];
        float bill;
        if (total <= 100) bill = total * 1.5;
        else if (total <= 300) bill = 100*1.5 + (total-100)*2.0;
        else bill = 100*1.5 + 200*2.0 + (total-300)*3.0;

        fprintf(fp, "User: %s\nTotal: %d\nAverage: %.2f\nBill: %.2f",
                names[i], total, avg, bill);
        free(units[i]);
        free(names[i]);
    }
    free(units);
    free(names);
    free(days);
    fclose(fp);
    printf("\nBill summary saved to bill_summary.txt");
    return 0;
}
