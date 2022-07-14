#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include "utils.h"

using namespace std;

int main() {

  while (true) {
    // get inputs from shell
    string user_input;
    cout << "ffosh$ ";
    getline(cin, user_input);

    // exit shell
    if ((user_input == "exit" || std::cin.eof())) {
      cout << "FFOSH exited normally\n";
      return 0;
    }

    if (!user_input.empty()) {
      // get commands from inputs
      string command_name = split(user_input, "/").back();
      char* command_name_pointer = &*command_name.begin();
      char* command_path = &*user_input.begin();

      // create a process
      cout << "============== Run program \""
	   << command_name << "\" ==============\n";
      pid_t proc = fork();
      int status;

      // in the child process
      if (proc == 0) {
	// construct arguments to the command
	vector<char*> args_vec;
	args_vec.push_back(command_name_pointer);
	args_vec.push_back(NULL);
	char* args[args_vec.size()];
	std::copy(args_vec.begin(), args_vec.end(), args);

	// construct environment to the command
	vector<char*> envs_vec;
	envs_vec.push_back(NULL);
	char* envs[envs_vec.size()];
	std::copy(envs_vec.begin(), envs_vec.end(), envs);

	// excute command
	return execve(command_path, args, envs);
      } else {
	// in main process
	// wait for proc to finish
	waitpid(proc, &status, 0);
	if (WEXITSTATUS(status) == 0) {
	  cout << "============== Program was successful ==============\n";
	} else if (WIFSIGNALED(status)) {
	  cerr << "============== Terminated by signal "
	       << WTERMSIG(status) << "==============\n";
	} else {
	  cerr << "============== Program failed with code "
	       << WEXITSTATUS(status) << "==============\n";
	}
      }
    }
  }

  return 0;
}
