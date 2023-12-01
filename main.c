#include <stdio.h>
#include <unistd.h>
#include <mysql.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <cups/cups.h>


void printBill(const char *customerName, const char *orderList, const char *quantityList, float totalCost) {
    if (cupsInit(NULL, NULL) == 0) {
        cupsSetUser("nav"); // Replace "username" with your system username
        const char *title ="Bill Print Job";
        int num_options = 0;
        cups_option_t *options = NULL;

        int jobId = cupsCreateJob(CUPS_HTTP_DEFAULT, "bill","bill", num_options, options);

        if (jobId) {
            cupsStartDocument(CUPS_HTTP_DEFAULT, "Bill Print Job", jobId, CUPS_FORMAT_AUTO, num_options,options);

            char billContent[255];
            snprintf(billContent, sizeof(billContent),
                     "Customer Name: %s\nOrder List: %s\nQuantities: %s\nTotal Cost: %.2f Rs",
                     customerName, orderList, quantityList, totalCost);

            cupsWriteRequestData(CUPS_HTTP_DEFAULT, billContent, strlen(billContent));
            cupsFinishDocument(CUPS_HTTP_DEFAULT, "Bill Print Job");
            cupsFinishJob(CUPS_HTTP_DEFAULT, jobId);
        } else {
            fprintf(stderr, "Failed to create a print job\n");
        }
        cupsFreeDests(0, NULL);
        cupsSetUser(NULL);
        cupsUnInit();
    } else {
        fprintf(stderr, "Failed to initialize CUPS\n");
    }
}


//This Code Is Assuming Youre Going To Do This For A Small Scale Cafe Or Something Similar

struct FoodItem {                           
    char name[50];
    int price;                    //A Structure Is Made In Which The Name And Prices Of The Food Will Be Stored and Billed
};

int main(int argv , char *argc){
    int order,i;
    struct FoodItem Menu[] =    //Array Is Initialized In Which The Prices And Name Of It Will Be Declared And Initialized
    {
        {"Burger" , 110 } ,
        {"Pizza" , 150 },
        {"CocaCola" , 25 },
        {"FrenchFries" , 70 },
        {"GrilledCheese" , 120 },
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

    }
    getchar();
    printf("Is This Correct?(y/n) ");
   
    scanf("%c", &option);
    
    option = tolower(option);
    int num;

    if (option == 'y')
    {
        printf("Great!");
    }
    else
    {
        printf("Let's Fix The Error!\n");
        printf("Do You Want To Change A Specific Order Or Do The Order All Over Again?(1/2)[1 - Specific Order \n2 - Complete Again.]");
        scanf("%d" , &num);

        if (num == 1){
          for (i = 0; i < order; i++){
            printf("%d. %s ------ %d\n"), i+1 , all_orders[i],quantity[i]);
          } 
          printf("Which Order Do You Want To Change?")
          scanf("%d" , &num);
          printf("What Do You Want Instead Of it?");
          scanf("%c" , &all_orders[num-1]);
        }
        else {
        printf("Restarting Order.");
        goto order_part;
      free(all_orders[]);
        }
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
    getchar();
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

    printf("\nCalculating Total Price....");
    sleep(2);

    printf("\nTotal Cost: %.2f Rs\n", total_cost);

    mysql_library_init(0, NULL, NULL);

     // MySQL database connection
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        mysql_library_end(); // Cleanup MySQL library
        return 1;
    }
   
//     if (mysql_options(conn, MYSQL_OPT_SSL_MODE, "DISABLED") != 0) {
//     fprintf(stderr, "mysql_options(MYSQL_OPT_SSL_MODE) failed: %s\n", mysql_error(conn));
//     mysql_close(conn);
//     return 1;
// }

    if (mysql_real_connect(conn, "localhost", "root", "P@ssw0rd123!", "billing_db", 3306, NULL, 0) == NULL) {
    fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
    mysql_close(conn);
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
    }

    // Close the database connection
    mysql_close(conn);

    // Cleanup MySQL library
    mysql_library_end();



    printBill(customer_name, all_orders,quantity,total_cost);
    sleep(2);

    printf("Thank You For Choosing Us!!");
    sleep(2);
    exit;
    
}
