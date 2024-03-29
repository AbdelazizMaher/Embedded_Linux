# Setup example of SystemV Init on Ubuntu with systemd

```
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
         

