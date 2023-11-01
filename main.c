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
    
    printf("How Many Items Will You Be Ordering Today?");
    scanf("%d",&order);
    int all_orders[order];          

    for(i = 0 ; i < order ; i++){               //a for loop so itll loop until the amount of food items is required.
        if (i == 1)
        {
            printf("Enter Your Food Item Order: %s");
        }
        
    }

    //This Is The Where The Database gets Connected And It Will Store The Data Inside The tables
    MYSQL *conn;
    conn = mysql_init(NULL);


}