#define siz (long long)4096
#define hsiz (long long)2008

struct bid{
    int pid;
    char * command;
    int index;
    int status;  
};

struct hist{
    char  history[20][100] ;
    int histins;
    int histed;
};

char home[100];
char  cmdlist[30][50] ;
char prevdir[100];
char name[100];
int backpointer;
int exst;
void pwd();

char * commandexec(char *);
char **splitargs(char *);
int checkand(char **);
int checklogical(char **);
void execute(char *);

void history (char **);
void inithist();
char  his_path[200] ;
void addhis (char * );
void exhis();

void pinfo (char **);
void unimplemented (char **  ,int );
void nightswatch(char **);
void echo (char **);

void ls (char **);
int  cd (char **);
void print_promt ( );
void getdir();
void red();
void yellow ();
void reset();

void backquit(int sig);
void unimplemented (char **  ,int );
struct bid backarray[128];
struct hist his;

int mypid;

//bghand.c
void bghand(char **);
char currpromt[250];

//jobs.c
void kjobs(char **);
void jobs(char **);
void fg(char **);

//logical.c
int logicalexec(char *);
void logical(char *);

//redir.c
void tagpiper(char *);

//overkill.c
void killemall(char **);

//setenv.c
void seten(char **);
void unseten(char **);

//sighnd.c
void null(int);

struct bid runproc;
