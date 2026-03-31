.PHONY:all
all:tcpclient tcpserver

tcpclient:TCPclient.cc
	g++ -o $@ $^ -std=c++17 
tcpserver:TCPserver.cc
	g++ -o $@ $^ -std=c++17

.PHONY:clean
clean:
	rm -f tcpclient tcpserver
