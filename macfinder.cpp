#include "macfinder.hpp"

namespace MACFINDER {

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

bool macIsFound(std::string& s,
                std::smatch& found,
                std::regex& p) {
  return std::regex_search(s,found,p);
}

bool file_exists (const std::string& filename) {
  struct stat buffer;   
  return (stat (filename.c_str(), &buffer) == 0); 
}


void MacFinderApp::printMacIpList() {
  for (const MacIp& macip_i : macIpList) {
    std::cout << "mac: " << macip_i.mac << " - ip: " << macip_i.ip << "\n";
  }
}

void MacFinderApp::findIps(const std::vector<std::string>& tableARP) {
  for (MacIp& macip_i : macIpList) {
    for (const std::string& l : tableARP) {
      std::regex mac_i(macip_i.mac);
      std::smatch mac_found;
      if (std::regex_search(l, mac_found, mac_i)) {
        std::smatch ip_found;
        if (std::regex_search(l, ip_found, MACFINDER::ip_regex)) {
          macip_i.ip = ip_found[0];
        }
      }
    }
  }
}

void printUsage() {
  std::cout << "\n"
            << "Usage: ./mac_finder [--update_table|-u] <network_ip> <mac_address> [<mac_address>]\n"
            << "\n"
            << "MAC addresses should be specified as a space-separated list.\n"
            << "Use lower case letters. Ex. 00:0e:c6:5b:65:ab" << "\n"
            << "\n";
}

void MacFinderApp::showVariables() {
  std::cout << " =====  start show variables  =====\n";
  std::cout << "NetworkIP: " << networkIp << "\n";
  std::cout << "update_table:" << update_table << "\n"; 
  std::cout << "networkIpSet:" << networkIpSet << "\n";
  std::cout << "showHelp:" << showHelp << "\n";
  printMacIpList();
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

}  // namespace MACFINDER 
