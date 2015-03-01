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

int read_in_webpage_file(const char *filename, char **pagetext)
{
	FILE *fp;
	if ((fp = fopen(filename, "r")) != NULL) {
		fseek(fp, 0L, SEEK_END);
		*pagetext = (char *)malloc(ftell(fp)+1);
		memset(*pagetext, 0, ftell(fp)+1);
		char *buf = (char *)malloc(ftell(fp)+1); 
		memset(buf, 0, ftell(fp)+1);
		rewind(fp);
		int n;
		while ((n = fscanf(fp, "%c", buf)) != EOF) {
			strncat(*pagetext, buf, n);
		}
		return 0;	
	}
	return -1;
}
