#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <thread>
#include <cstdlib>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

struct MacIp {
  MacIp(const std::string& mac_, 
        const std::string& ip_)
  : mac(mac_), ip(ip_)
  {};
  std::string mac;
  std::string ip;
};

void sendPingAroundNetwork(const std::string& networkIp);

void systemCalltoFile(const std::string& call,
                      const std::string& filename);

void fileToVectorOfStrings(const std::string& filename, 
                           std::vector<std::string>& lines);

bool file_exists (const std::string& filename);

void delete_file(const std::string& filename);

void printMacIpList(const std::vector<MacIp>& list);

void printUsage();

void showVariables();

void parseInputArgs(int argc, char* argv[]);

