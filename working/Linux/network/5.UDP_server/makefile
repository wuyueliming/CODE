.PHONY:all
all:udpclient udpserver

udpclient:UDPclient.cc
	g++ -o $@ $^ -std=c++17 
udpserver:UDPserver.cc
	g++ -o $@ $^ -std=c++17

.PHONY:clean
clean:
	rm -f udpclient udpserver