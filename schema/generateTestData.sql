USE UnitTesting;

INSERT INTO Customer (FirstName, MiddleName, LastName, Notes)
VALUES
    ('Testy', 'Mc', 'Testerton', 'Can get a little testy at times...'),
    ('Minimalist', NULL, NULL, NULL),
    ('Normalist', NULL, 'Normie', NULL),
    ('Maximus', 'Entrius', 'Ineverius', 'Fieldius');

INSERT INTO Business (CustomerID, BusinessName, TaxNumber, Notes)
VALUES
    (1, 'Seriously Interesting LLC.', NULL, NULL),
    (4, 'Entitled Inc.', 'Tax', 'Just a front.'),
    (4, 'Overly Entitled Inc.', 'Evasion', 'For money laundering.');

INSERT INTO Email (CustomerID, EmailAddress, Preferred)
VALUES
    (3, 'ordinary@average.guy', FALSE),
    (4, 'moar@stufffor.me', TRUE),
    (4, 'less@stufffor.me', FALSE);

INSERT INTO Phone (CustomerID, PhoneNumber, Extension, PhoneType, Preferred)
VALUES
    (1, '3038675309', NULL, 'Landline', FALSE),
    (3, '1112223334', NULL, 'Cell', FALSE),
    (4, '9876543210', '123', 'Landline', TRUE),
    (4, '1234567890', NULL, 'Cell', FALSE);

INSERT INTO Vehicle (CustomerID, VIN, LicenseNumber, `Year`, Make, Model, TrimLevel, DriveType, FuelType, Engine, Notes)
VALUES 
    (1, 'JT3HM84R9X1234567', 'E-E1B2C', 1999, 'Toyota', '4Runner', 'SR5', 'AWD', 'Gasoline', '2.7 L 2694 CC L4 DOHC', NULL),
    (2, NULL, NULL, NULL, NULL, NULL, NULL, 'N/A', 'N/A', NULL, NULL),
    (3, '3D7MX38A17G123456', '7T-865AB', 2007, 'Dodge', 'Ram 3500HD', 'Laramie', '4WD', 'Diesel', '6.7 L 408 CID L6 Cummins ISB-07 Diesel', 'Land Shark'),
    (4, 'WDDGF54X08F123456', 'SPECIAL', 2008, 'Mercedes', 'C300', '4Matic', 'RWD', 'Electric', 'Dual Motor', 'More money than brains.'),
    (4, '1G6KH5EY0AU123456', 'SLOWAF', 2010, 'Cadillac', 'DTS', 'PREMIUM', 'FWD', 'Propane/Natural Gas', '4.6 L 281 CID V8 DOHC 32 Valve Northstar', NULL);

INSERT INTO Invoice (CustomerID, VehicleID, InvoiceType, DateOpened, DateClosed, Odometer, HourMeter, Request, WorkPerformed)
VALUES
    (1, 1, 'Quotation', '2024-06-15', NULL, 123456, NULL, 'Quote for fuel level sensor.', NULL),
    (2, 2, 'Invoice', '2020-01-01', '2020-01-02', 123, 12, 'Do as little as possible.', 'Did practically nothing.'),
    (3, 3, 'Invoice', '2023-05-25', '2023-06-18', 379877, 5388.6, 'Do things as if you were doing things.', 'Did many things, but did actually do things?  Never know...'),
    (4, 4, 'Quotation', '2010-11-12', NULL, NULL, 1236.0, 'Just a quote', NULL),
    (4, 5, 'Invoice', '2018-12-06', '2018-12-08', 87654, NULL, 'Iz broke, plox fix.', 'Fixed brokies, or something, idk.');

INSERT INTO Parts (InvoiceID, VehicleID, Position, Quantity, PartDescription, Vendor, PartNumber, PurchaseCost, RetailPrice)
VALUES
    (1, 1, 1, 1, 'Fuel Pump Assembly', 'OhReally', 'A4Z154', 316.99, 380.39),
    (3, 3, 1, 6, 'Spark Plug', 'No Auto Parts Available', 'P3000', 8.99, 12.57),
    (3, 3, 2, 1, 'Serpentine Belt', 'Horrible Service', 'PK8199', 35.88, 50.55),
    (4, 4, 1, 10, '15w-40 Engine Oil', 'Questing', 'JOOS', 12.56, 14.99),
    (4, 4, 2, 1, 'Earl Feelter', 'Questing', '55144', 14.99, 18.56),
    (5, 5, 1, 1, 'Trans Filter', 'Warehouse', 'TF6623', 86.33, 99.00),
    (5, 5, 2, 8, 'Trans Fluid', 'Warehouse', 'LQID', 6.99, 8.12),
    (5, 5, 3, 4, 'Tires', 'Rack', 'RUBR', 115.86, 145.99),
    (5, 5, 4, 4, 'Wheels', 'Rack', 'ALMNM', 117.89, 199.99);

INSERT INTO Labor (InvoiceID, VehicleID, Position, Quantity, LaborDescription, Rate)
VALUES
    (1, 1, 1, 2.2, 'Fuel Pump - Remove & Replace', 100.00),
    (3, 3, 1, 1.5, 'Spark Plugs - Remove & Replace, ALL', 100.00),
    (3, 3, 2, .5, 'Combination - Spark Plug Wires - Remove & Replace', 100.00),
    (4, 4, 1, 6, 'Install Belt', 100.00),
    (4, 4, 2, 0, 'Freebie', 100.00),
    (5, 5, 1, 10, 'Replace Everything', 100.00);

