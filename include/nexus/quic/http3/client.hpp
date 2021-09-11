#pragma once

#include <nexus/quic/client.hpp>
#include <nexus/quic/sockaddr.hpp>

namespace nexus::quic::http3 {

class client_connection;

class client {
  friend class client_connection;
  quic::detail::engine_state state;
 public:
  // arguments for getaddrinfo() to bind a specific address or port
  client(const char* node = nullptr, const char* service = "0");

  void local_endpoint(sockaddr_union& local);

  void close() { state.close(); }
};

class client_connection {
  friend class stream;
  quic::detail::connection_state state;
 public:
  explicit client_connection(client& c) : state(c.state) {}

  void remote_endpoint(sockaddr_union& remote);

  void connect(const sockaddr* endpoint, const char* hostname, error_code& ec);
  void connect(const sockaddr* endpoint, const char* hostname);

  void close(error_code& ec) { state.close(ec); }
  void close();
};

} // namespace nexus::quic::http3