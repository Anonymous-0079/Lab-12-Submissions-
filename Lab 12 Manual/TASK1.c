#include <stdio.h>
#include <stdlib.h>

struct Order {
    char ItemName[50];
    int Qaunt;
    char C_Name[50];
    float U_Price;
};
int main() {
    int n, i;
    struct Order *o = NULL;
    char choice;
    do {
        o = realloc(o, (n + 1) * sizeof(struct Order)); 
        printf("Enter the item name:\n");
        scanf("%s", o[n].ItemName);
        printf("Enter the customer name:\n");
        scanf("%s", o[n].C_Name);
        printf("Enter the amount:\n");
        scanf("%f", &o[n].U_Price);
        printf("Enter the quantity:\n");
        scanf("%d", &o[n].Qaunt);
        n++;  
        printf("Do you want to enter another order [Y or N]: ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');
    // Calculate total
    float total = 0;
    for (i = 0; i < n; i++)
        total += o[i].Qaunt * o[i].U_Price;
    // Store in file
    FILE *f = fopen("billing.txt", "w");
    fprintf(f, "Order Summary:\n");
    for (i = 0; i < n; i++) {
        fprintf(f, "%s x %d = %.2f for %s\n",o[i].ItemName, o[i].Qaunt,o[i].U_Price * o[i].Qaunt,
                o[i].C_Name);
    }
    fprintf(f, "\nTotal Revenue: %.2f\n", total);
    fclose(f);
    free(o);
    printf("Saved\n");
    return 0;
}

