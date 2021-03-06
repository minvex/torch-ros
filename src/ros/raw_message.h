#ifndef raw_message_h
#define raw_message_h

class RawMessage {
public:
  RawMessage()
    : buffer()
    , num_bytes(0) {
  }

  RawMessage(size_t length)
    : buffer(new uint8_t[length])
    , num_bytes(length) {
  }

  void copyFrom(uint8_t *source, size_t length) {
    buffer = boost::shared_array<uint8_t>(new uint8_t[length]);
    memcpy(buffer.get(), source, length);
    this->num_bytes = length;
  }

  size_t get_length() const {
    return num_bytes;
  }

  uint8_t *get() const {
    return buffer.get();
  }

  ros::serialization::IStream get_IStream() const {
    return ros::serialization::IStream(buffer.get(), num_bytes);
  }

  ros::serialization::OStream get_OStream() const {
    return ros::serialization::OStream(buffer.get(), num_bytes);
  }

  const boost::shared_array<uint8_t>& get_buffer() const {
    return buffer;
  }

  void set_header(const ros::M_string& header) {
    this->header = header;
  }

  const ros::M_string& get_header() const {
    return header;
  }

private:
  ros::M_string header;
  boost::shared_array<uint8_t> buffer;
  size_t num_bytes;
};

namespace ros {
namespace serialization {

template<>
inline SerializedMessage serializeMessage(const RawMessage &message)
{
  SerializedMessage sm(message.get_buffer(), message.get_length());
  sm.message_start = sm.buf.get() + sizeof(uint32_t);
  return sm;
}

}   // namespace serialization
}   // namespace ros

#endif    // raw_message_h
