#ifndef QUERY_EXCEPTION_H
#define QUERY_EXCEPTION_H

#include <exception>

class QueryException : std::exception {
private:
  const char *ErrorMessage;

public:
  QueryException(const char *Msg);
  const char *what() const noexcept override;
};

#endif
