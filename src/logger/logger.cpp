#include <logger/logger.hpp>

namespace logger {
// Constructors & Destructor
Logger::Logger()
    : stdout_loglevel_(loglevel_t::DEBUG), file_loglevel_(loglevel_t::NONE) {}

Logger::Logger(const string& logfile, loglevel_t::e file_loglevel,
               loglevel_t::e stdout_loglevel)
    : stdout_loglevel_(stdout_loglevel), file_loglevel_(file_loglevel) {
  ofs.open(logfile.c_str(), std::fstream::out | std::fstream::app);
}

// Getters/Setters
void Logger::set_loglevel(loglevel_t::e stdout_loglevel,
                          loglevel_t::e file_loglevel) {
  bool out, file;
  if ((out = (stdout_loglevel != loglevel_t::UNSET))) {
    stdout_loglevel_ = stdout_loglevel;
    debug(Message("set stdout_loglevel_ to").cyan(stdout_loglevel_));
  }
  if ((file = (file_loglevel != loglevel_t::UNSET))) {
    file_loglevel_ = file_loglevel;
    debug(Message("set file_loglevel_ to").cyan(file_loglevel_));
  }
  if (!out && !file)
    throw std::invalid_argument("loglevels cannot be both unset");
}

// Private members
void Logger::log(const Message& msg, const loglevel_t::e level) {
  const Message levelMessages[] = {
      Message("DEBUG:    ", color_t::HBLU),
      Message("INFO:     ", color_t::HGRN),
      Message("WARNING:  ", color_t::BHYEL),
      Message("ERROR:    ", color_t::RED),
      Message("CRITICAL: ", color_t::BHRED),
  };

  if (level >= loglevel_t::LOGLEVEL_SIZE) {
    throw std::out_of_range(
        Message("level").red(level).add("is out of range").str());
  }
  if (level >= file_loglevel_)
    ofs << levelMessages[level].plaintext() << msg.plaintext(flag_t::NEWLINE);
  if (level >= stdout_loglevel_)
    std::cout << levelMessages[level] << msg.str(flag_t::NEWLINE);
}

// Methods
void Logger::debug(const Message& msg) { log(msg, loglevel_t::DEBUG); }
void Logger::info(const Message& msg) { log(msg, loglevel_t::INFO); }
void Logger::warning(const Message& msg) { log(msg, loglevel_t::WARNING); }
void Logger::error(const Message& msg) { log(msg, loglevel_t::ERROR); }
void Logger::critical(const Message& msg) { log(msg, loglevel_t::CRITICAL); }
}  // namespace logger
