# msh


## Known issues

- crash by heredoc without command: '<< END'

## Time line

2024-04-18 redirections '> >> <' works for single buildin, single general command and pipes.
Some usefull test cases:
'''bash
cat < f3.txt
tr a-z A-Z < f3.txt
echo Hello > f4.txt | tr a-z A-Z < f3.txt
'''
