/*****************************************************************************
 * Solver.cpp - sudoku solver, cpp                                           *
 * Pawel 'nkoder' Barszcz <pawelbarszcz(at)gmail.com>                        *
 *****************************************************************************/
#include <set>

#include "Field.hpp"
#include "Puzzle.hpp"
#include "Solver.hpp"

using namespace std;
using namespace boost;

int Solver::solve(PPuzzle puzzle) {

	PPossibilities possibilities;

	int iteration = 0;
	bool changesMade = true;
	bool sudokuNotSolved = true;

	while (sudokuNotSolved && changesMade ) {
		sudokuNotSolved = false;
		changesMade = false;

		for (int r = 0; r < 9; ++r) {
			for (int c = 0; c < 9; ++c) {

				++iteration;

				if (puzzle->getNumber(r,c) == Field::EMPTY_FIELD) {
					sudokuNotSolved = true;

					possibilities = puzzle->getPossibilities(r,c);

					if (possibilities->size() < 1) {
					// error: there is no value to put in field
						return NO_SOLUTION;
					} else if (possibilities->size() == 1) {
						// if there is certainity about value which has to be put in field
						puzzle->setNumber(r,c,*(possibilities->begin()));
						changesMade = true;
					}
				}

			}
		}
	}

	if (sudokuNotSolved) return NO_SOLUTION;
	return SOLVED;
}

