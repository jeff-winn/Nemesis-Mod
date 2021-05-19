#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <stdint.h>

// Defines the callback method for remote command received notifications.
typedef void (*RemoteCommandReceivedCallback) (uint8_t type, uint8_t* data, uint16_t len, uint8_t subtype);

// Sets the global callback to be invoked when a bluetooth command has been received.
void SetBluetoothCommandReceivedCallback(RemoteCommandReceivedCallback callback);

// Notifies the application when a bluetooth command has been received.
void NotifyBluetoothCommandReceived(uint8_t type, uint8_t* data, uint16_t len, uint8_t subtype);

#endif /* CALLBACKS_H */