
#BusyBox Init

## Configuration example :

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
	echo "rsc1 is on"
	deamonapp &
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

	::restart:/sbin/init

	# Excute when the system will go down
	::shutdown:/etc/init.d/rcS 5
  ```



