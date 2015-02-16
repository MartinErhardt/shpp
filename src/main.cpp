/*  ./src/main.cpp is a source file of shpp a gplv3 licensed shell written in c++
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
#include<iostream>
#include<string>
#include<fstream>
#include<streambuf>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
int main(int argc, char **argv)
{
	int i=0;
	FILE*f=NULL;
	std::string to_interprete;
	for(;i<argc;i++)
		if(!strcmp(argv[i],"-c") && (i+1)<argc)
		{
			std::cout << "interpreting ";
			std::cout << argv[i+1];
			std::cout << "\n";
			f=fopen(argv[i+1],"rb");
			break;
		}
	if(!f && !isatty(0)) // is there some pipe input ?
		f=fdopen(0,"rb");
	if(f) // non-interactive
		std::cout << "non interactive";
	else // interactive
		while(to_interprete.compare(0,1,"q"))
		{
			if(to_interprete.length())
				to_interprete.append("\n");
			std::cout << to_interprete;
			to_interprete.clear();
			std::cout << "$ "; // this will be $PS1 in later versions
			while((i=getchar()) != '\n')
				to_interprete+=i;
		}
	return 0;
}
