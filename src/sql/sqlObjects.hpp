#ifndef SQL_OBJECTS_HPP
#define SQL_OBJECTS_HPP

#include "sqlRawToDate.hpp"

#include </usr/include/mysql-cppconn/mysqlx/xdevapi.h>
#include </usr/include/mysql-cppconn/mysql/jdbc.h>

#include <chrono>
//#include <compare>
#include <optional>
#include <string>


struct Business
{
public:
	Business() = default;
	Business(const int businessID,
		const int customerID,
		const std::string& businessName,
		const std::optional<std::string> taxNumber,
		const std::optional<std::string> notes)
		: BusinessID{ businessID },
		CustomerID{ customerID },
		BusinessName{ businessName },
		TaxNumber{ taxNumber },
		Notes{ notes }
	{ }
	Business(const mysqlx::Row& row)
		: BusinessID{ static_cast<int>(row[0]) },
		CustomerID{ static_cast<int>(row[1]) },
		BusinessName{ static_cast<std::string>(row[2]) },
		TaxNumber{ row[3].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[3]) } },
		Notes{ row[4].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[4]) } }
	{ }

	int								BusinessID = 0;
	int								CustomerID = 0;
	std::string						BusinessName;
	std::optional<std::string>		TaxNumber;
	std::optional<std::string>		Notes;
	auto operator<=>(const Business&) const = default;
};

struct Customer
{
public:
	Customer() = default;
	Customer(const int customerID,
		const std::string& firstName,
		const std::optional<std::string> middleName,
		const std::optional<std::string> lastName,
		const std::optional<std::string> notes)
		: CustomerID{ customerID },
		FirstName{ firstName },
		MiddleName{ middleName },
		LastName{ lastName },
		Notes{ notes }
	{ }
	Customer(const mysqlx::Row& row)
		: CustomerID{ static_cast<int>(row[0]) },
		FirstName{ static_cast<std::string>(row[1]) },
		MiddleName{ row[2].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[2]) } },
		LastName{ row[3].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[3]) } },
		Notes{ row[4].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[4]) } }
	{ }

	int								CustomerID{ 0 };
	std::string						FirstName;
	std::optional<std::string>		MiddleName;
	std::optional<std::string>		LastName;
	std::optional<std::string>		Notes;
	auto operator<=>(const Customer&) const = default;
};

// Email table contains no nullable fields.
struct Email
{
public:
	Email() = default;
	Email(const int emailID,
		const int customerID,
		const std::string& emailAddress,
		const bool preferred)
		: EmailID{ emailID },
		CustomerID{ customerID },
		EmailAddress{ emailAddress },
		Preferred{ preferred }
	{ }
	Email(const mysqlx::Row& row)
		: EmailID{ static_cast<int>(row[0]) },
		CustomerID{ static_cast<int>(row[1]) },
		EmailAddress{ static_cast<std::string>(row[2]) },
        Preferred{ static_cast<bool>(row[3]) }
	{ }

	int				EmailID{ 0 };
	int				CustomerID{ 0 };
	std::string		EmailAddress;
	bool			Preferred{ false };
	auto operator<=>(const Email&) const = default;
};

struct Invoice
{
	Invoice() = default;
	Invoice(const int invoiceID,
		const int customerID,
		const int vehicleID,
		const std::string& invoiceType,
		const std::chrono::year_month_day dateOpened,
		const std::optional<std::chrono::year_month_day> dateClosed,
		const std::optional<int> odometer,
		const std::optional<float> hourMeter,
		const std::string& request,
		const std::optional<std::string> workPerformed)
		: InvoiceID{ invoiceID },
		CustomerID{ customerID },
		VehicleID{ vehicleID },
		InvoiceType{ invoiceType },
		DateOpened{ dateOpened },
		DateClosed{ dateClosed },
		Odometer{ odometer },
		HourMeter{ hourMeter },
		Request{ request },
		WorkPerformed{ workPerformed }
	{ }
	Invoice(const mysqlx::Row& row)
		: InvoiceID{ static_cast<int>(row[0]) },
		CustomerID{ static_cast<int>(row[1]) },
		VehicleID{ static_cast<int>(row[2]) },
		InvoiceType{ static_cast<std::string>(row[3]) },
		DateOpened{ mysqlx::toYearMonthDay(row[4]) },
		DateClosed{ row[5].isNull() ? std::nullopt :
			std::optional<std::chrono::year_month_day>{ mysqlx::toYearMonthDay(row[5]) } },
		Odometer{ row[6].isNull() ? std::nullopt : std::optional<int>{ static_cast<int>(row[6]) } },
		HourMeter{ row[7].isNull() ? std::nullopt : std::optional<float>{ row[7] } },
		Request{ static_cast<std::string>(row[8]) },
		WorkPerformed{ row[9].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[9]) } }
	{ }

	int											InvoiceID{ 0 };
	int											CustomerID{ 0 };
	int											VehicleID{ 0 };
	std::string									InvoiceType;
	std::chrono::year_month_day					DateOpened;
	std::optional<std::chrono::year_month_day>	DateClosed{ std::nullopt };
	std::optional<int>							Odometer{ std::nullopt };
	std::optional<float>						HourMeter{ std::nullopt };
	std::string									Request;
	std::optional<std::string>					WorkPerformed{ std::nullopt };
	auto operator<=>(const Invoice&) const = default;
};

// Labor table contains no nullable fields.
struct Labor
{
	Labor() = default;
	Labor(const int laborID,
		const int invoiceID,
		const int vehicleID,
		const int position,
		const double quantity,
		const std::string& laborDescription,
		const double rate)
		: LaborID{ laborID },
		InvoiceID{ invoiceID },
		VehicleID{ vehicleID },
		Position{ position },
		Quantity{ quantity },
		LaborDescription{ laborDescription },
		Rate{ rate }
	{ }
	Labor(const mysqlx::Row& row)
		: LaborID{ static_cast<int>(row[0]) },
		InvoiceID{ static_cast<int>(row[1]) },
		VehicleID{ static_cast<int>(row[2]) },
		Position{ static_cast<int>(row[3]) },
		Quantity{ static_cast<double>(row[4]) },
		LaborDescription{ static_cast<std::string>(row[5]) },
		Rate{ static_cast<double>(row[6]) }
	{ }

	int				LaborID{ 0 };
	int				InvoiceID{ 0 };
	int				VehicleID{ 0 };
	int				Position{ 0 };
	double			Quantity{ 0.0 };
	std::string		LaborDescription;
	double			Rate{ 0.0 };
	auto operator<=>(const Labor&) const = default;
};

// Parts table contains no nullable fields.
struct Part
{
public:
	Part() = default;
	Part(const int partID,
		const int invoiceID,
		const int vehicleID,
		const int position,
		const double quantity,
		const std::string& partDescription,
		const std::string& vendor,
		const std::string& partNumber,
		const double purchaseCost,
		const double retailPrice)
		: PartID{ partID },
		InvoiceID{ invoiceID },
		VehicleID{ vehicleID },
		Position{ position },
		Quantity{ quantity },
		PartDescription{ partDescription },
		Vendor{ vendor },
		PartNumber{ partNumber },
		PurchaseCost{ purchaseCost },
		RetailPrice{ retailPrice }
	{ }
	Part(const mysqlx::Row& row)
		: PartID{ static_cast<int>(row[0]) },
		InvoiceID{ static_cast<int>(row[1]) },
		VehicleID{ static_cast<int>(row[2]) },
		Position{ static_cast<int>(row[3]) },
		Quantity{ static_cast<double>(row[4]) },
		PartDescription{ static_cast<std::string>(row[5]) },
		Vendor{ static_cast<std::string>(row[6]) },
		PartNumber{ static_cast<std::string>(row[7]) },
		PurchaseCost{ static_cast<double>(row[8]) },
		RetailPrice{ static_cast<double>(row[9]) }
	{ }

	int				PartID{ 0 };
	int				InvoiceID{ 0 };
	int				VehicleID{ 0 };
	int				Position{ 0 };
	double			Quantity{ 0.0 };
	std::string		PartDescription;
	std::string		Vendor;
	std::string		PartNumber;
	double			PurchaseCost{ 0.0 };
	double			RetailPrice{ 0.0 };
	auto operator<=>(const Part&) const = default;
};

struct Phone
{
	Phone() = default;
	Phone(const int phoneID,
		const int customerID,
		const std::string phoneNumber,
		const std::optional<std::string> extension,
		const std::string& phoneType,
		const bool preferred)
		: PhoneID{ phoneID },
		CustomerID{ customerID },
		PhoneNumber{ phoneNumber },
		Extension{ extension },
		PhoneType{ phoneType },
		Preferred{ preferred }
	{ }
	Phone(const mysqlx::Row& row)
		: PhoneID{ static_cast<int>(row[0]) },
		CustomerID{ static_cast<int>(row[1]) },
		PhoneNumber{ static_cast<std::string>(row[2]) },
		Extension{ row[3].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[3]) } },
		PhoneType{ static_cast<std::string>(row[4]) },
		Preferred{ static_cast<bool>(row[5]) }
	{ }

	int					        PhoneID{ 0 };
	int					        CustomerID{ 0 };
    std::string			        PhoneNumber{ 0 };
	std::optional<std::string>	Extension{ std::nullopt };
	std::string			        PhoneType;
	bool				        Preferred{ false };
	auto operator<=>(const Phone&) const = default;
};

struct Vehicle
{
	Vehicle() = default;
	Vehicle(const int vehicleID,
		const int customerID,
		const std::optional<std::string> vin,
		const std::optional<std::string> licenseNumber,
		const std::optional<std::chrono::year> year,
		const std::optional<std::string> make,
		const std::optional<std::string> model,
		const std::optional<std::string> trimLevel,
		const std::string& driveType,
		const std::string& fuelType,
		const std::optional<std::string> engine,
		const std::optional<std::string> notes)
		: VehicleID{ vehicleID },
		CustomerID{ customerID },
		VIN{ vin },
		LicenseNumber{ licenseNumber },
		Year{ year },
		Make{ make },
		Model{ model },
		TrimLevel{ trimLevel },
		DriveType{ driveType },
		FuelType{ fuelType },
		Engine{ engine },
		Notes{ notes }
	{ }
	Vehicle(const mysqlx::Row& row)
		: VehicleID{ static_cast<int>(row[0]) },
		CustomerID{ static_cast<int>(row[1]) },
		VIN{ row[2].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[2]) } },
		LicenseNumber{ row[3].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[3]) } },
		Year{ row[4].isNull() ? std::nullopt : std::optional<std::chrono::year>{ static_cast<std::chrono::year>(row[4]) }},
		Make{ row[5].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[5]) } },
		Model{ row[6].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[6]) } },
		TrimLevel{ row[7].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[7]) } },
		DriveType{ static_cast<std::string>(row[8]) },
		FuelType{ static_cast<std::string>(row[9]) },
		Engine{ row[10].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[10]) } },
		Notes{ row[11].isNull() ? std::nullopt : std::optional<std::string>{ static_cast<std::string>(row[11]) } }
	{ }

	int									VehicleID{ 0 };
	int									CustomerID{ 0 };
	std::optional<std::string>			VIN{ std::nullopt };
	std::optional<std::string>			LicenseNumber{ std::nullopt };
	std::optional<std::chrono::year>	Year{ std::nullopt };
	std::optional<std::string>			Make{ std::nullopt };
	std::optional<std::string>			Model{ std::nullopt };
	std::optional<std::string>			TrimLevel{ std::nullopt };
	std::string							DriveType;
	std::string							FuelType;
	std::optional<std::string>			Engine{ std::nullopt };
	std::optional<std::string>			Notes{ std::nullopt };
	auto operator<=>(const Vehicle&) const = default;
};

#endif

