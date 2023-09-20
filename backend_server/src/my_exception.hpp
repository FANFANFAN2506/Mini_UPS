#ifndef MY_EXCEPTION_HPP
#define MY_EXCEPTION_HPP
#include <exception>
/** 
A customized exception class.
Reference xz353's code in hw2 http server. Note: it is already published in https://github.com/WaAaaAterfall/ECE568-HTTP-Proxy
*/
class my_exception : public std::exception {
  const char * message;

 public:
  my_exception(const char * _message) : message(_message) {}
  virtual const char * what() const throw() { return this->message; }
};
#endif
