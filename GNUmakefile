PPO_MKDIR = MKDIR
PPO_CLEAN = CLEAN
PPO_CXX   = CXX
PPO_LD    = LD

CXX           = clang++
OPTIMIZATIONS = -pipe -O3

YAMLCPP_HDR_DIR   = vendor/yaml-cpp/include
YAMLCPP_SRC_DIR   = vendor/yaml-cpp/src
YAMLCPP_BUILD_DIR = build/yaml-cpp
YAMLCPP_SRCS     := $(wildcard $(YAMLCPP_SRC_DIR)/*.cpp) $(wildcard $(YAMLCPP_SRC_DIR)/contrib/*.cpp)
YAMLCPP_OBJS     := $(patsubst $(YAMLCPP_SRC_DIR)/%.cpp, $(YAMLCPP_BUILD_DIR)/%.o, $(YAMLCPP_SRCS))
YAMLCPP_OBJS     := $(patsubst $(YAMLCPP_BUILD_DIR)/contrib/%.o, $(YAMLCPP_BUILD_DIR)/%.o, $(YAMLCPP_OBJS))
YAMLCPP_CPPFLAGS  = -isystem $(YAMLCPP_HDR_DIR)
YAMLCPP_CXXFLAGS  = -std=c++11 $(OPTIMIZATIONS)

SKAP_HDR_DIR   = include
SKAP_SRC_DIR   = src
SKAP_BUILD_DIR = build
SKAP_SRCS     := $(wildcard $(SKAP_SRC_DIR)/*.cc)
SKAP_OBJS     := $(patsubst $(SKAP_SRC_DIR)/%.cc, $(SKAP_BUILD_DIR)/%.o, $(SKAP_SRCS))
SKAP_CPPFLAGS  = -I $(SKAP_HDR_DIR) -isystem $(YAMLCPP_HDR_DIR)
SKAP_CXXFLAGS  = -std=c++20 -Wall -Wextra -Wpedantic -Werror $(OPTIMIZATIONS)
SKAP_LDFLAGS   = -static $(OPTIMIZATIONS)
SKAP_OUT       = skap

DIRS_OUT = $(SKAP_BUILD_DIR) $(YAMLCPP_BUILD_DIR)

.PHONY: all clean mrproper

all: $(DIRS_OUT) $(SKAP_OUT)
	@:

$(DIRS_OUT):
	@echo "  $(PPO_MKDIR)   $@"
	@mkdir -p $@

$(SKAP_OUT): $(YAMLCPP_OBJS) $(SKAP_OBJS)
	@echo "  $(PPO_LD)      $@"
	@$(CXX) $^ $(SKAP_LDFLAGS) -o $@

$(YAMLCPP_BUILD_DIR)/%.o: $(YAMLCPP_SRC_DIR)/%.cpp
	@echo "  $(PPO_CXX)     $@"
	@$(CXX) $(YAMLCPP_CPPFLAGS) $(YAMLCPP_CXXFLAGS) -c -MD $< -o $@

$(YAMLCPP_BUILD_DIR)/%.o: $(YAMLCPP_SRC_DIR)/contrib/%.cpp
	@echo "  $(PPO_CXX)     $@"
	@$(CXX) $(YAMLCPP_CPPFLAGS) $(YAMLCPP_CXXFLAGS) -c -MD $< -o $@

$(SKAP_BUILD_DIR)/%.o: $(SKAP_SRC_DIR)/%.cc
	@echo "  $(PPO_CXX)     $@"
	@$(CXX) $(SKAP_CPPFLAGS) $(SKAP_CXXFLAGS) -c -MD $< -o $@

-include $(SKAP_BUILD_DIR)/*.d

clean:
	@if [ -d $(SKAP_BUILD_DIR) ]; then           \
	  echo "  $(PPO_CLEAN)   $(SKAP_BUILD_DIR)"; \
	  rm -r $(SKAP_BUILD_DIR);                   \
	fi

mrproper: clean
	@if [ -e $(SKAP_OUT) ]; then           \
	  echo "  $(PPO_CLEAN)   $(SKAP_OUT)"; \
	  rm $(SKAP_OUT);                      \
	fi
