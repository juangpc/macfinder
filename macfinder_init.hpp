#include <string>
#include <vector>
#include <iostream>
#include <regex>

const std::string mac_finder_table_filename(".mac_finder_171921");

struct MacIp {
  MacIp(const std::string& mac_, const std::string& ip_): mac(mac_), ip(ip_){};
  std::string mac;
  std::string ip;
};

bool update_table(false);
bool networkIpSet(false);
bool showHelp(false);
std::string networkIp;
std::vector<MacIp> macIpList;

std::smatch ip_parsed;
std::regex ip_regex("[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}");
std::smatch mac_parsed;
std::regex mac_regex("[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}:[0-9a-f]{2}");

