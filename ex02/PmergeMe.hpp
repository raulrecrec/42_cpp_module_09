/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 20:08:37 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/10 14:27:14 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class	PmergeMe
{
	private:
		std::vector<int>	vector;
		std::deque<int>		deque;

		int		parse_number(const std::string &argument) const;
		void	swap_vector_groups(size_t first, size_t second, size_t group_size);
		void	ford_johnson_vector(size_t group_size);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe	&operator=(const PmergeMe &other);
		~PmergeMe();

		void	parse_arguments(int argc, char ** argv);
		void	print_vector_deque() const;
};

#endif