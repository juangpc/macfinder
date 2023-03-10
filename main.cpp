#include <iostream>
#include <regex>
#include <vector>

#include "macfinder.hpp"


int main(int argc, char* argv[]) {

 
  // show variables
  showVariables();
  std::cout << " =====  start show variables  =====\n";
  std::cout << "NetworkIP: " << networkIp << "\n";
  std::cout << "update_table:" << update_table << "\n"; 
  std::cout << "networkIpSet:" << networkIpSet << "\n";
  std::cout << "showHelp:" << showHelp << "\n";
  printMacIpList(macIpList);
  std::cout << " =====  end show variables  =====\n";

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
//  for (std::string& l: lines) {
//    if (std::regex_search(l, ip_found, ip_regex)) {
//      std::cout << "found!\n";
//        for (size_t i_found = 0; i_found < ip_found.size(); ++i_found) 
//          std::cout << i_found << ": " << ip_found[i_found] << '\n';
//    }
//  }
//

//    std::cout << "\n\n";
//  std::cout << "Searching for mac addresses\n";
//  std::cout << "\n\n";
//  std::smatch mac_found;
//  for ( std::string& maci : macList) {
//    for (std::string& l : lines) {
//        std::regex mac_regex(maci);
//        if (std::regex_search(l, mac_found, mac_regex)) {
//            if (std::regex_search(l, ip_found, ip_regex)) {
//                std::cout << maci << " - " << ip_found[0] << "\n";
//            }
//        }
//    }
//  }
    //   std::ofstream fp(".2222");
    //   fp.write(macList[0].c_str(), macList[0].size());
    //   fp.write(macList[1].c_str(), macList[1].size());
    //   fp.close();

    //   std::ifstream fp(".2222");

  //std::vector<std::string> lines;
  //for (int i = 0; i < 2; i++) {
  //  lines.push_back(txtList[i]);
  //}

  //for (std::string& s: lines) {
  //  std::cout << s << "\n";
  //}


//   if (fp.is_open()) {
//     while (std::getline(fp, line)) {
//       for (int mac_i = 0; mac_i < 2; mac_i++) {
//         if (line.find(macList[mac_i])) {
//           std::regex ip_regex("\((([0-9]{1,3}\.?){4})\)");
//           std::smatch ip_found;
//           if (std::regex_search(line, ip_found, ip_regex)) {
//             //std::cout << "Chassis: " << mac_i << " (" << macList[mac_i] 
//             //  << ") - ip: " << ipAddr << "\n";
//             for (size_t i = 0; i < ip_found.size(); ++i) 
//               std::cout << i << ": " << ip_found[i] << '\n';
//           }

//         }
//       }

 //     if(line.find(macList[1]))

//      std::cout << line << "\n";
//     }
//   }

//   fp.close();
//   std::system("rm .2222");

  return 0;
}


