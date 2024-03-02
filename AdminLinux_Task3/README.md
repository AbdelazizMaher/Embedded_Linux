# Day3_Task01

## Description
    .The bash script checks if the .bashrc file exists in the user's home directory.
    .If the file exists,
      - It appends to the .bashrc file the environment variable -> HELLO with the value of HOSTNAME 
      - LOCAL with the value of whoami 
    .It then sources the .bashrc file to apply the changes in the current session.
    .It opens another terminal as child process -> This new terminal will inherit the environment variables set in .bashrc.
