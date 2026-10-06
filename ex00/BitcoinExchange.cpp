/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 13:10:47 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/07 01:56:30 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <cctype>

BitcoinExchange::BitcoinExchange()
	: database()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
	: database(other.database)
{
}

BitcoinExchange::BitcoinExchange(const std::string &filename)
{
	parse_database(filename);
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		this->database = other.database;

	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}


bool	BitcoinExchange::is_valid_date(const std::string &date) const
{
	if (date.size() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);

	size_t	i;

	i = 0;
	while (i < 10)
	{
		if (i != 4 && i != 7)
		{
			if (!std::isdigit(date[i]))
				return (false);
		}
		i++;
	}

	int	year;
	int	month;
	int	day;

	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return (false);

	if (month == 2)
	{
		if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
		{
			if (day < 1 || day > 29)
				return (false);
		}
		else
		{
			if (day < 1 || day > 28)
				return (false);
		}
	}

	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day < 1 || day > 30)
			return (false);
	}
	else if (month != 2)
	{
		if (day < 1 || day > 31)
			return (false);
	}

	return (true);
}

bool	BitcoinExchange::is_valid_value(const std::string &value) const
{
	if (value.empty())
		return (false);

	size_t		i;
	int		dot_count;
	bool	has_digit;

	i = 0;
	dot_count = 0;
	has_digit = false;

	if (value[0] == '-')
		i++;

	while (i < value.size())
	{
		if (value[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (false);
		}
		else
		{
			if (!std::isdigit(value[i]))
				return (false);
			else
				has_digit = true;
		}
		i++;
	}

	return (has_digit);
}

bool	BitcoinExchange::parse_entry(const std::string &line, const std::string &delimiter, std::string &date, std::string &value_str) const
{
	size_t	separator;

	separator = line.find(delimiter);
	if (separator == std::string::npos)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}

	date = line.substr(0, separator);
	value_str = line.substr(separator + delimiter.size());

	if (!is_valid_date(date) || !is_valid_value(value_str))
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}

	return (true);
}

void	BitcoinExchange::parse_database(const std::string &filename)
{
	std::ifstream	file(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");

	std::string	line;

	if (!std::getline(file, line) || line != "date,exchange_rate")
		throw std::runtime_error("Error: invalid database header.");

	std::string	date;
	std::string	value_str;
	double		value;

	while (std::getline(file, line))
	{
		if (parse_entry(line, ",", date, value_str))
		{
			value = std::strtod(value_str.c_str(), NULL);
			if (value < 0)
				std::cerr << "Error: bad input => " << line << std::endl;
			else
				database[date] = value;
		}
	}
}

void	BitcoinExchange::process_input(const std::string &filename)
{
	std::ifstream	file(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");

	std::string	line;

	if (!std::getline(file, line) || line != "date | value")
		throw std::runtime_error("Error: invalid input header.");

	std::string	date;
	std::string	value_str;
	double		value;

	std::map<std::string, double>::const_iterator	it;

	while (std::getline(file, line))
	{
		if (parse_entry(line, " | ", date, value_str))
		{
			value = std::strtod(value_str.c_str(), NULL);
			if (value < 0)
				std::cerr << "Error: not a positive number." << std::endl;
			else if (value > 1000)
				std::cerr << "Error: too large a number." << std::endl;
			else
			{
				it = database.upper_bound(date);
				if (it == database.begin())
					std::cerr << "Error: no exchange rate available for this date." << std::endl;
				else
				{
					it--;
					std::cout << date << " => " << value << " = " << value * it->second << std::endl;
				}
			}
		}
	}
}