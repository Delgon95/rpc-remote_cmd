struct ClientInput {
  string program_name_<>;
  string flags_<>;
  string stdin_<>;
  int part_;
  int parts_;
};

struct ServerOutput {
  string stdout_<>;
  string stderr_<>;
  int status_;
  int part_;
  int parts_;
};

program remote_cmd {
version remote_cmd_ver {
  ServerOutput execute_cmd(ClientInput input) = 1;
} = 1;
} = 0x20000000;
