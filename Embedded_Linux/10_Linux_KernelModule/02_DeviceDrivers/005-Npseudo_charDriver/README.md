# Multiple Pseudo Character Device Driver

This Linux kernel module implements a pseudo character device driver(GPIO) that supports multiple devices. Each device has its own Number and permissions.


## Output in /sys
![](output.png)

## Output in /dev
![](dev.png)

## Overview

This driver creates multiple character devices.The driver supports four devices (`NO_OF_DEVICES = 2`), each with different permissions 



