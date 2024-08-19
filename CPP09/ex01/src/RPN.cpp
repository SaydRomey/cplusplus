/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:56:11 by cdumais           #+#    #+#             */
/*   Updated: 2024/08/18 20:56:12 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/* ************************************************************************** */ // Constructors / Destructors

RPN::RPN(void)
{
	std::cout << GRAYTALIC << "RPN [default constructor]" << RESET << std::endl;
}

RPN::RPN(const RPN &other)
{
	*this = other;
	std::cout << GRAYTALIC << "RPN [copy constructor]" << RESET << std::endl;
}

RPN::~RPN(void)
{
	std::cout << GRAYTALIC << "RPN [default destructor]" << RESET << std::endl;
}

/* ************************************************************************** */ // Getters / Setters

/* ************************************************************************** */ // Functions / Methods

/* ************************************************************************** */ // Operators

RPN&	RPN::operator=(const RPN &other)
{
	// if (this != &other)
	// {}
	
	return (*this);
}

// std::ostream&	operator<<(std::ostream &out, const RPN &param)

/* ************************************************************************** */ // Exceptions

