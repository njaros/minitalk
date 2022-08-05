# minitalk 125/100 without usleep

That's a stable version of the minitalk subject of 42 school.

The three nexts points allowed me to not use usleep.
* I use sigaction for server. (no need for client).
* Mac Kernel don't get lost thanks of sigaction's flags I used.
* Server and client can't loose data thanks of the fact I call kill() at the very last in each exchange.

They're is a lot of french touch in function's and variable's names. I'm not sorry about that.

Don't use my Makefile, he's weird (I keep it because I won't modify my olds projects). I guess he can relink easily when modify libft.


I hope I helped you to anderstand the project.
