/*****************************************************************************
 * Puzzle.cpp - puzzle of sudoku, hpp                                        *
 * Pawel 'nkoder' Barszcz <pawelbarszcz(at)gmail.com>                        *
 *****************************************************************************/

#ifndef _PUZZLE_HPP_
#define _PUZZLE_HPP_

#include <string>
#include <set>

#include <boost/shared_ptr.hpp>

#include "Field.hpp"

class Puzzle {

	public:
		static const int TEXT_TOO_SHORT = 0;
		static const int INITIALIZED = 1;

	private:
		Field fields_[9][9];

	public:
		int initialize(std::string puzzle_as_string);
		int getNumber(int row, int column);
		void setNumber(int row, int column, int number);
		PPossibilities getPossibilities(int row, int column);
		std::string toString();
		std::string getPossibilitiesDescription();

	private:
		void eliminateOther(int row, int column, int number);
};

typedef boost::shared_ptr<Puzzle> PPuzzle;

#endif
