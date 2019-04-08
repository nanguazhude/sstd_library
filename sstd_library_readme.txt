
a private cplusplus macro
\uacc1   => a private cplusplus macro 1
\uacc2   => a private cplusplus macro 2
……
\uacc9   => a private cplusplus macro 9
\uacc10  => a private cplusplus macro 10

a private cplusplus macro arg
\uaca1   => a private cplusplus macro arg 1
\uaca2   => a private cplusplus macro arg 2
……
\uaca9   => a private cplusplus macro arg 9
\uaca10  => a private cplusplus macro arg 10

a private cplusplus function =>
\uacf1   => a private cplusplus function 1
\uacf2   => a private cplusplus function 2
……
\uacf9   => a private cplusplus function 9
\uacf10  => a private cplusplus function 10

example :

#ifndef \uacc1GetChar0
#define \uacc1GetChar0(\uaca1String) (\uaca1String)[0]
#endif

constexpr const auto z = \uacc1GetChar0("test");

