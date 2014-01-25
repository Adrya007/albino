/*****************************************************************************
 * Solver.cpp - sudoku solver, hpp                                           *
 * Pawel 'nkoder' Barszcz <pawelbarszcz(at)gmail.com>                        *
 *****************************************************************************/
#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_

#include "Puzzle.hpp"

class Solver {
	public:
		static const int NO_SOLUTION = 0;
		static const int SOLVED = 1;

	public:
		static int solve(PPuzzle puzzle);
};		

#endif
