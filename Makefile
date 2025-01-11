# Makefile

# Параметры по умолчанию
CMAKE_BUILD_TYPE ?= Release
CMAKE_BUILD_DIR ?= build
CMAKE_INSTALL_DIR ?= $(CMAKE_BUILD_DIR)

all: $(CMAKE_BUILD_DIR)/Makefile
	$(MAKE) -C $(CMAKE_BUILD_DIR) $(MAKEFLAGS)

debug: CMAKE_BUILD_TYPE = Debug
debug: $(CMAKE_BUILD_DIR)/Makefile
	$(MAKE) -C $(CMAKE_BUILD_DIR) $(MAKEFLAGS)

clean:
	rm -rf $(CMAKE_BUILD_DIR)

run: all
	$(CMAKE_INSTALL_DIR)/GameEngine

$(CMAKE_BUILD_DIR)/Makefile:
	mkdir -p $(CMAKE_BUILD_DIR)
	cd $(CMAKE_BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) ..
