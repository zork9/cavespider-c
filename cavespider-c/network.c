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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>

#include "globals.c"

int is_http_url(const char *url)
{
	regex_t comp;
	if (regcomp(&comp, "http://", 0) < 0) {
		fprintf(stdout, "Bad regexp matching http://, returning");
		return -1;
	} 

	regmatch_t matchptr[1];
	if (regexec (&comp, url, 1, matchptr, 0) < 0) {
		fprintf(stdout, "Bad url!, returning");
		return -1;
	}
	//fprintf(stdout, "end offset=%d\n", matchptr[0].rm_eo);

	return matchptr[0].rm_eo;
}

int retrieve_url(const char **text, char **url, int *len)
{
	//*url = (char *)malloc(strlen(*text));
	//memset(*url, 0, strlen(*text));
	regex_t comp;
	if (regcomp(&comp, "\"[A-Za-z0-9.&/]*\"", 0) < 0) {
		fprintf(stdout, "Bad regexp matching , returning");
		return -1;
	} 

	regmatch_t matchptr[1];
	if (regexec (&comp, *text, 1, matchptr, 0) < 0) {
		fprintf(stdout, "Bad pagetext match href!, returning");
		return -1;
	}

	//remove " and "
	retrieve_substring(matchptr[0].rm_so+1, matchptr[0].rm_eo-1, text, url);	
	*len = matchptr[0].rm_eo-matchptr[0].rm_so-2;
	return matchptr[0].rm_eo;
}

int retrieve_ahref_from_page(const char **pagetext, char **href, int *len)
{
	regex_t comp;
	if (regcomp(&comp, "a href[\"=]*[A-Za-z0-9.&/]*\"", 0) < 0
	|| regcomp(&comp, "A HREF[\"=]*[A-Za-z0-9.&/]*\"", 0) < 0) {
		fprintf(stdout, "Bad regexp matching  <a href=http://*>, returning");
		return -1;
	} 

	regmatch_t matchptr[1];
	if (regexec (&comp, *pagetext, 1, matchptr, 0) < 0) {
		fprintf(stdout, "Bad pagetext match href!, returning");
		return -1;
	}

	retrieve_substring(matchptr[0].rm_so, matchptr[0].rm_eo, pagetext, href);	
	
	*len = matchptr[0].rm_eo-matchptr[0].rm_so;
	return matchptr[0].rm_eo;

}

int retrieve_url_from_href(const char **href, char **url)
{
	regex_t comp;
	if (regcomp(&comp, "(\"http://)([A-Za-z0-9.&])*\"", 0) 
	|| regcomp(&comp, "(http://)([A-Za-z0-9.&])*", 0) < 0) {
		fprintf(stdout, "Bad regexp matching  <a href=http://*>, returning");
		return -1;
	} 

	regmatch_t matchptr[1];
	if (regexec (&comp, *href, 1, matchptr, 0) < 0) {
		fprintf(stdout, "Bad href url!, returning");
		return -1;
	}

	memcpy(*url, *href+matchptr[0].rm_so, matchptr[0].rm_eo-matchptr[0].rm_so);
	retrieve_substring(matchptr[0].rm_so, matchptr[0].rm_eo, href, url);	
	return 0;
}
	
int ask_network(const char *url) 
{
	fprintf(stdout, "grabbing %s...", url);
	execl(WGET, WGET, url, (char *)0);
	fprintf(stdout, "done.\n");
}		
