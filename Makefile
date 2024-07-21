BUILD_DIR = build

TARGET = terminal_game

all:
	cmake --build $(BUILD_DIR)

main:
	cmake --build $(BUILD_DIR) --target main
