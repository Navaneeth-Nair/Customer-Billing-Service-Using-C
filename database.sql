CREATE  DATABASE IF NOT EXISTS billing_db;

USE billing_db;

CREATE TABLE IF NOT EXISTS customers(
    id INT AUTO_INCREMENT PRIMARY KEY,
    customer_name VARCHAR(50)

);

CREATE TABLE IF NOT EXISTS billing_records(
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT,
    item_names VARCHAR(100),
    quantity INT,
    total_cost DECIMAL(10,2),
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (customer_id) REFERENCES customers(id)
);