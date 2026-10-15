/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:57:45 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/16 00:23:08 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <cstdlib>
#include <climits>
#include <iostream>

RPN::RPN()
	: operands()
{
}

RPN::RPN(const RPN &other)
	: operands(other.operands)
{
}

RPN	&RPN::operator=(const RPN &other)
{
	if (this != &other)
		this->operands = other.operands;

	return (*this);
}

RPN::~RPN()
{
}

int RPN::calculate(int left, int right, const char symbol) const
{
	long long result;

	if (symbol == '+')
		result = static_cast<long long>(left) + right;
	else if (symbol == '-')
		result = static_cast<long long>(left) - right;
	else if (symbol == '/')
	{
		if (right == 0)
			throw std::runtime_error("Error");
		result = static_cast<long long>(left) / right;
	}
	else
		result = static_cast<long long>(left) * right;

	if (result > INT_MAX || result < INT_MIN)
		throw std::runtime_error("Error");

	return (static_cast<int>(result));
}

void	RPN::apply_operation(const char symbol)
{
	int	right;
	int	left;

	if (operands.size() < 2)
		throw std::runtime_error("Error");
	right = operands.top();
	operands.pop();
	if (symbol == '/')
	{
		if (right == 0)
			throw std::runtime_error("Error");
	}
	left = operands.top();
	operands.pop();
	operands.push(calculate(left, right, symbol));
}

void	RPN::process_expression(const std::string &expression)
{
	std::istringstream	stream(expression);
	std::string			token;

	while (stream >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("Error");
		else if (std::isdigit(token[0]))
			operands.push(std::atoi(token.c_str()));
		else if (token[0] == '+' || token[0] == '-' || token[0] == '/' || token[0] == '*')
			apply_operation(token[0]);
		else
			throw std::runtime_error("Error");
	}

	if (operands.size() != 1)
		throw std::runtime_error("Error");
	else
		std::cout << operands.top() << std::endl;
}