#include "catch2/catch_test_macros.hpp"

#include "../src/sqlObjects.hpp"
#include "../src/sqlQueries.hpp"

#include </usr/include/mysql-cppconn/mysqlx/xdevapi.h>
#include </usr/include/mysql-cppconn/mysql/jdbc.h>

#include <array>
#include <cstdlib>
#include <utility>
#include <vector>

TEST_CASE("Query for Business Objects by CustomerID")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

	std::array<std::pair<int, std::vector<Business>>, 2> data{ {
		{ 1, { { 1, 1, "Seriously Interesting LLC.", std::nullopt, std::nullopt } } },
		{ 4, { { 2, 4, "Entitled Inc.", "Tax", "Just a front." },
			   { 3, 4, "Overly Entitled Inc.", "Evasion", "For money laundering." } } }
	} };

	REQUIRE(queryDatabaseForVecOf<Business>(session,
		{ Table::Business, Field::CustomerID, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseForVecOf<Business>(session,
		{ Table::Business, Field::CustomerID, data.at(1).first }) == data.at(1).second);
}

TEST_CASE("Query for Email Objects by CustomerID")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

	std::array<std::pair<int, std::vector<Email>>, 2> data{ {
		{ 3, { { 1, 3, "ordinary@average.guy", false } } },
		{ 4, { { 2, 4, "moar@stufffor.me", true },
			   { 3, 4, "less@stufffor.me", false } } }
	} };

	REQUIRE(queryDatabaseForVecOf<Email>(session,
		{ Table::Email, Field::CustomerID, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseForVecOf<Email>(session,
		{ Table::Email, Field::CustomerID, data.at(1).first }) == data.at(1).second);
}

TEST_CASE("Query for Phone Objects by CustomerID")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

	std::array<std::pair<int, std::vector<Phone>>, 3> data{ {
		{ 1, { { 1, 1, "3038675309", std::nullopt, "Landline", false } } },
		{ 3, { { 2, 3, "1112223334", std::nullopt, "Cell", false } } },
		{ 4, { { 3, 4, "9876543210", "123", "Landline", true },
			   { 4, 4, "1234567890", std::nullopt, "Cell", false } } }
	} };

	REQUIRE(queryDatabaseForVecOf<Phone>(session,
		{ Table::Phone, Field::CustomerID, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseForVecOf<Phone>(session,
		{ Table::Phone, Field::CustomerID, data.at(1).first }) == data.at(1).second);
	REQUIRE(queryDatabaseForVecOf<Phone>(session,
		{ Table::Phone, Field::CustomerID, data.at(2).first }) == data.at(2).second);
}

TEST_CASE("Query for Invoice by CustomerID")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

    std::array<std::pair<int, std::vector<Invoice>>, 4> data{ {
        { 1, { { 1, 1, 1, "Quotation", { std::chrono::year{ 2024 }/6/15 }, std::nullopt, 123456, std::nullopt, "Quote for fuel level sensor.", std::nullopt } } },
        { 2, { { 2, 2, 2, "Invoice", { std::chrono::year{ 2020 }/1/1 }, { std::chrono::year{ 2020 }/1/2 }, 123, 12.0f, "Do as little as possible.", "Did practically nothing." } } },
        { 3, { { 3, 3, 3, "Invoice", { std::chrono::year{ 2023 }/5/25 }, { std::chrono::year{ 2023 }/6/18 }, 379877, 5388.6f, "Do things as if you were doing things.", "Did many things, but did actually do things?  Never know..." } } },
        { 4, { { 4, 4, 4, "Quotation", { std::chrono::year{ 2010 }/11/12 }, std::nullopt, std::nullopt, 1236.0f, "Just a quote", std::nullopt },
               { 5, 4, 5, "Invoice", { std::chrono::year{ 2018 }/12/6 }, { std::chrono::year{ 2018 }/12/8 }, 87654, std::nullopt, "Iz broke, plox fix.", "Fixed brokies, or something, idk." } } }
    } };

	REQUIRE(queryDatabaseForVecOf<Invoice>(session,
		{ Table::Invoice, Field::CustomerID, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseForVecOf<Invoice>(session,
		{ Table::Invoice, Field::CustomerID, data.at(1).first }) == data.at(1).second);
	REQUIRE(queryDatabaseForVecOf<Invoice>(session,
		{ Table::Invoice, Field::CustomerID, data.at(2).first }) == data.at(2).second);
	REQUIRE(queryDatabaseForVecOf<Invoice>(session,
		{ Table::Invoice, Field::CustomerID, data.at(3).first }) == data.at(3).second);
}

TEST_CASE("Query for Invoice by InvoiceID")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

    std::array<std::pair<int, Invoice>, 5> data{ {
        { 1, { 1, 1, 1, "Quotation", { std::chrono::year{ 2024 }/6/15 }, std::nullopt, 123456, std::nullopt, "Quote for fuel level sensor.", std::nullopt } },
        { 2, { 2, 2, 2, "Invoice", { std::chrono::year{ 2020 }/1/1 }, { std::chrono::year{ 2020 }/1/2 }, 123, 12.0f, "Do as little as possible.", "Did practically nothing." } },
        { 3, { 3, 3, 3, "Invoice", { std::chrono::year{ 2023 }/5/25 }, { std::chrono::year{ 2023 }/6/18 }, 379877, 5388.6f, "Do things as if you were doing things.", "Did many things, but did actually do things?  Never know..." } },
        { 4, { 4, 4, 4, "Quotation", { std::chrono::year{ 2010 }/11/12 }, std::nullopt, std::nullopt, 1236.0f, "Just a quote", std::nullopt } },
        { 5, { 5, 4, 5, "Invoice", { std::chrono::year{ 2018 }/12/6 }, { std::chrono::year{ 2018 }/12/8 }, 87654, std::nullopt, "Iz broke, plox fix.", "Fixed brokies, or something, idk." } },
    } };

	REQUIRE(queryDatabaseFor<Invoice>(session,
		{ Table::Invoice, Field::InvoiceID, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseFor<Invoice>(session,
		{ Table::Invoice, Field::InvoiceID, data.at(1).first }) == data.at(1).second);
	REQUIRE(queryDatabaseFor<Invoice>(session,
		{ Table::Invoice, Field::InvoiceID, data.at(2).first }) == data.at(2).second);
	REQUIRE(queryDatabaseFor<Invoice>(session,
		{ Table::Invoice, Field::InvoiceID, data.at(3).first }) == data.at(3).second);
	REQUIRE(queryDatabaseFor<Invoice>(session,
		{ Table::Invoice, Field::InvoiceID, data.at(4).first }) == data.at(4).second);
}

TEST_CASE("Query for Vehicle by CustomerID")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

    std::array<std::pair<int, std::vector<Vehicle>>, 4> data{ {
        { 1, { { 1, 1, "JT3HM84R9X1234567", "E-E1B2C", std::chrono::year{ 1999 }, "Toyota", "4Runner", "SR5", "AWD", "Gasoline", "2.7 L 2694 CC L4 DOHC", std::nullopt } } },
        { 2, { { 2, 2, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, "N/A", "N/A", std::nullopt, std::nullopt } } },
        { 3, { { 3, 3, "3D7MX38A17G123456", "7T-865AB", std::chrono::year{ 2007 }, "Dodge", "Ram 3500HD", "Laramie", "4WD", "Diesel", "6.7 L 408 CID L6 Cummins ISB-07 Diesel", "Land Shark" } } },
        { 4, { { 4, 4, "WDDGF54X08F123456", "SPECIAL", std::chrono::year{ 2008 }, "Mercedes", "C300", "4Matic", "RWD", "Electric", "Dual Motor", "More money than brains." },
               { 5, 4, "1G6KH5EY0AU123456", "SLOWAF", std::chrono::year{ 2010 }, "Cadillac", "DTS", "PREMIUM", "FWD", "Propane/Natural Gas", "4.6 L 281 CID V8 DOHC 32 Valve Northstar", std::nullopt } } },
    } };

	REQUIRE(queryDatabaseForVecOf<Vehicle>(session,
		{ Table::Vehicle, Field::CustomerID, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseForVecOf<Vehicle>(session,
		{ Table::Vehicle, Field::CustomerID, data.at(1).first }) == data.at(1).second);
	REQUIRE(queryDatabaseForVecOf<Vehicle>(session,
		{ Table::Vehicle, Field::CustomerID, data.at(2).first }) == data.at(2).second);
	REQUIRE(queryDatabaseForVecOf<Vehicle>(session,
		{ Table::Vehicle, Field::CustomerID, data.at(3).first }) == data.at(3).second);
}

TEST_CASE("Query for Customer by CustomerID")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

	std::array<std::pair<int, Customer>, 4> data{ {
		{ 1, { 1, "Testy", "Mc", "Testerton", "Can get a little testy at times..." } },
		{ 2, { 2, "Minimalist", std::nullopt, std::nullopt, std::nullopt } },
		{ 3, { 3, "Normalist", std::nullopt, "Normie", std::nullopt } },
		{ 4, { 4, "Maximus", "Entrius", "Ineverius", "Fieldius" } }
	} };

	REQUIRE(queryDatabaseFor<Customer>(session,
		{ Table::Customer, Field::CustomerID, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseFor<Customer>(session,
		{ Table::Customer, Field::CustomerID, data.at(1).first }) == data.at(1).second);
	REQUIRE(queryDatabaseFor<Customer>(session,
		{ Table::Customer, Field::CustomerID, data.at(2).first }) == data.at(2).second);
	REQUIRE(queryDatabaseFor<Customer>(session,
		{ Table::Customer, Field::CustomerID, data.at(3).first }) == data.at(3).second);
}

TEST_CASE("Query for Customer by Name")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

	std::array<std::pair<std::string, Customer>, 4> data{ {
		{ "Testerton", {1, "Testy", "Mc", "Testerton", "Can get a little testy at times..."}},
		{ "Minimalist", {2, "Minimalist", std::nullopt, std::nullopt, std::nullopt}},
		{ "Normalist", {3, "Normalist", std::nullopt, "Normie", std::nullopt}},
		{ "Ineverius", {4, "Maximus", "Entrius", "Ineverius", "Fieldius"}}
	} };

	REQUIRE(queryDatabaseFor<Customer>(session,
		{ Table::Customer, Field::LastName, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseFor<Customer>(session,
		{ Table::Customer, Field::FirstName, data.at(1).first }) == data.at(1).second);
	REQUIRE(queryDatabaseFor<Customer>(session,
		{ Table::Customer, Field::FirstName, data.at(2).first }) == data.at(2).second);
	REQUIRE(queryDatabaseFor<Customer>(session,
		{ Table::Customer, Field::LastName, data.at(3).first }) == data.at(3).second);
}

TEST_CASE("Query for Part by InvoiceID")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

    std::array<std::pair<int, std::vector<Part>>, 4> data{ {
        { 1, { { 1, 1, 1, 1, 1, "Fuel Pump Assembly", "OhReally", "A4Z154", 316.99f, 380.39f } } },
        { 3, { { 2, 3, 3, 1, 6, "Spark Plug", "No Auto Parts Available", "P3000", 8.99f, 12.57f },
               { 3, 3, 3, 2, 1, "Serpentine Belt", "Horrible Service", "PK8199", 35.88f, 50.55f } } },
        { 4, { { 4, 4, 4, 1, 10, "15w-40 Engine Oil", "Questing", "JOOS", 12.56f, 14.99f },
               { 5, 4, 4, 2, 1, "Earl Feelter", "Questing", "55144", 14.99f, 18.56f } } },
        { 5, { { 6, 5, 5, 1, 1, "Trans Filter", "Warehouse", "TF6623", 86.33f, 99.00f },
               { 7, 5, 5, 2, 8, "Trans Fluid", "Warehouse", "LQID", 6.99f, 8.12f },
               { 8, 5, 5, 3, 4, "Tires", "Rack", "RUBR", 115.86f, 145.99f },
               { 9, 5, 5, 4, 4, "Wheels", "Rack", "ALMNM", 117.89f, 199.99f } } },
    } };

	REQUIRE(queryDatabaseForVecOf<Part>(session,
		{ Table::Parts, Field::InvoiceID, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseForVecOf<Part>(session,
		{ Table::Parts, Field::InvoiceID, data.at(1).first }) == data.at(1).second);
	REQUIRE(queryDatabaseForVecOf<Part>(session,
		{ Table::Parts, Field::InvoiceID, data.at(2).first }) == data.at(2).second);
	REQUIRE(queryDatabaseForVecOf<Part>(session,
		{ Table::Parts, Field::InvoiceID, data.at(3).first }) == data.at(3).second);
}

TEST_CASE("Query for Part by VehicleID")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

    std::array<std::pair<int, std::vector<Part>>, 4> data{ {
        { 1, { { 1, 1, 1, 1, 1, "Fuel Pump Assembly", "OhReally", "A4Z154", 316.99f, 380.39f } } },
        { 3, { { 2, 3, 3, 1, 6, "Spark Plug", "No Auto Parts Available", "P3000", 8.99f, 12.57f },
               { 3, 3, 3, 2, 1, "Serpentine Belt", "Horrible Service", "PK8199", 35.88f, 50.55f } } },
        { 4, { { 4, 4, 4, 1, 10, "15w-40 Engine Oil", "Questing", "JOOS", 12.56f, 14.99f },
               { 5, 4, 4, 2, 1, "Earl Feelter", "Questing", "55144", 14.99f, 18.56f } } },
        { 5, { { 6, 5, 5, 1, 1, "Trans Filter", "Warehouse", "TF6623", 86.33f, 99.00f },
               { 7, 5, 5, 2, 8, "Trans Fluid", "Warehouse", "LQID", 6.99f, 8.12f },
               { 8, 5, 5, 3, 4, "Tires", "Rack", "RUBR", 115.86f, 145.99f },
               { 9, 5, 5, 4, 4, "Wheels", "Rack", "ALMNM", 117.89f, 199.99f } } },
    } };

	REQUIRE(queryDatabaseForVecOf<Part>(session,
		{ Table::Parts, Field::VehicleID, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseForVecOf<Part>(session,
		{ Table::Parts, Field::VehicleID, data.at(1).first }) == data.at(1).second);
	REQUIRE(queryDatabaseForVecOf<Part>(session,
		{ Table::Parts, Field::VehicleID, data.at(2).first }) == data.at(2).second);
	REQUIRE(queryDatabaseForVecOf<Part>(session,
		{ Table::Parts, Field::VehicleID, data.at(3).first }) == data.at(3).second);
}

TEST_CASE("Query for Labor by InvoiceID")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

    std::array<std::pair<int, std::vector<Labor>>, 4> data{ {
        { 1, { { 1, 1, 1, 1, 2.2, "Fuel Pump - Remove & Replace", 100.00f } } },
        { 3, { { 2, 3, 3, 1, 1.5, "Spark Plugs - Remove & Replace, ALL", 100.00f },
               { 3, 3, 3, 2, .5, "Combination - Spark Plug Wires - Remove & Replace", 100.00f } } },
        { 4, { { 4, 4, 4, 1, 6, "Install Belt", 100.00f },
               { 5, 4, 4, 2, 0, "Freebie", 100.00f } } },
        { 5, { { 6, 5, 5, 1, 10, "Replace Everything", 100.00f } } },
    } };

	REQUIRE(queryDatabaseForVecOf<Labor>(session,
		{ Table::Labor, Field::InvoiceID, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseForVecOf<Labor>(session,
		{ Table::Labor, Field::InvoiceID, data.at(1).first }) == data.at(1).second);
	REQUIRE(queryDatabaseForVecOf<Labor>(session,
		{ Table::Labor, Field::InvoiceID, data.at(2).first }) == data.at(2).second);
	REQUIRE(queryDatabaseForVecOf<Labor>(session,
		{ Table::Labor, Field::InvoiceID, data.at(3).first }) == data.at(3).second);
}

TEST_CASE("Query for Labor by VehicleID")
{
	mysqlx::Session session("localhost", 33060, std::getenv("DBUN"), std::getenv("DBPW"), "UnitTesting");

    std::array<std::pair<int, std::vector<Labor>>, 4> data{ {
        { 1, { { 1, 1, 1, 1, 2.2, "Fuel Pump - Remove & Replace", 100.00f } } },
        { 3, { { 2, 3, 3, 1, 1.5, "Spark Plugs - Remove & Replace, ALL", 100.00f },
               { 3, 3, 3, 2, .5, "Combination - Spark Plug Wires - Remove & Replace", 100.00f } } },
        { 4, { { 4, 4, 4, 1, 6, "Install Belt", 100.00f },
               { 5, 4, 4, 2, 0, "Freebie", 100.00f } } },
        { 5, { { 6, 5, 5, 1, 10, "Replace Everything", 100.00f } } },
    } };

	REQUIRE(queryDatabaseForVecOf<Labor>(session,
		{ Table::Labor, Field::VehicleID, data.at(0).first }) == data.at(0).second);
	REQUIRE(queryDatabaseForVecOf<Labor>(session,
		{ Table::Labor, Field::VehicleID, data.at(1).first }) == data.at(1).second);
	REQUIRE(queryDatabaseForVecOf<Labor>(session,
		{ Table::Labor, Field::VehicleID, data.at(2).first }) == data.at(2).second);
	REQUIRE(queryDatabaseForVecOf<Labor>(session,
		{ Table::Labor, Field::VehicleID, data.at(3).first }) == data.at(3).second);
}

