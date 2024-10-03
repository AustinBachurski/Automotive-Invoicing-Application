--docker run --name <name> -p 3306:3306 -p 33060:33060 -e MYSQL_ROOT_PASSWORD=<password> -d mysql:latest
CREATE DATABASE UnitTesting;
USE UnitTesting;


CREATE TABLE Customer (
    CustomerID INT NOT NULL AUTO_INCREMENT,
    FirstName VARCHAR(25) NOT NULL,
    MiddleName VARCHAR(25),
    LastName VARCHAR(25),
    Notes VARCHAR(1000),
    PRIMARY KEY (CustomerID)
);

CREATE TABLE Business (
    BusinessID INT NOT NULL AUTO_INCREMENT,
    CustomerID INT NOT NULL,
    BusinessName VARCHAR(50) NOT NULL,
    TaxNumber VARCHAR(25),
    Notes VARCHAR(1000),
    PRIMARY KEY(BusinessID),
    FOREIGN KEY(CustomerID) REFERENCES Customer(CustomerID)
);

CREATE TABLE Phone (
    PhoneID INT NOT NULL AUTO_INCREMENT,
    CustomerID INT NOT NULL,
    PhoneNumber VARCHAR(25) NOT NULL,
    Extension VARCHAR(25),
    PhoneType ENUM('Landline', 'Cell') NOT NULL,
    Preferred BOOL NOT NULL DEFAULT 0,
    PRIMARY KEY(PhoneID),
    FOREIGN KEY(CustomerID) REFERENCES Customer(CustomerID)
);

CREATE TABLE Email (
    EmailID INT NOT NULL AUTO_INCREMENT,
    CustomerID INT NOT NULL,
    EmailAddress VARCHAR(50) NOT NULL,
    Preferred BOOL NOT NULL DEFAULT 0,
    PRIMARY KEY(EmailID),
    FOREIGN KEY(CustomerID) REFERENCES Customer(CustomerID)
);

CREATE TABLE Vehicle (
    VehicleID INT NOT NULL AUTO_INCREMENT,
    CustomerID INT NOT NULL,
    VIN VARCHAR(17),
    LicenseNumber VARCHAR(8),
    `Year` YEAR,
    Make VARCHAR(25),
    Model VARCHAR(25),
    TrimLevel VARCHAR(25),
    DriveType ENUM('FWD', 'RWD', 'AWD', '4WD', 'N/A') NOT NULL,
    FuelType ENUM('Gasoline', 'Diesel', 'Propane/Natural Gas', 'Electric', 'N/A') NOT NULL,
    Engine VARCHAR(50),
    Notes VARCHAR(1000),
    PRIMARY KEY(VehicleID),
    FOREIGN KEY(CustomerID) REFERENCES Customer(CustomerID)
);

CREATE TABLE Invoice (
    InvoiceID INT NOT NULL AUTO_INCREMENT,
    CustomerID INT NOT NULL,
    VehicleID INT NOT NULL,
    InvoiceType ENUM('Invoice', 'Quotation') NOT NULL,
    DateOpened DATE NOT NULL,
    DateClosed DATE,
    Odometer INT,
    HourMeter FLOAT(1),
    Request VARCHAR(1000) NOT NULL,
    WorkPerformed TEXT(65535),
    PRIMARY KEY(InvoiceID),
    FOREIGN KEY(CustomerID) REFERENCES Customer(CustomerID)
);

CREATE TABLE Parts (
    PartID INT NOT NULL AUTO_INCREMENT,
    InvoiceID INT NOT NULL,
    VehicleID INT NOT NULL,
    Position INT NOT NULL,
    Quantity DECIMAL(4, 2) NOT NULL,
    PartDescription VARCHAR(255) NOT NULL,
    Vendor VARCHAR(50) NOT NULL,
    PartNumber VARCHAR(50) NOT NULL,
    PurchaseCost FLOAT(2) NOT NULL,
    RetailPrice FLOAT(2) NOT NULL,
    PRIMARY KEY(PartID),
    FOREIGN KEY(InvoiceID) REFERENCES Invoice(InvoiceID),
    FOREIGN KEY(VehicleID) REFERENCES Vehicle(VehicleID)
);

CREATE TABLE Labor (
    LaborID INT NOT NULL AUTO_INCREMENT,
    InvoiceID INT NOT NULL,
    VehicleID INT NOT NULL,
    Position INT NOT NULL,
    Quantity FLOAT(1) NOT NULL,
    LaborDescription VARCHAR(255) NOT NULL,
    Rate FLOAT(2) NOT NULL,
    PRIMARY KEY(LaborID),
    FOREIGN KEY(InvoiceID) REFERENCES Invoice(InvoiceID),
    FOREIGN KEY(VehicleID) REFERENCES Vehicle(VehicleID)
);

