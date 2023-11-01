CREATE  DATABASE IF NOT EXISTS USE billing_db;

USE billing_db;

CREATE TABLE IF NOT EXISTS customers(
    id INT AUTO_INCREMENT PRIMARY KEY,
    customer_name varchar[50],

)

CREATE TABLE IF NOT EXISTS orders(
    order_id INT AUTO_INCREMENT PRIMARY KEY;
    customer_id INT;
    item_name varchar(100);
    quantity INT;
    
)