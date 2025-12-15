#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, add, i, threshold;
    float *t;

    printf("Readings: ");
    scanf("%d", &n);
    t = malloc(n * sizeof(float));
    for (i = 0; i < n; i++)
        scanf("%f", t + i);

    printf("Add more readings: ");
    scanf("%d", &add);

    if (add > 0) {
        t = realloc(t, (n + add) * sizeof(float));
        for (i = n; i < n + add; i++)
            scanf("%f", t + i);
        n += add;
    }
    float max = t[0], min = t[0];
    for (i = 1; i < n; i++) {
        if (t[i] > max) max = t[i];
        if (t[i] < min) min = t[i];
    }
    printf("Alert threshold: ");
    scanf("%d", &threshold);
    int count = 0;
    for (i = 0; i < n; i++)
        if (t[i] > threshold) count++;

    FILE *f = fopen("temperature_summary.txt", "w");
    fprintf(f, "Temperature Summary Report\n");
    fprintf(f, "Total Readings: %d\n", n);
    fprintf(f, "Highest Temperature: %.2f\n", max);
    fprintf(f, "Lowest Temperature: %.2f\n", min);
    fprintf(f, "Readings Above %d: %d\n", threshold, count);
    fclose(f);

    printf("Summary saved to temperature_summary.txt\n");

    free(t);
    return 0;
}
