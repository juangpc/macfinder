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

  app.findIps(tableARP);

  app.printMacIpList();

  if (MACFINDER::file_exists(app.table_filename)) {
    MACFINDER::delete_file(app.table_filename);
  }

  return 0;
}


