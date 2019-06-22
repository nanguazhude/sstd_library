﻿/* Example of Outcome used with UDTs
(C) 2017-2019 Niall Douglas <http://www.nedproductions.biz/> (149 commits)


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "../../../include/boost/outcome.hpp"

#include <iostream>

int main()
{
  using namespace BOOST_OUTCOME_V2_NAMESPACE;
  //! [udts]
  struct udt
  {
    int a{0};
    explicit udt(int _a)
        : a(_a)
    {
    }
    udt() = default;
    int operator*() const { return a; }
  };

  struct err
  {
    int a{0};
    explicit err(int _a)
        : a(_a)
    {
    }
    err() = default;
  };
//! [udts]
#if 0
//! [implicit]
  result<udt, err> res(5);  // fails to compile, cannot convert 'int' to result
//! [implicit]
  //! [explicit]
  // When it is not unambiguous which to construct, we must say which we want same as with std::variant<>
  result<udt, err> res(in_place_type<err>, 5);
  //! [explicit]
#endif
  //! [access]
  result<udt, err, policy::terminate> res(in_place_type<err>, 5);

  // What happens here? What exception type is thrown?
  try
  {
    std::cout << *res.value() << std::endl;
  }
  catch(const std::exception &e)
  {
    std::cerr << "Exception thrown was " << e.what() << std::endl;
  }
  //! [access]
  return 0;
}
