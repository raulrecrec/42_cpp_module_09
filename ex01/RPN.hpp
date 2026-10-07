/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:57:55 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/07 16:55:42 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <string>

class	RPN
{
	private:
		std::stack<int>	operands;

		int		calculate(int left, int right, const char symbol) const;
		void	apply_operation(const char symbol);

	public:
		RPN();
		RPN(const RPN &other);
		RPN	&operator=(const RPN &other);
		~RPN();

		void	process_expression(const std::string &expression);
};

#endif