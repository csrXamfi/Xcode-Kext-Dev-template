TARGET := Final
SRC    := src
BUILD  := build
BIN_OUT := $(BUILD)/bin

# Don't use ?= with $(shell ...)
ifndef CXX_FLAGS
CXX_FLAGS := --std=gnu++17 -Wall -O3 -nostdinc -nostdlib -mkernel -DKERNEL -isystem $(shell xcrun --show-sdk-path)/System/Library/Frameworks/Kernel.framework/Headers -Wl,-kext -lcc_kext $(CXXFLAGS)
endif

.PHONY: all clean build install

all: $(TARGET).kext/Contents/_CodeSignature/CodeResources 

$(TARGET).kext/Contents/MacOS/$(TARGET): $(SRC)/*.cpp $(SRC)/*.h | $(TARGET).kext/Contents/MacOS
	$(CXX) -arch arm64e -o $@ $(SRC)/*.cpp $(CXX_FLAGS)

$(TARGET).kext/Contents/Info.plist: misc/Info.plist | $(TARGET).kext/Contents
	cp -f $^ $@

$(TARGET).kext/Contents/_CodeSignature/CodeResources: $(TARGET).kext/Contents/MacOS/$(TARGET) $(TARGET).kext/Contents/Info.plist
	codesign -s - -f $(TARGET).kext

$(TARGET).kext/Contents $(TARGET).kext/Contents/MacOS:
	mkdir -p $@

build:
	mkdir -p $(BIN_OUT)

install: all
	sudo cp -r $(TARGET).kext /Library/Extensions

clean:
	rm -rf $(TARGET).kext $(BUILD)
