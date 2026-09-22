#include <libssh/libssh.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <regex>


std::string getip(){
  std::string ip;
  std::cerr << "enter an IP address: \n";
  std::cin >> ip;

  return ip;
}


std::string getUser(){
  std::string user;
  std::cerr << "enter a user: \n";
  std::cin >> user;
  return user;
}


int main (){
  ssh_session my_ssh_session = ssh_new();
  std::string str_ip = getip();
  const char* ip = str_ip.c_str();
  
  if (my_ssh_session == NULL){
    std::cerr << "session NULL \n";
    exit(-1); }

  int rc = ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, ip);
  if (rc < 0){
    std::cerr << "error setting ssh host: %s\n", ssh_get_error(my_ssh_session);
    ssh_free(my_ssh_session);
    return -1;
  }


  rc = ssh_connect(my_ssh_session);
  if(rc != SSH_OK){
    std::cerr << "error connecting: %s\n", ssh_get_error(my_ssh_session);
    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);
    return -1;
  }
  ssh_disconnect(my_ssh_session);
  ssh_free(my_ssh_session);
  return 0;
}
