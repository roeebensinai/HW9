CC = g++ 
CCFLAGS = -Wall -Wextra 
RM = rm -f 

all:firewall.exe

firewall:
	$(CC) ${CCFLAGS} -fPIC -shared string.cpp field.cpp ip.cpp port.cpp -o libfirewall.so -L. -g

firewall.exe: firewall
	$(CC) ${CCFLAGS} main.cpp -o firewall.exe -lfirewall -linput -L. -g

clean:
	-${RM} firewall firewall.exe