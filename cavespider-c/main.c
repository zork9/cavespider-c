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

int main(int argc, char **argv, char **envp)
{
	if (argc > 1) {
		fprintf(stdout, "No args needed");
	}

	char *url;
	url = "http://www.textfiles.com/phreak/\0";
	//ask_network(url);

		
	if (is_http_url(url) >= 0) {
		fprintf(stdout, "found a non-local url (http:// header)\n");
	}
	char *webpagecontents;
	read_in_webpage_file("./index.html", &webpagecontents);

	char *href;
	int endoffset = 0;
	fprintf(stdout, "endoffset=%d strlen webpage=%d\n", endoffset, strlen(webpagecontents));
	while (endoffset < strlen(webpagecontents)) {
		int len;
		endoffset = retrieve_ahref_from_page(&webpagecontents, &href, &len);
		char *href2 = (char *)malloc(len+1);
		href2[len] = '\0';
		strncpy(href2,href,len);
		fprintf(stdout, "href=%s\n", href2);


		char *tmpcontents = (char *)malloc(strlen(webpagecontents)-endoffset+1);
		memset(tmpcontents, 0, strlen(webpagecontents)-endoffset+1);
		int i = endoffset;	
		while (i < strlen(webpagecontents)) {
			//fprintf(stdout, "%c", webpagecontents[i]);
			tmpcontents[i-endoffset] = webpagecontents[i++];
		}
		free(webpagecontents);
		webpagecontents = tmpcontents;
		endoffset = 0;
		
		char *foundurl;
		retrieve_url(&href2, &foundurl, &len);
		char *foundurl2 = (char *)malloc(len+1);
		foundurl2[len] = '\0';
		strncpy(foundurl2,foundurl,len);
		fprintf(stdout, "foundurl2=%s\n", foundurl2);
		if (is_http_url(foundurl) >= strlen(foundurl)) {
		
			char fullurl[strlen(foundurl2)+strlen(url)+1];
			fullurl[strlen(foundurl2)+strlen(url)] = '\0';
			memset(fullurl, 0, strlen(foundurl2)+strlen(url)+1);
		 	strncat(fullurl,url,strlen(url));
		 	strncat(fullurl,foundurl2,strlen(foundurl2));
			fprintf(stdout, "prepared %s\n", fullurl);
	
			//free(fullurl);
			//free(foundurl);
			memset(foundurl, 0, strlen(foundurl));
			memset(href2, 0, strlen(href2));
			free(href2);
		}
		free(foundurl2);	
	}	

	return 0;
}	
