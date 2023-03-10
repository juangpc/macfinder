#include "macfinder.hpp"

namespace MACFINDER {

std::smatch ip_parsed;
std::regex ip_regex("[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}");
std::smatch mac_parsed;
std::regex mac_regex("[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}");

void sendPingAroundNetwork(const std::string& networkIp) {
  std::string appStr("ping");
  std::string appFlags("-c 1 -w 0.002");

  std::thread* threads[255];

  for(int i = 0; i < 255; i++) {
    std::string commandStr = appStr + " " + \
      appFlags + " " + networkIp + "." + std::to_string(i) + \
      " &>/dev/null";
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

void fileToVectorOfStrings(const std::string& filename,
                           std::vector<std::string>& lines) {
  std::string line;
  std::ifstream fp(filename);
  
  if (fp.is_open()) {
    while (std::getline(fp, line)) {
      lines.push_back(line);
    }
  }

}

bool file_exists (const std::string& filename) {
  struct stat buffer;   
  return (stat (filename.c_str(), &buffer) == 0); 
}


void printMacIpList(const std::vector<MacIp>& list) {
  for (const MacIp& macip_i : list) {
    std::cout << "mac: " << macip_i.mac << " - ip: " << macip_i.ip << "\n";
  }
}

void printUsage() {
  std::cout << "\n";
  std::cout << "Usage: ./mac_finder [--update_table] <network_ip> <mac_address> [<mac_address>]\n\n";
  std::cout << "\n";
  std::cout << "MAC addresses should be specified as a space-separated list. "
            << "Use lower case letters. Ex. 00:0e:c6:5b:65:ab" << "\n";
}

void MacFinderApp::showVariables() {
  std::cout << " =====  start show variables  =====\n";
  std::cout << "NetworkIP: " << networkIp << "\n";
  std::cout << "update_table:" << update_table << "\n"; 
  std::cout << "networkIpSet:" << networkIpSet << "\n";
  std::cout << "showHelp:" << showHelp << "\n";
  printMacIpList(macIpList);
  std::cout << " =====  end show variables  =====\n";
}

void MacFinderApp::parseInputArgs(int argc, char* argv[]) {
  std::string arg;
  // parse argumets
  if (argc < 3) {
    showHelp = true;
  }
  for (size_t argi = 1; argi < argc; argi++) {
    arg = argv[argi];
    if ( arg  == "--update_table") { 
      update_table = true;
    } 
    else if (std::regex_search(arg, ip_parsed, ip_regex) && !networkIpSet ) {
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

}  // namespace MACFINDER 
