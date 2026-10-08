/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 20:08:34 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/08 20:17:02 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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