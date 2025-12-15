#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, add, i;
    float rate;

    printf("Initial rentals: ");
    scanf("%d", &n);
    float *r = malloc(n * sizeof(float));
    printf("Rate per unit: ");
    scanf("%f", &rate);

    for (i = 0; i < n; i++)
        scanf("%f", r + i);

    printf("Add rentals: ");
    scanf("%d", &add);

    if (add > 0) {
        r = realloc(r, (n + add) * sizeof(float));
        for (i = n; i < n + add; i++)
            scanf("%f", r + i);
        n += add;
    }
    float total = 0, max = *r;
    for (i = 0; i < n; i++) {
        float v = *(r + i);
        total += v;
        if (v > max) max = v;
    }

    FILE *f = fopen("Rental_Invoices.txt", "w");
    for (i = 0; i < n; i++)
        fprintf(f, "Customer %d: Duration %.2f Cost %.2f\n",
                i+1, *(r + i), *(r + i) * rate);
    fprintf(f, "\nTotal Rental Time: %.2f\nHighest Duration: %.2f\n",
            total, max);
    fclose(f);

    printf("Invoices saved.\n");
    free(r);
    return 0;
}
