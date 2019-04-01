// Before running this test: export LANG=foo

#include <sstd/boost/filesystem.hpp>
int main() {
  boost::filesystem::path("/abc").root_directory();
}


