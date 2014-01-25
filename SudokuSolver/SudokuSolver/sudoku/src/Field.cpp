/*****************************************************************************
 * Field.cpp - one field in sudoku, cpp                                      *
 * Pawel 'nkoder' Barszcz <pawelbarszcz(at)gmail.com>                        *
 *****************************************************************************/
#include <set>
#include <string>

#include "Puzzle.hpp"

using namespace std;

Field::Field() {
	number_ = EMPTY_FIELD;
	possibilities_ = PPossibilities(new set<int>());
	for (int i = 1; i <= 9; ++i) {
		possibilities_->insert(i);
	}
}

int Field::getNumber() {
	return number_;
}

void Field::setNumber(int number) {
	number_ = number;
	possibilities_->clear();
}

PPossibilities Field::getPossibilities() {
	return possibilities_;
}

void Field::eliminate(int number) {
	if (number >= 1 && number <= 9) {
		possibilities_->erase(number);
	}
}

