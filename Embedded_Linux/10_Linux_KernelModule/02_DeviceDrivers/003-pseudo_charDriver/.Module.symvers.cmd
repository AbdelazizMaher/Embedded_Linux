cmd_/home/abdelaziz/NTI_WS/Linux_Workspace/DeviceDrivers/LKM/003-pseudo_charDriver/Module.symvers := sed 's/\.ko$$/\.o/' /home/abdelaziz/NTI_WS/Linux_Workspace/DeviceDrivers/LKM/003-pseudo_charDriver/modules.order | scripts/mod/modpost -m -a  -o /home/abdelaziz/NTI_WS/Linux_Workspace/DeviceDrivers/LKM/003-pseudo_charDriver/Module.symvers -e -i Module.symvers   -T -
