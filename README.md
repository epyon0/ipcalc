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
``` bash
./ipcalc 10.3.4.5/30 192.168.5.4/29 -v

Address:   10.3.4.5            00001010.00000011.00000100.00000101
Netmask:   255.255.255.252     11111111.11111111.11111111.11111100
Wildcard:  0.0.0.3             00000000.00000000.00000000.00000011
Network:   10.3.4.4/30         00001010.00000011.00000100.00000100
Broadcast: 10.3.4.7            00001010.00000011.00000100.00000111
Host Min:  10.3.4.5            00001010.00000011.00000100.00000101
Host Max:  10.3.4.6            00001010.00000011.00000100.00000110
Hosts/Net: 2
Class:     A
Hosts:
  10.3.4.5
  10.3.4.6

Address:   192.168.5.4         11000000.10101000.00000101.00000100
Netmask:   255.255.255.248     11111111.11111111.11111111.11111000
Wildcard:  0.0.0.7             00000000.00000000.00000000.00000111
Network:   192.168.5.0/29      11000000.10101000.00000101.00000000
Broadcast: 192.168.5.7         11000000.10101000.00000101.00000111
Host Min:  192.168.5.1         11000000.10101000.00000101.00000001
Host Max:  192.168.5.6         11000000.10101000.00000101.00000110
Hosts/Net: 6
Class:
Hosts:
  192.168.5.1
  192.168.5.2
  192.168.5.3
  192.168.5.4
  192.168.5.5
  192.168.5.6
```
``` bash
./ipcalc 1.2.3.4/5 6.7.8.9/10 12.34.56.78/32

Address:   1.2.3.4
Netmask:   248.0.0.0
Wildcard:  7.255.255.255
Network:   0.0.0.0/5
Broadcast: 7.255.255.255
Host Min:  0.0.0.1
Host Max:  7.255.255.254
Hosts/Net: 134217726
Class:     A

Address:   6.7.8.9
Netmask:   255.192.0.0
Wildcard:  0.63.255.255
Network:   6.0.0.0/10
Broadcast: 6.63.255.255
Host Min:  6.0.0.1
Host Max:  6.63.255.254
Hosts/Net: 4194302
Class:     A

Address:   12.34.56.78
Netmask:   255.255.255.255
Wildcard:  0.0.0.0
Network:   12.34.56.78/32
Broadcast: 12.34.56.78
Host Min:  12.34.56.79
Host Max:  12.34.56.77
Hosts/Net: -1
Class:     A
```