# ipcalc
## Help:
``` bash
./ipcalc -h

Calculate CIDR IP Address

./ipcalc <A.B.C.D/XY>

[-h || --help]     Print this help message
[-d || --debug]    Dispaly debug output
[-v || --verbose]  List IP address of each host
<A.B.C.D/XY>       CIDR IP address
```
## Examples:
``` bash
./ipcalc 98.76.54.32/10
Address:   98.76.54.32
Netmask:   255.192.0.0
Wildcard:  0.63.255.255
Network:   98.64.0.0/10
Broadcast: 98.127.255.255
Host Min:  98.64.0.1
Host Max:  98.127.255.254
Hosts/Net: 4194302
Class:     A
```
``` bash
./ipcalc 192.168.1.250/29 -v
Address:   192.168.1.250       11000000.10101000.00000001.11111010
Netmask:   255.255.255.248     11111111.11111111.11111111.11111000
Wildcard:  0.0.0.7             00000000.00000000.00000000.00000111
Network:   192.168.1.248/29    11000000.10101000.00000001.11111000
Broadcast: 192.168.1.255       11000000.10101000.00000001.11111111
Host Min:  192.168.1.249       11000000.10101000.00000001.11111001
Host Max:  192.168.1.254       11000000.10101000.00000001.11111110
Hosts/Net: 6
Class:
Hosts:
  192.168.1.249
  192.168.1.250
  192.168.1.251
  192.168.1.252
  192.168.1.253
  192.168.1.254
```
``` bash
./ipcalc 10.1.2.3/12 -d
12:29:43 | ./ipcalc.c:71 | parseIP | DEBUG: Parsing IP string: 10.1.2.3/12
12:29:43 | ./ipcalc.c:101 | parseIP | DEBUG: Octet 1 end position: 2
12:29:43 | ./ipcalc.c:103 | parseIP | DEBUG: Octet 2 end position: 4
12:29:43 | ./ipcalc.c:105 | parseIP | DEBUG: Octet 3 end position: 6
12:29:43 | ./ipcalc.c:107 | parseIP | DEBUG: Octet 4 end position: 8
12:29:43 | ./ipcalc.c:113 | parseIP | DEBUG: Octet 1: 10
12:29:43 | ./ipcalc.c:121 | parseIP | DEBUG: Octet 2: 1
12:29:43 | ./ipcalc.c:129 | parseIP | DEBUG: Octet 3: 2
12:29:43 | ./ipcalc.c:137 | parseIP | DEBUG: Octet 4: 3
12:29:43 | ./ipcalc.c:145 | parseIP | DEBUG: Network Bit: 12
12:29:43 | ./ipcalc.c:179 | parseIP | DEBUG: Given IP: 10.1.2.3
12:29:43 | ./ipcalc.c:190 | parseIP | DEBUG: Subnet mask: 255.240.0.0
12:29:43 | ./ipcalc.c:195 | parseIP | DEBUG: Network ID: 10.0.0.0
12:29:43 | ./ipcalc.c:200 | parseIP | DEBUG: Broadcast: 10.15.255.255
Address:   10.1.2.3
Netmask:   255.240.0.0
Wildcard:  0.15.255.255
Network:   10.0.0.0/12
Broadcast: 10.15.255.255
Host Min:  10.0.0.1
Host Max:  10.15.255.254
Hosts/Net: 1048574
Class:     A
```