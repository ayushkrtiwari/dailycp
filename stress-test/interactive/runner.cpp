// C++ runner (POSIX-compatible)
// This program launches the interactor and the solution, wires their stdin/stdout so they communicate
// directly, captures stderr of both, repeats random tests and saves a transcript on first failure.
// Compile: g++ -std=c++17 -O2 runner.cpp -o runner -pthread
// Usage example (after compiling interactor and solution):
// ./runner --solution ./sol --tests 1000 --N 100 --maxq 100 --timeout 1.5


#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>


using namespace std;


struct Subprocess {
pid_t pid = -1;
int stdin_fd = -1; // we write to child's stdin
int stdout_fd = -1; // we read from child's stdout
int stderr_fd = -1; // we read from child's stderr
};


static void set_nonblock(int fd){
int flags = fcntl(fd, F_GETFL, 0);
if(flags==-1) return;
fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}


// create a subprocess: argv[0]=path, argv is vector<string>
static Subprocess spawn_proc(const vector<string>& argv){
Subprocess s;
int inpipe[2]; // parent -> child (child stdin)
int outpipe[2]; // child -> parent (child stdout)
int errpipe[2]; // child stderr -> parent
if(pipe(inpipe) || pipe(outpipe) || pipe(errpipe)){
perror("pipe"); exit(1);
}
pid_t pid = fork();
if(pid==0){
// child
// connect stdin
dup2(inpipe[0], STDIN_FILENO);
dup2(outpipe[1], STDOUT_FILENO);
dup2(errpipe[1], STDERR_FILENO);
// close unused
close(inpipe[0]); close(inpipe[1]);
close(outpipe[0]); close(outpipe[1]);
close(errpipe[0]); close(errpipe[1]);
// make argv
vector<char*> cargs;
f << "=== INTERACTOR STDERR ===