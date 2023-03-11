#include <iostream>
#include <regex>
#include <vector>

#include "macfinder.hpp"

int main(int argc, char* argv[]) {

  MACFINDER::MacFinderApp app;

  app.parseInputArgs(argc, argv);

  if (app.showHelp) {
    MACFINDER::printUsage();
    return 1;
  }

  if (app.update_table) {
    MACFINDER::sendPingAroundNetwork(app.networkIp);
  }
  app.findIps();

  for (const MACFINDER::MacIp& macip_i : app.macIpList) {
    std::cout << "mac: " << macip_i.mac << " - ip: "
        << (macip_i.ip.empty() ? "not found" : macip_i.ip.c_str())
        << "\n";
  }

  return 0;
}


