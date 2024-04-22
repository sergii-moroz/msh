# msh

## TODOs:
- Signals (glocal variable save the number of received signal)

## Known issues

- crash by heredoc without command: '<< END'
- Check if multiple tries of the same redirections fail. (don't fail at the moment)
- Test fails: ls >"./outfiles/outfile""1""2""3""4""5". Currently takes only one token after redirect symbol. another goes to the command argument.

## Tools

 Minishell Tester by Lucas Kuhn (https://github.com/LucasKuhn/minishell_tester)

## Time line

2024-04-18 redirections '> >> <' works for single buildin, single general command and pipes.
2024-04-22 pass 140/148 tests
'''
