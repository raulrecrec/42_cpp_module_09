/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 20:08:34 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/10 18:44:10 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <iostream>

PmergeMe::PmergeMe()
	: vector(), deque()
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
	: vector(other.vector), deque(other.deque)
{
}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->vector = other.vector;
		this->deque = other.deque;
	}

	return (*this);
}

PmergeMe::~PmergeMe()
{
}

int	PmergeMe::parse_number(const std::string &argument) const
{
	if (argument.empty())
		throw std::runtime_error("Error");

	size_t	i;

	i = 0;
	if (argument[0] == '+')
		i++;
	if (i == argument.size())
		throw std::runtime_error("Error");

	while (i < argument.size())
	{
		if (!std::isdigit(argument[i]))
			throw std::runtime_error("Error");
		i++;
	}

	long long	value;

	errno = 0;
	value = std::strtoll(argument.c_str(), NULL, 10);

	if (errno == ERANGE || value <= 0 || value > INT_MAX)
		throw std::runtime_error("Error");

	return (static_cast<int>(value));
}

void	PmergeMe::swap_vector_groups(size_t first, size_t second, size_t group_size)
{
	int		aux;
	size_t	i;

	i = 0;
	while (i < group_size)
	{
		aux = vector[first + i];
		vector[first + i] = vector[second + i];
		vector[second + i] = aux;
		i++;
	}
}

void	PmergeMe::ford_johnson_vector(size_t group_size)
{
	if (vector.size() < 2 * group_size)
		return ;

	size_t	i;

	i = 0;
	while (i + 2 * group_size <= vector.size())
	{
		if (vector[i + group_size - 1] > vector[i + 2 * group_size - 1])
			swap_vector_groups(i, i + group_size, group_size);
		i = i + 2 * group_size;
	}

	ford_johnson_vector(group_size * 2);
}

size_t	PmergeMe::binary_search_vector(int value, size_t end) const
{
	size_t	mid;
	size_t	left;
	size_t	right;

	left = 0;
	right = end;

	while (left < right)
	{
		mid = left + (right - left) / 2;
		if (value < vector[mid])
			right = mid;
		else
			left = mid + 1;
	}

	return (left);
}

void	PmergeMe::parse_arguments(int argc, char **argv)
{
	if (argc < 2)
		throw std::runtime_error("Error");

	int	i;
	int	value;

	i = 1;
	while (i < argc)
	{
		value = parse_number(argv[i]);
		if (std::find(vector.begin(), vector.end(), value) != vector.end())
			throw std::runtime_error("Error");
		vector.push_back(value);
		deque.push_back(value);
		i++;
	}
}

void	PmergeMe::print_vector_deque() const
{
	std::cout << "Vector:" << std::endl;

	size_t	i;

	i = 0;
	while (i < vector.size())
	{
		std::cout << vector[i] << " ";
		i++;
	}
	std::cout << std::endl;

	std::cout << "Deque:" << std::endl;

	i = 0;
	while (i < deque.size())
	{
		std::cout << deque[i] << " ";
		i++;
	}
	std::cout << std::endl;
}