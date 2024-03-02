# Day04_Task

## Description
	- This script checks if the user and group already exist before creating them and provides relevant information for both after creating them.

#Questions	
1- Create a supplementary (Secondary) group called pgroup with group ID of 30000:
	- sudo groupadd -g 30000 pgroup
	- cat /etc/group | grep pgroupor directories, the "x" permission allows users to access and navigate through the directory
	
2- Lock any user created account so he can't log in:
	- sudo passwd -l  abdo 
	- cat /etc/passwd | grep user
	
3- Delete user account:
	- sudo userdel -r user
	
4- Delete group account:
	- sudo groupdel pgroup
	
5- State the difference between adduser and useradd with example shown:
	- adduser -> is a user-friendly frontend for creatior directories, the "x" permission allows users to access and navigate through the directoryng new user accounts. It provides an interactive interface that prompts for necessary information, such as the user's password and full name. It also handles the creation of a home directory and setting up the user's environment.		
	-useradd -> is a low-level command-line tool that requires you to specify all necessary options manually. It does not provide any interactive prompts and assumes default values for some settings unless explicitly specified
	# Using adduser (interactive mode)               # Using useradd (command-line options)
	- sudo adduser name                              - sudo useradd -m -s /bin/bash name
							   - sudo passwd name		
