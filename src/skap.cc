#include <iostream>
#include <filesystem>
#include <yaml-cpp/yaml.h>

static constexpr std::string kind    { "SKAP" };
static constexpr std::string version { "v1"   };

static inline void usage(const char *prog_name) {
  std::cerr << "usage: " << prog_name << " <MANIFEST_FILE>" << std::endl;
  exit(1);
}

int main(int argc, char **argv) {
  if (argc != 2) usage(argv[0]);
  if (not std::filesystem::exists(argv[1])) {
    std::cerr << "ERROR: `" << argv[1] << "` does not exist" << std::endl;
    usage(argv[0]);
  }

  YAML::Node mf { YAML::LoadFile(argv[1]) };

  if (mf["kind"].as<std::string>() != kind) {
    std::cerr << "ERROR: `" << argv[1] << "` is not a valid SKAP manifest file" << std::endl;
    usage(argv[0]);
  }
  if (mf["apiVersion"].as<std::string>() != version) {
    std::cerr << "ERROR: `" << argv[1] << "` has an invalid apiVersion" << std::endl;
    usage(argv[0]);
  }
  if (not mf["metadata"]["name"]) {
    std::cerr << "ERROR: `" << argv[1] << "` has no output name defined" << std::endl;
    usage(argv[0]);
  }
  const std::string name { mf["metadata"]["name"].as<std::string>() + ".skap" };
  std::cout << "Output SKAP file: " << name << std::endl;
}
