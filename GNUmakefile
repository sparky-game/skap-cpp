PPO_MKDIR = MKDIR
PPO_CLEAN = CLEAN
PPO_CXX   = CXX
PPO_LD    = LD

CXX           = clang++
OPTIMIZATIONS = -pipe -O3

SKAP_HDR_DIR   = include
SKAP_SRC_DIR   = src
SKAP_BUILD_DIR = build
SKAP_SRCS     := $(wildcard $(SKAP_SRC_DIR)/*.cc)
SKAP_OBJS     := $(patsubst $(SKAP_SRC_DIR)/%.cc, $(SKAP_BUILD_DIR)/%.o, $(SKAP_SRCS))
SKAP_CPPFLAGS  = -I $(SKAP_HDR_DIR)
SKAP_CXXFLAGS  = -std=c++20 -Wall -Wextra -Wpedantic -Werror $(OPTIMIZATIONS)
SKAP_LDFLAGS   = -static $(OPTIMIZATIONS)
SKAP_OUT       = skap

.PHONY: all clean mrproper

all: $(SKAP_BUILD_DIR) $(SKAP_OUT)
	@:

$(SKAP_BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	@mkdir -p $@

$(SKAP_OUT): $(SKAP_OBJS)
	@echo "  $(PPO_LD)      $@"
	@$(CXX) $^ $(SKAP_LDFLAGS) -o $@

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
