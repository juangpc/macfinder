#include "macfinder.hpp"

namespace MACFINDER {

void MacFinderApp::printMacIpList() const {
  for (const MacIp& macip_i : macIpList) {
    std::cout << "mac: " << macip_i.mac << " - ip: " << macip_i.ip << "\n";
  }
}

void printMacIpList(const std::vector<MacIp>& macIpList) {
  for (const MacIp& macip_i : macIpList) {
    std::cout << "mac: " << macip_i.mac << " - ip: "
      << (macip_i.ip.empty() ? "not found" : macip_i.ip)
      << "\n";
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
        // std::cout << line << "\n";
        if (std::regex_search(line, ip_found, IP_REGEX)) {
          macip_i.ip = ip_found[0];
        }
      }
    }
    fp.clear();
    fp.seekg(0);
  }
  fp.close();
  delete_file(arp_table_filename);
}

void printAllInputArg(int argc, char* argv[]) {
  std::cout << " =====  printing all args  ======\n"
    << "\n"
    << "num args: " << argc << "\n";
  for (int ii = 0; ii < argc; ii++) {
    std::cout << ii << " - " << argv[ii] << "\n";
  }
  std::cout << "\n";
}

void MacFinderApp::parseInputArgs(int argc, char* argv[]) {
  //printAllInputArg(argc, argv);
  std::string arg;

  if (argc == 1) {
    errorParsingArgs = true;
  } else {
    for (int argi = 1; argi < argc; argi++) {
      arg = argv[argi];
      std::smatch ip_parsed, ip_net_parsed, mac_parsed;
      if ((arg == "-h") || (arg == "--help")) {
        printHelp();
        exit(0);
      }
      else if ( arg == "--version") {
        printVersion();
        exit(0);
      }
      else if ( arg  == "--update_table" || arg == "-u") { 
        update_table = true;
      }
      else if (std::regex_search(arg, ip_parsed, IP_REGEX) && !networkIpSet) {
        std::regex_search(arg, ip_net_parsed, IP_NET_REGEX);
        networkIp = ip_net_parsed.str(0);
        networkIpSet = true;
      }
      else if (std::regex_search(arg, mac_parsed, MAC_REGEX)) {
        macIpList.emplace_back(MacIp(mac_parsed[0],""));
      } 
      else {
        std::cout << "Incorrect usage: " << arg << "\n";
        errorParsingArgs = true;
      }
    }
  }
}

void MacFinderApp::showState() const {
  std::cout << " =====  start show variables  =====\n";
  std::cout << "NetworkIP: " << networkIp << "\n";
  std::cout << "update_table:" << update_table << "\n"; 
  std::cout << "networkIpSet:" << networkIpSet << "\n";
  std::cout << "showHelp:" << errorParsingArgs << "\n";
  printMacIpList();
  std::cout << " =====  end show variables  =====\n";
}

void sendPingsAroundNetwork(const std::string& networkIp) {
  std::string appStr("ping");
  std::string appFlags("-c 1 -w 0.002");
  std::thread* threads[255];
  for(int i = 0; i < 255; i++) {
    std::string commandStr = appStr + " " + \
      appFlags + " " + networkIp + "." + std::to_string(i) + " &>/dev/null";
    //std::cout << commandStr << "\n";
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

void printVersion() {
  std::cout << "\n"
    << "MacFinder 0.1 (2023)\n"
    << "author: juangpc\n"
    << "\n";
}

void printHelp() {
  printVersion();
  std::cout 
    << "Usage: ./macfinder [--update_table|-u] <network_ip> <mac_address_list>\n"
    << "\n"
    << "--help (-h)          Show (this) help.\n"
    << "--version            Show version.\n"
    << "--update_table (-u)  Update the list of known hosts in the network.\n"
    << "<networ_ip>          Network IP example: 192.169.1.0\n"
    << "<mac_address_list>   MAC addresses list should be specified as a \n"
    << "                     space-separated list. Use lower case letters.\n"
    << "\n"
    << "Ex: ./macfinder -u 172.21.16.0 00:0e:c6:5b:65:ab 00:0e:c6:73:c7:31\n"
    << "\n"
    << "\n";
}

}  // namespace MACFINDER 
