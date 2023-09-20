#include "socket.hpp"

/** 
Reference xz353's code in hw2 http server. Note: it is already published in https://github.com/WaAaaAterfall/ECE568-HTTP-Proxy
*/

/**
Return -1 on failure, 0 on success
modify len to bytes that actually sent 
*/
int my_socket::sendall(int sock_fd, char * buf, int * len) {
  //reference from Beej's Guide
  int total = 0;         // how many bytes we've sent
  int bytesleft = *len;  // how many we have left to send
  int n;
  while (total < *len) {
    n = send(sock_fd, buf + total, bytesleft, 0);
    if (n == -1) {
      break;
    }
    total += n;
    bytesleft -= n;
  }
  *len = total;             // return number actually sent here
  return n == -1 ? -1 : 0;  // return -1 on failure, 0 on success
}

/** 
Return -1 on failure
listen fd on success
*/
int my_socket::create_tcp_listener_fd(const char * port) {  //reference from Beej's Guide
  int listener_fd = -1;
  int status = -1;
  struct addrinfo host_info_hints;
  struct addrinfo * host_info_list;
  struct addrinfo * host_ptr;

  memset(&host_info_hints, 0, sizeof(host_info_hints));
  host_info_hints.ai_family = AF_UNSPEC;
  host_info_hints.ai_socktype = SOCK_STREAM;  //TCP
  host_info_hints.ai_flags = AI_PASSIVE;

  status = getaddrinfo(NULL, port, &host_info_hints, &host_info_list);
  if (status != 0) {
    return -1;
  }

  for (host_ptr = host_info_list; host_ptr != NULL; host_ptr = host_ptr->ai_next) {
    listener_fd =
        socket(host_ptr->ai_family, host_ptr->ai_socktype, host_ptr->ai_protocol);
    if (listener_fd == -1) {
      continue;
    }
    int yes = 1;
    setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    status = bind(listener_fd, host_ptr->ai_addr, host_ptr->ai_addrlen);
    if (status == -1) {
      continue;
    }
    break;  //successful create socket and bind
  }

  freeaddrinfo(host_info_list);
  if (host_ptr == NULL) {
    return -1;
  }

  status = listen(listener_fd, 20);
  if (status == -1) {
    return -1;
  }

  return listener_fd;
}

/** 
Return -1 on failure
socket fd on success
*/
int my_socket::connect_to_host(const char * theHostname,
                               const char * thePort) {  //reference from Beej's Guide
  int status;
  int socket_fd;
  struct addrinfo host_info;
  struct addrinfo * host_info_list;
  struct addrinfo * host_ptr;
  const char * hostname = theHostname;
  const char * port = thePort;
  memset(&host_info, 0, sizeof(host_info));
  host_info.ai_family = AF_UNSPEC;
  host_info.ai_socktype = SOCK_STREAM;
  status = getaddrinfo(hostname, port, &host_info, &host_info_list);
  if (status != 0) {
    return -1;
  }

  for (host_ptr = host_info_list; host_ptr != NULL; host_ptr = host_ptr->ai_next) {
    socket_fd = socket(host_ptr->ai_family, host_ptr->ai_socktype, host_ptr->ai_protocol);
    if (socket_fd == -1) {
      continue;
    }
    break;  //successful create socket and bind
  }

  if (host_ptr == NULL) {
    return -1;
  }

  status = connect(socket_fd, host_info_list->ai_addr, host_info_list->ai_addrlen);
  if (status == -1) {
    return -1;
  }
  freeaddrinfo(host_info_list);
  return socket_fd;
}

/**
Return the new accepted socket fd,
also modifies the "request_ip" to the ip of the client
*/
int my_socket::accpect_connection(int listener, std::string & request_ip) {
  struct sockaddr_storage client_socket_addr;
  socklen_t len = sizeof(client_socket_addr);
  int new_fd = accept(listener, (struct sockaddr *)&client_socket_addr, &len);
  char ip_buffer[INET6_ADDRSTRLEN];
  inet_ntop(client_socket_addr.ss_family,
            get_in_addr((struct sockaddr *)&client_socket_addr),
            ip_buffer,
            INET6_ADDRSTRLEN);
  request_ip = std::string(ip_buffer);
  return new_fd;
}

//Reference: Beej's Guide
// Get sockaddr, IPv4 or IPv6:
void * my_socket::get_in_addr(struct sockaddr * sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}
