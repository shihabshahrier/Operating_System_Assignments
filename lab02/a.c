#include<stdio.h>

struct Item{
    int price;
    int quantity;

};

int main(){
    struct Item paratha, veg, water;
    int people;
    printf("Quantity Of Paratha: ");
    scanf("%d", &paratha.quantity);

    printf("\nUnit Price:: ");
    scanf("%d", &paratha.price);

    printf("\nQuantity Of Vegetables: ");
    scanf("%d", &veg.quantity);

    printf("\nUnit Price:: ");
    scanf("%d", &veg.price);

    printf("\nQuantity Of Mineral Water: ");
    scanf("%d", &water.quantity);

    printf("\nUnit Price: ");
    scanf("%d", &water.price);

    printf("\nNumber of People: ");
    scanf("%d", &people);

    int total_price = (paratha.price*paratha.quantity) + (veg.price * veg.quantity) + (water.price*water.quantity);

    float splited_ticket = total_price / people;

    printf("Individual people will pay: %0.2f", splited_ticket);

    return 0;
}