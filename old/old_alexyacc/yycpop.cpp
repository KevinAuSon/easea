/************************************************************
yycpop.cpp
This file can be freely modified for the generation of
custom code.

Copyright (c) 1997-99 P. D. Stearns
************************************************************/

#include "cyacc.h"

#ifdef YYDEBUG
void yyparser::yypop(int num)
{
	yyassert(num >= 0);
	yytop -= num;
	yyassert(yytop >= -1);

	// debugging
	if (::yydebug || yydebug) {
		if (num > 0) {
			char string[128];

			sprintf(string, "%p: pop %d state(s)", (void*)this, (int)num);
			yydebugoutput(string);
			if (yytop >= 0) {
				sprintf(string, " uncovering state %d", (int)yystackptr[yytop]);
				yydebugoutput(string);
			}
			yydebugoutput("\n");
		}
	}
}
#endif
