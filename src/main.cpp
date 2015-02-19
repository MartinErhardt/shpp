/**
 * @file src/main.cpp
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
 * Here in main.cpp, the input is read and transferred to the lexer and the parser
 */
#include<iostream>
#include<string>
#include<fstream>
#include<streambuf>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<shpp.h>
#include<lexer.h>
using namespace shpp;
/**
 * read input
 *
 * input can either be gained from the -c option, from stdin or 
 * 
 * @param	argc is the number of arguments
 * @param	argv is a pointer to list of char*pointers containing all the fancy arguments
 * @return	exit status
 */
int main(int argc, char **argv)
{
	int i=0;
	std::string to_interprete;
	for(;i<argc;i++)
		if(!strcmp(argv[i],"-c") && (i+1)<argc)
			return interprete(new std::string(argv[i+1]));
	if(!isatty(0)) // is there some pipe input ?
	{ 
		while((i=getchar())>0)
			to_interprete+=i;
		return interprete(&to_interprete);
	}
	std::cout << "shpp 0.0.1 "
		  	"Copyright (C) 2015 Martin Erhardt<martin.erhardt98@googlemail.com>\n"
			"This is free software with ABSOLUTELY NO WARRANTY.\n"
			"This is free software, and you are welcome to redistribute it under certain conditions\n";
	while(to_interprete.compare(0,1,"q"))
	{
		if(to_interprete.length())
			to_interprete.append("\n");
		interprete(&to_interprete);
		to_interprete.clear();
		std::cout << "\n$ "; // this will be $PS1 in later versions
		while((i=getchar()) != '\n' && i)
			to_interprete+=i;
	}
	return 0;
}
int shpp::interprete(std::string * to_interprete)
{
	shpp::Lexer::tokenize(to_interprete);
	return 0;
}
