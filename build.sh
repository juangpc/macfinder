#/bin/sh!


g++ -std=c++17 main.cpp macfinder.cpp -o macfinder -lpthread -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror 

g++ -std=c++17 main.cpp macfinder.cpp -o macfinder -lpthread 
./macfinder 172.21.16.0 00:0e:c6:5b:65:ab 00:0e:c6:73:c7:31 
./macfinder --update_table 172.21.16.0 00:0e:c6:5b:65:ab 00:0e:c6:73:c7:31 

