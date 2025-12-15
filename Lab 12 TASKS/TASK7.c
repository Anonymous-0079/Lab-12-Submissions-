#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int qty;
    float price;
} Medicine;

int main() {
    Medicine *meds = NULL;
    int n = 0, choice, i, j;
    char temp[50];
    int lowStock = 5;

    while (1) {
        printf("\n1.Add 2.Remove 3.Show 0.Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 0) break;

        if (choice == 1) {
            n++;
            meds = realloc(meds, n * sizeof(Medicine));
            printf("Name: "); fgets(meds[n-1].name,50,stdin);
            meds[n-1].name[strcspn(meds[n-1].name,"\n")]=0;
            printf("Quantity: "); scanf("%d",&meds[n-1].qty);
            printf("Price: "); scanf("%f",&meds[n-1].price);
            getchar();
        } 
        else if (choice == 2) {
            printf("Name to remove: "); fgets(temp,50,stdin);
            temp[strcspn(temp,"\n")]=0;
            for(i=0;i<n;i++) {
                if(strcmp(meds[i].name,temp)==0) {
                    for(j=i;j<n-1;j++) meds[j]=meds[j+1];
                    n--;
                    meds = realloc(meds,n*sizeof(Medicine));
                    printf("Removed.\n");
                    break;
                }
            }
        } 
        else if (choice == 3) {
            float total=0;
            printf("\nInventory:\n");
            for(i=0;i<n;i++){
                printf("%s - Qty:%d, Price:%.2f",meds[i].name,meds[i].qty,meds[i].price);
                if(meds[i].qty<=lowStock) printf(" [LOW STOCK]");
                printf("\n");
                total+=meds[i].qty*meds[i].price;
            }
            printf("Total inventory value: %.2f\n",total);
        }
    }

    FILE *f=fopen("medicine_inventory.txt","w");
    for(i=0;i<n;i++) fprintf(f,"%s,%d,%.2f\n",meds[i].name,meds[i].qty,meds[i].price);
    fclose(f);
    free(meds);
    printf("Inventory saved.\n");
    return 0;
}
