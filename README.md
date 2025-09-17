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
./ipcalc 245.58.99.13/10

Address:   245.58.99.13
Netmask:   255.192.0.0
Wildcard:  0.63.255.255
Network:   245.0.0.0/10
Broadcast: 245.63.255.255
Host Min:  245.0.0.1
Host Max:  245.63.255.254
Hosts/Net: 4194302
Class:     E
```
``` bash
./ipcalc 230.55.255.72/29 -v

Address:   230.55.255.72       11100110.00110111.11111111.01001000
Netmask:   255.255.255.248     11111111.11111111.11111111.11111000
Wildcard:  0.0.0.7             00000000.00000000.00000000.00000111
Network:   230.55.255.72/29    11100110.00110111.11111111.01001000
Broadcast: 230.55.255.79       11100110.00110111.11111111.01001111
Host Min:  230.55.255.73       11100110.00110111.11111111.01001001
Host Max:  230.55.255.78       11100110.00110111.11111111.01001110
Hosts/Net: 6
Class:     D
Hosts:
  230.55.255.73
  230.55.255.74
  230.55.255.75
  230.55.255.76
  230.55.255.77
  230.55.255.78
```
``` bash
./ipcalc 192.168.55.99/12 -d

09:39:01 | ./ipcalc.c:73 | parseIP | DEBUG: Parsing IP string: 192.168.55.99/12
09:39:01 | ./ipcalc.c:103 | parseIP | DEBUG: Octet 1 end position: 3
09:39:01 | ./ipcalc.c:106 | parseIP | DEBUG: Octet 2 end position: 7
09:39:01 | ./ipcalc.c:109 | parseIP | DEBUG: Octet 3 end position: 10
09:39:01 | ./ipcalc.c:112 | parseIP | DEBUG: Octet 4 end position: 13
09:39:01 | ./ipcalc.c:118 | parseIP | DEBUG: Octet 1: 192
09:39:01 | ./ipcalc.c:126 | parseIP | DEBUG: Octet 2: 168
09:39:01 | ./ipcalc.c:134 | parseIP | DEBUG: Octet 3: 55
09:39:01 | ./ipcalc.c:142 | parseIP | DEBUG: Octet 4: 99
09:39:01 | ./ipcalc.c:150 | parseIP | DEBUG: Network Bit: 12
09:39:01 | ./ipcalc.c:184 | parseIP | DEBUG: Given IP: 192.168.55.99
09:39:01 | ./ipcalc.c:195 | parseIP | DEBUG: Subnet mask: 255.240.0.0
09:39:01 | ./ipcalc.c:200 | parseIP | DEBUG: Network ID: 192.160.0.0
09:39:01 | ./ipcalc.c:205 | parseIP | DEBUG: Broadcast: 192.175.255.255
Address:   192.168.55.99
Netmask:   255.240.0.0
Wildcard:  0.15.255.255
Network:   192.160.0.0/12
Broadcast: 192.175.255.255
Host Min:  192.160.0.1
Host Max:  192.175.255.254
Hosts/Net: 1048574
Class:     C
```
``` bash
./ipcalc 128.55.66.77/30 127.0.0.1/29 -v

Address:   128.55.66.77        10000000.00110111.01000010.01001101
Netmask:   255.255.255.252     11111111.11111111.11111111.11111100
Wildcard:  0.0.0.3             00000000.00000000.00000000.00000011
Network:   128.55.66.76/30     10000000.00110111.01000010.01001100
Broadcast: 128.55.66.79        10000000.00110111.01000010.01001111
Host Min:  128.55.66.77        10000000.00110111.01000010.01001101
Host Max:  128.55.66.78        10000000.00110111.01000010.01001110
Hosts/Net: 2
Class:     B
Hosts:
  128.55.66.77
  128.55.66.78

Address:   127.0.0.1           01111111.00000000.00000000.00000001
Netmask:   255.255.255.248     11111111.11111111.11111111.11111000
Wildcard:  0.0.0.7             00000000.00000000.00000000.00000111
Network:   127.0.0.0/29        01111111.00000000.00000000.00000000
Broadcast: 127.0.0.7           01111111.00000000.00000000.00000111
Host Min:  127.0.0.1           01111111.00000000.00000000.00000001
Host Max:  127.0.0.6           01111111.00000000.00000000.00000110
Hosts/Net: 6
Class:     A
Hosts:
  127.0.0.1
  127.0.0.2
  127.0.0.3
  127.0.0.4
  127.0.0.5
  127.0.0.6
```
``` bash
./ipcalc 127.2.3.4/5 190.5.4.9/10 222.255.255.255/30

Address:   127.2.3.4
Netmask:   248.0.0.0
Wildcard:  7.255.255.255
Network:   120.0.0.0/5
Broadcast: 127.255.255.255
Host Min:  120.0.0.1
Host Max:  127.255.255.254
Hosts/Net: 134217726
Class:     A

Address:   190.5.4.9
Netmask:   255.192.0.0
Wildcard:  0.63.255.255
Network:   190.0.0.0/10
Broadcast: 190.63.255.255
Host Min:  190.0.0.1
Host Max:  190.63.255.254
Hosts/Net: 4194302
Class:     B

Address:   222.255.255.255
Netmask:   255.255.255.252
Wildcard:  0.0.0.3
Network:   222.255.255.252/30
Broadcast: 222.255.255.255
Host Min:  222.255.255.253
Host Max:  222.255.255.254
Hosts/Net: 2
Class:     C
```