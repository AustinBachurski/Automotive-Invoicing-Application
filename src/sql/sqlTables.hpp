#ifndef SQL_TABLES_HPP
#define SQL_TABLES_HPP

#include <stdexcept>
#include <string>

enum class Table
{
	Business,
	Customer,
	Email,
	Invoice,
	Labor,
	Parts,
	Phone,
	Vehicle,
};

enum class Field
{
	CustomerID,
	InvoiceID,
	VehicleID,
	FirstName,
	LastName,
};

namespace sql
{
	std::string asString(Table value)
	{
		switch (value)
		{
		case Table::Business:
			return "Business";

		case Table::Customer:
			return "Customer";

		case Table::Email:
			return "Email";

		case Table::Invoice:
			return "Invoice";

		case Table::Labor:
			return "Labor";

		case Table::Parts:
			return "Parts";

		case Table::Phone:
			return "Phone";

		case Table::Vehicle:
			return "Vehicle";
		}
		throw std::invalid_argument("Missing enum case for [Table].");
	}

	std::string asString(Field field)
	{
		switch (field)
		{
		case Field::CustomerID:
			return "CustomerID";

		case Field::InvoiceID:
			return "InvoiceID";

		case Field::VehicleID:
			return "VehicleID";

		case Field::FirstName:
			return "FirstName";

		case Field::LastName:
			return "LastName";
		}
		throw std::invalid_argument("Missing enum case for [Field].");
	}
};

#endif

