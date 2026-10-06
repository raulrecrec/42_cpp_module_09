/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 13:10:45 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/07 01:53:35 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class	BitcoinExchange
{
	private:
		std::map<std::string, double>	database;

		bool	is_valid_date(const std::string &date) const;
		bool	is_valid_value(const std::string &value) const;
		bool	parse_entry(const std::string &line, const std::string &delimiter, std::string &date, std::string &value_str) const;
		void	parse_database(const std::string &filename);

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange(const std::string &filename);
		BitcoinExchange	&operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void	process_input(const std::string &filename);
};

#endif