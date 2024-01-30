#include "myshell.h"

int main()
{
	char in[MAX_INPUT_LENGTH];
	char *args[MAX_ARGS];

	while (1)
	{
		prompt();
		input(in);

		//Internal commands check
		if (execInternalCmd(in) == 1)
			continue;

		//External command exec.
		execExternalCmd(in);
	}

	return 0;
}
