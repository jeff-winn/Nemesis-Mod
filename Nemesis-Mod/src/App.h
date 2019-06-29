#ifndef APP_H
#define APP_H

#include "hardware/BluetoothManager.h"
#include "Button.h"
#include "Command.h"
#include "ConfigurationSettings.h"
#include "FeedController.h"
#include "FlywheelController.h"

// Represents the main application.
class App {
    public:
        App(
            FlywheelController* flywheelController,
            FeedController* feedController,            
            Button* revTrigger, 
            Button* firingTrigger,
            Button* resetButton,
            BluetoothManager* ble,
            ConfigurationSettings* config,
            Mainboard* hardware);

        ~App();
        
        // Initializes the application.
        void init();

        // Runs the application.
        void run();

        // Authenticates the operator (thereby releasing the software lock).
        void authenticate();

        // Deauthenticates the operator (thereby restoring the software lock).
        void deauthenticate();

    protected:        
        Command* createCommandFromPacket(Packet_t packet);
        void handleAnyExternalCommands();
        void handleResetAttempt();
    
    private:
        FlywheelController* m_flywheelController;
        FeedController* m_feedController;
        Button* m_revTrigger;
        Button* m_firingTrigger;
        Button* m_resetButton;
        BluetoothManager* m_ble;
        ConfigurationSettings* m_config;
        Mainboard* m_hardware;
};

#endif