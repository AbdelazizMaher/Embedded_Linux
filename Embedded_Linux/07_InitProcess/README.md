# Init Process

The init process is the first process started during booting of the operating system. It's responsible for initializing the system in user space and managing the subsequent bootstrapping of the system components and services.

## General Concept of Init Processes

Init processes typically perform the following tasks:

- **Kernel Initialization**: The init process is responsible for initializing the kernel parameters and setting up essential kernel data structures.
  
- **Launching System Services**: It starts essential system services required for the proper functioning of the operating system, such as network services, logging daemons, and hardware drivers.
  
- **Runlevel Management**: Init processes often manage system runlevels, which represent different system states or configurations. Each runlevel may have a different set of services enabled or disabled.

- **Service Dependency Management**: Init processes handle service dependencies, ensuring that services are started or stopped in the correct order based on their dependencies.

## Types of Init Processes

### 1. BusyBox Init

BusyBox is a software suite that provides several stripped-down Unix tools in a single executable file. BusyBox init is a simple init system commonly used in embedded systems or systems with limited resources.

#### Features of BusyBox Init:

- Lightweight and resource-efficient.
- Provides basic functionalities for starting and stopping services.
- Typically used in embedded Linux systems, routers, and other resource-constrained devices.

#### Configuration Example:

```sh
#!/bin/sh

# Mount essential filesystems
mount -t proc proc /proc
mount -t sysfs sys /sys

# Start necessary system services
/sbin/syslogd -n
/sbin/klogd -n
/etc/init.d/rcS
```

### 2. SystemV Init

SystemV init is one of the traditional init systems found in Unix-like operating systems. It sequentially starts services defined in a series of shell scripts located in /etc/rc.d directories.

#### Features of SystemV Init:

- Sequential startup of services defined in runlevel-specific directories.
- Init scripts typically follow a naming convention (e.g., S##service for start and K##service for stop).
- Supports runlevels for defining system states.

Configuration Example:
```sh
#!/bin/sh
#
# rc       This file is executed by init(8) when the system is being
#          initialized (in single user mode).  It usually includes
#          some system setup and any other initialization specific to
#          the particular system.
#
#          Add your local setup commands here.
#

echo "Initializing SystemV Init..."

# Start essential system services
/etc/rc.d/rc.sysinit
/etc/rc.d/rc.multi
/etc/rc.d/rc.local
```
#### Setup example on Ubuntu with systemd
**Note:** In Ubuntu and many other Linux distributions, including those that use systemd as the init system, SystemV runlevels are often still present for compatibility reasons.

`/etc/init.d/PrintDaemon.sh`

take in count that **PrintDaemon.sh** is a script inside the init.d, **PrintDaemon** is the elf generated.

```sh
#! /bin/sh
case "$1" in
      start)
           echo "Starting Print app........."
           start-stop-daemon -S -n PrintDaemon -a /bin/PrintDaemon &
           ;;
      stop)
           echo "Stopping Print app.........":
           start-stop-daemon -K -n PrintDaemon
           ;;
      *)
           echo "Usage: $0 {start|stop}"
           exit 1
esac
exit 0
```
**start-stop-daemon** : start and stop system daemon programs,and is used to control the creation and termination of system-level processes.Using one of the matching options, start-stop-daemon can be configured to find existing instances of a running process.

#### Usage of the app

- Ask for Help

```sh
/etc/init.d/PrintDaemon.sh --help
```

- stop service

```sh
/etc/init.d/PrintDaemon.sh stop
```

- start service

```sh
/etc/init.d/PrintDaemon.sh start
```
**Note:** you can view the output by using `journalctl` command

- Then add this script to one of the `/etc/rc<x>.d/` folders to specify on what run level we will start the application

  ```sh
  # from file system root we create a symbolic link to our application and place it in one of the rc<runlevel> folders(runlevel)
  ln -s ../init.d/PrintDaemon.sh ./etc/rc3.d/S40PrintDaemon.sh
  # this simplic link file is named `S40`, S -> will call our script with `start` as argument, `40` order of execution
  ```

- To kill the application at when getting in specific runlevel we create similar symbolic link

  ```sh
  # Kill the process in runlevel 5
  ln -s ../init.d/PrintDaemon.sh ./etc/rc5.d/K40PrintDaemon.sh
  ```
  
 - to switch to runlevel
  
  ```sh
  telinit 5 # switching to runlevel 5 will kill the application
  ```
         
### 3. systemd

systemd is a modern init system used in many Linux distributions. It's designed to parallelize the boot process and manage system services dynamically.

#### Features of systemd:

- Parallel execution of service units to improve boot time.
- Integration with D-Bus for inter-process communication.
- Dependency-based service management.
- Supports socket and device activation.

Configuration Example:
```bash
[Unit]
Description=MyService
After=network.target

[Service]
Type=simple
ExecStart=/path/to/executable

[Install]
WantedBy=multi-user.target
```



