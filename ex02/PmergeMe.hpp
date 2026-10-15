/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 20:08:37 by rexposit          #+#    #+#             */
/*   Updated: 2026/10/15 06:56:06 by rexposit         ###   ########.fr       */
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
		std::vector<int>	numbers;
		std::vector<int>	vector;
		std::deque<int>		deque;

		struct	PendingVectorGroup
		{
			std::vector<int>	group;
			int					partner;
			bool				has_partner;
		};

		struct	PendingDequeGroup
		{
			std::deque<int>	group;
			int				partner;
			bool			has_partner;
		};

		int		parse_number(const std::string &argument) const;

		void	swap_vector_groups(size_t first, size_t second, size_t group_size);
		size_t	binary_search_vector(const std::vector<int> &chain, int value, size_t end, size_t group_size) const;
		void	insert_pending_vector(const std::vector<PendingVectorGroup> &pending, std::vector<int> &main_chain, size_t group_size);
		void	build_main_chain_vector(size_t group_size);
		void	ford_johnson_vector(size_t group_size);

		void	swap_deque_groups(size_t first, size_t second, size_t group_size);
		size_t	binary_search_deque(const std::deque<int> &chain, int value, size_t end, size_t group_size) const;
		void	insert_pending_deque(const std::deque<PendingDequeGroup> &pending, std::deque<int> &main_chain, size_t group_size);
		void	build_main_chain_deque(size_t group_size);
		void	ford_johnson_deque(size_t group_size);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe	&operator=(const PmergeMe &other);
		~PmergeMe();

		void	parse_arguments(int argc, char ** argv);
		void	sort_vector();
		void	sort_deque();
		void	print_sorted() const;
};

#endif