#include <atomic>
#include <thread>


struct SBusMsg {
  // Constants
  static constexpr int kNChannels = 16;
  static constexpr uint16_t kMinCmd = 192;   // corresponds to 1000 on FC
  static constexpr uint16_t kMeanCmd = 992;  // corresponds to 1500 on FC
  static constexpr uint16_t kMaxCmd = 1792;  // corresponds to 2000 on FC

  // Normal 11 bit channels
  uint16_t channels[kNChannels];

  // Flags
  bool frame_lost;
  bool failsafe;
};


class SBusSerialPort {
public:
    SBusSerialPort();
    SBusSerialPort(const std::string& port, const bool start_receiver_thread = true);
    virtual ~SBusSerialPort();

    SBusMsg getData();

private:
    bool setUpSBusSerialPort(const std::string& port,
                             const bool start_receiver_thread);

    bool connectSerialPort(const std::string& port);
    void disconnectSerialPort();

    bool startReceiverThread();
    bool stopReceiverThread();

    void transmitSerialSBusMessage(const SBusMsg& sbus_msg) const;
//    virtual void handleReceivedSbusMessage(
//            const sbus_bridge::SBusMsg& received_sbus_msg) = 0;

private:
    static constexpr int kSbusFrameLength_ = 25;
    static constexpr uint8_t kSbusHeaderByte_ = 0x0F;
    static constexpr uint8_t kSbusFooterByte_ = 0x00;
    static constexpr int kPollTimeoutMilliSeconds_ = 500;

    bool configureSerialPortForSBus() const;
    void serialPortReceiveThread();
    SBusMsg parseSbusMessage(
            uint8_t sbus_msg_bytes[kSbusFrameLength_]) const;

    std::thread receiver_thread_;
    std::atomic_bool receiver_thread_should_exit_;

    int serial_port_fd_;

    SBusMsg current_msg_;
};
