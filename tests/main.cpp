#include <filesystem>
#include <iostream>

int main() {
  std::cout << "Current working directory: " << std::filesystem::current_path()
            << std::endl;

  return EXIT_SUCCESS;
}