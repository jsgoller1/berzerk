# Adapted from https://stackoverflow.com/a/28663974/1320882, and
# "Recursive Make Considered Harmful" by Peter Miller

### General vars
SHELL:=/bin/bash
DIR:=$(shell pwd)
PLATFORM:=$(shell uname)
PROJECT_NAME:=berzerk
PROJECT_BIN:=$(PROJECT_NAME)-bin
ENGINE_BIN:=$(BIN_DIR)/$(PROJECT_NAME)

### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
#ANALYZER:=scan-build --status-bugs

### Uncomment to run Valgrind on target for memory analysis
#VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

### Compiler settings for C++
CCACHE:=ccache
CXX:=clang++
CXXFLAGS:=-std=c++20 -g

# Uncomment this to add diagnostic flags to clang that provide information
# about build times.
#CXXFLAGS:=$(CXXFLAGS) -save-stats -ftime-report --verbose

### Uncomment this to cause any failed assumptions to crash the engine; if commented out,
### they will instead be logged at LogLevel::ERROR.
#CXXFLAGS:=$(CXXFLAGS) -DFWRONG_ASSUMPTIONS_FATAL=true

# Warning settings
CXXFLAGS:=$(CXXFLAGS) -Weverything -Werror
# Don't care about C++98 backwards compatibility.
CXXFLAGS:=$(CXXFLAGS) -Wno-c++98-compat -Wno-c++98-compat-pedantic
# Padding is irrelevant, we have memory to waste
# TODO: Doesn't seem like a problem presently, but doesn't padding solve cache fetch / alignment issues? Need
# to confirm this is actually irrelevant.
CXXFLAGS:=$(CXXFLAGS) -Wno-padded 
# Constructors with parameters shadowing attributes makes them concise
# Elsewhere, we use shadowing intentionally so we can chain constructors or make it clear what attribute
# a parameter will be assigned to. 
CXXFLAGS:=$(CXXFLAGS) -Wno-shadow-field-in-constructor -Wno-shadow-field -Wno-shadow
# We don't need to worry about missing values of an enum in a switch as long as we use a default path
CXXFLAGS:=$(CXXFLAGS) -Wno-switch-enum
# Loggers created at compile time are destroyed at exit time, but clang throws
# warnings and ignores [[clang::always_destroy]], so we're just going to disable the warning. 
CXXFLAGS:=$(CXXFLAGS) -Wno-global-constructors -Wno-exit-time-destructors
# We need to use C headers from other projects, for now.
CXXFLAGS:=$(CXXFLAGS) -Wno-deprecated
# We're only building on MacOS and Linux right now, so using *nix paths is fine
CXXFLAGS:=$(CXXFLAGS) -Wno-poison-system-directories
# I don't personally use C-style casting or double underscore identifiers but SDL does.
CXXFLAGS:=$(CXXFLAGS) -Wno-old-style-cast -Wno-reserved-identifier -Wno-reserved-macro-identifier


SRC_DIR:=berzerk
MODULES:=3rdparty $(SRC_DIR) $(SRC_DIR)/animation $(SRC_DIR)/audio $(SRC_DIR)/drawing  $(SRC_DIR)/gameobject
MODULES:=$(MODULES) $(SRC_DIR)/gameobject/gameobject $(SRC_DIR)/gameobject/bullet $(SRC_DIR)/gameobject/robot
MODULES:=$(MODULES) $(SRC_DIR)/gameobject/wall $(SRC_DIR)/level $(SRC_DIR)/math $(SRC_DIR)/texture 
INCLUDES:=$(patsubst %, -I %,$(MODULES))
CXXFLAGS:=$(CXXFLAGS) $(INCLUDES)
SRC_FILES:=$(shell find $(MODULES) -name "*.cc" | sort -u)
OBJ_FILES:=$(patsubst %.cc, %.o, $(SRC_FILES))
SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.dylib" -or -name "*.so")
ASSETS_DIR_PATH:=$(DIR)/assets/

.PHONY: berzerk
berzerk: $(OBJ_FILES)
	$(CCACHE) $(CXX) $(CXXFLAGS) $(OBJ_FILES) $(SHARED_OBJ_FILES) -o $(PROJECT_BIN)
	./$(PROJECT_BIN) $(ASSETS_DIR_PATH)
loc:
	git ls-files | grep berzerk | grep -E "(\.cc|\.hh)$$" | uniq | xargs cat | wc -l

# Utilizes Clang preprocessor to automatically generate dependency 
# makefile targets; this target be evaluated every time the Makefile
# is read, so dependencies will be recalculated regularly. Inclusion
# will cause to make to restart with the new targets available
.depend: $(SRC_FILES) # $(BREAKOUT_SRC_FILES) $(SPRAWL_SRC_FILES)
	$(CXX) $(CXXFLAGS) -MM $^>>./$@;
include .depend

clean-obj:
	-rm -f $(OBJ_FILES)

clean-deps:
	-rm .depend

clean-logs:
	-rm bin/*.log

clean-bin:
	-rm $(PROJECT_BIN)

clean-purge: clean-deps clean-logs clean-bin
	-find $(MODULES) -name "*.o" | sort -u | xargs rm

sdl-setup:
	cd tmp; \
	wget https://github.com/libsdl-org/SDL/releases/download/release-2.26.2/SDL2-2.26.2.zip; \
	unzip SDL2-2.26.2.zip; \
	cd SDL2-2.26.2/; \
	cmake -S . -B build && cmake --build build && sudo cmake --install build; \
	cp /tmp/SDL2-2.26.2/include/* ./3rdparty/; \
	cp /tmp/SDL2-2.26.2/libSDL2-2.0.so ./3rdparty


sdl-img-setup:
	cd tmp; \
	wget https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.2/SDL2_image-2.6.2.zip; \
	unzip SDL2_image-2.6.2.zip; \
	cd SDL2_image-2.6.2; \
	cmake -S . -B build && cmake --build build && sudo cmake --install build; \
	cp /tmp/SDL2_image-2.6.2/SDL_image.h ./3rdparty; \
	cp /tmp/SDL2_image-2.6.2/build/libSDL2_image.so ./3rdparty
	

