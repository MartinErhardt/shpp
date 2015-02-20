/**
 * @file src/lexer.cpp
 * @author  Martin Erhardt <martin.erhardt98@googlemail.com>
 * @version 0.0.01-prealpha
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file contains the token class.
 */
#include<string>
#include<iostream>
#include<lexer.h>
using namespace shpp::Lexer;
void shpp::Lexer::Token::add(std::string * to_add)
{
	*lexem=*lexem+*to_add;
}
