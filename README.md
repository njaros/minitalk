# minitalk 125/100 without usleep

That's a stable version of the minitalk subject of 42 school.

The tree next point allowed me to not use usleep.
* I use sigaction for server. (no need for client).
* Mac Kernel don't get lost thanks of sigaction's flags I used.
* Server and client can't loose data thanks of the fact I call kill() at the very last in each exchange.

I hope I helped you to anderstand the project.
