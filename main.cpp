#include <iostream>
#include <regex>
#include <vector>

#include "macfinder.hpp"

bool update_table(false);
bool networkIpSet(false);
bool showHelp(false);
std::string networkIp;
std::vector<MacIp> macIpList;

int main(int argc, char* argv[]) {

  parseInputArgs(argc, argv);

  // start actual execution
  if (showHelp) {
    printUsage();
    return 1;
  }

  if (update_table) {
    sendPingAroundNetwork(networkIp);
  }

  systemCalltoFile("arp -a", mac_finder_table_filename.c_str());

  std::vector<std::string> tableARP;
  fileToVectorOfStrings(mac_finder_table_filename, tableARP);

//  std::smatch mac_found;
//  std::smatch ip_found;
  for (MacIp& macip_i : macIpList) {
    for (std::string& l : tableARP) {
      std::regex mac_regex(macip_i.mac);
      if (std::regex_search(l, mac_parsed, mac_regex)) {
        if (std::regex_search(l, ip_parsed, ip_regex)) {
          macip_i.ip = ip_par[0];
        }
      }
    }
  }

  printMacIpList(macIpList);

  if (file_exists(mac_finder_table_filename)) {
    delete_file(mac_finder_table_filename);
  }

  return 0;
}


