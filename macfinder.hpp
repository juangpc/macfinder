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

const std::regex mac_regex("[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}");
const std::regex ip_regex("[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}");

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
    showHelp(false),
    table_filename(".macfinder_171921")
  {  }
  void parseInputArgs(int argc, char* argv[]);
  void showVariables();
  void printMacIpList();
  void findIps(const std::vector<std::string>& tableARP);
  bool update_table;
  bool networkIpSet;
  bool showHelp;
  std::string networkIp;
  std::vector<MacIp> macIpList;
  const char* table_filename;
private:
};


void sendPingAroundNetwork(const std::string& networkIp);

void systemCalltoFile(const std::string& call,
                      const std::string& filename);

void fileToVectorOfStrings(const std::string& filename, 
                           std::vector<std::string>& lines);

bool macIsFound(std::string& s,
                std::smatch& found,
                std::regex& p);

bool file_exists (const std::string& filename);

void delete_file(const std::string& filename);

void printUsage();


}  // namespace MACFINDER
