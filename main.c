#include <stdio.h>
#include <mysql.h>


//This Code Is Assuming Youre Going To Do This For A Small Scale Cafe Or Something Similar

struct FoodItem {                           
    char name[50];
    float price;                    //A Structure Is Made In Which The Name And Prices Of The Food Will Be Stored and Billed
};

int main(){
    struct FoodItem Menu[] =    //Array Is Initialized In Which The Prices And Name Of It Will Be Declared And Initialized
    {
        {"Veg Burger" , 70 } ,
        {"Non Veg Burger" , 70 },
        {"Veg Pizza" , 70 },
        {"Margherita Pizza" , 119 },
        {"Tandoori Paneer Pizza" , 319 },
    };
    
}