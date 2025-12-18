#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include <string>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace ssl = asio::ssl;
namespace websocket = beast::websocket;
using tcp = asio::ip::tcp;

static nlohmann::json subscribe_msg(const std::string& channel) {
  return {
      {"jsonrpc", "2.0"},
      {"id", 1},
      {"method", "public/subscribe"},
      {"params", {{"channels", nlohmann::json::array({channel})}}}};
}

int main() {
  try {
    const std::string host = "www.deribit.com";
    const std::string port = "443";
    const std::string target = "/ws/api/v2";
    const std::string channel = "deribit_volatility_index.btc_usd";

    spdlog::set_level(spdlog::level::info);
    spdlog::info("Connecting to wss://{}{} (channel={})", host, target, channel);

    asio::io_context ioc;
    ssl::context ctx{ssl::context::tlsv12_client};
    ctx.set_default_verify_paths();

    tcp::resolver resolver{ioc};
    beast::ssl_stream<beast::tcp_stream> tls_stream{ioc, ctx};

    auto results = resolver.resolve(host, port);
    beast::get_lowest_layer(tls_stream).connect(results);
    spdlog::info("TCP connected");

    tls_stream.handshake(ssl::stream_base::client);
    spdlog::info("TLS handshake ok");

    websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws{std::move(tls_stream)};
    ws.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));
    ws.set_option(websocket::stream_base::decorator([](websocket::request_type& req) {
      req.set(http::field::user_agent, "VolLabTerminal/0.1");
    }));

    ws.handshake(host, target);
    spdlog::info("WebSocket handshake ok");

    const auto sub = subscribe_msg(channel).dump();
    ws.write(asio::buffer(sub));
    spdlog::info("Subscribe sent");

    beast::flat_buffer buffer;
    for (;;) {
      buffer.clear();
      ws.read(buffer);
      const auto msg = beast::buffers_to_string(buffer.data());

      try {
        auto j = nlohmann::json::parse(msg);
        spdlog::info("RX {}", j.dump());
      } catch (...) {
        spdlog::info("RX {}", msg);
      }
    }
  } catch (const std::exception& e) {
    spdlog::error("Fatal: {}", e.what());
    return 1;
  }
}
