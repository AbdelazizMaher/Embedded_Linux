
# Setup example of BusyBox Init

### Add the application

We need to add the application into the init script so it run at startup.

We need to modify rcS script:

- `/etc/init.d/rcS`

  ```bash
	mount -t proc comment proc/

	mount -t sysfs comment sys/

	ARG=$1

	if [ "$ARG" -eq 3 ]
	then

		for i in /etc/init.d/S??*
		do	
			$i start
		done
	fi	
	
	if [ "$ARG" -eq 5 ]
	then

		for i in /etc/init.d/K??*
		do	
			$i stop
		done
	fi	
  ```

We need to add two scripts:

- `/etc/init.d/S01PrintHello`

	```bash
	echo "Starting PrintHello_Daemon"
	./bin/PrintHello_Daemon &
	```

- `/etc/init.d/K01PrintHello`

	```bash
	echo "Stopping PrintHello_Daemon"
	pkill -e ./bin/PrintHello_Daemon
	sleep 3
  ```

- Adding the script in inittab

  ```bash
	# Start services when system starts up
	::sysinit:/etc/init.d/rcS 3

	# start shell
	ttyAMA0::askfirst:-/bin/sh
  
	# Stuff to do when restarting the init process
	::restart:/sbin/init
  
	# Excute when the system will go down
	::shutdown:/etc/init.d/rcS 5
  ```

### inittab syntax
  ```sh
id:runlevels:action:process
```
| Field      | Description                                                                                     |
|------------|-------------------------------------------------------------------------------------------------|
| id         | An arbitrary identifier for the entry.                                                         |
| runlevels  | Specifies the runlevels in which the entry is active. It can be represented as a single level (0-6) or a combination of levels. "S" denotes system startup. |
| action     | Specifies the action to be taken when conditions defined by id and runlevels are met. Possible actions include: `initdefault`, `respawn`, `wait`, `once`, `ctrlaltdel`, among others. |
| process    | Specifies the command or script to be executed when the conditions defined by id and runlevels are met. This could be an absolute path to an executable program or a script. |


 **`action:`**
   - **`initdefault`**: Specifies the default runlevel to be entered after system boot.
   - **`respawn`**: Restarts the specified process if it terminates.
   - **`wait`**: Waits for the specified process to terminate before proceeding.
   - **`once`**: Executes the specified process once and then removes the entry.
   - **`ctrlaltdel`**: Defines the action to be taken when the Ctrl+Alt+Delete key combination is pressed.
   - **`powerfail`**: Specifies the action to be taken when a power failure occurs.
   - **`sysinit`**: Specifies commands to be executed during system initialization.
   - **`bootwait`**: Similar to wait, but executed at boot time.
   - **`powerwait`**: Similar to wait, but executed when a power failure occurs.
   - **`off`**: Disables the entry.



