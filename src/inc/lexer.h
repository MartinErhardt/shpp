/**
 * @file src/inc/lexer.h
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
 * Header file of
 * @see lexer.cpp
 */
#ifndef LEXER_H
#define LEXER_H
#include<vector>
#include<string>
/**
 * \namespace shpp
 * The main namespace for this project
 */
namespace shpp
{
	/**
	 * \namespace lexer
	 * namespace for the lexer
	 */
	namespace Lexer
	{
		typedef enum
		{
			WORD,
			ASSIGNMENT_WORD,
			NAME,
			NEWLINE,
			IO_NUMBER,
			AND_IF,
			OR_IF,
			DSEMI,
			DLESS,
			DGREAT,
			LESSAND,
			GREATAND,
			LESSGREAT,
			DLESSDASH,
			CLOBBER,
			If,
			Then,
			Else,
			Elif,
			Fi,
			Do,
			Done,
			Case,
			Esac,
			While,
			Until,
			For,
			Lbrace,
			Rbrace,
			Bang,
			In
		} token_t;
		/**
		 * My Token class
		 */
		class Token
		{
			std::string * lexem;
			token_t type;
			public:
				Token()
				{
					lexem=new std::string();
				};
				Token(std::string * start)
				{
					lexem=start;
				};
				void add(std::string * to_add);
		};
		std::vector<class Token> * tokenize(std::string * to_tokenize);
		std::vector<class Token> * delimit(std::string * to_tokenize);
		void check_alias(std::vector<class Token>* to_check);
		void classify(std::vector<class Token> * to_classify);
	}
}
#endif // LEXER_H
