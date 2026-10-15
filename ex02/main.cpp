/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 20:12:12 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/15 05:37:31 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <exception>

int	main(int argc, char **argv)
{
	PmergeMe	sorter;

	try
	{
		sorter.parse_arguments(argc, argv);
		sorter.sort_vector();
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	sorter.print_vector_deque();
	return (0);
}