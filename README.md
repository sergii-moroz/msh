# msh

## TODOs:
- Signals (glocal variable save the number of received signal)

## Known issues

- crash by heredoc without command: '<< END'
- if command consist only from spaces, than msh return command not found. it means command execution was started.
- Check if multiple tries of the same redirections fail. (don't fail at the moment)

## Time line

2024-04-18 redirections '> >> <' works for single buildin, single general command and pipes.
Some usefull test cases:
'''bash
cat < f3.txt
tr a-z A-Z < f3.txt
echo Hello > f4.txt | tr a-z A-Z < f3.txt
'''
