#include <stdio.h>
#include <mysql.h>
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
            scanf("%d", &quantity[i]);
        }
        else  if (i+1 == 2){
            printf("Enter Your 2nd Food Item Order: ");
            scanf("%s" , &all_orders[i]);
            printf("Enter The Quantity: ");
            scanf("%d", &quantity[i]);
        }

        else if (i+1 > 2){
            printf("Enter your %dth Food Item Order: ", i+1);
            scanf("%s", &all_orders[i]);
            printf("Enter The Quantity: ");
            scanf("%d", &quantity[i]);
        }
        
    }
        int item_index = -1;
        int j;
        int item_found = 0;

        for (j = 0; j < order; j++) {
            int found = 0; // Variable to track if the item was found

            for (i = 0; i < menu_items; i++) {
                if (strcmp(all_orders[j], Menu[i].name) == 0) {
                    item_index = i;
                    found = 1; // Set found to 1 when a match is found
                    break;
                }
            }

            if (!found) {
                printf("Item '%s' is not in the menu. Ignoring.\n", all_orders[j]);
                exit(1);
            }
        }
    char option;

    printf("This Is Your Order List:\n");

    for(i = 0; i< order; i++){
        printf("%d. %s ------ %d\n", i+1 ,all_orders[i] , quantity[i]);

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

    float total_cost = 0.0;

    for (i = 0; i < order; i++) {
        // Find the corresponding menu item's price
        int menu_item_index = -1;
        
        for (int j = 0; j < menu_items; j++) {
            if (strcmp(all_orders[i], Menu[j].name) == 0) {
                menu_item_index = j;
                break;
            }
        }

        if (menu_item_index != -1) {
            total_cost += Menu[menu_item_index].price * quantity[i];
        }
    }

    printf("Total Cost: %.2f Rs\n", total_cost);

    mysql_library_init(0, NULL, NULL);

     // MySQL database connection
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        mysql_library_end(); // Cleanup MySQL library
        return 1;
    }

    if (mysql_real_connect(conn, "localhost", "root", "navaneeth69420112233@", "billing_db", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        mysql_library_end(); // Cleanup MySQL library
        return 1;
    }

        // Execute SQL queries to insert order records into the 'billing_records' table
    char order_insert_query[255];
    for (i = 0; i < order; i++) {
        sprintf(order_insert_query, "INSERT INTO billing_records (customer_id, item_names, quantity, total_cost) VALUES (LAST_INSERT_ID(), '%s', %d, %.2f)",
                all_orders[i], quantity[i], Menu[i].price * quantity[i]);

        if (mysql_query(conn, order_insert_query)) {
            fprintf(stderr, "INSERT into billing_records failed: %s\n", mysql_error(conn));
        }

    // Close the database connection
    mysql_close(conn);

    // Cleanup MySQL library
    mysql_library_end();

    }
    return 0;
    }
}