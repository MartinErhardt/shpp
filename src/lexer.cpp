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
 * The Lexer produces a list of Tokens.
 */
#include<string.h>
#include<string>
#include<vector>
#include<iostream>
#include<lexer.h>
using namespace shpp::Lexer;
/**
 * This is the only action of our pushdown automaton in shpp::Lexer::delimit(), which is not a state. 
 * That's why it's kept seperate from enum state in a macro.
 */
#define POP -1
/**
 * These are the states of our pushdown automaton implemented in shpp::Lexer::delimit().
 * The values are hardcoded to potencies of 2, so that they can be OR combined.
 */
enum state
{
	NORMAL=0,
	DOUBLE_QUOTED=1,
	SINGLE_QUOTED=2,
	BACKSLASH_ESCAPED=4
};
/**
 * These are the actions for our pushdown automaton implemented in
 * @see shpp::Lexer::delimit()
 */
static const int actions[4][3*2] =
{
   	{ 
		'"', DOUBLE_QUOTED, 
		'\'', SINGLE_QUOTED,
		'\\', BACKSLASH_ESCAPED
	}, /** NORMAL*/
	{
		'"', POP,
		'\'', NORMAL,
		'\\', BACKSLASH_ESCAPED
	}, /** DOUBLE_QUOTED*/
	{
		'"', NORMAL,
		'\'', POP,
		'\\', NORMAL
	}, /** SINGLE_QUOTED*/
	{
		'"', POP,
		'\'', POP,
		'\\', POP
	} /** BACKSLASH_ESCAPED*/
};
static const char unescaped[][8]
{
	" \n&|;<>",
	" \n",
	"",
	""
};
/**
 * current operand state
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_03 :
 * If the previous character was used as part of an operator and the current character is not quoted and can be used with the current characters to form an operator, it shall be used as part of that (operator) token.
 * @see shpp::Lexer::delimit()
 */
enum operand_state
{
	NONE,
	AND_IF,
	OR_IF,
	DSEMI,
	DLESS,
	DGREAT,
	THIRD	/**< enum value THIRD(This is special we only need it for <<-) */ 
};
/**
 * This contains the charactars that could possibly follow onto the first character of a character. 
 * secondoperand_char[<enum operandstate>] contains the possible second characters of a specific first character of an operand.
 * @see enum operand_state
 */
static const char secondoperand_char[][5]=
{
	"\0",
	"&",
	"|",
	";",
	"<&>|",
	">"
};
/**
 * builds up the list of classified tokens
 *
 * by calling delimit(), check_alias(), and classify()
 * 
 * @param	to_tokenize (std::string)
 * @return	List of yet classified tokens(std::vector)
 */
std::vector<class Token * > * shpp::Lexer::tokenize(std::string * to_tokenize)
{
	std::vector<class Token * > * TokenList=delimit(to_tokenize);
	check_alias(TokenList);
	classify(TokenList);
	return TokenList;
}
/**
 * delimetes a list of tokens from a continuous string
 *
 * This is implemented as a pushdown automaton,so that I can keep track of the quotation marks and escape characters.
 * for more information look here:
 * http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_03
 * http://en.wikipedia.org/wiki/Pushdown_automaton
 * 
 * @param	to_tokenize String to tokenize (std::string)
 * @return	List of yet unclassified tokens(std::vector)
 */
std::vector<class Token * > * shpp::Lexer::delimit(std::string * to_tokenize)
{
	std::vector<class Token * > * TokenList = new std::vector<class Token * >;
	std::vector<enum state> * state_stack = new std::vector<enum state>;
	int current_action,current_state,j;
	class Token * current_token=new Token;
	bool in_a_comment=false;
	//enum operand_state current_operand_state=NONE;
	state_stack->push_back(NORMAL);
	for (std::string::iterator i=to_tokenize->begin(); i<to_tokenize->end(); i++)
	{
		current_state=state_stack->back(),current_action=NORMAL,j=0;
		do if(actions[current_state][j*2]==*i)
				current_action=actions[current_state][j*2+1];
		while(!current_action && (++j)<3);
		if(((*i)=='#') && !current_action)
			in_a_comment=true;
		if(in_a_comment && ((*i)=='\n'))
			in_a_comment=false;
		if(!in_a_comment && strstr(&unescaped[current_state][0],&(*i)))
		{
			current_token = new Token(*i);
			TokenList->push_back(current_token);
		}else current_token->add_chr(*i);
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
void shpp::Lexer::check_alias(std::vector<class Token *>* to_check)
{
	
}
void shpp::Lexer::classify(std::vector<class Token *> * to_classify)
{
	
}
