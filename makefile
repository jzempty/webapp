obj1=WebServer/client.cpp
obj2=main.cpp WebServer/WebServer.cpp


Server:${obj2}
	g++ -std=c++17 -Wall -o2 -g ${obj2} -o run/Server -pthread

client:${obj1}
	g++ -std=c++17 -Wall -o2 -g ${obj1} -o run/Client

