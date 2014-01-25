/*****************************************************************************
 * Puzzle.cpp - puzzle of sudoku, cpp                                        *
 * Pawel 'nkoder' Barszcz <pawelbarszcz(at)gmail.com>                        *
 *****************************************************************************/
#include <set>
#include <string>

#include "Field.hpp"
#include "Puzzle.hpp"

using namespace std;

int Puzzle::getNumber(int row, int column) {
	return fields_[row][column].getNumber();
}

void Puzzle::setNumber(int row, int column, int number) {
	fields_[row][column].setNumber(number);
	eliminateOther(row, column, number);
}

PPossibilities Puzzle::getPossibilities(int row, int column) {
	return fields_[row][column].getPossibilities();
}

int Puzzle::initialize(string puzzle_as_string) {
	unsigned int i = 0;
	for (int r = 0; r < 9; ++r) {
		for (int c = 0; c < 9; ++c) {
			while(i < puzzle_as_string.size() &&
					puzzle_as_string[i] != '.' && 
					(puzzle_as_string[i] < '1' || puzzle_as_string[i] > '9')) {
				++i;
			}
			if (i >= puzzle_as_string.size()) return TEXT_TOO_SHORT;
			if (puzzle_as_string[i] != '.') {
				fields_[r][c].setNumber(puzzle_as_string[i]-'0');
				eliminateOther(r,c,puzzle_as_string[i]-'0');
			}
			++i;
		}
	}
	return  INITIALIZED;
}

void Puzzle::eliminateOther(int row, int column, int number) {
	for (int r = 0; r < 9; ++r) {
		if (r != row) fields_[r][column].eliminate(number);
	}
	for (int c = 0; c < 9; ++c) {
		if (c != column) fields_[row][c].eliminate(number);
	}
	for (int r = 3*(row/3); r < 3*(1+row/3); ++r) {
		for (int c = 3*(column/3); c < 3*(1+column/3); ++c) {
			if (r != row && c != column) fields_[r][c].eliminate(number);
		}
	}
}

string Puzzle::toString() {
	string s;
	int v;
	for (int r = 0; r < 9; ++r) {
		if (r == 3 || r == 6) {
			for (int j = 0; j < 9; ++j) {
				if (j == 3 || j == 6) s += '+';
				s += '-';
			}
			s += '\n';
		}
		for (int c = 0; c < 9; ++c) {
			if (c == 3 || c == 6) s += '|';
			v = fields_[r][c].getNumber();
			if (v == Field::EMPTY_FIELD) s += '.';
			else s += '0' + v;
			if (c == 8) s += '\n';
		}
	}
	return s;
}

std::string Puzzle::getPossibilitiesDescription() {
	PPossibilities p;
	string s;
	for (int r = 0; r < 9; ++r) {
		for (int c = 0; c < 9; ++c) {
			p = getPossibilities(r,c);
			if (p->size() > 0) {
				s += "(";
				s += '0'+r+1;
				s += ",";
				s += '0'+c+1;
				s += "): ";
				for (set<int>::iterator it = p->begin(); it != p->end(); ++it) {
					s += ('0'+*it);
					s += " ";
				}
				s += "\n";
			}
		}
	}
	return s;
}

