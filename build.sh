#/bin/sh!
#
#
#


g++ -std=c++17 main.cpp mac_finder.cpp -o mac_finder -lpthread
./mac_finder 172.21.16.0 00:0e:c6:5b:65:ab 00:0e:c6:73:c7:31 
./mac_finder --update_table 172.21.16.0 00:0e:c6:5b:65:ab 00:0e:c6:73:c7:31 

std::regex ip_regex("[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}");
