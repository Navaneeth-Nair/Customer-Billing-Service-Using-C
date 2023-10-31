CREATE  DATABASE IF NOT EXISTS USE billing_db;

USE billing_db;

CREATE TABLE IF NOT EXISTS billing_records(
    id INT AUTO_INCREMENT PRIMARY KEY,
    customer_name varchar[50],
    quantity INT;
    total_cost DECIMAL,
    transaction_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP

)