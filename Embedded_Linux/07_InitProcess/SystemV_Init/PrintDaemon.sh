#!/bin/sh

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
