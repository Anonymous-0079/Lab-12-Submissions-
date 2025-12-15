#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char title[50], id[20];
    int out, days, due;
} Log;

int main() {
    int n, add, i;
    scanf("%d", &n);

    Log *L = malloc(n * sizeof(Log));
    for (i = 0; i < n; i++) {
        scanf("%s %s %d %d", L[i].title, L[i].id, &L[i].out, &L[i].days);
        L[i].due = L[i].out + L[i].days;
    }

    scanf("%d", &add);
    if (add > 0) {
        L = realloc(L, (n + add) * sizeof(Log));
        for (i = n; i < n + add; i++) {
            scanf("%s %s %d %d", L[i].title, L[i].id, &L[i].out, &L[i].days);
            L[i].due = L[i].out + L[i].days;
        }
        n += add;
    }

    FILE *f = fopen("library_checkout.csv", "a");
    for (i = 0; i < n; i++)
        fprintf(f, "%s,%s,%d,%d,%d\n", L[i].title, L[i].id, L[i].out, L[i].days, L[i].due);

    fclose(f);
    free(L);
    return 0;
}

