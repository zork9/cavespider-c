/*
* Copyright (C) Johan Ceuppens 2015 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int retrieve_substring(const int startoffset, const int endoffset, const char **pagetext, char **r)
{
	int i = startoffset;
	*r = (char *)malloc(endoffset - startoffset + 1);
	//memset(*r, 0, sizeof(*r));
	while (i < endoffset) 
		(*r)[i-startoffset] = (*pagetext)[i++];
	return 0;
}		
