/*  ./src/inc/lexer.h is a source file of shpp a gplv3 licensed shell written in c++
    Copyright (C) 2015  Martin Erhardt<martin.erhardt98@googlemail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/
#ifndef SHPP_H
#define SHPP_H
#include<string>
namespace shpp
{
	int interprete(std::string * to_interprete);
}
#endif // SHPP_H
