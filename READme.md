This is my implementation of a linux shell using C

HOW TO RUN:
For compiling all files : make all
For running the shell : ./c_shell
For removing all executables, object files and history : make clean
To exit the shell : 'quit' or 'exit'

If command prompt is not visible after running a backgrouond process press Enter.

Files:
i) Headerfile.h : contains all function definitions, variables, structures and constants.

ii) main.c : implemented main() function which initialises history and stores the home location, color functions, print_prompt() which prints the username, host and pwd on STDOUT. It also handles the signals SIGTSTP(for CTRL+Z), SIGQUIT(for CTRL+\), SIGINT(for CTRL+C) and prevents shell from exitting on these signals. Also the exit codes are printed here with 'exst'(Bonus 2).

iii) cmdhandle.c : commandexec() is called from main.c (print_prompt()) whenever we execute a command, init() stores the name of in-built commands, splitcmd() splits the input into multiple commands, splitargs() splits a command into multiple arguments, checkand() checks if there is & at end of a command (for background process). Checklogical checks if given command is logical command.  contains redirection 

iv) cd.c : cd() uses chdir() to change current directory from pwd to the directory whose path is given in args[1]. Also handles 'cd -' command (Bonus 1)

v) pwd.c : prints pwd using getcwd() function.

vi) echo.c : echo() converts the arguments given with echo command to token then separates them using space and tab as delimeters and then prints them separated by spaces.

vii) ls.c : ls() first checks if the flags -a -l (or their combination) are given, if the flags are given list hidden files or use long listing format accordingly, if more than one directory paths are given their list is separated by a newline. get_print_info() prints the long listing format in case -l flag is given. filter() is used to print or ignore hidden files if -a is given or absent respectively.

viii) pinfo.c : pinfo() prints the pid given as argument (or uses getpid() if argument is NULL), prints process status by opening and viewing the /proc/$(pid)/status file, prints memory by viewing /proc/$(pid)/statm file, and prints executable path using /proc/$(pid)/exe file.

ix) nightswatch.c : nightswatch checks if valid arguments are given, starts a timer and calls interrupt() or newborn() function periodically while listening to keyDown event at each clock cycle. keyDown() returns 1 if a key is pressed else returns 0. interrupt() prints the number of times keyboard interrupted CPU's, newborn() opens the file /proc/loadavg and printf pid of the process last created.

x) history.c : init_hist() creates a .history hisdden file to store history in the ~ directory and initialises history pointer to 0 index (stores index where last change was made). addhis() adds the last command executed to history array. exhis() saves the current shell's history and exits. history() takes a argument (possibly NULL) and prints last min(20,argument) arguments stored in history.

xi) unimplemented.c : it handles those commands which run in background and those which are not declared in cmdhandle.c. unimplemented() forks the given process and checks, if & was given as argument then run the process in background using backquit, else run it normally. backquit() handles the background process.
It also handles the event CTRL+Z when a process is running by sending it to background.

xii) bghand.c : bghand() function implements bg command.

xiii) sighnd.c : sighnd.c contains the null() function for handling CTRL+Z, CTRL+C, CTRL+\ signal in the shell.

xiv) jobs.c : jobs() function checks all the stoppped or running processes and prints their details. kjob() functions sends signals like kill or interrupt to the specified process. fg() implements fg command. checkallkill() checks if there are any remaining processes (stopped or running) in the background.

xv) overkill.c : it sends kill signal to all the commands in background.

xvi) setenv.c : seten() is used to set the set the value of an environmental variable (setenv command) and unseten() is used to unset environmental variables (unsetenv command).

xvii) logical.c : implements logical commands (bonus 3). here only valid commands are processed.

xviii) redir.c : handles those commands which contain piping or i/o redirection.
