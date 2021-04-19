BUILD_DIR = build
CC = clang
CFLAGS += -DNDEBUG
CFLAGS += -Ofast -Wall -Werror
CFLAGS += -march=native
CFLAGS += -std=c17
CXX = clang++
CXXFLAGS += -DNDEBUG
CXXFLAGS += -Ofast -Wall -Werror
CXXFLAGS += -march=native
CXXFLAGS += -std=c++17
CXXFLAGS += -stdlib=libc++
ifeq ($(TOOL),cmake)
ENV = env CC=$(CC) CFLAGS="$(CFLAGS)"
ENV += CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)"
ENV += LD=$(LD) LDFLAGS="$(LDFLAGS)"
endif
LD = clang++
LDFLAGS += -Wl,-s
LDFLAGS += -fuse-ld=lld
LDFLAGS += -lGL -lGLU -lglfw -pthread
LDFLAGS += -rtlib=compiler-rt
LDFLAGS += -stdlib=libc++
LDFLAGS += -unwindlib=libunwind
RM = rm -fr
TARGET_BINARY = glfwapp
TARGET_OBJECTS = $(TARGET_SOURCES:%.cpp=%.o)
TARGET_PCH = stdafx.h.pch
TARGET_SOURCES = GLapplication.cpp
TARGET_SOURCES += GLcamera.cpp
TARGET_SOURCES += GLcontext.cpp
TARGET_SOURCES += glfw.cpp
TARGET_SOURCES += GLmaterial.cpp
TARGET_SOURCES += GLquadric.cpp
TARGET_SOURCES += GLsphere.cpp
TARGET_SOURCES += GLtexture.cpp
TARGET_SOURCES += GLtorus.cpp
TARGET_SOURCES += GLtorusVertex.cpp
TARGET_SOURCES += MyApplication.cpp
TARGET_SOURCES += PS4axes.cpp
TARGET_SOURCES += PS4joystick.cpp

all: $(TARGET_BINARY)

clean:
	$(RM) $(BUILD_DIR) $(TARGET_BINARY) $(TARGET_OBJECTS)

disasm: $(TARGET_BINARY)
	llvm-objdump --disassemble-all $(TARGET_BINARY) | less

readelf: $(TARGET_BINARY)
	readelf --all $(TARGET_BINARY) | less

.PHONY: all clean disasm readelf

ifeq ($(TOOL),cmake)
glfw:
	@[ ! -d $@ ] && $(RM) $@
	git clone https://github.com/glfw/glfw.git

$(TARGET_BINARY): $(TARGET_PCH)
	@[ -d $(BUILD_DIR) ] || mkdir $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(ENV) cmake .. && cmake --build . -j13

$(TARGET_PCH): glfw stdafx.h
	$(CXX) $(CXXFLAGS) -x c++-header stdafx.h -o $(TARGET_PCH)
else
.cpp.o:
	$(CXX) $(CXXFLAGS) -include-pch $(TARGET_PCH) -c $<

$(TARGET_BINARY): $(TARGET_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(TARGET_OBJECTS)

$(TARGET_OBJECTS): $(TARGET_PCH)

$(TARGET_PCH): stdafx.h
	$(CXX) $(CXXFLAGS) -x c++-header stdafx.h -o $(TARGET_PCH)
endif
