# minishell (42Porto - 42Cursus) <img src="https://github.com/devicons/devicon/blob/master/icons/linux/linux-original.svg" title="Linux" alt="Linux Logo" width="50" height="60" align="right" />&nbsp; <img src="https://github.com/devicons/devicon/blob/master/icons/c/c-original.svg" title="C" alt="C Logo" width="55" height="55" align="right" />&nbsp;  

#### Project done in collaboration with [ramos21rodrigo](https://github.com/ramos21rodrigo)

## Grade: 101/100

###  Demonstration:
![](./extras/showcase.gif)

### Installing and running the project:
1- Installing minishell dependencies:  

	sudo apt-get install make libreadline-dev
2- Clone this repository:  

	git clone https://github.com/Kuninoto/42_minishell
3- Navigate to _lvl_3_minishell_ and run `make`

	cd 42_minishell/lvl_3_minishell
	make
4- `make clean` so that you don't keep those object files that you won't need anymore  

	make clean
5- Run minishell

	./minishell

###  Subject: [minishell en_subject](./extras/en.subject_minishell.pdf)

#### Makefile Available Targets:  
`make` or `make all` - compiles minishell      
`make clean` - wipes all object files   
`make fclean` - deletes minishell and all object files   
`make re` - fclean  + all   

## Useful links
Understanding Bash/Shell behavior:  
- https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/  
- https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/  
- https://indradhanush.github.io/blog/writing-a-unix-shell-part-3/  
- https://www.gnu.org/software/bash/manual/html_node/Redirections.html  
- https://www.youtube.com/watch?v=ubt-UjcQUYg  
- https://www.youtube.com/watch?v=ZjzMdsTWF0U  
- https://www.youtube.com/watch?v=k6TTj4C0LF0  
- https://www.tutorialspoint.com/unix_system_calls/execve.htm  
- https://www.geeksforgeeks.org/signals-and-traps-in-unix/  
- https://www.tutorialspoint.com/unix/unix-signals-traps.htm  
- https://unix.stackexchange.com/questions/362559/list-of-terminal-generated-signals-eg-ctrl-c-sigint#362566  
- https://www.computerhope.com/jargon/r/relapath.htm  
- https://www.techopedia.com/definition/5817/absolute-path  
- https://www.ibm.com/docs/en/informix-servers/12.10?topic=products-term-environment-variable-unix  
- https://kinsta.com/knowledgebase/what-is-an-environment-variable/  
- https://linuxconfig.org/term-environment-variable-not-set-solution  
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf  
- http://www.cems.uwe.ac.uk/~irjohnso/coursenotes/lrc/system/shell/index.html  
- https://www.rozmichelle.com/pipes-forks-dups/  
- https://velog.io/@sham/minishell%EA%B3%BC-readline  
- https://github.com/Swoorup/mysh  

Parsing:  
- https://youtu.be/bxpc9Pp5pZM  
- https://youtu.be/r6vNthpQtSI  
- https://www.youtube.com/watch?v=dDtZLm7HIJs  
- https://www.youtube.com/watch?v=SToUyjAsaFk  
- https://github.com/mit-pdos/xv6-public/blob/master/sh.c  
- https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html  

AST:  
- https://en.wikipedia.org/wiki/Abstract_syntax_tree  
- https://stackoverflow.com/questions/1721553/how-to-construct-an-abstract-syntax-tree  
- https://www.twilio.com/blog/abstract-syntax-trees  

Parsing/AST/Interpreter:  
- https://github.com/Swoorup/mysh  

## Disclaimer
> At [42School](https://en.wikipedia.org/wiki/42_(school)), almost every project must be written in accordance to the [Norm](./extras/en_norm.pdf), the schools' coding standard. As a result, the implementation of certain parts may appear strange and for sure had room for improvement.

---
Made by Nuno Carvalho (Kuninoto) | nnuno-ca@student.42porto.com  
<div id="badge"> <a href="https://www.linkedin.com/in/nuno-carvalho-218822247"/> <img src="https://img.shields.io/badge/LinkedIn-blue?style=for-the-badge&logo=linkedin&logoColor=white" alt="LinkedIn Badge"/>&nbsp;
