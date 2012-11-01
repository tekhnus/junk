#include <mutex>

static std::mutex safelog;

template<typename T>
Logger& Logger::operator<<(const T &message)
{
  if (!enabled)
  {
    return *this;
  }
  std::lock_guard<std::mutex> lock(safelog);
  if (verbose)
  {
    writeHead(std::cerr, true, false);
    std::cerr << message << std::endl;
  }
  if (file.is_open())
  {
    writeHead(file, false, true);
    file << message << std::endl;
  }
  return *this;
}
