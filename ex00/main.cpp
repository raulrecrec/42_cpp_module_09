/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 13:10:49 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/07 01:54:26 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <exception>

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./btc input.txt" << std::endl;
		return (1);
	}

	try
	{
		BitcoinExchange	exchange("data.csv");
		exchange.process_input(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}