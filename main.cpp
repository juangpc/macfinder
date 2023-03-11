#include <iostream>
#include <regex>
#include <vector>

#include "macfinder.hpp"

int main(int argc, char* argv[]) {

  MACFINDER::MacFinderApp app;

  app.parseInputArgs(argc, argv);
  if (app.errorParsingArgs) {
    MACFINDER::printUsage();
    return 1;
  }

  if (app.update_table) {
    MACFINDER::sendPingAroundNetwork(app.networkIp);
  }
  app.findIps();


  return 0;
}


