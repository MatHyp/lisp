#define DEBUG

#ifndef LOG_HPP
#define LOG_HPP

#ifdef DEBUG
#define LOG(x) std::cout << (x) << " " << __FILE__ << ":" << __LINE__ << "\n"
#else
#define LOG(X)
#endif

#endif