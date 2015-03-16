#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*

  words - writes stdin to stdout, one word to a line

  Author: Dick Lang

  */

int main(int argc, char* argv[]) {

	char c = getchar();		/* current character */

	/* loop, reading characters, until there are no more */

	while (c != EOF) {

		/* scan past any leading non-alpha characters */

		while (!isalpha(c) && (c != EOF)) {
			c = getchar();
		}

		/* write out any contiguous string of alphabetic characters */

		while (isalpha(c) && (c != EOF)) {
			putchar(c);
			c = getchar();
		}
		putchar('\n');	/* end the word with a new line */
	}

	return 0;
}
