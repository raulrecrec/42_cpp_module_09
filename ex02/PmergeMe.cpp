/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 20:08:34 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/13 23:11:18 by rexposit         ###   ########.fr       */
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

struct	PendingGroup
{
	std::vector<int>	group;
	int					partner;
	bool				has_partner;
};

void	PmergeMe::build_main_chain_vector(size_t group_size)
{
	std::vector<int>			main_chain;
	std::vector<PendingGroup>	pending;
	PendingGroup				aux;
	size_t						group_count;
	size_t						i;
	size_t						j;
	

	group_count = 0;
	i = 0;
	while (i + group_size <= vector.size())
	{
		if (i < group_size || group_count % 2 != 0)
		{
			j = 0;
			while (j < group_size)
			{
				main_chain.push_back(vector[i + j]);
				j++;
			}
			group_count++;
		}
		else
		{
			j = 0;
			while (j < group_size)
			{
				aux.group.push_back(vector[i + j]);
				j++;
			}
			if (i + 2 * group_size <= vector.size())
			{
				aux.partner = vector[i + 2 * group_size - 1];
				aux.has_partner = true;
			}
			else
				aux.has_partner = false;
			pending.push_back(aux);
			aux.group.clear();
			group_count++;
		}
		i = i + group_size;
	}

	std::vector<int>	leftover;

	while (i < vector.size())
	{
		leftover.push_back(vector[i]);
		i++;
	}

	size_t	end;
	size_t	position;
	bool	found;

	i = 0;
	while (i < pending.size())
	{
		j = 0;
		found = false;
		end = main_chain.size() / group_size;
		if (pending[i].has_partner)
		{
			while (j < main_chain.size())
			{
				if (main_chain[j + group_size - 1] == pending[i].partner)
				{
					end = j / group_size;
					found = true;
					break ;
				}
				j = j + group_size;
			}
			if (!found)
				throw std::logic_error("Partner group not found");
		}
		position = binary_search_vector(main_chain, pending[i].group[group_size - 1], end, group_size);
		main_chain.insert(main_chain.begin() + position * group_size, pending[i].group.begin(), pending[i].group.end());
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
	build_main_chain_vector(group_size);
}

size_t	PmergeMe::binary_search_vector(const std::vector<int> &chain, int value, size_t end, size_t group_size) const
{
	size_t	mid;
	size_t	left;
	size_t	right;

	left = 0;
	right = end;

	while (left < right)
	{
		mid = left + (right - left) / 2;
		if (value < chain[mid * group_size + group_size - 1])
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