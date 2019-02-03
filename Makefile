# Arduino Library base folder and example structure
WORKSPACE_FOLDER ?= 

# Arduino CLI executable name and directory location
ARDUINO_CLI = $(WORKSPACE_FOLDER)\arduino-cli.exe

# Arduino CLI Board type
BOARD_TYPE = arduino:avr
FQBN = $(BOARD_TYPE):uno

# Default port to upload to
SERIAL_PORT ?= 

# Optional verbose compile/upload trigger
VERBOSE = 

# Build path -- used to store built binary and object files
BUILD_FOLDER=$(WORKSPACE_FOLDER)\build
PROJECT_FOLDER=$(WORKSPACE_FOLDER)\Nemesis-Mod

.PHONY: all

all: install_prerequisites rebuild
rebuild: clean build

install_prerequisites:
	$(ARDUINO_CLI) core update-index
	$(ARDUINO_CLI) core install $(BOARD_TYPE)
	
build:
	$(ARDUINO_CLI) compile $(VERBOSE) --build-path=$(BUILD_FOLDER) --build-cache-path=$(BUILD_FOLDER) -b $(FQBN) $(PROJECT_FOLDER)

upload:
	$(ARDUINO_CLI) upload --port $(SERIAL_PORT) --fqbn $(FQBN) --verify $(PROJECT_FOLDER)

clean:
	@rd /s /q $(BUILD_FOLDER)
	del $(PROJECT_FOLDER)\*.elf
	del $(PROJECT_FOLDER)\*.hex