#include <stdio.h>
#include <mysql.h>
#include <windows.h>


//This Code Is Assuming Youre Going To Do This For A Small Scale Cafe Or Something Similar

struct FoodItem {                           
    char name[50];
    float price;                    //A Structure Is Made In Which The Name And Prices Of The Food Will Be Stored and Billed
};

int main(){
    int order,i;
    struct FoodItem Menu[] =    //Array Is Initialized In Which The Prices And Name Of It Will Be Declared And Initialized
    {
        {"Veg Burger" , 70 } ,
        {"Non Veg Burger" , 70 },
        {"Veg Pizza" , 70 },
        {"Margherita Pizza" , 119 },
        {"Tandoori Paneer Pizza" , 319 },
    };

    int menu_items = sizeof(Menu[])/sizeof(Menu[0]);

    for(i = 0;i<menu_items;i++){
        printf("\%s" , &Menu[i])
    }
    
    printf("How Many Items Will You Be Ordering Today?");
    scanf("%d",&order);
    int all_orders[order];          

    for(i = 0 ; i < order ; i++){               //a for loop so itll loop until the amount of food items is required.
        if (i+1 == 1)
        {
            printf("Enter Your 1st Food Item Order: ");
            scanf("%s", &all_orders[i]);
        }
        elseif (i+1 == 2){
            printf("Enter Your 2nd Food Item Order");
            scanf("%s" , &all_orders[i]);
        }

        elseif (i+1 > 2){
            printf("Enter your %dth Food Item Order:");
            scanf("%s", &all_orders[i]);
        }
        
    }

    printf("Is This Your Order List?\n");
    for(i = 0; i< order; i++){
        printf("%s,", &all_orders[i]);
        if(i+1 == order){
            printf("%s.", &all_order[order-1])
        }

    }

    //Asks Customer For Their Name
    char customer_name[250];
    printf("Please Enter Your Full Name: ");
    scanf("%s",&customer_name);
    


    //This Is The Where The Database gets Connected And It Will Store The Data Inside The tables
    MYSQL *conn;
    conn = mysql_init(NULL);


}