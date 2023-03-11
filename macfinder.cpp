#include "macfinder.hpp"

namespace MACFINDER {

void MacFinderApp::printMacIpList() const {
  for (const MacIp& macip_i : macIpList) {
    std::cout << "mac: " << macip_i.mac << " - ip: " << macip_i.ip << "\n";
  }
}

void MacFinderApp::findIps() {
  systemCalltoFile("arp -a", arp_table_filename);
  std::ifstream fp(arp_table_filename);
  if (!fp.is_open()) {
    std::cout << "Error: Unable to open arp file table.\n";
    return;
  } 

  std::string line;
  for (MacIp& macip_i : macIpList) {
      while (std::getline(fp, line)) {
        std::smatch mac_found;
      std::regex mac_i(macip_i.mac);
        if (std::regex_search(line, mac_found, mac_i)) {
          std::smatch ip_found;
          if (std::regex_search(line, ip_found, MACFINDER::ip_regex)) {
            macip_i.ip = ip_found[0];
        }
      }
    }
  }
  fp.close();
  delete_file(arp_table_filename);
}

void MacFinderApp::parseInputArgs(int argc, char* argv[]) {
  std::string arg;
  // parse argumets
  if (argc < 3) {
    showHelp = true;
  }
  for (size_t argi = 1; argi < argc; argi++) {
    arg = argv[argi];
    std::smatch ip_parsed, mac_parsed;
    if ( arg  == "--update_table" || arg == "-u") { 
      update_table = true;
    }
    else if (std::regex_search(arg, ip_parsed, ip_regex) && !networkIpSet) {
      networkIp = arg;
      networkIpSet = true;
    }
    else if (std::regex_search(arg, mac_parsed, mac_regex)) {
      macIpList.emplace_back(MacIp(mac_parsed[0],""));
    } 
    else {
      std::cout << "Incorrect argument format: " << arg << "\n";
      showHelp = true;
    }
  }
}

void MacFinderApp::showState() const {
  std::cout << " =====  start show variables  =====\n";
  std::cout << "NetworkIP: " << networkIp << "\n";
  std::cout << "update_table:" << update_table << "\n"; 
  std::cout << "networkIpSet:" << networkIpSet << "\n";
  std::cout << "showHelp:" << showHelp << "\n";
  printMacIpList();
  std::cout << " =====  end show variables  =====\n";
}

void sendPingAroundNetwork(const std::string& networkIp) {
  std::string appStr("ping");
  std::string appFlags("-c 1 -w 0.002");
  std::thread* threads[255];
  for(int i = 0; i < 255; i++) {
    std::string commandStr = appStr + " " + \
      appFlags + " " + networkIp + "." + std::to_string(i) + " &>/dev/null";
    threads[i] = new std::thread(
        [=] {
          std::system(commandStr.c_str());
        });
  }
  for(int i = 0; i < 255; i++) {
    threads[i]->join();
  }
}

void systemCalltoFile(const std::string& call, const std::string& filename) { 
  std::string callStr(call);
  callStr.append(" > ").append(filename);
  std::system(callStr.c_str());
}

void delete_file(const std::string& filename) {
  std::string command("rm -f");
  std::system(command.append(" ").append(filename).c_str());
}

void printUsage() {
  std::cout << "\n"
            << "Usage: ./mac_finder [--update_table|-u] <network_ip> <mac_address> [<mac_address>]\n"
            << "\n"
            << "MAC addresses should be specified as a space-separated list.\n"
            << "Use lower case letters. Ex. 00:0e:c6:5b:65:ab" << "\n"
            << "\n";
}

}  // namespace MACFINDER 
