/**
 * @file src/lexer.cpp
 * @author  Martin Erhardt <martin.erhardt98@googlemail.com>
 * @version 0.0.01-prealpha
 *
 * @section LICENSE
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
 * @section DESCRIPTION
 *
 * The Lexer produces a list of Tokens.
 */
#include<string>
#include<vector>
#include<lexer.h>
#include<iostream>
using namespace shpp::Lexer;
#define POP -1
enum state
{
	NORMAL,
	DOUBLE_QUOTED,
	SINGLE_QUOTED,
	BACKSLASH_ESCAPED
};
const int states[4][3*2] =
{
   	{ //NORMAL
		'"', DOUBLE_QUOTED, 
		'\'', SINGLE_QUOTED,
		'\\', BACKSLASH_ESCAPED
	}, // DOUBLE_QUOTED
	{
		'"', POP,
		'\'', NORMAL,
		'\\', BACKSLASH_ESCAPED
	}, // SINGLE_QUOTED
	{
		'"', NORMAL,
		'\'', POP,
		'\\', NORMAL
	}, // BACKSLASH_ESCAPED
	{
		'"', POP,
		'\'', POP,
		'\\', POP
	}
};
enum operand_state
{
	NONE,
	AND_IF,
	OR_IF,
	DSEMI,
	DLESS,
	DGREAT,
	THIRD
};
const char secondoperand_char[][5]=
{
	"\0",
	"&",
	"|",
	";",
	"<&>|",
	">"
};
std::vector<class Token> * shpp::Lexer::tokenize(std::string * to_tokenize)
{
	std::vector<class Token> * TokenList=delimit(to_tokenize);
	check_alias(TokenList);
	classify(TokenList);
	return TokenList;
}
/**
 * Delimetes a list of tokens from a continuous string
 *
 * This is implemented as a pushdown automaton,so that I can keep track of the quotation marks and escape characters
 * 
 * @param	String to tokenize (std::string)
 * @return	List of yet unclassified tokens(std::vector)
 * @see		http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_03
 * @see		http://en.wikipedia.org/wiki/Pushdown_automaton
 */
std::vector<class Token> * shpp::Lexer::delimit(std::string * to_tokenize)
{
	std::vector<class Token>* TokenList = new std::vector<class Token>;
	std::vector<enum state> * state_stack = new std::vector<enum state>;
	int current_action,current_state,j;
	//enum operand_state current_operand_state=NONE;
	state_stack->push_back(NORMAL);
	for (std::string::iterator i=to_tokenize->begin(); i<to_tokenize->end(); i++)
	{
		current_state=state_stack->back(),current_action=NORMAL,j=0;
		do if(states[current_state][j*2]==*i)
				current_action=states[current_state][j*2+1];
		while(!current_action && (++j)<3);
		std::cout << "current_action";
    		std::cout << +current_action;
		if(current_state==BACKSLASH_ESCAPED)	current_action=POP;
		if(current_action==POP)			state_stack->pop_back();
		else if(current_action)			state_stack->push_back((enum state)current_action);
	}
	current_state=state_stack->back();
	delete state_stack;
	if(current_state==NORMAL) return TokenList;
	else 
	{
		std::cout << "unexpected EOF";
		std::cout << +current_state;
		return NULL;
	}
}
void shpp::Lexer::check_alias(std::vector<class Token>* to_check)
{
	
}
void shpp::Lexer::classify(std::vector<class Token> * to_classify)
{
	
}
