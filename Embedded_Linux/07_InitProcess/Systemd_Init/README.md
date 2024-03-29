# Setup example of Systemd Init on Ubuntu


# Systemd Unit Types

- **Service Units**: Manage system services or daemons.
- **Socket Units**: Handle inter-process communication sockets.
- **Target Units**: Group other units together for dependency management.
- **Device Units**: Represent devices in the Linux device tree.
- **Mount Units**: Manage mount points in the filesystem.
- **Automount Units**: Automatically mount filesystems when accessed.
- **Path Units**: Trigger actions based on changes to paths in the filesystem.
- **Timer Units**: Activate other units based on time.
- **Slice Units**: Manage resource usage limits for system processes.
- **Scope Units**: Group processes created outside of systemd's control.
- **Swap Units**: Manage swap space in the system.
- **Snapshot Units**: Save and restore the state of systemd.

## Example on service units

```bash
[Unit]
Description=Sanity Check Daemon server
Documentation=https://github.com/AbdelazizMaher/Embedded_Linux/tree/c3b5da7e592de32071176f564be0a4d6ebae7385/Embedded_Linux/07_InitProcess
After=tftpd-hpa.service
Wants=

[Service]
Type=simple
ExecStart=/bin/PrintDaemon
ExecStop=/etc/init.d/tftpd-hpa stop

[Install]
WantedBy=multi-user.target
```

### Explanation:

- **Description**: A brief description of the systemd service.

- **Documentation**: A link to the documentation for more information about the service.

- **Dependencies**:
  - **After**: Specifies that this service should start after `tftpd-hpa.service`.
  - **Wants**: (Empty) Additional units that are wanted when this unit is activated. In this case, it's not specifying any additional dependencies.

- **Service Definition**:
  - **Type**: Describes the startup type of the service. `simple` means that the process started by the service manager will not fork or background itself.
  - **ExecStart**: Specifies the command to start the service. In this case, it's `/bin/PrintDaemon`.
  - **ExecStop**: Specifies the command to stop the service. In this case, it's `/etc/init.d/tftpd-hpa stop`.

- **Installation Information**:
  - **WantedBy**: Specifies the target units that this unit should be installed with. In this case, it's `multi-user.target`, which typically represents a non-graphical multi-user system.



### Usage with systemctl and journalctl:

Both `systemctl` and `journalctl` are powerful tools for managing and troubleshooting Linux systems, providing administrators with insights into system state and behavior.

## systemctl

`systemctl` is a command-line tool used to control systemd, a system and service manager for Linux. It allows administrators to manage system services, control the boot process, and inspect the state of the system and its services. Some common `systemctl` commands include:

- `start <unit>`: Start a specified unit.
- `stop <unit>`: Stop a specified unit.
- `restart <unit>`: Restart a specified unit.
- `enable <unit>`: Enable a specified unit to start automatically at boot.
- `disable <unit>`: Disable a specified unit from starting automatically at boot.
- `status <unit>`: Display the status of a specified unit.
- `list-unit-files`: List all installed unit files.

## journalctl

`journalctl` is a command-line tool used to query and view logs managed by systemd's journaling system. It provides access to system logs, including messages from the kernel, system services, and applications. Some common `journalctl` commands include:

- `journalctl`: View all available logs.
- `journalctl -u <unit>`: View logs for a specific unit or service.
- `journalctl -b`: View logs from the current boot.
- `journalctl -f`: Follow the live stream of journal entries.
- `journalctl --since "YYYY-MM-DD HH:MM:SS"`: View logs since a specified time.
- `journalctl --disk-usage`: Display disk usage statistics for the journal.

