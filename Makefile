compile = gcc -c
F1 = Implemented/
F2 = Implemented/Bonus/
F3 = Unimplemented/

all : main.o $(F1)bghand.o $(F1)sighnd.o  $(F1)jobs.o $(F1)overkill.o $(F1)redir.o $(F1)setenv.o cmdhandle.o $(F1)cd.o $(F1)pwd.o $(F1)echo.o $(F1)ls.o $(F1)pinfo.o $(F2)nightswatch.o $(F2)history.o $(F3)unimplemented.o $(F2)logical.o
	gcc  main.o $(F1)bghand.o $(F1)sighnd.o  $(F1)jobs.o $(F1)overkill.o $(F1)redir.o $(F1)setenv.o cmdhandle.o $(F1)cd.o $(F1)pwd.o $(F1)echo.o $(F1)ls.o $(F1)pinfo.o $(F2)nightswatch.o $(F2)history.o $(F3)unimplemented.o $(F2)logical.o -o c_shell

main.o : main.c
	$(compile) main.c

cmdhandle.o : cmdhandle.c
	$(compile) cmdhandle.c

$(F1)bghand.o : $(F1)bghand.c 
	$(compile) $(F1)bghand.c -o $(F1)bghand.o

$(F1)sighnd.o : $(F1)sighnd.c 
	$(compile) $(F1)sighnd.c -o $(F1)sighnd.o

$(F1)jobs.o : $(F1)jobs.c 
	$(compile) $(F1)jobs.c -o $(F1)jobs.o

$(F1)overkill.o : $(F1)overkill.c 
	$(compile) $(F1)overkill.c -o $(F1)overkill.o

$(F1)redir.o : $(F1)redir.c 
	$(compile) $(F1)redir.c -o $(F1)redir.o

$(F1)setenv.o : $(F1)setenv.c 
	$(compile) $(F1)setenv.c -o $(F1)setenv.o

$(F1)cd.o : $(F1)cd.c 
	$(compile) $(F1)cd.c -o $(F1)cd.o

$(F1)pwd.o : $(F1)pwd.c
	$(compile) $(F1)pwd.c -o $(F1)pwd.o

$(F1)echo.o : $(F1)echo.c
	$(compile) $(F1)echo.c -o $(F1)echo.o

$(F1)ls.o : $(F1)ls.c
	$(compile) $(F1)ls.c -o $(F1)ls.o

$(F1)pinfo.o : $(F1)pinfo.c
	$(compile) $(F1)pinfo.c -o $(F1)pinfo.o

$(F2)nightswatch.o : $(F2)nightswatch.c
	$(compile) $(F2)nightswatch.c -o $(F2)nightswatch.o 

$(F2)history.o : $(F2)history.c
	$(compile) $(F2)history.c -o $(F2)history.o

$(F3)unimplemented.o : $(F3)unimplemented.c 
	$(compile) $(F3)unimplemented.c -o $(F3)unimplemented.o

$(F2)logical.o : $(F2)logical.c
	$(compile) $(F2)logical.c -o $(F2)logical.o

clean:
	rm -r *.o $(F1)*.o $(F2)*.o $(F3)*.o c_shell .history
