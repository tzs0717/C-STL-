// Predefined symbols and macros -*- C++ -*-

// Copyright (C) 1997-2014 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file bits/c++config.h
 *  这是一个内部头文件，其他库头文件会包含它。
 *  请不要直接使用它。@headername{iosfwd}
 */
/*

省流小提示 by Crab_Tang[洛谷 /user/1021365] 
这个文件没什么好看的。
都是些用于编译的奇怪的宏定义。
如果你在其他代码中发现了一些难以理解的宏定义。
可以打开此文件，按Ctrl+F查询宏定义的概念。 

*/
#ifndef _GLIBCXX_CXX_CONFIG_H
#define _GLIBCXX_CXX_CONFIG_H 1

// 当前的 C++ 库版本，采用压缩的 ISO 日期格式。
#define __GLIBCXX__ 20141030

// 各种属性的宏定义。
//   _GLIBCXX_PURE
//   _GLIBCXX_CONST
//   _GLIBCXX_NORETURN
//   _GLIBCXX_NOTHROW
//   _GLIBCXX_VISIBILITY
#ifndef _GLIBCXX_PURE
# define _GLIBCXX_PURE __attribute__ ((__pure__))
// __pure__ 是用于标记函数不会修改程序的全局状态。
#endif

#ifndef _GLIBCXX_CONST
# define _GLIBCXX_CONST __attribute__ ((__const__))
// __const__ 是用于标记函数不会修改其输入的参数。
#endif

#ifndef _GLIBCXX_NORETURN
# define _GLIBCXX_NORETURN __attribute__ ((__noreturn__))
// __noreturn__ 是用于标记一个函数不会返回。
#endif

// C++ 中的特殊宏
#ifndef _GLIBCXX_NOTHROW
# ifndef __cplusplus
#  define _GLIBCXX_NOTHROW __attribute__((__nothrow__))
// 如果不是 C++，定义为 no-throw 属性。
# endif
#endif

// 可见性属性宏定义。
//   _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY
//   _GLIBCXX_VISIBILITY
# define _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY 0

#if _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY
# define _GLIBCXX_VISIBILITY(V) __attribute__ ((__visibility__ (#V)))
#else
// 如果操作系统或 CPU 特定的头文件没有提供此功能，则将其定义为一个空的默认。
# define _GLIBCXX_VISIBILITY(V) _GLIBCXX_PSEUDO_VISIBILITY(V)
#endif

// 弃用属性的宏定义。
//   _GLIBCXX_USE_DEPRECATED
//   _GLIBCXX_DEPRECATED
#ifndef _GLIBCXX_USE_DEPRECATED
# define _GLIBCXX_USE_DEPRECATED 1
#endif

#if defined(__DEPRECATED) && (__cplusplus >= 201103L)
# define _GLIBCXX_DEPRECATED __attribute__ ((__deprecated__))
// 如果编译器支持弃用（deprecated），则标记为弃用。
#else
# define _GLIBCXX_DEPRECATED
#endif

// ABI 标签属性的宏定义。
#ifndef _GLIBCXX_ABI_TAG_CXX11
# define _GLIBCXX_ABI_TAG_CXX11 __attribute ((__abi_tag__ ("cxx11")))
// 标记 ABI 版本为 cxx11。
#endif


#if __cplusplus

// 对于 constexpr 的宏定义，以支持混合 03/0x 模式。
#ifndef _GLIBCXX_CONSTEXPR
# if __cplusplus >= 201103L
#  define _GLIBCXX_CONSTEXPR constexpr
#  define _GLIBCXX_USE_CONSTEXPR constexpr
# else
#  define _GLIBCXX_CONSTEXPR
#  define _GLIBCXX_USE_CONSTEXPR const
# endif
#endif

// 对于 noexcept 的宏定义，以支持混合 03/0x 模式。
#ifndef _GLIBCXX_NOEXCEPT
# if __cplusplus >= 201103L
#  define _GLIBCXX_NOEXCEPT noexcept
#  define _GLIBCXX_USE_NOEXCEPT noexcept
#  define _GLIBCXX_THROW(_EXC)
# else
#  define _GLIBCXX_NOEXCEPT
#  define _GLIBCXX_USE_NOEXCEPT throw()
#  define _GLIBCXX_THROW(_EXC) throw(_EXC)
# endif
#endif

#ifndef _GLIBCXX_NOTHROW
# define _GLIBCXX_NOTHROW _GLIBCXX_USE_NOEXCEPT
#endif

#ifndef _GLIBCXX_THROW_OR_ABORT
# if __EXCEPTIONS
#  define _GLIBCXX_THROW_OR_ABORT(_EXC) (throw (_EXC))
# else
#  define _GLIBCXX_THROW_OR_ABORT(_EXC) (__builtin_abort())
# endif
#endif

// 外部模板的宏定义，用于控制通过 extern 关键字声明模板的链接方式。
// 如 G++ 手册中所述，它会禁止所有隐式实例化，用于避免库中已显式实例化的类型
// 产生多个弱定义，减少生成的可执行文件的二进制大小。
// 特殊情况：_GLIBCXX_EXTERN_TEMPLATE == -1 只禁止在 basic_string 中使用 extern 模板。
// 从而启用其调试模式检查，即使在 -O0 下也是如此。
# define _GLIBCXX_EXTERN_TEMPLATE 1

/*
  libstdc++ 命名空间的概述。

  namespace std
  {
    namespace __debug { }
    namespace __parallel { }
    namespace __profile { }
    namespace __cxx1998 { }

    namespace __detail { }

    namespace rel_ops { }

    namespace tr1
    {
      namespace placeholders { }
      namespace regex_constants { }
      namespace __detail { }
    }

    namespace tr2 { }
    
    namespace decimal { }

    namespace chrono { }
    namespace placeholders { }
    namespace regex_constants { }
    namespace this_thread { }

    namespace experimental { }
  }

  namespace abi { }

  namespace __gnu_cxx
  {
    namespace __detail { }
  }

  完整的详细信息请参见:
  http://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/namespaces.html
*/
namespace std
{
  typedef __SIZE_TYPE__ 	size_t;
  typedef __PTRDIFF_TYPE__	ptrdiff_t;

#if __cplusplus >= 201103L
  typedef decltype(nullptr)	nullptr_t;
#endif
}


// 如果使用内联命名空间进行版本控制，则定义此宏。
# define _GLIBCXX_INLINE_VERSION 0 

// 用于符号版本控制的内联命名空间。
#if _GLIBCXX_INLINE_VERSION

namespace std
{
  inline namespace __7 { }

  namespace rel_ops { inline namespace __7 { } }

  namespace tr1
  {
    inline namespace __7 { }
    namespace placeholders { inline namespace __7 { } }
    namespace regex_constants { inline namespace __7 { } }
    namespace __detail { inline namespace __7 { } }
  }

  namespace tr2
  { inline namespace __7 { } }

  namespace decimal { inline namespace __7 { } }

  namespace chrono { inline namespace __7 { } }
  namespace placeholders { inline namespace __7 { } }
  namespace regex_constants { inline namespace __7 { } }
  namespace this_thread { inline namespace __7 { } }

  namespace experimental { inline namespace __7 { } }

  namespace __detail { inline namespace __7 { } }
}

namespace __gnu_cxx
{
  inline namespace __7 { }
  namespace __detail { inline namespace __7 { } }
}
# define _GLIBCXX_BEGIN_NAMESPACE_VERSION namespace __7 {
# define _GLIBCXX_END_NAMESPACE_VERSION }
#else
# define _GLIBCXX_BEGIN_NAMESPACE_VERSION
# define _GLIBCXX_END_NAMESPACE_VERSION
#endif

// 用于调试、并行、性能分析等特殊模式的内联命名空间。
#if defined(_GLIBCXX_DEBUG) || defined(_GLIBCXX_PARALLEL) \
    || defined(_GLIBCXX_PROFILE)
namespace std
{
  // 非内联命名空间，用于替代调试模式中的替代实现。
  namespace __cxx1998
  {
#if _GLIBCXX_INLINE_VERSION
 inline namespace __7 { }
#endif
  }

  // 内联命名空间，用于调试模式。
# ifdef _GLIBCXX_DEBUG
  inline namespace __debug { }
# endif

  // 内联命名空间，用于并行模式。
# ifdef _GLIBCXX_PARALLEL
  inline namespace __parallel { }
# endif

  // 内联命名空间，用于性能分析模式。
# ifdef _GLIBCXX_PROFILE
  inline namespace __profile { }
# endif
}

// 检查是否有不合法
// 检查无效的使用和不支持的混合模式使用。
// 如果同时定义了 _GLIBCXX_DEBUG 和 _GLIBCXX_PARALLEL，抛出错误
# if defined(_GLIBCXX_DEBUG) && defined(_GLIBCXX_PARALLEL)
#  error illegal use of multiple inlined namespaces
# endif

// 如果同时定义了 _GLIBCXX_PROFILE 和 _GLIBCXX_DEBUG，抛出错误
# if defined(_GLIBCXX_PROFILE) && defined(_GLIBCXX_DEBUG)
#  error illegal use of multiple inlined namespaces
# endif

// 如果同时定义了 _GLIBCXX_PROFILE 和 _GLIBCXX_PARALLEL，抛出错误
# if defined(_GLIBCXX_PROFILE) && defined(_GLIBCXX_PARALLEL)
#  error illegal use of multiple inlined namespaces
# endif

// 检查由于缺少弱符号而导致的无效使用。
// 如果 __NO_INLINE__ 被定义并且没有弱符号，发出警告
# if __NO_INLINE__ && !__GXX_WEAK__
#  warning currently using inlined namespace mode which may fail \
   without inlining due to lack of weak symbols
# endif
#endif

// 用于命名空间作用域的宏定义。可以是 std:: 命名空间或其内部的嵌套命名空间。
// _GLIBCXX_STD_A
// _GLIBCXX_STD_C
//
// 用于打开/关闭条件命名空间的宏定义。
// _GLIBCXX_BEGIN_NAMESPACE_ALGO
// _GLIBCXX_END_NAMESPACE_ALGO
// _GLIBCXX_BEGIN_NAMESPACE_CONTAINER
// _GLIBCXX_END_NAMESPACE_CONTAINER
#if defined(_GLIBCXX_DEBUG) || defined(_GLIBCXX_PROFILE)
# define _GLIBCXX_STD_C __cxx1998
# define _GLIBCXX_BEGIN_NAMESPACE_CONTAINER \
	 namespace _GLIBCXX_STD_C { _GLIBCXX_BEGIN_NAMESPACE_VERSION
# define _GLIBCXX_END_NAMESPACE_CONTAINER \
	 _GLIBCXX_END_NAMESPACE_VERSION }
# undef _GLIBCXX_EXTERN_TEMPLATE
# define _GLIBCXX_EXTERN_TEMPLATE -1
#endif

// 如果定义了 _GLIBCXX_PARALLEL，则使用 _GLIBCXX_STD_A 命名空间。
#ifdef _GLIBCXX_PARALLEL
# define _GLIBCXX_STD_A __cxx1998
# define _GLIBCXX_BEGIN_NAMESPACE_ALGO \
	 namespace _GLIBCXX_STD_A { _GLIBCXX_BEGIN_NAMESPACE_VERSION
# define _GLIBCXX_END_NAMESPACE_ALGO \
	 _GLIBCXX_END_NAMESPACE_VERSION }
#endif

// 如果没有定义 _GLIBCXX_STD_A，则将其默认定义为 std 命名空间。
#ifndef _GLIBCXX_STD_A
# define _GLIBCXX_STD_A std
#endif

// 如果没有定义 _GLIBCXX_STD_C，则将其默认定义为 std 命名空间。
#ifndef _GLIBCXX_STD_C
# define _GLIBCXX_STD_C std
#endif

// 如果没有定义 _GLIBCXX_BEGIN_NAMESPACE_ALGO，则不做任何操作。
#ifndef _GLIBCXX_BEGIN_NAMESPACE_ALGO
# define _GLIBCXX_BEGIN_NAMESPACE_ALGO
#endif

// 如果没有定义 _GLIBCXX_END_NAMESPACE_ALGO，则不做任何操作。
#ifndef _GLIBCXX_END_NAMESPACE_ALGO
# define _GLIBCXX_END_NAMESPACE_ALGO
#endif

// 如果没有定义 _GLIBCXX_BEGIN_NAMESPACE_CONTAINER，则不做任何操作。
#ifndef _GLIBCXX_BEGIN_NAMESPACE_CONTAINER
# define _GLIBCXX_BEGIN_NAMESPACE_CONTAINER
#endif

// 如果没有定义 _GLIBCXX_END_NAMESPACE_CONTAINER，则不做任何操作。
#ifndef _GLIBCXX_END_NAMESPACE_CONTAINER
# define _GLIBCXX_END_NAMESPACE_CONTAINER
#endif

// GLIBCXX_ABI 已弃用。
// 如果需要为 -mlong-double-64 提供兼容性，请定义此宏。
#undef _GLIBCXX_LONG_DOUBLE_COMPAT

// 用于长双精度 128 模式的内联命名空间。
#if defined _GLIBCXX_LONG_DOUBLE_COMPAT && defined __LONG_DOUBLE_128__
namespace std
{
  inline namespace __gnu_cxx_ldbl128 { }
}
// 定义长双精度命名空间。
# define _GLIBCXX_NAMESPACE_LDBL __gnu_cxx_ldbl128::
// 打开长双精度命名空间。
# define _GLIBCXX_BEGIN_NAMESPACE_LDBL namespace __gnu_cxx_ldbl128 {
// 关闭长双精度命名空间。
# define _GLIBCXX_END_NAMESPACE_LDBL }
#else
// 如果没有定义长双精度兼容性，则不使用长双精度命名空间。
# define _GLIBCXX_NAMESPACE_LDBL
# define _GLIBCXX_BEGIN_NAMESPACE_LDBL
# define _GLIBCXX_END_NAMESPACE_LDBL
#endif

// assert。
// 如果没有定义 _GLIBCXX_DEBUG 和 _GLIBCXX_PARALLEL，则不进行assert检查。
#if !defined(_GLIBCXX_DEBUG) && !defined(_GLIBCXX_PARALLEL)
# define __glibcxx_assert(_Condition)
#else
namespace std
{
  // 避免使用 assert，因为我们试图避免引入 <cassert> 头文件。
  inline void
  __replacement_assert(const char* __file, int __line,
		       const char* __function, const char* __condition)
  {
    // 输出assert失败的详细信息并终止程序。
    __builtin_printf("%s:%d: %s: Assertion '%s' failed.\n", __file, __line,
		     __function, __condition);
    __builtin_abort();
  }
}

// 定义 __glibcxx_assert 宏，进行assert检查。
#define __glibcxx_assert(_Condition)				   	 \
  do 									 \
  {							      		 \
    if (! (_Condition))                                                  \
      std::__replacement_assert(__FILE__, __LINE__, __PRETTY_FUNCTION__, \
				#_Condition);				 \
  } while (false)
#endif

// 用于竞争检测器的宏定义。
// _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(A) 和
// _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(A) 应该用于向竞争检测器解释
// 原子（无锁）同步：
// 竞争检测器将在共享相同参数指针时，推断出从前者到后者的 happens-before 连线。
//
// 这些宏的最常见用法（也是当前库实现中唯一的用法）是原子引用计数：
//   void _M_remove_reference()
//   {
//     _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(&this->_M_refcount);
//     if (__gnu_cxx::__exchange_and_add_dispatch(&this->_M_refcount, -1) <= 0)
//       {
//         _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&this->_M_refcount);
//         _M_destroy(__a);
//       }
//   }
// 在这个例子中，注解告诉竞争检测器：当引用计数为正时，所有内存访问不会与引用计数为零后的内存访问发生竞争。
#ifndef _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE
# define  _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(A)
#endif
#ifndef _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER
# define  _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(A)
#endif

// 用于 C 语言链接的宏定义：仅在使用 C++ 时才定义 extern "C" 链接。
# define _GLIBCXX_BEGIN_EXTERN_C extern "C" {
# define _GLIBCXX_END_EXTERN_C }

#else // !__cplusplus
# define _GLIBCXX_BEGIN_EXTERN_C
# define _GLIBCXX_END_EXTERN_C
#endif

// 第一次包含的头文件。

// 包含任何操作系统特定的定义。
#include <bits/os_defines.h>

// 包含任何 CPU 特定的定义。
#include <bits/cpu_defines.h>

// 如果平台既不使用可见性也不使用伪可见性，则
// 为命名空间注解宏指定空的默认值。
#ifndef _GLIBCXX_PSEUDO_VISIBILITY
# define _GLIBCXX_PSEUDO_VISIBILITY(V)
#endif

// 某些函数定义是为了允许用户代码覆盖的。
// 对于某些目标平台，此宏会使这些定义变为弱定义。
#ifndef _GLIBCXX_WEAK_DEFINITION
# define _GLIBCXX_WEAK_DEFINITION
#endif

// 其余的预定义配置是自动的；所有的用户钩子都在上面列出。

// 创建一个布尔标志，用于确定是否设置了 --fast-math。
#ifdef __FAST_MATH__
# define _GLIBCXX_FAST_MATH 1
#else
# define _GLIBCXX_FAST_MATH 0
#endif

// 这标记了头文件中的字符串文字，用于最终的翻译。
// 主要用于抛出异常时的消息；见 src/functexcept.cc。
// 我们使用 __N，因为在某些操作系统中传统的 _N 已经被用于其他目的（见 BADNAMES）。
#define __N(msgid)     (msgid)

// 例如，<windows.h> 被知名地定义了 min 和 max 宏...
#undef min
#undef max

// 预定义配置的结束；以下是配置时发现的设置.
/* config.h.  从 config.h.in 通过 configure 生成. */
/* config.h.in.  从 configure.ac 通过 autoheader 生成. */

/* 如果你有 `acosf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_ACOSF 1

/* 如果你有 `acosl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_ACOSL 1

/* 如果你有 `asinf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_ASINF 1

/* 如果你有 `asinl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_ASINL 1

/* 如果目标汇编器支持 .symver 指令，定义为 1。 */
/* #undef _GLIBCXX_HAVE_AS_SYMVER_DIRECTIVE */

/* 如果你有 `atan2f` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_ATAN2F 1

/* 如果你有 `atan2l` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_ATAN2L 1

/* 如果你有 `atanf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_ATANF 1

/* 如果你有 `atanl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_ATANL 1

/* 如果你有 `at_quick_exit` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_AT_QUICK_EXIT */

/* 如果目标汇编器支持线程局部存储，定义为 1。 */
/* #undef _GLIBCXX_HAVE_CC_TLS */

/* 如果你有 `ceilf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_CEILF 1

/* 如果你有 `ceill` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_CEILL 1

/* 如果你有 <complex.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_COMPLEX_H 1

/* 如果你有 `cosf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_COSF 1

/* 如果你有 `coshf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_COSHF 1

/* 如果你有 `coshl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_COSHL 1

/* 如果你有 `cosl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_COSL 1

/* 如果你有 <dlfcn.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_DLFCN_H */

/* 如果 EBADMSG 存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_EBADMSG */

/* 如果 ECANCELED 存在，定义为 1。 */
#define _GLIBCXX_HAVE_ECANCELED 1

/* 如果 ECHILD 存在，定义为 1。 */
#define _GLIBCXX_HAVE_ECHILD 1

/* 如果 EIDRM 存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_EIDRM */

/* 如果你有 <endian.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ENDIAN_H */

/* 如果 ENODATA 存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ENODATA */

/* 如果 ENOLINK 存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ENOLINK */

/* 如果 ENOSPC 存在，定义为 1。 */
#define _GLIBCXX_HAVE_ENOSPC 1

/* 如果 ENOSR 存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ENOSR */

/* 如果 ENOSTR 存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ENOSTR */

/* 如果 ENOTRECOVERABLE 存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ENOTRECOVERABLE */

/* 如果 ENOTSUP 存在，定义为 1。 */
#define _GLIBCXX_HAVE_ENOTSUP 1

/* 如果 EOVERFLOW 存在，定义为 1。 */
#define _GLIBCXX_HAVE_EOVERFLOW 1

/* 如果 EOWNERDEAD 存在，定义为 1。 */
#define _GLIBCXX_HAVE_EOWNERDEAD 1

/* 如果 EPERM 存在，定义为 1。 */
#define _GLIBCXX_HAVE_EPERM 1

/* 如果 EPROTO 存在，定义为 1。 */
#define _GLIBCXX_HAVE_EPROTO 1

/* 如果 ETIME 存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ETIME */

/* 如果 ETIMEDOUT 存在，定义为 1。 */
#define _GLIBCXX_HAVE_ETIMEDOUT 1

/* 如果 ETXTBSY 存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ETXTBSY */

/* 如果 EWOULDBLOCK 存在，定义为 1。 */
#define _GLIBCXX_HAVE_EWOULDBLOCK 1

/* 如果你有 <execinfo.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_EXECINFO_H */

/* 如果你有 `expf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_EXPF 1

/* 如果你有 `expl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_EXPL 1

/* 如果你有 `fabsf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_FABSF 1

/* 如果你有 `fabsl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_FABSL 1

/* 如果你有 <fenv.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_FENV_H 1

/* 如果你有 `finite` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_FINITE 1

/* 如果你有 `finitef` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_FINITEF */

/* 如果你有 `finitel` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_FINITEL */

/* 如果你有 <float.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_FLOAT_H 1

/* 如果你有 `floorf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_FLOORF 1

/* 如果你有 `floorl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_FLOORL 1

/* 如果你有 `fmodf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_FMODF 1

/* 如果你有 `fmodl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_FMODL 1

/* 如果你有 `fpclass` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_FPCLASS 1

/* 如果你有 <fp.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_FP_H */

/* 如果你有 `frexpf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_FREXPF 1

/* 如果你有 `frexpl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_FREXPL 1

/* 如果 _Unwind_GetIPInfo 可用，定义为 1。 */
#define _GLIBCXX_HAVE_GETIPINFO 1

/* 如果你有 `gets` 函数，在 <stdio.h> 中，定义为 1。 */
#define _GLIBCXX_HAVE_GETS 1

/* 如果你有 `hypot` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_HYPOT 1

/* 如果你有 `hypotf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_HYPOTF 1

/* 如果你有 `hypotl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_HYPOTL 1

/* 如果你有 iconv() 函数，定义为 1。 */
#define _GLIBCXX_HAVE_ICONV 1

/* 如果你有 <ieeefp.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_IEEEFP_H 1

/* 如果 <stdint.h> 中有 int64_t，定义为 1。 */
#define _GLIBCXX_HAVE_INT64_T 1

/* 如果 int64_t 是 long 类型，定义为 1。 */
/* #undef _GLIBCXX_HAVE_INT64_T_LONG */

/* 如果 int64_t 是 long long 类型，定义为 1。 */
#define _GLIBCXX_HAVE_INT64_T_LONG_LONG 1

/* 如果你有 <inttypes.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_INTTYPES_H 1

/* 如果你有 `isinf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ISINF */

/* 如果你有 `isinff` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ISINFF */

/* 如果你有 `isinfl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ISINFL */

/* 如果你有 `isnan` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_ISNAN 1

/* 如果你有 `isnanf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ISNANF */

/* 如果你有 `isnanl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_ISNANL */

/* 如果 iswblank 存在，定义为 1。 */
#define _GLIBCXX_HAVE_ISWBLANK 1

/* 如果 <locale.h> 中有 LC_MESSAGES，定义为 1。 */
/* #undef _GLIBCXX_HAVE_LC_MESSAGES */

/* 如果你有 `ldexpf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_LDEXPF 1

/* 如果你有 `ldexpl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_LDEXPL 1

/* 如果你有 <libintl.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_LIBINTL_H */

/* 仅用于构建目录中的 testsuite_hooks.h。 */
/* #undef _GLIBCXX_HAVE_LIMIT_AS */

/* 仅用于构建目录中的 testsuite_hooks.h。 */
/* #undef _GLIBCXX_HAVE_LIMIT_DATA */

/* 仅用于构建目录中的 testsuite_hooks.h。 */
/* #undef _GLIBCXX_HAVE_LIMIT_FSIZE */

/* 仅用于构建目录中的 testsuite_hooks.h。 */
/* #undef _GLIBCXX_HAVE_LIMIT_RSS */

/* 仅用于构建目录中的 testsuite_hooks.h。 */
/* #undef _GLIBCXX_HAVE_LIMIT_VMEM */

/* 如果 futex 系统调用可用，定义为 1。 */
/* #undef _GLIBCXX_HAVE_LINUX_FUTEX */

/* 如果你有 <locale.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_LOCALE_H 1

/* 如果你有 `log10f` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_LOG10F 1

/* 如果你有 `log10l` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_LOG10L 1

/* 如果你有 `logf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_LOGF 1

/* 如果你有 `logl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_LOGL 1

/* 如果你有 <machine/endian.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_MACHINE_ENDIAN_H */

/* 如果你有 <machine/param.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_MACHINE_PARAM_H */

/* 如果 mbstate_t 存在于 wchar.h 中，定义为 1。 */
#define _GLIBCXX_HAVE_MBSTATE_T 1

/* 如果你有 <memory.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_MEMORY_H 1

/* 如果你有 `modf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_MODF 1

/* 如果你有 `modff` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_MODFF 1

/* 如果你有 `modfl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_MODFL 1

/* 如果你有 <nan.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_NAN_H */

/* 如果 <poll.h> 中有 poll 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_POLL */

/* 如果你有 `powf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_POWF 1

/* 如果你有 `powl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_POWL 1

/* 如果你有 `qfpclass` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_QFPCLASS */

/* 如果你有 `quick_exit` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_QUICK_EXIT */

/* 如果你有 `setenv` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SETENV */

/* 如果你有 `sincos` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_SINCOS 1

/* 如果你有 `sincosf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_SINCOSF 1

/* 如果你有 `sincosl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_SINCOSL 1

/* 如果你有 `sinf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_SINF 1

/* 如果你有 `sinhf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_SINHF 1

/* 如果你有 `sinhl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_SINHL 1

/* 如果你有 `sinl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_SINL 1

/* 如果 sleep 函数存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SLEEP */

/* 如果你有 `sqrtf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_SQRTF 1

/* 如果你有 `sqrtl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_SQRTL 1

/* 如果你有 <stdalign.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_STDALIGN_H 1

/* 如果你有 <stdbool.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_STDBOOL_H 1

/* 如果你有 <stdint.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_STDINT_H 1

/* 如果你有 <stdlib.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_STDLIB_H 1

/* 如果 string.h 中有 strerror_l 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_STRERROR_L */

/* 如果 string.h 中有 strerror_r 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_STRERROR_R */

/* 如果你有 <strings.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_STRINGS_H 1

/* 如果你有 <string.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_STRING_H 1

/* 如果你有 `strtof` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_STRTOF 1

/* 如果你有 `strtold` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_STRTOLD 1

/* 如果 string.h 中有 strxfrm_l 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE_STRXFRM_L */

/* 如果目标运行时链接器支持将同一符号绑定到不同的版本，定义为 1。 */
#define _GLIBCXX_HAVE_SYMVER_SYMBOL_RENAMING_RUNTIME_SUPPORT 1

/* 如果你有 <sys/filio.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SYS_FILIO_H */

/* 如果你有 <sys/ioctl.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SYS_IOCTL_H */

/* 如果你有 <sys/ipc.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SYS_IPC_H */

/* 如果你有 <sys/isa_defs.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SYS_ISA_DEFS_H */

/* 如果你有 <sys/machine.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SYS_MACHINE_H */

/* 如果你有 <sys/param.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_SYS_PARAM_H 1

/* 如果你有 <sys/resource.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SYS_RESOURCE_H */

/* 如果你有合适的 <sys/sdt.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SYS_SDT_H */

/* 如果你有 <sys/sem.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SYS_SEM_H */

/* 如果你有 <sys/stat.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_SYS_STAT_H 1

/* 如果你有 <sys/sysinfo.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SYS_SYSINFO_H */

/* 如果你有 <sys/time.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_SYS_TIME_H 1

/* 如果你有 <sys/types.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_SYS_TYPES_H 1

/* 如果你有 <sys/uio.h> 头文件，定义为 1。 */
/* #undef _GLIBCXX_HAVE_SYS_UIO_H */

/* 如果 sys/stat.h 中有 S_IFREG，定义为 1。 */
/* #undef _GLIBCXX_HAVE_S_IFREG */

/* 如果 sys/stat.h 中有 S_IFREG，定义为 1。 */
#define _GLIBCXX_HAVE_S_ISREG 1

/* 如果你有 `tanf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_TANF 1

/* 如果你有 `tanhf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_TANHF 1

/* 如果你有 `tanhl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_TANHL 1

/* 如果你有 `tanl` 函数，定义为 1。 */
#define _GLIBCXX_HAVE_TANL 1

/* 如果你有 <tgmath.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_TGMATH_H 1

/* 如果目标支持线程局部存储，定义为 1。 */
#define _GLIBCXX_HAVE_TLS 1

/* 如果你有 <unistd.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_UNISTD_H 1

/* 如果 usleep 函数存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_USLEEP */

/* 如果 vfwscanf 函数存在，定义为 1。 */
#define _GLIBCXX_HAVE_VFWSCANF 1

/* 如果 vswscanf 函数存在，定义为 1。 */
#define _GLIBCXX_HAVE_VSWSCANF 1

/* 如果 vwscanf 函数存在，定义为 1。 */
#define _GLIBCXX_HAVE_VWSCANF 1

/* 如果你有 <wchar.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_WCHAR_H 1

/* 如果 wcstof 函数存在，定义为 1。 */
#define _GLIBCXX_HAVE_WCSTOF 1

/* 如果你有 <wctype.h> 头文件，定义为 1。 */
#define _GLIBCXX_HAVE_WCTYPE_H 1

/* 如果 Sleep 函数存在，定义为 1。 */
/* #undef _GLIBCXX_HAVE_WIN32_SLEEP */

/* 如果 writev 函数在 <sys/uio.h> 中可用，定义为 1。 */
/* #undef _GLIBCXX_HAVE_WRITEV */

/* 如果你有 `_acosf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ACOSF */

/* 如果你有 `_acosl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ACOSL */

/* 如果你有 `_asinf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ASINF */

/* 如果你有 `_asinl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ASINL */

/* 如果你有 `_atan2f` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ATAN2F */

/* 如果你有 `_atan2l` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ATAN2L */

/* 如果你有 `_atanf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ATANF */

/* 如果你有 `_atanl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ATANL */

/* 如果你有 `_ceilf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__CEILF */

/* 如果你有 `_ceill` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__CEILL */

/* 如果你有 `_cosf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__COSF */

/* 如果你有 `_coshf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__COSHF */

/* 如果你有 `_coshl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__COSHL */

/* 如果你有 `_cosl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__COSL */

/* 如果你有 `_expf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__EXPF */

/* 如果你有 `_expl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__EXPL */

/* 如果你有 `_fabsf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__FABSF */

/* 如果你有 `_fabsl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__FABSL */

/* 如果你有 `_finite` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__FINITE */

/* 如果你有 `_finitef` 函数，定义为 1。 */
#define _GLIBCXX_HAVE__FINITEF 1

/* 如果你有 `_finitel` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__FINITEL */

/* 如果你有 `_floorf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__FLOORF */

/* 如果你有 `_floorl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__FLOORL */

/* 如果你有 `_fmodf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__FMODF */

/* 如果你有 `_fmodl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__FMODL */

/* 如果你有 `_fpclass` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__FPCLASS */

/* 如果你有 `_frexpf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__FREXPF */

/* 如果你有 `_frexpl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__FREXPL */

/* 如果你有 `_hypot` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__HYPOT */

/* 如果你有 `_hypotf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__HYPOTF */

/* 如果你有 `_hypotl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__HYPOTL */

/* 如果你有 `_isinf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ISINF */

/* 如果你有 `_isinff` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ISINFF */

/* 如果你有 `_isinfl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ISINFL */

/* 如果你有 `_isnan` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ISNAN */

/* 如果你有 `_isnanf` 函数，定义为 1。 */
#define _GLIBCXX_HAVE__ISNANF 1

/* 如果你有 `_isnanl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__ISNANL */

/* 如果你有 `_ldexpf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__LDEXPF */

/* 如果你有 `_ldexpl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__LDEXPL */

/* 如果你有 `_log10f` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__LOG10F */

/* 如果你有 `_log10l` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__LOG10L */

/* 如果你有 `_logf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__LOGF */

/* 如果你有 `_logl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__LOGL */

/* 如果你有 `_modf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__MODF */

/* 如果你有 `_modff` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__MODFF */

/* 如果你有 `_modfl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__MODFL */

/* 如果你有 `_powf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__POWF */

/* 如果你有 `_powl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__POWL */

/* 如果你有 `_qfpclass` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__QFPCLASS */

/* 如果你有 `_sincos` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__SINCOS */

/* 如果你有 `_sincosf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__SINCOSF */

/* 如果你有 `_sincosl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__SINCOSL */

/* 如果你有 `_sinf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__SINF */

/* 如果你有 `_sinhf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__SINHF */

/* 如果你有 `_sinhl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__SINHL */

/* 如果你有 `_sinl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__SINL */

/* 如果你有 `_sqrtf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__SQRTF */

/* 如果你有 `_sqrtl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__SQRTL */

/* 如果你有 `_tanf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__TANF */

/* 如果你有 `_tanhf` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__TANHF */

/* 如果你有 `_tanhl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__TANHL */

/* 如果你有 `_tanl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE__TANL */

/* 如果你有 `__cxa_thread_atexit_impl` 函数，定义为 1。 */
/* #undef _GLIBCXX_HAVE___CXA_THREAD_ATEXIT_IMPL */

/* 如果 iconv() 函数需要 const 修饰符，定义为 const。 */
#define _GLIBCXX_ICONV_CONST 

/* 定义 libtool 存储未安装库的子目录路径。 */
#define LT_OBJDIR ".libs/"

/* 包的名称 */
/* #undef _GLIBCXX_PACKAGE */

/* 如果这个包有 bug 报告，定义为发送的地址。 */
#define _GLIBCXX_PACKAGE_BUGREPORT ""

/* 包的完整名称。 */
#define _GLIBCXX_PACKAGE_NAME "package-unused"

/* 包的完整名称和版本。 */
#define _GLIBCXX_PACKAGE_STRING "package-unused version-unused"

/* 包的短名称。 */
#define _GLIBCXX_PACKAGE_TARNAME "libstdc++"

/* 包的主页地址。 */
#define _GLIBCXX_PACKAGE_URL ""

/* 包的版本号。 */
#define _GLIBCXX_PACKAGE__GLIBCXX_VERSION "version-unused"

/* `char` 类型的大小，由 sizeof 计算。 */
/* #undef SIZEOF_CHAR */

/* `int` 类型的大小，由 sizeof 计算。 */
/* #undef SIZEOF_INT */

/* `long` 类型的大小，由 sizeof 计算。 */
/* #undef SIZEOF_LONG */

/* `short` 类型的大小，由 sizeof 计算。 */
/* #undef SIZEOF_SHORT */

/* `void *` 类型的大小，由 sizeof 计算。 */
/* #undef SIZEOF_VOID_P */

/* 如果有 ANSI C 头文件，定义为 1。 */
#define STDC_HEADERS 1

/* 包的版本号 */
/* #undef _GLIBCXX_VERSION */

/* 如果编译器支持 C++11 原子操作，定义为 1。 */
#define _GLIBCXX_ATOMIC_BUILTINS 1

/* 如果使用 boost 库中的概念检查代码，定义为 1。 */
/* #undef _GLIBCXX_CONCEPT_CHECKS */

/* 如果希望使用完全动态的基本字符串，定义为 1，否则禁用，平台默认值为未定义。 */
#define _GLIBCXX_FULLY_DYNAMIC_STRING 1

/* 如果 gthreads 库可用，定义为 1。 */
#define _GLIBCXX_HAS_GTHREADS 1

/* 如果构建的是完整的托管库，定义为 1，否则定义为 0（如果是独立的）。 */
#define _GLIBCXX_HOSTED 1

/* 如果应该为 -mlong-double-64 提供兼容性，定义为 1。 */
/* #undef _GLIBCXX_LONG_DOUBLE_COMPAT */

/* 如果 ptrdiff_t 是 int 类型，定义为 1。 */
/* #undef _GLIBCXX_PTRDIFF_T_IS_INT */

/* 如果在 "make check" 时使用 setrlimit 设置资源限制，定义为 1。 */
/* #undef _GLIBCXX_RES_LIMITS */

/* 如果 size_t 是 unsigned int 类型，定义为 1。 */
/* #undef _GLIBCXX_SIZE_T_IS_UINT */

/* 如果编译器为 setjmp/longjmp 异常配置，定义为 1。 */
/* #undef _GLIBCXX_SJLJ_EXCEPTIONS */

/* 定义为 EOF 整数常量的值。 */
#define _GLIBCXX_STDIO_EOF -1

/* 定义为 SEEK_CUR 整数常量的值。 */
#define _GLIBCXX_STDIO_SEEK_CUR 1

/* 定义为 SEEK_END 整数常量的值。 */
#define _GLIBCXX_STDIO_SEEK_END 2

/* 定义为在共享库中使用符号版本控制。 */
#define _GLIBCXX_SYMVER 1

/* 如果在共享库中使用 Darwin 版本控制，定义为 1。 */
/* #undef _GLIBCXX_SYMVER_DARWIN */

/* 如果在共享库中使用 GNU 版本控制，定义为 1。 */
#define _GLIBCXX_SYMVER_GNU 1

/* 如果在共享库中使用 GNU 命名空间版本控制，定义为 1。 */
/* #undef _GLIBCXX_SYMVER_GNU_NAMESPACE */

/* 如果在共享库中使用 Sun 版本控制，定义为 1。 */
/* #undef _GLIBCXX_SYMVER_SUN */

/* 如果可以使用或暴露 C99 标准中的函数或宏（来自 <wchar.h>, <math.h>, <complex.h>, <stdio.h>, <stdlib.h>），定义为 1。 */
#define _GLIBCXX_USE_C99 1

/* 如果在 <complex.h> 中使用 C99 函数，定义为 1。使用编译器内建函数需要相应的 C99 库函数支持。 */
#define _GLIBCXX_USE_C99_COMPLEX 1

/* 如果在 <tr1/complex> 中使用 C99 函数，定义为 1。使用编译器内建函数需要相应的 C99 库函数支持。 */
#define _GLIBCXX_USE_C99_COMPLEX_TR1 1

/* 如果在 <tr1/cctype> 中使用 C99 函数，定义为 1。 */
#define _GLIBCXX_USE_C99_CTYPE_TR1 1

/* 如果在 <tr1/cfenv> 中使用 C99 函数，定义为 1。 */
#define _GLIBCXX_USE_C99_FENV_TR1 1

/* 如果在 <tr1/cinttypes> 中使用 C99 函数，定义为 1。 */
#define _GLIBCXX_USE_C99_INTTYPES_TR1 1

/* 如果在 <tr1/cinttypes> 中使用 C99 对 wchar_t 的函数，定义为 1。 */
#define _GLIBCXX_USE_C99_INTTYPES_WCHAR_T_TR1 1

/* 如果在 <cmath> 中使用 C99 函数或宏，定义为 1。 */
#define _GLIBCXX_USE_C99_MATH 1

/* 如果在 <tr1/cmath> 中使用 C99 函数或宏，定义为 1。 */
#define _GLIBCXX_USE_C99_MATH_TR1 1

/* 如果在 <tr1/cstdint> 中使用 C99 类型，定义为 1。 */
#define _GLIBCXX_USE_C99_STDINT_TR1 1

/* 如果支持 clock_gettime 系统调用的单调时钟和实时时钟，定义为 1。 */
/* #undef _GLIBCXX_USE_CLOCK_GETTIME_SYSCALL */

/* 如果 clock_gettime 支持单调时钟，定义为 1。 */
#define _GLIBCXX_USE_CLOCK_MONOTONIC 1

/* 如果 clock_gettime 支持实时时钟，定义为 1。 */
#define _GLIBCXX_USE_CLOCK_REALTIME 1

/* 如果支持 ISO/IEC TR 24733 十进制浮点类型，定义为 1。 */
#define _GLIBCXX_USE_DECIMAL_FLOAT 1

/* 如果支持 __float128 类型，定义为 1。 */
#define _GLIBCXX_USE_FLOAT128 1

/* 如果 gettimeofday 可用，定义为 1。 */
#define _GLIBCXX_USE_GETTIMEOFDAY 1

/* 如果 <sys/sysinfo.h> 中的 get_nprocs 可用，定义为 1。 */
/* #undef _GLIBCXX_USE_GET_NPROCS */

/* 如果支持 __int128 类型，定义为 1。 */
#define _GLIBCXX_USE_INT128 1

/* 如果支持大文件系统（LFS），定义为 1。 */
#define _GLIBCXX_USE_LFS 1

/* 如果使用专门为 long long 类型优化的代码，定义为 1。 */
#define _GLIBCXX_USE_LONG_LONG 1

/* 如果 nanosleep 可用，定义为 1。 */
#define _GLIBCXX_USE_NANOSLEEP 1

/* 如果需要使用 NLS（本地化）翻译，定义为 1。 */
/* #undef _GLIBCXX_USE_NLS */

/* 如果 <pthread.h> 中的 pthreads_num_processors_np 可用，定义为 1。 */
#define _GLIBCXX_USE_PTHREADS_NUM_PROCESSORS_NP 1

/* 如果 /dev/random 和 /dev/urandom 可用于 TR1（第 5.1 章）的 random_device，定义为 1。 */
/* #undef _GLIBCXX_USE_RANDOM_TR1 */

/* 如果 sched_yield 可用，定义为 1。 */
#define _GLIBCXX_USE_SCHED_YIELD 1

/* 如果 <unistd.h> 中的 _SC_NPROCESSORS_ONLN 可用，定义为 1。 */
/* #undef _GLIBCXX_USE_SC_NPROCESSORS_ONLN */

/* 如果 <unistd.h> 中的 _SC_NPROC_ONLN 可用，定义为 1。 */
/* #undef _GLIBCXX_USE_SC_NPROC_ONLN */

/* 如果 <sys/sysctl.h> 中的 sysctl()、CTL_HW 和 HW_NCPU 可用，定义为 1。 */
/* #undef _GLIBCXX_USE_SYSCTL_HW_NCPU */

/* 如果 <stdio.h> 中的过时 tmpnam 可用，定义为 1。 */
#define _GLIBCXX_USE_TMPNAM 1

/* 如果专门为 wchar_t 类型使用的代码，定义为 1。 */
#define _GLIBCXX_USE_WCHAR_T 1

/* 如果构建的是详细版本的库，定义为 1，否则为 0。 */
#define _GLIBCXX_VERBOSE 1

/* 如果 as 可以处理 rdrand，定义为 1。 */
#define _GLIBCXX_X86_RDRAND 1

/* 如果 mutex_timedlock 可用，定义为 1。 */
#define _GTHREAD_USE_MUTEX_TIMEDLOCK 1

/* 如果 _acosf 存在并且 _GLIBCXX_HAVE_ACOSF 未定义，定义 _GLIBCXX_HAVE_ACOSF 为 1，并且将 acosf 映射到 _acosf。 */
#if defined (_GLIBCXX_HAVE__ACOSF) && ! defined (_GLIBCXX_HAVE_ACOSF)
# define _GLIBCXX_HAVE_ACOSF 1
# define acosf _acosf
#endif

/* 如果 _acosl 存在并且 _GLIBCXX_HAVE_ACOSL 未定义，定义 _GLIBCXX_HAVE_ACOSL 为 1，并且将 acosl 映射到 _acosl。 */
#if defined (_GLIBCXX_HAVE__ACOSL) && ! defined (_GLIBCXX_HAVE_ACOSL)
# define _GLIBCXX_HAVE_ACOSL 1
# define acosl _acosl
#endif

/* 如果 _asinf 存在并且 _GLIBCXX_HAVE_ASINF 未定义，定义 _GLIBCXX_HAVE_ASINF 为 1，并且将 asinf 映射到 _asinf。 */
#if defined (_GLIBCXX_HAVE__ASINF) && ! defined (_GLIBCXX_HAVE_ASINF)
# define _GLIBCXX_HAVE_ASINF 1
# define asinf _asinf
#endif

/* 如果 _asinl 存在并且 _GLIBCXX_HAVE_ASINL 未定义，定义 _GLIBCXX_HAVE_ASINL 为 1，并且将 asinl 映射到 _asinl。 */
#if defined (_GLIBCXX_HAVE__ASINL) && ! defined (_GLIBCXX_HAVE_ASINL)
# define _GLIBCXX_HAVE_ASINL 1
# define asinl _asinl
#endif

/* 如果 _atan2f 存在并且 _GLIBCXX_HAVE_ATAN2F 未定义，定义 _GLIBCXX_HAVE_ATAN2F 为 1，并且将 atan2f 映射到 _atan2f。 */
#if defined (_GLIBCXX_HAVE__ATAN2F) && ! defined (_GLIBCXX_HAVE_ATAN2F)
# define _GLIBCXX_HAVE_ATAN2F 1
# define atan2f _atan2f
#endif

/* 如果 _atan2l 存在并且 _GLIBCXX_HAVE_ATAN2L 未定义，定义 _GLIBCXX_HAVE_ATAN2L 为 1，并且将 atan2l 映射到 _atan2l。 */
#if defined (_GLIBCXX_HAVE__ATAN2L) && ! defined (_GLIBCXX_HAVE_ATAN2L)
# define _GLIBCXX_HAVE_ATAN2L 1
# define atan2l _atan2l
#endif

/* 如果 _atanf 存在并且 _GLIBCXX_HAVE_ATANF 未定义，定义 _GLIBCXX_HAVE_ATANF 为 1，并且将 atanf 映射到 _atanf。 */
#if defined (_GLIBCXX_HAVE__ATANF) && ! defined (_GLIBCXX_HAVE_ATANF)
# define _GLIBCXX_HAVE_ATANF 1
# define atanf _atanf
#endif

/* 如果 _atanl 存在并且 _GLIBCXX_HAVE_ATANL 未定义，定义 _GLIBCXX_HAVE_ATANL 为 1，并且将 atanl 映射到 _atanl。 */
#if defined (_GLIBCXX_HAVE__ATANL) && ! defined (_GLIBCXX_HAVE_ATANL)
# define _GLIBCXX_HAVE_ATANL 1
# define atanl _atanl
#endif

/* 如果 _ceild 存在并且 _GLIBCXX_HAVE_CEILF 未定义，定义 _GLIBCXX_HAVE_CEILF 为 1，并且将 ceilf 映射到 _ceilf。 */
#if defined (_GLIBCXX_HAVE__CEILF) && ! defined (_GLIBCXX_HAVE_CEILF)
# define _GLIBCXX_HAVE_CEILF 1
# define ceilf _ceilf
#endif

/* 如果 _ceill 存在并且 _GLIBCXX_HAVE_CEILL 未定义，定义 _GLIBCXX_HAVE_CEILL 为 1，并且将 ceill 映射到 _ceill。 */
#if defined (_GLIBCXX_HAVE__CEILL) && ! defined (_GLIBCXX_HAVE_CEILL)
# define _GLIBCXX_HAVE_CEILL 1
# define ceill _ceill
#endif

/* 如果 _cosf 存在并且 _GLIBCXX_HAVE_COSF 未定义，定义 _GLIBCXX_HAVE_COSF 为 1，并且将 cosf 映射到 _cosf。 */
#if defined (_GLIBCXX_HAVE__COSF) && ! defined (_GLIBCXX_HAVE_COSF)
# define _GLIBCXX_HAVE_COSF 1
# define cosf _cosf
#endif

/* 如果 _coshf 存在并且 _GLIBCXX_HAVE_COSHF 未定义，定义 _GLIBCXX_HAVE_COSHF 为 1，并且将 coshf 映射到 _coshf。 */
#if defined (_GLIBCXX_HAVE__COSHF) && ! defined (_GLIBCXX_HAVE_COSHF)
# define _GLIBCXX_HAVE_COSHF 1
# define coshf _coshf
#endif

/* 如果 _coshl 存在并且 _GLIBCXX_HAVE_COSHL 未定义，定义 _GLIBCXX_HAVE_COSHL 为 1，并且将 coshl 映射到 _coshl。 */
#if defined (_GLIBCXX_HAVE__COSHL) && ! defined (_GLIBCXX_HAVE_COSHL)
# define _GLIBCXX_HAVE_COSHL 1
# define coshl _coshl
#endif

/* 如果 _cosl 存在并且 _GLIBCXX_HAVE_COSL 未定义，定义 _GLIBCXX_HAVE_COSL 为 1，并且将 cosl 映射到 _cosl。 */
#if defined (_GLIBCXX_HAVE__COSL) && ! defined (_GLIBCXX_HAVE_COSL)
# define _GLIBCXX_HAVE_COSL 1
# define cosl _cosl
#endif

/* 如果 _expf 存在并且 _GLIBCXX_HAVE_EXPF 未定义，定义 _GLIBCXX_HAVE_EXPF 为 1，并且将 expf 映射到 _expf。 */
#if defined (_GLIBCXX_HAVE__EXPF) && ! defined (_GLIBCXX_HAVE_EXPF)
# define _GLIBCXX_HAVE_EXPF 1
# define expf _expf
#endif

/* 如果 _expl 存在并且 _GLIBCXX_HAVE_EXPL 未定义，定义 _GLIBCXX_HAVE_EXPL 为 1，并且将 expl 映射到 _expl。 */
#if defined (_GLIBCXX_HAVE__EXPL) && ! defined (_GLIBCXX_HAVE_EXPL)
# define _GLIBCXX_HAVE_EXPL 1
# define expl _expl
#endif

/* 如果 _fabsf 存在并且 _GLIBCXX_HAVE_FABSF 未定义，定义 _GLIBCXX_HAVE_FABSF 为 1，并且将 fabsf 映射到 _fabsf。 */
#if defined (_GLIBCXX_HAVE__FABSF) && ! defined (_GLIBCXX_HAVE_FABSF)
# define _GLIBCXX_HAVE_FABSF 1
# define fabsf _fabsf
#endif

/* 如果 _fabsl 存在并且 _GLIBCXX_HAVE_FABSL 未定义，定义 _GLIBCXX_HAVE_FABSL 为 1，并且将 fabsl 映射到 _fabsl。 */
#if defined (_GLIBCXX_HAVE__FABSL) && ! defined (_GLIBCXX_HAVE_FABSL)
# define _GLIBCXX_HAVE_FABSL 1
# define fabsl _fabsl
#endif

/* 如果 _finite 存在并且 _GLIBCXX_HAVE_FINITE 未定义，定义 _GLIBCXX_HAVE_FINITE 为 1，并且将 finite 映射到 _finite。 */
#if defined (_GLIBCXX_HAVE__FINITE) && ! defined (_GLIBCXX_HAVE_FINITE)
# define _GLIBCXX_HAVE_FINITE 1
# define finite _finite
#endif

/* 如果 _finitef 存在并且 _GLIBCXX_HAVE_FINITEF 未定义，定义 _GLIBCXX_HAVE_FINITEF 为 1，并且将 finitef 映射到 _finitef。 */
#if defined (_GLIBCXX_HAVE__FINITEF) && ! defined (_GLIBCXX_HAVE_FINITEF)
# define _GLIBCXX_HAVE_FINITEF 1
# define finitef _finitef
#endif

/* 如果 _finitel 存在并且 _GLIBCXX_HAVE_FINITEL 未定义，定义 _GLIBCXX_HAVE_FINITEL 为 1，并且将 finitel 映射到 _finitel。 */
#if defined (_GLIBCXX_HAVE__FINITEL) && ! defined (_GLIBCXX_HAVE_FINITEL)
# define _GLIBCXX_HAVE_FINITEL 1
# define finitel _finitel
#endif

/* 如果 _floorf 存在并且 _GLIBCXX_HAVE_FLOORF 未定义，定义 _GLIBCXX_HAVE_FLOORF 为 1，并且将 floorf 映射到 _floorf。 */
#if defined (_GLIBCXX_HAVE__FLOORF) && ! defined (_GLIBCXX_HAVE_FLOORF)
# define _GLIBCXX_HAVE_FLOORF 1
# define floorf _floorf
#endif

/* 如果 _floorl 存在并且 _GLIBCXX_HAVE_FLOORL 未定义，定义 _GLIBCXX_HAVE_FLOORL 为 1，并且将 floorl 映射到 _floorl。 */
#if defined (_GLIBCXX_HAVE__FLOORL) && ! defined (_GLIBCXX_HAVE_FLOORL)
# define _GLIBCXX_HAVE_FLOORL 1
# define floorl _floorl
#endif

/* 如果 _fmodf 存在并且 _GLIBCXX_HAVE_FMODF 未定义，定义 _GLIBCXX_HAVE_FMODF 为 1，并且将 fmodf 映射到 _fmodf。 */
#if defined (_GLIBCXX_HAVE__FMODF) && ! defined (_GLIBCXX_HAVE_FMODF)
# define _GLIBCXX_HAVE_FMODF 1
# define fmodf _fmodf
#endif

/* 如果 _fmodl 存在并且 _GLIBCXX_HAVE_FMODL 未定义，定义 _GLIBCXX_HAVE_FMODL 为 1，并且将 fmodl 映射到 _fmodl。 */
#if defined (_GLIBCXX_HAVE__FMODL) && ! defined (_GLIBCXX_HAVE_FMODL)
# define _GLIBCXX_HAVE_FMODL 1
# define fmodl _fmodl
#endif

/* 如果 _fpclass 存在并且 _GLIBCXX_HAVE_FPCLASS 未定义，定义 _GLIBCXX_HAVE_FPCLASS 为 1，并且将 fpclass 映射到 _fpclass。 */
#if defined (_GLIBCXX_HAVE__FPCLASS) && ! defined (_GLIBCXX_HAVE_FPCLASS)
# define _GLIBCXX_HAVE_FPCLASS 1
# define fpclass _fpclass
#endif

/* 如果 _frexpf 存在并且 _GLIBCXX_HAVE_FREXPF 未定义，定义 _GLIBCXX_HAVE_FREXPF 为 1，并且将 frexpf 映射到 _frexpf。 */
#if defined (_GLIBCXX_HAVE__FREXPF) && ! defined (_GLIBCXX_HAVE_FREXPF)
# define _GLIBCXX_HAVE_FREXPF 1
# define frexpf _frexpf
#endif

/* 如果 _frexpl 存在并且 _GLIBCXX_HAVE_FREXPL 未定义，定义 _GLIBCXX_HAVE_FREXPL 为 1，并且将 frexpl 映射到 _frexpl。 */
#if defined (_GLIBCXX_HAVE__FREXPL) && ! defined (_GLIBCXX_HAVE_FREXPL)
# define _GLIBCXX_HAVE_FREXPL 1
# define frexpl _frexpl
#endif

/* 如果 _hypot 存在并且 _GLIBCXX_HAVE_HYPOT 未定义，定义 _GLIBCXX_HAVE_HYPOT 为 1，并且将 hypot 映射到 _hypot。 */
#if defined (_GLIBCXX_HAVE__HYPOT) && ! defined (_GLIBCXX_HAVE_HYPOT)
# define _GLIBCXX_HAVE_HYPOT 1
# define hypot _hypot
#endif

/* 如果 _hypotf 存在并且 _GLIBCXX_HAVE_HYPOTF 未定义，定义 _GLIBCXX_HAVE_HYPOTF 为 1，并且将 hypotf 映射到 _hypotf。 */
#if defined (_GLIBCXX_HAVE__HYPOTF) && ! defined (_GLIBCXX_HAVE_HYPOTF)
# define _GLIBCXX_HAVE_HYPOTF 1
# define hypotf _hypotf
#endif

/* 如果 _hypotl 存在并且 _GLIBCXX_HAVE_HYPOTL 未定义，定义 _GLIBCXX_HAVE_HYPOTL 为 1，并且将 hypotl 映射到 _hypotl。 */
#if defined (_GLIBCXX_HAVE__HYPOTL) && ! defined (_GLIBCXX_HAVE_HYPOTL)
# define _GLIBCXX_HAVE_HYPOTL 1
# define hypotl _hypotl
#endif

/* 如果 _isinf 存在并且 _GLIBCXX_HAVE_ISINF 未定义，定义 _GLIBCXX_HAVE_ISINF 为 1，并且将 isinf 映射到 _isinf。 */
#if defined (_GLIBCXX_HAVE__ISINF) && ! defined (_GLIBCXX_HAVE_ISINF)
# define _GLIBCXX_HAVE_ISINF 1
# define isinf _isinf
#endif

/* 如果 _isinff 存在并且 _GLIBCXX_HAVE_ISINFF 未定义，定义 _GLIBCXX_HAVE_ISINFF 为 1，并且将 isinff 映射到 _isinff。 */
#if defined (_GLIBCXX_HAVE__ISINFF) && ! defined (_GLIBCXX_HAVE_ISINFF)
# define _GLIBCXX_HAVE_ISINFF 1
# define isinff _isinff
#endif

/* 如果 _isinfl 存在并且 _GLIBCXX_HAVE_ISINFL 未定义，定义 _GLIBCXX_HAVE_ISINFL 为 1，并且将 isinfl 映射到 _isinfl。 */
#if defined (_GLIBCXX_HAVE__ISINFL) && ! defined (_GLIBCXX_HAVE_ISINFL)
# define _GLIBCXX_HAVE_ISINFL 1
# define isinfl _isinfl
#endif

/* 如果 _isnan 存在并且 _GLIBCXX_HAVE_ISNAN 未定义，定义 _GLIBCXX_HAVE_ISNAN 为 1，并且将 isnan 映射到 _isnan。 */
#if defined (_GLIBCXX_HAVE__ISNAN) && ! defined (_GLIBCXX_HAVE_ISNAN)
# define _GLIBCXX_HAVE_ISNAN 1
# define isnan _isnan
#endif

/* 如果 _isnanf 存在并且 _GLIBCXX_HAVE_ISNANF 未定义，定义 _GLIBCXX_HAVE_ISNANF 为 1，并且将 isnanf 映射到 _isnanf。 */
#if defined (_GLIBCXX_HAVE__ISNANF) && ! defined (_GLIBCXX_HAVE_ISNANF)
# define _GLIBCXX_HAVE_ISNANF 1
# define isnanf _isnanf
#endif

/* 如果 _isnanl 存在并且 _GLIBCXX_HAVE_ISNANL 未定义，定义 _GLIBCXX_HAVE_ISNANL 为 1，并且将 isnanl 映射到 _isnanl。 */
#if defined (_GLIBCXX_HAVE__ISNANL) && ! defined (_GLIBCXX_HAVE_ISNANL)
# define _GLIBCXX_HAVE_ISNANL 1
# define isnanl _isnanl
#endif

/* 如果 _ldexpf 存在并且 _GLIBCXX_HAVE_LDEXPF 未定义，定义 _GLIBCXX_HAVE_LDEXPF 为 1，并且将 ldexpf 映射到 _ldexpf。 */
#if defined (_GLIBCXX_HAVE__LDEXPF) && ! defined (_GLIBCXX_HAVE_LDEXPF)
# define _GLIBCXX_HAVE_LDEXPF 1
# define ldexpf _ldexpf
#endif

/* 如果 _ldexpl 存在并且 _GLIBCXX_HAVE_LDEXPL 未定义，定义 _GLIBCXX_HAVE_LDEXPL 为 1，并且将 ldexpl 映射到 _ldexpl。 */
#if defined (_GLIBCXX_HAVE__LDEXPL) && ! defined (_GLIBCXX_HAVE_LDEXPL)
# define _GLIBCXX_HAVE_LDEXPL 1
# define ldexpl _ldexpl
#endif

/* 如果 _log10f 存在并且 _GLIBCXX_HAVE_LOG10F 未定义，定义 _GLIBCXX_HAVE_LOG10F 为 1，并且将 log10f 映射到 _log10f。 */
#if defined (_GLIBCXX_HAVE__LOG10F) && ! defined (_GLIBCXX_HAVE_LOG10F)
# define _GLIBCXX_HAVE_LOG10F 1
# define log10f _log10f
#endif

/* 如果 _log10l 存在并且 _GLIBCXX_HAVE_LOG10L 未定义，定义 _GLIBCXX_HAVE_LOG10L 为 1，并且将 log10l 映射到 _log10l。 */
#if defined (_GLIBCXX_HAVE__LOG10L) && ! defined (_GLIBCXX_HAVE_LOG10L)
# define _GLIBCXX_HAVE_LOG10L 1
# define log10l _log10l
#endif

/* 如果 _logf 存在并且 _GLIBCXX_HAVE_LOGF 未定义，定义 _GLIBCXX_HAVE_LOGF 为 1，并且将 logf 映射到 _logf。 */
#if defined (_GLIBCXX_HAVE__LOGF) && ! defined (_GLIBCXX_HAVE_LOGF)
# define _GLIBCXX_HAVE_LOGF 1
# define logf _logf
#endif

/* 如果 _logl 存在并且 _GLIBCXX_HAVE_LOGL 未定义，定义 _GLIBCXX_HAVE_LOGL 为 1，并且将 logl 映射到 _logl。 */
#if defined (_GLIBCXX_HAVE__LOGL) && ! defined (_GLIBCXX_HAVE_LOGL)
# define _GLIBCXX_HAVE_LOGL 1
# define logl _logl
#endif

/* 如果 _modf 存在并且 _GLIBCXX_HAVE_MODF 未定义，定义 _GLIBCXX_HAVE_MODF 为 1，并且将 modf 映射到 _modf。 */
#if defined (_GLIBCXX_HAVE__MODF) && ! defined (_GLIBCXX_HAVE_MODF)
# define _GLIBCXX_HAVE_MODF 1
# define modf _modf
#endif

/* 如果 _modff 存在并且 _GLIBCXX_HAVE_MODFF 未定义，定义 _GLIBCXX_HAVE_MODFF 为 1，并且将 modff 映射到 _modff。 */
#if defined (_GLIBCXX_HAVE__MODFF) && ! defined (_GLIBCXX_HAVE_MODFF)
# define _GLIBCXX_HAVE_MODFF 1
# define modff _modff
#endif

/* 如果 _modfl 存在并且 _GLIBCXX_HAVE_MODFL 未定义，定义 _GLIBCXX_HAVE_MODFL 为 1，并且将 modfl 映射到 _modfl。 */
#if defined (_GLIBCXX_HAVE__MODFL) && ! defined (_GLIBCXX_HAVE_MODFL)
# define _GLIBCXX_HAVE_MODFL 1
# define modfl _modfl
#endif

/* 如果 _powf 存在并且 _GLIBCXX_HAVE_POWF 未定义，定义 _GLIBCXX_HAVE_POWF 为 1，并且将 powf 映射到 _powf。 */
#if defined (_GLIBCXX_HAVE__POWF) && ! defined (_GLIBCXX_HAVE_POWF)
# define _GLIBCXX_HAVE_POWF 1
# define powf _powf
#endif

/* 如果 _powl 存在并且 _GLIBCXX_HAVE_POWL 未定义，定义 _GLIBCXX_HAVE_POWL 为 1，并且将 powl 映射到 _powl。 */
#if defined (_GLIBCXX_HAVE__POWL) && ! defined (_GLIBCXX_HAVE_POWL)
# define _GLIBCXX_HAVE_POWL 1
# define powl _powl
#endif

/* 如果 _qfpclass 存在并且 _GLIBCXX_HAVE_QFPCLASS 未定义，定义 _GLIBCXX_HAVE_QFPCLASS 为 1，并且将 qfpclass 映射到 _qfpclass。 */
#if defined (_GLIBCXX_HAVE__QFPCLASS) && ! defined (_GLIBCXX_HAVE_QFPCLASS)
# define _GLIBCXX_HAVE_QFPCLASS 1
# define qfpclass _qfpclass
#endif

/* 如果 _sincos 存在并且 _GLIBCXX_HAVE_SINCOS 未定义，定义 _GLIBCXX_HAVE_SINCOS 为 1，并且将 sincos 映射到 _sincos。 */
#if defined (_GLIBCXX_HAVE__SINCOS) && ! defined (_GLIBCXX_HAVE_SINCOS)
# define _GLIBCXX_HAVE_SINCOS 1
# define sincos _sincos
#endif

/* 如果 _sincosf 存在并且 _GLIBCXX_HAVE_SINCOSF 未定义，定义 _GLIBCXX_HAVE_SINCOSF 为 1，并且将 sincosf 映射到 _sincosf。 */
#if defined (_GLIBCXX_HAVE__SINCOSF) && ! defined (_GLIBCXX_HAVE_SINCOSF)
# define _GLIBCXX_HAVE_SINCOSF 1
# define sincosf _sincosf
#endif

/* 如果 _sincosl 存在并且 _GLIBCXX_HAVE_SINCOSL 未定义，定义 _GLIBCXX_HAVE_SINCOSL 为 1，并且将 sincosl 映射到 _sincosl。 */
#if defined (_GLIBCXX_HAVE__SINCOSL) && ! defined (_GLIBCXX_HAVE_SINCOSL)
# define _GLIBCXX_HAVE_SINCOSL 1
# define sincosl _sincosl
#endif

/* 如果 _sinf 存在并且 _GLIBCXX_HAVE_SINF 未定义，定义 _GLIBCXX_HAVE_SINF 为 1，并且将 sinf 映射到 _sinf。 */
#if defined (_GLIBCXX_HAVE__SINF) && ! defined (_GLIBCXX_HAVE_SINF)
# define _GLIBCXX_HAVE_SINF 1
# define sinf _sinf
#endif

/* 如果 _sinhf 存在并且 _GLIBCXX_HAVE_SINHF 未定义，定义 _GLIBCXX_HAVE_SINHF 为 1，并且将 sinhf 映射到 _sinhf。 */
#if defined (_GLIBCXX_HAVE__SINHF) && ! defined (_GLIBCXX_HAVE_SINHF)
# define _GLIBCXX_HAVE_SINHF 1
# define sinhf _sinhf
#endif

/* 如果 _sinhl 存在并且 _GLIBCXX_HAVE_SINHL 未定义，定义 _GLIBCXX_HAVE_SINHL 为 1，并且将 sinhl 映射到 _sinhl。 */
#if defined (_GLIBCXX_HAVE__SINHL) && ! defined (_GLIBCXX_HAVE_SINHL)
# define _GLIBCXX_HAVE_SINHL 1
# define sinhl _sinhl
#endif

/* 如果 _sinl 存在并且 _GLIBCXX_HAVE_SINL 未定义，定义 _GLIBCXX_HAVE_SINL 为 1，并且将 sinl 映射到 _sinl。 */
#if defined (_GLIBCXX_HAVE__SINL) && ! defined (_GLIBCXX_HAVE_SINL)
# define _GLIBCXX_HAVE_SINL 1
# define sinl _sinl
#endif

/* 如果 _sqrtf 存在并且 _GLIBCXX_HAVE_SQRTF 未定义，定义 _GLIBCXX_HAVE_SQRTF 为 1，并且将 sqrtf 映射到 _sqrtf。 */
#if defined (_GLIBCXX_HAVE__SQRTF) && ! defined (_GLIBCXX_HAVE_SQRTF)
# define _GLIBCXX_HAVE_SQRTF 1
# define sqrtf _sqrtf
#endif

/* 如果 _sqrtl 存在并且 _GLIBCXX_HAVE_SQRTL 未定义，定义 _GLIBCXX_HAVE_SQRTL 为 1，并且将 sqrtl 映射到 _sqrtl。 */
#if defined (_GLIBCXX_HAVE__SQRTL) && ! defined (_GLIBCXX_HAVE_SQRTL)
# define _GLIBCXX_HAVE_SQRTL 1
# define sqrtl _sqrtl
#endif

/* 如果 _strtof 存在并且 _GLIBCXX_HAVE_STRTOF 未定义，定义 _GLIBCXX_HAVE_STRTOF 为 1，并且将 strtof 映射到 _strtof。 */
#if defined (_GLIBCXX_HAVE__STRTOF) && ! defined (_GLIBCXX_HAVE_STRTOF)
# define _GLIBCXX_HAVE_STRTOF 1
# define strtof _strtof
#endif

/* 如果 _strtold 存在并且 _GLIBCXX_HAVE_STRTOLD 未定义，定义 _GLIBCXX_HAVE_STRTOLD 为 1，并且将 strtold 映射到 _strtold。 */
#if defined (_GLIBCXX_HAVE__STRTOLD) && ! defined (_GLIBCXX_HAVE_STRTOLD)
# define _GLIBCXX_HAVE_STRTOLD 1
# define strtold _strtold
#endif

/* 如果 _tanf 存在并且 _GLIBCXX_HAVE_TANF 未定义，定义 _GLIBCXX_HAVE_TANF 为 1，并且将 tanf 映射到 _tanf。 */
#if defined (_GLIBCXX_HAVE__TANF) && ! defined (_GLIBCXX_HAVE_TANF)
# define _GLIBCXX_HAVE_TANF 1
# define tanf _tanf
#endif

/* 如果 _tanhf 存在并且 _GLIBCXX_HAVE_TANHF 未定义，定义 _GLIBCXX_HAVE_TANHF 为 1，并且将 tanhf 映射到 _tanhf。 */
#if defined (_GLIBCXX_HAVE__TANHF) && ! defined (_GLIBCXX_HAVE_TANHF)
# define _GLIBCXX_HAVE_TANHF 1
# define tanhf _tanhf
#endif

/* 如果 _tanhl 存在并且 _GLIBCXX_HAVE_TANHL 未定义，定义 _GLIBCXX_HAVE_TANHL 为 1，并且将 tanhl 映射到 _tanhl。 */
#if defined (_GLIBCXX_HAVE__TANHL) && ! defined (_GLIBCXX_HAVE_TANHL)
# define _GLIBCXX_HAVE_TANHL 1
# define tanhl _tanhl
#endif

/* 如果 _tanl 存在并且 _GLIBCXX_HAVE_TANL 未定义，定义 _GLIBCXX_HAVE_TANL 为 1，并且将 tanl 映射到 _tanl。 */
#if defined (_GLIBCXX_HAVE__TANL) && ! defined (_GLIBCXX_HAVE_TANL)
# define _GLIBCXX_HAVE_TANL 1
# define tanl _tanl
#endif

#endif // _GLIBCXX_CXX_CONFIG_H


