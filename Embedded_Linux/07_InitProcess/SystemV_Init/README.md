# System V Init Process

## how it works step-by-step:

1. **`init Process:`**  Starts the system and reads `/etc/inittab` to determine actions for each run level.

2. **`/etc/inittab:`**  Defines the default run level and references the `rc script` to run the scripts for the appropriate run level.
> ! The inittab file specifies commands to run, including the rc script with the run level as an argument.

3. **`Run Levels:`**  define different states of the machine. Common run levels include:

      **S:** Runs startup tasks

      **0:** Halt (shut down the system)

      **1:** Single-user mode (maintenance or recovery mode)

      **2:** Multi-user mode without networking

      **3:** Multi-user mode with networking
      
      **5:** Multi-user mode with networking and graphical interface

      **6:** Reboot

4. **`rc Script:`** Runs the appropriate `start and kill` scripts for the specified run level.
> ! The rc script uses inittab argument to determine which services to start or stop for the specified run level.


5. **`Scripts in /etc/init.d:**` These scripts are executed by init through the symbolic links in the run level directories.
> ! Each script in /etc/init.d can take start, stop, restart, and status as arguments to control the service.

## Directory Structure

### Here’s a simplified view of the directory structure related to the System V init system:

```plainText
/etc
├── init.d
│   ├── script1
│   ├── script2
│   ├── script3
│   └── ...
├── inittab
├── rc.d
│   ├── rc0.d
│   │   ├── K20script1 -> ../init.d/script1
│   │   ├── ...
│   ├── rc1.d
│   │   ├── ...
│   ├── rc2.d
│   │   ├── ...
│   ├── rc3.d
│   │   ├── S20script1 -> ../init.d/script1
│   │   ├── S01script2 -> ../init.d/script2
│   │   ├── S10script3 -> ../init.d/script3
│   │   ├── ...
│   ├── rc4.d
│   │   ├── ...
│   ├── rc5.d
│   │   ├── ...
│   ├── rc6.d
│   │   ├── ...
│   └── rc.local
└── ...
```
## Example of /etc/inittab
```bash
# Default runlevel. The runlevels used by RHS are:
#   0 - halt (Do NOT set initdefault to this)
#   1 - Single user mode
#   2 - Multiuser, without NFS (The same as 3, if you do not have networking)
#   3 - Full multiuser mode
#   4 - unused
#   5 - X11
#   6 - reboot (Do NOT set initdefault to this)
id:3:initdefault:

# System initialization.
si::sysinit:/etc/rc.d/rc.sysinit

# Runlevel 0
l0:0:wait:/etc/rc.d/rc 0

# Runlevel 1
l1:1:wait:/etc/rc.d/rc 1

# Runlevel 2
l2:2:wait:/etc/rc.d/rc 2

# Runlevel 3
l3:3:wait:/etc/rc.d/rc 3

# Runlevel 4
l4:4:wait:/etc/rc.d/rc 4

# Runlevel 5
l5:5:wait:/etc/rc.d/rc 5

# Runlevel 6
l6:6:wait:/etc/rc.d/rc 6
```

## Example of rc Script

- The rc script (/etc/rc.d/rc) is a common script that runs the appropriate scripts in the run level directories. `Here is a simplified version`:

```bash
#!/bin/sh

# Run the scripts in the appropriate runlevel directory

runlevel=$1
previous_level=$2

if [ -z "$runlevel" ]; then
  echo "Usage: $0 <runlevel>"
  exit 1
fi

# Execute K scripts (Kill scripts)
for script in /etc/rc${runlevel}.d/K*; do
  [ -x "$script" ] && "$script" stop
done

# Execute S scripts (Start scripts)
for script in /etc/rc${runlevel}.d/S*; do
  [ -x "$script" ] && "$script" start
done
```



# Setup example of SystemV Init on Ubuntu with systemd


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
  # init 5 also work
  telinit 5 # switching to runlevel 5 will kill the application
  ```

         

