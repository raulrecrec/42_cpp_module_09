/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 20:12:12 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/15 06:55:50 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <exception>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	PmergeMe		sorter;
	struct timeval	start;
	struct timeval	end;
	double			vector_time_elapsed;
	double			deque_time_elapsed;
	int				i;

	try
	{
		sorter.parse_arguments(argc, argv);

		std::cout << "Before: ";
		i = 1;
		while (i < argc)
		{
			std::cout << argv[i] << " ";
			i++;
		}
		std::cout << std::endl;

		gettimeofday(&start, NULL);
		sorter.sort_vector();
		gettimeofday(&end, NULL);
		vector_time_elapsed = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

		gettimeofday(&start, NULL);
		sorter.sort_deque();
		gettimeofday(&end, NULL);
		deque_time_elapsed = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

		std::cout << "After: ";
		sorter.print_sorted();

		std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector --> " << vector_time_elapsed << " us" << std::endl;
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque --> " << deque_time_elapsed << " us" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}