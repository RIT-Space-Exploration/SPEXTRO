//
// SPEXTRO Flight Software
// file: comms_actor.hh
// class: CommsActor
// desc:
//      Used to facilitate telemetry dispatch and command handling using 
//      an XBee SX transciever module.
//

#include <stdint.h>
#include <XBee.h>

#include "config_defines.hh"

class CommsActor{
public:

    /**
     * State queries method used to check if data may be loaded into
     * the communications actor or not.
     * 
     * @return True if data can be loaded, false otherwise.
     */
    bool can_load_data();

    /**
     * Used to load data into the communication actor which is sent by 
     * the comminications director.
     * 
     * @param data Pointer to the data to be loaded.
     * @param data_size Size of the data to be copied.
     * @return True if data can be loaded, false otherwise.
     */
    bool load_data(uint8_t* data, uint8_t data_size);

    /**
     * Used to send the data blocking, bypassing the communications director. 
     * 
     * @param data Pointer to the data to be loaded.
     * @param data_size Size of the data to be copied.
     * @return True if data was sent, false otherwise.
     */
    bool send_blocking(uint8_t* data, uint8_t data_size);

    /**
     * Used to perform state resolution logic, directed by the communications 
     * director.
     */
    void perform();

    /**
     * Initialize the transceiver module.
     */
    void init();

private:

    /**
     * Used to handle incoming messages from the transciever module.
     * 
     * @param block_for_tansmit_status Block for transmit status messages.
     */
    void receive_handler(bool block_for_tansmit_status = false);

    bool initalized{false};

    bool m_packet_data_loaded{true};
    uint8_t load_buffer[UINT8_MAX] = {0};

    XBee xbee{};
    XBeeAddress64 addr64_ground{XBEE_ADDR_GROUND_HI, XBEE_ADDR_GROUND_LOW};
};