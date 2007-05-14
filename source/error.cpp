/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include <crisscross/universal_include.h>
#include <crisscross/error.h>

#ifndef TARGET_OS_WINDOWS
#    include <netdb.h>
#endif

using namespace CrissCross;

struct tl
{
  int w;
  const char *s;
  CrissCross::Errors e;
};

#if defined ( TARGET_OS_WINDOWS )
const struct tl errmap[] =
{
    {WSANO_DATA, "WSANO_DATA", CC_ERR_NO_DATA},
    {WSAHOST_NOT_FOUND, "WSAHOST_NOT_FOUND", CC_ERR_HOST_NOT_FOUND},
    {WSANO_RECOVERY, "WSANO_RECOVERY", CC_ERR_NO_RECOVERY},
    {WSATRY_AGAIN, "WSATRY_AGAIN", CC_ERR_TRY_AGAIN},
    {WSAEINTR, "WSAEINTR", CC_ERR_EINTR},
    {WSAEINTR, "WSAEINTR", CC_ERR_EINTR},
    {WSAEWOULDBLOCK, "WSAEWOULDBLOCK", CC_ERR_EWOULDBLOCK},
    {WSAEINPROGRESS, "WSAEINPROGRESS", CC_ERR_EINPROGRESS},
    {WSAEALREADY, "WSAEALREADY", CC_ERR_EALREADY},
    {WSAENOTSOCK, "WSAENOTSOCK", CC_ERR_ENOTSOCK},
    {WSAEDESTADDRREQ, "WSAEDESTADDRREQ", CC_ERR_EDESTADDRREQ},
    {WSAEMSGSIZE, "WSAEMSGSIZE", CC_ERR_EMSGSIZE},
    {WSAEPROTOTYPE, "WSAEPROTOTYPE", CC_ERR_EPROTOTYPE},
    {WSAENOPROTOOPT, "WSAENOPROTOOPT", CC_ERR_ENOPROTOOPT},
    {WSAEPROTONOSUPPORT, "WSAEPROTONOSUPPORT", CC_ERR_EPROTONOSUPPORT},
    {WSAESOCKTNOSUPPORT, "WSAESOCKTNOSUPPORT", CC_ERR_ESOCKTNOSUPPORT},
    {WSAEOPNOTSUPP, "WSAEOPNOTSUPP", CC_ERR_EOPNOTSUPP},
    {WSAEPFNOSUPPORT, "WSAEPFNOSUPPORT", CC_ERR_EPFNOSUPPORT},
    {WSAEAFNOSUPPORT, "WSAEAFNOSUPPORT", CC_ERR_EAFNOSUPPORT},
    {WSAEADDRINUSE, "WSAEADDRINUSE", CC_ERR_EADDRINUSE},
    {WSAEADDRNOTAVAIL, "WSAEADDRNOTAVAIL", CC_ERR_EADDRNOTAVAIL},
    {WSAENETDOWN, "WSAENETDOWN", CC_ERR_ENETDOWN},
    {WSAENETUNREACH, "WSAENETUNREACH", CC_ERR_ENETUNREACH},
    {WSAENETRESET, "WSAENETRESET", CC_ERR_ENETRESET},
    {WSAECONNABORTED, "WSAECONNABORTED", CC_ERR_ECONNABORTED},
    {WSAECONNRESET, "WSAECONNRESET", CC_ERR_ECONNRESET},
    {WSAENOBUFS, "WSAENOBUFS", CC_ERR_ENOBUFS},
    {WSAEISCONN, "WSAEISCONN", CC_ERR_EISCONN},
    {WSAENOTCONN, "WSAENOTCONN", CC_ERR_ENOTCONN},
    {WSAESHUTDOWN, "WSAESHUTDOWN", CC_ERR_ESHUTDOWN},
    {WSAETOOMANYREFS, "WSAETOOMANYREFS", CC_ERR_ETOOMANYREFS},
    {WSAETIMEDOUT, "WSAETIMEDOUT", CC_ERR_ETIMEDOUT},
    {WSAECONNREFUSED, "WSAECONNREFUSED", CC_ERR_ECONNREFUSED},
    {WSAELOOP, "WSAELOOP", CC_ERR_ELOOP},
    {WSAENAMETOOLONG, "WSAENAMETOOLONG", CC_ERR_ENAMETOOLONG},
    {WSAEHOSTDOWN, "WSAEHOSTDOWN", CC_ERR_EHOSTDOWN},
    {WSAEHOSTUNREACH, "WSAEHOSTUNREACH", CC_ERR_EHOSTUNREACH},
    {WSAENOTEMPTY, "WSAENOTEMPTY", CC_ERR_ENOTEMPTY},
    /*{WSAEPROCLIM, "WSAEPROCLIM", CC_ERR_EPROCLIM}, // MISSING? */
    {WSAEUSERS, "WSAEUSERS", CC_ERR_EUSERS},
    {WSAEDQUOT, "WSAEDQUOT", CC_ERR_EDQUOT},
    {WSAESTALE, "WSAESTALE", CC_ERR_ESTALE},
    {WSAEREMOTE, "WSAEREMOTE", CC_ERR_EREMOTE},
    {WSAEINVAL, "WSAEINVAL", CC_ERR_EINVAL},
    {WSAEFAULT, "WSAEFAULT", CC_ERR_EFAULT},
    {0, "NOERROR", CC_ERR_NONE},
    {0, "UNKNOWN_ERROR", CC_ERR_INTERNAL},
    {0, NULL, CC_ERR_NONE}
};
#else
const struct tl errmap[] =
{
    {NO_DATA, "NO_DATA", CC_ERR_NO_DATA},
    {HOST_NOT_FOUND, "HOST_NOT_FOUND", CC_ERR_HOST_NOT_FOUND},
    {NO_RECOVERY, "NO_RECOVERY", CC_ERR_NO_RECOVERY},
    {TRY_AGAIN, "TRY_AGAIN", CC_ERR_TRY_AGAIN},
    {EINTR, "EINTR", CC_ERR_EINTR},
    {EWOULDBLOCK, "EWOULDBLOCK", CC_ERR_EWOULDBLOCK},
    {EINPROGRESS, "EINPROGRESS", CC_ERR_EINPROGRESS},
    {EALREADY, "EALREADY", CC_ERR_EALREADY},
    {ENOTSOCK, "ENOTSOCK", CC_ERR_ENOTSOCK},
    {EDESTADDRREQ, "EDESTADDRREQ", CC_ERR_EDESTADDRREQ},
    {EMSGSIZE, "EMSGSIZE", CC_ERR_EMSGSIZE},
    {EPROTOTYPE, "EPROTOTYPE", CC_ERR_EPROTOTYPE},
    {ENOPROTOOPT, "ENOPROTOOPT", CC_ERR_ENOPROTOOPT},
    {EPROTONOSUPPORT, "EPROTONOSUPPORT", CC_ERR_EPROTONOSUPPORT},
    {ESOCKTNOSUPPORT, "ESOCKTNOSUPPORT", CC_ERR_ESOCKTNOSUPPORT},
    {EOPNOTSUPP, "EOPNOTSUPP", CC_ERR_EOPNOTSUPP},
    {EPFNOSUPPORT, "EPFNOSUPPORT", CC_ERR_EPFNOSUPPORT},
    {EAFNOSUPPORT, "EAFNOSUPPORT", CC_ERR_EAFNOSUPPORT},
    {EADDRINUSE, "EADDRINUSE", CC_ERR_EADDRINUSE},
    {EADDRNOTAVAIL, "EADDRNOTAVAIL", CC_ERR_EADDRNOTAVAIL},
    {ENETDOWN, "ENETDOWN", CC_ERR_ENETDOWN},
    {ENETUNREACH, "ENETUNREACH", CC_ERR_ENETUNREACH},
    {ENETRESET, "ENETRESET", CC_ERR_ENETRESET},
    {ECONNABORTED, "ECONNABORTED", CC_ERR_ECONNABORTED},
    {ECONNRESET, "ECONNRESET", CC_ERR_ECONNRESET},
    {ENOBUFS, "ENOBUFS", CC_ERR_ENOBUFS},
    {EISCONN, "EISCONN", CC_ERR_EISCONN},
    {ENOTCONN, "ENOTCONN", CC_ERR_ENOTCONN},
    {ESHUTDOWN, "ESHUTDOWN", CC_ERR_ESHUTDOWN},
    {ETOOMANYREFS, "ETOOMANYREFS", CC_ERR_ETOOMANYREFS},
    {ETIMEDOUT, "ETIMEDOUT", CC_ERR_ETIMEDOUT},
    {ECONNREFUSED, "ECONNREFUSED", CC_ERR_ECONNREFUSED},
    {ELOOP, "ELOOP", CC_ERR_ELOOP},
    {ENAMETOOLONG, "ENAMETOOLONG", CC_ERR_ENAMETOOLONG},
    {EHOSTDOWN, "EHOSTDOWN", CC_ERR_EHOSTDOWN},
    {EHOSTUNREACH, "EHOSTUNREACH", CC_ERR_EHOSTUNREACH},
    {ENOTEMPTY, "ENOTEMPTY", CC_ERR_ENOTEMPTY},
    /*{EPROCLIM, "EPROCLIM", CC_ERR_EPROCLIM}, // MISSING? */
    {EUSERS, "EUSERS", CC_ERR_EUSERS},
    {EDQUOT, "EDQUOT", CC_ERR_EDQUOT},
    {ESTALE, "ESTALE", CC_ERR_ESTALE},
    {EREMOTE, "EREMOTE", CC_ERR_EREMOTE},
    {EINVAL, "EINVAL", CC_ERR_EINVAL},
    {EFAULT, "EFAULT", CC_ERR_EFAULT},
    {0, "NOERROR", CC_ERR_NONE},
    {0, "UNKNOWN_ERROR", CC_ERR_INTERNAL},
    {0, NULL, CC_ERR_NONE}
};
#endif

CrissCross::Errors
CrissCross::GetErrorNumber (int why)
{
  for (int i = 0; errmap[i].s != NULL; ++i)
    if (why == errmap[i].w)
      return errmap[i].e;

  return CC_ERR_INTERNAL;
}

const char *
CrissCross::GetErrorDescription (CrissCross::Errors why)
{
  for (int i = 0; errmap[i].e != CC_ERR_NONE; ++i)
    if (why == errmap[i].e)
      return errmap[i].s;

  return NULL;
}