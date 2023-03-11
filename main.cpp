#include <iostream>
#include <regex>
#include <vector>

#include "macfinder.hpp"

int main(int argc, char* argv[]) {

  MACFINDER::MacFinderApp app;

  app.parseInputArgs(argc, argv);

  // start actual execution
  if (app.showHelp) {
    MACFINDER::printUsage();
    return 1;
  }

  if (app.update_table) {
    MACFINDER::sendPingAroundNetwork(app.networkIp);
  }

  MACFINDER::systemCalltoFile("arp -a", app.table_filename);

  std::vector<std::string> tableARP;
  MACFINDER::fileToVectorOfStrings(app.table_filename, tableARP);

//  std::smatch mac_found;
//  std::smatch ip_found;
  for (MACFINDER::MacIp& macip_i : app.macIpList) {
    for (std::string& l : tableARP) {
      std::regex mac_regex(macip_i.mac);
      if (std::regex_search(l, MACFINDER::mac_parsed, mac_regex)) {
        if (std::regex_search(l,MACFINDER::ip_parsed, ip_regex)) {
          macip_i.ip = ip_par[0];
        }
      }
    }
  }

  MACFINDER::printMacIpList(macIpList);

  if (file_exists(app.table_filename)) {
    delete_file(app.table_filename);
  }

  return 0;
}


