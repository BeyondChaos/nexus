#pragma once

#include <string_view>

#include <boost/intrusive_ptr.hpp>

#include <nexus/error_code.hpp>

struct ssl_ctx_st; // SSL_CTX from openssl/ssl.h
struct ssl_method_st; // SSL_METHOD

void intrusive_ptr_add_ref(ssl_ctx_st* ctx);
void intrusive_ptr_release(ssl_ctx_st* ctx);

namespace nexus::quic::ssl {

using context_ptr = boost::intrusive_ptr<ssl_ctx_st>;

context_ptr context_create(const ssl_method_st* method);

// certificate lookup interface for SSL_set_cert_cb()
class certificate_provider {
 public:
  virtual ~certificate_provider() = default;

  virtual ssl_ctx_st* get_certificate_for_name(std::string_view sni) = 0;
};

} // namespace nexus::quic::ssl
