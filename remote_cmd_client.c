/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "remote_cmd.h"
#include <stdlib.h> // malloc
#include <stdio.h> // fprintf
#include <string.h> // strlen
#include <fcntl.h> // stdout stderr
#include <unistd.h> // STDIN_FILENO

void remote_cmd_1(char* host, ClientInput* input) {
  CLIENT *clnt;
  ServerOutput* result_1;
  ClientInput  execute_cmd_1_arg = *input;
  execute_cmd_1_arg.part_ = -1;  
  execute_cmd_1_arg.parts_ = 0;

#ifndef	DEBUG
	clnt = clnt_create (host, remote_cmd, remote_cmd_ver, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */


	result_1 = execute_cmd_1(&execute_cmd_1_arg, clnt);
	if (result_1 == (ServerOutput *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	
	ClientInput  execute_cmd_1_part;
	execute_cmd_1_part.part_ = -1;
	execute_cmd_1_part.parts_ = 0;
	int comm_len = strlen(execute_cmd_1_arg.program_name_);
	static const size_t buf_size = 2048;
	execute_cmd_1_part.program_name_ = (char*) malloc(sizeof(char) * buf_size + 1);
	execute_cmd_1_part.flags_ = (char*) malloc(sizeof(char) * buf_size + 1);
  execute_cmd_1_part.flags_[0] = '\0';
	execute_cmd_1_part.stdin_ = (char*) malloc(sizeof(char) * buf_size + 1);
  execute_cmd_1_part.stdin_[0] = '\0';
	for (int i = 0; i < comm_len; i += buf_size) {
	  execute_cmd_1_part.part_--;
	  strncpy(execute_cmd_1_part.program_name_, execute_cmd_1_arg.program_name_  + (i * buf_size), buf_size);
    ServerOutput* part = execute_cmd_1(&execute_cmd_1_part, clnt);
	}
	execute_cmd_1_part.program_name_[0] = '\0'; 
  int flag_len = strlen(execute_cmd_1_arg.flags_);

	for (int i = 0; i < flag_len; i += buf_size) {
		execute_cmd_1_part.part_--;
	  strncpy(execute_cmd_1_part.flags_, execute_cmd_1_arg.flags_  + (i * buf_size), buf_size);
    ServerOutput* part = execute_cmd_1(&execute_cmd_1_part, clnt);
	}
	execute_cmd_1_part.flags_[0] = '\0';
	
	// unblock stdin.
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
	size_t read_size = 0;
	while ((read_size = read(STDIN_FILENO, execute_cmd_1_part.stdin_, buf_size)) > 0) {
	  //printf("read: %lu\n", read_size);
		execute_cmd_1_part.part_--;
		execute_cmd_1_part.stdin_[read_size] = '\0';
		ServerOutput* part = execute_cmd_1(&execute_cmd_1_part, clnt);
	}

  execute_cmd_1_part.stdin_[0] = '\0';
  execute_cmd_1_part.part_ = 0;
  execute_cmd_1_part.parts_ = 0;
  
  
  // Initialize first proper message.
  ServerOutput* part = execute_cmd_1(&execute_cmd_1_part, clnt);
  
  // Allocate memory for all incoming parts from server.
  ServerOutput* parts =
    (ServerOutput*) malloc((result_1->parts_ + 1) * sizeof(ServerOutput));
  parts[0] = *result_1;
  
  // Receive all packages.
  for (size_t i = 1; i <= result_1->parts_; ++i) {
    execute_cmd_1_part.part_ = i;
    ServerOutput* part = execute_cmd_1(&execute_cmd_1_part, clnt);
    parts[part->part_] = *part;
  }

	//fprintf(stdout, "Status: %d\n", result_1->status_);
	//fflush(stdout);

  // Printf stdout & stderr.
  for (size_t i = 0; i < result_1->parts_ + 1; ++i) {
    fprintf(stdout, "%s", parts[i].stdout_);
    fflush(stdout);
  }
  //fprintf(stdout, "\n");
  fflush(stdout);
  for (size_t i = 0; i < result_1->parts_ + 1; ++i) {
    fprintf(stdout, "%s", parts[i].stderr_);
    fflush(stderr);
  }
  //fprintf(stderr, "\n");
  fflush(stderr);

	
	
	
	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
  if(argc < 2) {
    printf("usage: %s server_host\n", argv[0]);
    exit(1);
  }
  char* host = argv[1];

  ClientInput input;
  input.program_name_ = argv[2];

  // Add input flags if any.
  if ((argv - 3) > 0) {
    // Calculate how many bytes are for every flag + space.
    size_t flags_size = 0;
    for (size_t i = 3; i < argc; ++i) {
      flags_size += strlen(argv[i]) + 1;
      //printf("'%s' - size: %lu\n", argv[i], strlen(argv[i]));
    }
    // Space for '\0' already calculated with last space
    input.flags_ = (char*) malloc(sizeof(char) * flags_size);
    size_t it = 0;
    //printf("Iter flags: '");
    for (size_t i = 3; i < argc; ++i) {
      sprintf(input.flags_ + it, "%s ", argv[i]);
      //printf("%s ", argv[i]);
      it += strlen(argv[i]) + 1;
    }
    //printf("' - size: %lu\n", it);
    // Switch last character to '\0'.
    input.flags_[flags_size - 1] = '\0';
    //printf("All flags:  '%s' - size: %lu\n", input.flags_, strlen(input.flags_));
  }
  remote_cmd_1(host, &input);
}
