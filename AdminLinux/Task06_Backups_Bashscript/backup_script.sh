#!/bin/bash

# Ensure that the script creates the backups directory if it does not exist
if [ ! -d "backups" ]; then
    echo "Creating Backup directory.."
    mkdir backups
else
    echo "Backup directory exists"
fi

# For each specified directory, create a compressed backup file in the format backup_<directory>_<date>.tar.gz
for dir in ${@}
do
	current_date=`date`; current_date=${current_date// /}
	dir_name=`basename ${dir}`
	tar -czf backups/${dir_name}_${current_date}.tar.gz ${dir} && echo "[Backup created]: ${dir}" || echo "[Backup failed]: ${dir}" 
	
done


