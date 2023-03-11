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

namespace MACFINDER {

const std::regex MAC_REGEX("[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}");
const std::regex IP_REGEX("[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}");

struct MacIp {
  MacIp(const std::string& mac_, 
        const std::string& ip_)
  : mac(mac_), ip(ip_)
  {};
  std::string mac;
  std::string ip;
};

class MacFinderApp {
public: 
  MacFinderApp()
    : update_table(false),
    networkIpSet(false), 
    errorParsingArgs(false),
    arp_table_filename(".macfinder_171921")
  {  }
  void printMacIpList() const;
  void findIps();
  void parseInputArgs(int argc, char* argv[]);
  void showState() const;
  bool update_table;
  bool networkIpSet;
  bool errorParsingArgs;
  std::string networkIp;
  std::vector<MacIp> macIpList;
  const char* arp_table_filename;
private:
  std::vector<std::string> talbeARP;
};

void printMacIpList(const std::vector<MacIp>& macIpList);

void sendPingsAroundNetwork(const std::string& networkIp);

void systemCalltoFile(const std::string& call,
                      const std::string& filename);

void delete_file(const std::string& filename);

void printVersion();

void printHelp();

void printAllInputArg(int argc, char* argv[]);

}  // namespace MACFINDER
