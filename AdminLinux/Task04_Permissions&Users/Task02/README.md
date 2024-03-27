# Question01
-----------

## 1- Create a folder called myteam in your home directory and change its permissions to read only for the owner:
	- mkdir ~/myteam
	- chmod u-wx myteam

## 2- Log out and log in by another user:
	- su another_user

## 3- Try to access (by cd command) the folder (myteam):
	- cd /home/first_user/myteam -> by default there is read permission for others
	
## 4- 
    a) first way:    - chmod u+rw oldpasswd           second way:   - chmod 651 oldpasswd 
                    - chmod g+wx-r oldpasswd
		     - chmod o-r+x oldpasswd
    b) change the default permissions using (umask)
    c) max permisson for file -> 666  max permisson for folder -> 777
    d) umask 777 -> drwxrwxr-x 2 abdelaziz abdelaziz 4096 Mar  2 10:07 dir1
		    d--------- 2 abdelaziz abdelaziz 4096 Mar  2 12:57 dir2
		    -rw-rw-r-- 1 abdelaziz abdelaziz    0 Mar  2 12:55 file1
		    ---------- 1 abdelaziz abdelaziz    0 Mar  2 12:55 file2
    e) users getting sudo privilage		    
	
## 5- 
      - file is readonly -> can't edit or remove (only using sudo) 
## 6- 
      - files: the "x" permission allows the file to be executed as a program.		    
      - directories: the "x" permission allows users to access and navigate through the directory
   
# Question02
-----------
    
## 2-  
    - Create a new directory -> mkdir ~/newdir  
    1)Set the sticky bit on the newly created directory:
    	- chmod +t ~/newdir	  		     
    2)set the setgui bit on the created directory:
    	- chmod g+s ~/newdir
    3)Create multiple user accounts:	
    	-sudo adduser acc1            --sudo adduser acc2   				    		
    4)Allow these users to create files within the directory and directory:
    	- chmod o+rw newdir
    5)Attempt to delete or rename each other's files:
        - in newdir -> -rw-rw-r-- 1 acc1      abdelaziz 0 Mar  2 06:42 acc1file
			-rw-rw-r-- 1 acc2      abdelaziz 0 Mar  2 06:43 acc2file
			-rw-rw-r-- 1 abdelaziz abdelaziz 0 Mar  2 06:54 myfile
    6)Provide a clear output demonstrating the impact of the sticky bit on file deletion and renaming within the directory:
    	- rm: cannot remove 'myfile': Operation not permitted
	- rm: cannot remove 'acc1file': Operation not permitted
	- owner of the file can delete an file
    7) drwxrwsrwt 2 abdelaziz abdelaziz 4096 Mar  2 07:08 newdir/

## - List the permission passwd command has and explain why it has S:
	- -rwsr-xr-x 1 root root 67816 Jan 15  2021 /usr/bin/passwd 
	- The s in the owner's execute permission (-rws) indicates the setuid (Set User ID) bit is set. This means that when the passwd 		  command is executed, it runs with the permissions of the file owner (typically root), not the user executing the command.	
			

