#include <stdio.h>
#include<mysql.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


//This Code Is Assuming Youre Going To Do This For A Small Scale Cafe Or Something Similar

struct FoodItem {                           
    char name[50];
    int price;                    //A Structure Is Made In Which The Name And Prices Of The Food Will Be Stored and Billed
};

int main(){
    int order,i;
    struct FoodItem Menu[] =    //Array Is Initialized In Which The Prices And Name Of It Will Be Declared And Initialized
    {
        {"Burger" , 110 } ,
        {"Pizza" , 150 },
        {"Coca Cola" , 25 },
        {"French Fries" , 70 },
        {"Grilled Cheese" , 120 },
    };

    int menu_items = sizeof(Menu)/sizeof(Menu[0]);

    for(i = 0;i<menu_items;i++){
        printf("%s ---- %d Rs\n" , Menu[i].name , Menu[i].price);
    }
    order_part:
    printf("How Many Items Will You Be Ordering Today? ");
    scanf("%d",&order);
    if (order < 1)
    {
        printf("Have A Nice Day!");
        return  0;
    }
    
    char all_orders[order][255];  
    int quantity[order];        

    for(i = 0 ; i < order ; i++){               //a for loop so itll loop until the amount of food items is required.
        if (i+1 == 1)
        {
            printf("Enter Your 1st Food Item Order: ");
            scanf("%s", &all_orders[i]);
            printf("Enter The Quantity: ");
            scanf("%s", &quantity[i]);
        }
        else  if (i+1 == 2){
            printf("Enter Your 2nd Food Item Order: ");
            scanf("%s" , &all_orders[i]);
            printf("Enter The Quantity: ");
            scanf("%s", &quantity[i]);
        }

        else if (i+1 > 2){
            printf("Enter your %dth Food Item Order: ", i+1);
            scanf("%s", &all_orders[i]);
            printf("Enter The Quantity: ");
            scanf("%s", &quantity[i]);
        }
        
    }
    int  item_index = -1;
    int j;
    int item_found = 0;

    for ( j = 0; j < order; j++)
    {
        for (i = 0; i < order; i++)
    {
        if (strcmp(all_orders[j], Menu[i].name) == 0)
    {
      printf("Hello World!");
    }
    }
    }
    char option;

    printf("This Is Your Order List:\n");

    for(i = 0; i< order; i++){
        printf("%d. %s\n", i+1 ,all_orders[i]);
    }
    getchar();
    printf("Is This Correct?(y/n) ");
   
    scanf("%c", &option);
    
    option = tolower(option);

    if (option == 'y')
    {
        printf("Great!");
    }
    else
    {
        printf("Let's Fix The Error!\n");
        goto order_part;
    }
    //Asks Customer For Their Name
    char customer_name[255];
    name_label:
    getchar();
    printf("\nPlease Enter Your Full Name: ");
    fgets(customer_name, sizeof(customer_name), stdin);
    customer_name[strlen(customer_name)-1] = '\0';

    printf("Is the Entered Name Correct(y/n): %s  ", customer_name);
    scanf("%c", &option);

    option = tolower(option);
    if (option =='y')
    {
        printf("Great!");
    }
    else{
        printf("Lets Fix The Errors.\n");
        goto name_label;
    }
    
    float total_cost;
    for ( i = 0; i < order; i++)
    {
        total_cost += quantity[i];
    }
    


    MYSQL *conn =  mysql_init(NULL);

    if (conn  == NULL){
        fprintf(stderr , "MySQL Initialization Failed");
        mysql_close(conn);
        return 0;
    }

    if (mysql_real_connect(conn,"localhost","root","navaneeth69420112233@","billing_db",0,NULL,0) == NULL)
    {
        fprintf(stderr,"MYSQL Real Connect Failed");
        return 0;
    }

    char query[256];
    for (i = 0; i < order; i++)
    {
        sprintf(query, "INSERT INTO billing_records(customer_name, item_orders, quantity, total_cost) VALUES ('%s', '%s', '%d', '%.2f')", customer_name , all_orders[i]);
    }
    
    
    
}