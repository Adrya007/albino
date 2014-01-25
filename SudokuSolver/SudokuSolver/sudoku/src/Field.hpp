/*****************************************************************************
 * Field.cpp - one field in sudoku, hpp                                      *
 * Pawel 'nkoder' Barszcz <pawelbarszcz(at)gmail.com>                        *
 *****************************************************************************/

#ifndef _FIELD_HPP_
#define _FIELD_HPP_

#include <string>
#include <set>

#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<std::set<int> > PPossibilities;

class Field {
	public:
		const static int EMPTY_FIELD = 0;

	private:
		int number_;
		PPossibilities possibilities_;

	public:
		Field();
		int getNumber();
		void setNumber(int number);
		PPossibilities getPossibilities();
		void eliminate(int number);
};

#endif
