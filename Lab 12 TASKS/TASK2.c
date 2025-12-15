#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50], roll[20];
    int seat;
} Student;

int valid(char *r, int i) {
    if (!r[i]) return 1;
    char c = r[i];
    if (!((c>='0'&&c<='9')||(c>='A'&&c<='Z')||(c>='a'&&c<='z')))
        return 0;
    return valid(r, i+1);
}

int main() {
    int n, add, i;
    printf("Students: ");
    scanf("%d", &n);

    Student *s = malloc(n * sizeof(Student));

    for (i = 0; i < n; i++) {
        scanf("%s %s", s[i].name, s[i].roll);
        while (!valid(s[i].roll, 0)) scanf("%s", s[i].roll);
        s[i].seat = i + 1;
    }

    printf("Add: ");
    scanf("%d", &add);
    if (add > 0) {
        s = realloc(s, (n + add) * sizeof(Student));
        for (i = n; i < n + add; i++) {
            scanf("%s %s", s[i].name, s[i].roll);
            while (!valid(s[i].roll, 0)) scanf("%s", s[i].roll);
            s[i].seat = i + 1;
        }
        n += add;
    }

    FILE *f = fopen("seating.txt", "w");
    for (i = 0; i < n; i++)
        fprintf(f, "%s %s Seat-%d\n", s[i].name, s[i].roll, s[i].seat);
    fclose(f);

    free(s);
    return 0;
}
