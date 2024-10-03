#ifndef SQL_QUERIES_HPP
#define SQL_QUERIES_HPP

#include "sqlTables.hpp"

#include </usr/include/mysql-cppconn/mysqlx/xdevapi.h>
#include </usr/include/mysql-cppconn/mysql/jdbc.h>

#include <string>
#include <vector>


#include <ranges>
#include <iostream>


class QueryData 
{
public:
	QueryData(const Table table, const Field field, const std::string string)
		: m_table{ table },
		m_field{ field },
		m_ID{ '\'' + string + '\'' }
	{ }
	QueryData(const Table table, const Field field, const int ID)
		: m_table{ table },
		m_field{ field },
		m_ID{ std::to_string(ID) }
	{ }

	operator std::string() const
	{
		return "SELECT * FROM " + sql::asString(m_table)
			+ " WHERE " + sql::asString(m_field)
			+ " = " + m_ID + ';';
	}

private:
	Table m_table;
	Field m_field;
	std::string m_ID;
};

// Query Templates
template<typename T>
T queryDatabaseFor(mysqlx::Session& db, const QueryData& query)
	requires std::constructible_from<T, mysqlx::Row>
{
	try
	{
		auto result = db.sql(static_cast<std::string>(query)).execute();
		return { result.fetchOne() };
	}
	catch (const mysqlx::Error& err)
	{
		std::cerr << "MySqlConnector Error: " << err.what() << std::endl;
		return {};
	}
}

template<typename T>
std::vector<T> queryDatabaseForVecOf(mysqlx::Session& db, const QueryData& query)
	requires std::constructible_from<T, mysqlx::Row>
{
	try
	{
		auto result = db.sql(static_cast<std::string>(query)).execute();

		std::vector<T> values;
		values.reserve(result.count());

		for (const auto& row : result)
		{
			values.emplace_back(row);
		}

		return values;
	}
	catch (const mysqlx::Error& err)
	{
		std::cerr << "MySqlConnector Error: " << err.what() << std::endl;
		return {};
	}
}

#endif

