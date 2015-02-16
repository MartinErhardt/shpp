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
#include<errno.h>
int main(int argc, char **argv)
{
	int i=0;
	FILE*f=NULL;
	bool no_input=true;
	std::string to_interprete;
	for(;i<argc;i++)
		if(!strcmp(argv[i],"-c") && (i+1)<argc)
		{
			f=fopen(argv[i+1],"rb");
			fseek(f, 0, SEEK_END);
			long fsize = ftell(f);
			fseek(f, 0, SEEK_SET);
			char *string = new char[fsize + 1];
			fread(string, fsize, 1, f);
			fclose(f);
			to_interprete=string;
			delete [] string;
			no_input=false;
			break;
		}
	if(no_input && !isatty(0)) // is there some pipe input ?
	{
		f=fdopen(0,"rb");
		while((i=getchar()))
			to_interprete+=i;
		no_input=false;
	}
	if(no_input) // interactive
	{
		std::cout << "shpp 0.0.1 "
			  	"Copyright (C) 2015 Martin Erhardt<martin.erhardt98@googlemail.com>\n"
				"This is free software with ABSOLUTELY NO WARRANTY.\n"
				"This is free software, and you are welcome to redistribute it under certain conditions\n";
		while(to_interprete.compare(0,1,"q"))
		{
			if(to_interprete.length())
				to_interprete.append("\n");
			std::cout << to_interprete;
			to_interprete.clear();
			std::cout << "$ "; // this will be $PS1 in later versions
			while((i=getchar()) != '\n' && i)
				to_interprete+=i;
		}
	}
	std::cout << to_interprete;
	return 0;
}
