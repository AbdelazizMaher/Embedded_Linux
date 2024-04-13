# LogFile DaemonAPP

This program is a daemon written in C that periodically reads data from `/dev/kmsg`, writes it to a logfile, and performs certain actions based on logfile conditions.

## Description

The daemon performs the following tasks:

1. Reads latest data from `/dev/kmsg`.
2. Writes the latest data to a logfile.
3. Checks if the logfile has reached a maximum number of lines.
4. If the maximum lines limit is reached:
   - Empties the logfile.
   - Toggles the CapsLock LED.

## Configuration

- `KMSG_PATH`: Path to the kernel message device file (`/dev/kmsg`).
- `LOGFILE_PATH`: Path to the logfile.

## Usage

1. Compile the program:	
```bash
gcc LogFileDaemonAPP.c -o LogFileDaemonAPP
```

2. Move the output to /bin
```bash
sudo cp LogFileDaemonAPP /bin/
```

3. Start Daemon Process
```bash
systemctl start LogFileDaemon.service
```




