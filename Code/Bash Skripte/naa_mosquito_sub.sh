gnome-terminal --title="PCIe1" -- mosquitto_sub -h 172.24.10.176 -t "PCIe1/#" -F %X
gnome-terminal --title="PCIe2" -- mosquitto_sub -h 172.24.10.176 -t "PCIe2/#" -F %X
gnome-terminal --title="Config" -- mosquitto_sub -h 172.24.10.176 -t "Config/#" 

