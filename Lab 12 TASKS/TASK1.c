#include <stdio.h>
#include <stdlib.h>

int main() {
    int h, extra, t, *s, i;
    
    printf("Hours: ");
    scanf("%d", &h);
    s = malloc(h * sizeof(int));
    for (i = 0; i < h; i++) {
        scanf("%d", s + i);
    }
    printf("Add more hours: ");
    scanf("%d", &extra);

    if (extra > 0) {
        s = realloc(s, (h + extra) * sizeof(int));
        for (i = h; i < h + extra; i++) {
            scanf("%d", s + i);
        }
        h += extra;
    }
    int max = *s, total = 0, above = 0;
    for (i = 0; i < h; i++) {
        int v = *(s + i);
        total += v;
        if (v > max) max = v;
    }
    printf("Threshold: ");
    scanf("%d", &t);
    for (i = 0; i < h; i++) 
        if (*(s + i) > t) above++;

    FILE *f = fopen("fitness_tracker.txt", "w");
    for (i = 0; i < h; i++)
        fprintf(f, "Hour %d: %d\n", i+1, *(s+i));
    fprintf(f, "Total=%d\nMax=%d\nAbove %d=%d\n", total, max, t, above);
    fclose(f);

    printf("Saved.\n");
    free(s);
}

