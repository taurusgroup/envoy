#include "source/common/network/matching/inputs.h"

#include "envoy/http/filter.h"
#include "envoy/registry/registry.h"

#include "absl/strings/str_cat.h"

namespace Envoy {
namespace Network {
namespace Matching {

template <>
Matcher::DataInputGetResult
DestinationIPInput<UdpMatchingData>::get(const UdpMatchingData& data) const {
  const auto& address = data.localAddress();
  if (address.type() != Network::Address::Type::Ip) {
    return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable, absl::nullopt};
  }
  return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable,
          address.ip()->addressAsString()};
}

template <>
Matcher::DataInputGetResult
DestinationPortInput<UdpMatchingData>::get(const UdpMatchingData& data) const {
  const auto& address = data.localAddress();
  if (address.type() != Network::Address::Type::Ip) {
    return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable, absl::nullopt};
  }
  return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable,
          absl::StrCat(address.ip()->port())};
}

template <>
Matcher::DataInputGetResult SourceIPInput<UdpMatchingData>::get(const UdpMatchingData& data) const {
  const auto& address = data.remoteAddress();
  if (address.type() != Network::Address::Type::Ip) {
    return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable, absl::nullopt};
  }
  return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable,
          address.ip()->addressAsString()};
}

template <>
Matcher::DataInputGetResult
SourcePortInput<UdpMatchingData>::get(const UdpMatchingData& data) const {
  const auto& address = data.remoteAddress();
  if (address.type() != Network::Address::Type::Ip) {
    return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable, absl::nullopt};
  }
  return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable,
          absl::StrCat(address.ip()->port())};
}

Matcher::DataInputGetResult TransportProtocolInput::get(const MatchingData& data) const {
  const auto transport_protocol = data.socket().detectedTransportProtocol();
  if (!transport_protocol.empty()) {
    return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable,
            std::string(transport_protocol)};
  }
  return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable, absl::nullopt};
}

Matcher::DataInputGetResult ApplicationProtocolInput::get(const MatchingData& data) const {
  const auto& protocols = data.socket().requestedApplicationProtocols();
  if (!protocols.empty()) {
    return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable,
            absl::StrCat("'", absl::StrJoin(protocols, "','"), "'")};
  }
  return {Matcher::DataInputGetResult::DataAvailability::AllDataAvailable, absl::nullopt};
}

class DestinationIPInputFactory : public DestinationIPInputBaseFactory<MatchingData> {};
class UdpDestinationIPInputFactory : public DestinationIPInputBaseFactory<UdpMatchingData> {};
class HttpDestinationIPInputFactory : public DestinationIPInputBaseFactory<Http::HttpMatchingData> {
};
REGISTER_FACTORY(DestinationIPInputFactory, Matcher::DataInputFactory<MatchingData>);
REGISTER_FACTORY(UdpDestinationIPInputFactory, Matcher::DataInputFactory<UdpMatchingData>);
REGISTER_FACTORY(HttpDestinationIPInputFactory, Matcher::DataInputFactory<Http::HttpMatchingData>);

class DestinationPortInputFactory : public DestinationPortInputBaseFactory<MatchingData> {};
class UdpDestinationPortInputFactory : public DestinationPortInputBaseFactory<UdpMatchingData> {};
class HttpDestinationPortInputFactory
    : public DestinationPortInputBaseFactory<Http::HttpMatchingData> {};
REGISTER_FACTORY(DestinationPortInputFactory, Matcher::DataInputFactory<MatchingData>);
REGISTER_FACTORY(UdpDestinationPortInputFactory, Matcher::DataInputFactory<UdpMatchingData>);
REGISTER_FACTORY(HttpDestinationPortInputFactory,
                 Matcher::DataInputFactory<Http::HttpMatchingData>);

class SourceIPInputFactory : public SourceIPInputBaseFactory<MatchingData> {};
class UdpSourceIPInputFactory : public SourceIPInputBaseFactory<UdpMatchingData> {};
class HttpSourceIPInputFactory : public SourceIPInputBaseFactory<Http::HttpMatchingData> {};
REGISTER_FACTORY(SourceIPInputFactory, Matcher::DataInputFactory<MatchingData>);
REGISTER_FACTORY(UdpSourceIPInputFactory, Matcher::DataInputFactory<UdpMatchingData>);
REGISTER_FACTORY(HttpSourceIPInputFactory, Matcher::DataInputFactory<Http::HttpMatchingData>);

class SourcePortInputFactory : public SourcePortInputBaseFactory<MatchingData> {};
class UdpSourcePortInputFactory : public SourcePortInputBaseFactory<UdpMatchingData> {};
class HttpSourcePortInputFactory : public SourcePortInputBaseFactory<Http::HttpMatchingData> {};
REGISTER_FACTORY(SourcePortInputFactory, Matcher::DataInputFactory<MatchingData>);
REGISTER_FACTORY(UdpSourcePortInputFactory, Matcher::DataInputFactory<UdpMatchingData>);
REGISTER_FACTORY(HttpSourcePortInputFactory, Matcher::DataInputFactory<Http::HttpMatchingData>);

class DirectSourceIPInputFactory : public DirectSourceIPInputBaseFactory<MatchingData> {};
class HttpDirectSourceIPInputFactory
    : public DirectSourceIPInputBaseFactory<Http::HttpMatchingData> {};
REGISTER_FACTORY(DirectSourceIPInputFactory, Matcher::DataInputFactory<MatchingData>);
REGISTER_FACTORY(HttpDirectSourceIPInputFactory, Matcher::DataInputFactory<Http::HttpMatchingData>);

class ServerNameInputFactory : public ServerNameInputBaseFactory<MatchingData> {};
class HttpServerNameInputFactory : public ServerNameInputBaseFactory<Http::HttpMatchingData> {};
REGISTER_FACTORY(ServerNameInputFactory, Matcher::DataInputFactory<MatchingData>);
REGISTER_FACTORY(HttpServerNameInputFactory, Matcher::DataInputFactory<Http::HttpMatchingData>);

class SourceTypeInputFactory : public SourceTypeInputBaseFactory<MatchingData> {};
class HttpSourceTypeInputFactory : public SourceTypeInputBaseFactory<Http::HttpMatchingData> {};
REGISTER_FACTORY(SourceTypeInputFactory, Matcher::DataInputFactory<MatchingData>);
REGISTER_FACTORY(HttpSourceTypeInputFactory, Matcher::DataInputFactory<Http::HttpMatchingData>);

REGISTER_FACTORY(TransportProtocolInputFactory, Matcher::DataInputFactory<MatchingData>);
REGISTER_FACTORY(ApplicationProtocolInputFactory, Matcher::DataInputFactory<MatchingData>);

} // namespace Matching
} // namespace Network
} // namespace Envoy
