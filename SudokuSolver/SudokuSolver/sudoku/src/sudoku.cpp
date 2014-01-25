/*****************************************************************************
 * sudoku.cpp - solving sudoku puzzles                                       *
 * Pawel 'nkoder' Barszcz <pawelbarszcz(at)gmail.com>                        *
 *****************************************************************************/
#include <string>

#include <boost/python.hpp>

#include "Puzzle.hpp"
#include "Solver.hpp"

using namespace std;
using namespace boost;
using namespace boost::python;

string solveSudoku(string sudoku_as_text)
{
	PPuzzle p(new Puzzle());
	int result;

	string output;

	result = p->initialize(sudoku_as_text);
	if (result == Puzzle::TEXT_TOO_SHORT) {
		output += "TEXT TOO SHORT!";
		return output;
	}

	result = Solver::solve(p);
	if (result == Solver::NO_SOLUTION) {
		output += "NO SOLUTION FOUND!\n";
		output += "Possibilities:\n";
		output += p->getPossibilitiesDescription();
	}

	output += p->toString();

	return output;
}

BOOST_PYTHON_MODULE(sudoku)
{
    def("solveSudoku", solveSudoku);
}
