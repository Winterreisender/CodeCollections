/*
Copyright 2021 Winterresender. 
License under AGPL-3.0-only.

coding: utf-8
lang: C11
environment: Windows 10 21H2 x64, MingW GCC 11.2.0 

direct execute script by run command due to program's file name
for example: ...\myapp.pwsh.exe -> pwsh myapp.ps1
*/

//#define __DEBUG__

#include <windows.h>
#include <stdlib.h>

#ifdef __DEBUG__
	#include <stdio.h>
	#define dbg(x) printf("%s = %s\n", #x, x)
#else
	#define dbg(x) ;
#endif



char* last_char(const char* begin, const char* end, const char chr)
{
	char* result = end;
	while(*(--result) != chr && result >= begin);
	return result;
}

int main(int argc, char** argv) {
	const char* argv0 = argv[0];
	
	dbg(argv0);
	char* argv0_end = argv[0];
	while(*(++argv0_end) != '\0');
	
	char* last_slash = last_char(argv0, argv0_end, '\\');
	
	dbg(last_slash);
	char* last_dot = last_char(last_slash, argv0_end, '.');
	dbg(last_dot);
	*last_dot = '\0';
	
	char* last2_dot = last_char(last_slash, last_dot, '.');
	dbg(last2_dot);
	*last2_dot = '\0';

	// assemble command = last2_dot + last_slash
	char command[128] = "";
	int i;
	for(i=0; (last2_dot+1)[i] != '\0'; ++i)
	{
		command[i] = (last2_dot+1)[i];
	}
	command[i++] = ' ';

	int j;
	for(j=0; (last_slash+1)[j] != '\0'; ++j)
	{
		command[j+i] = (last_slash+1)[j];
	}
	command[i+j] = '\0';
	
	dbg(command);
	
	system(command);
	return 0;
}
