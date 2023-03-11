#/bin/sh!


g++ -std=c++14 main.cpp macfinder.cpp -o macfinder -lpthread -g -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror 
g++ -std=c++14 main.cpp macfinder.cpp -o macfinder -lpthread -O3 

g++ -std=c++17 main.cpp macfinder.cpp -o macfinder -lpthread -O3

./macfinder 172.21.16.0 00:0e:c6:5b:65:ab 00:0e:c6:73:c7:31 
./macfinder -u 172.21.16.0 00:0e:c6:5b:65:ab 00:0e:c6:73:c7:31
./macfinder --update_table 172.21.16.0 00:0e:c6:5b:65:ab 00:0e:c6:73:c7:31 
./macfinder -u --172.21.16.0 00:0e:c6:5b:65:ab 00:0e:c6:73:c7:31 
./macfinder --version
./macfinder -h
./macfinder --help

