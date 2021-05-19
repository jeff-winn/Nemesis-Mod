# Arduino Library base folder and example structure
WORKSPACE_FOLDER ?= $(abspath .)
TOOLS_FOLDER = $(WORKSPACE_FOLDER)/tools

# Arduino CLI executable name and directory location
ifeq ($(OS),Windows_NT)
	ARDUINO_CLI = $(WORKSPACE_FOLDER)/arduino-cli.exe
else
	ARDUINO_CLI = $(WORKSPACE_FOLDER)/arduino-cli
endif

# Arduino CLI Board type
MAIN_BOARD_TYPE = adafruit:samd
MAIN_FQBN = $(MAIN_BOARD_TYPE):adafruit_feather_m4

BT_BOARD_TYPE = adafruit:nrf52
BT_FQBN = $(BT_BOARD_TYPE):feather52840

# Default port to upload to
SERIAL_PORT ?= 

# Optional verbose compile/upload trigger
VERBOSE = 

# Build path -- used to store built binary and object files
BUILD_FOLDER = $(WORKSPACE_FOLDER)/out
SKETCHES_FOLDER = $(WORKSPACE_FOLDER)/sketches

MAIN_PROJECT_NAME = Mainboard
MAIN_BUILD_FOLDER = $(BUILD_FOLDER)/$(MAIN_PROJECT_NAME)
MAIN_PROJECT_FOLDER = $(SKETCHES_FOLDER)/$(MAIN_PROJECT_NAME)
MAIN_SKETCH_PATH = $(MAIN_PROJECT_FOLDER)/$(MAIN_PROJECT_NAME).ino

BT_PROJECT_NAME = Bluetooth
BT_BUILD_FOLDER = $(BUILD_FOLDER)/$(BT_PROJECT_NAME)
BT_PROJECT_FOLDER = $(SKETCHES_FOLDER)/$(BT_PROJECT_NAME)
BT_SKETCH_PATH = $(BT_PROJECT_FOLDER)/$(BT_PROJECT_NAME).ino

CONFIG_FILE = $(WORKSPACE_FOLDER)/arduino-cli.yml

all: install_prerequisites rebuild

install_prerequisites: install_boards install_libraries

install_boards:
	"$(ARDUINO_CLI)" core update-index
	"$(ARDUINO_CLI)" core install $(MAIN_BOARD_TYPE)
	"$(ARDUINO_CLI)" core install $(BT_BOARD_TYPE)

install_libraries:
	"$(ARDUINO_CLI)" lib install "Adafruit FRAM I2C"
	"$(ARDUINO_CLI)" lib install "DualG2HighPowerMotorShield"

rebuild: clean build

clean:
	@rm -rf "$(BUILD_FOLDER)"

build:
	"$(ARDUINO_CLI)" compile $(VERBOSE) --build-path="$(MAIN_BUILD_FOLDER)" --build-cache-path="$(MAIN_BUILD_FOLDER)" --fqbn $(MAIN_FQBN) "$(MAIN_PROJECT_FOLDER)"
	"$(ARDUINO_CLI)" compile $(VERBOSE) --build-path="$(BT_BUILD_FOLDER)" --build-cache-path="$(BT_BUILD_FOLDER)" --fqbn $(BT_FQBN) "$(BT_PROJECT_FOLDER)"
