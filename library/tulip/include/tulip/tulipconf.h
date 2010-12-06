/**
 *
 * This file is part of Tulip (www.tulip-software.org)
 *
 * Authors: David Auber and the Tulip development Team
 * from LaBRI, University of Bordeaux 1 and Inria Bordeaux - Sud Ouest
 *
 * Tulip is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Tulip is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 */
#ifndef TULIPCONF_H
#define TULIPCONF_H

#define STRINGIFY(PARAM) STRINGIFY_INTERNAL(PARAM)
#define STRINGIFY_INTERNAL(PARAM) #PARAM

#if _MSC_VER
#  define _DEPRECATED __declspec(deprecated)
#  define __PRETTY_FUNCTION__ __FUNCTION__ //workaround
#  define strcasecmp stricmp  //strcasecmp does not exists for VC, workaround
#  define cbrt(arg) pow((double)arg, 1.0/3) //VC does not have cbrt, little workaround
#  define isnan(x) ((x) != (x)) //you guessed it, this is a C99 feature, and VC++ does not support C99. workaroud this.
#  define rint(arg) arg > 0 ? (int)std::floor((double)arg) : (int)std::ceil((double)arg)
#elif (__GNUC__ < 3)
#  define stdext std
#  define _DEPRECATED
#  include <stl_hash_fun.h>
#elif __clang__
#  define _DEPRECATED __attribute__ ((deprecated))
#  define stdext __gnu_cxx
#else
#    define _DEPRECATED __attribute__ ((deprecated))
#    define stdext __gnu_cxx
#  if  (__GNUC_MINOR__ < 4 && __GNUC__ < 4)
#    include <ext/stl_hash_fun.h>
#  elif (__GNUC_MINOR__ < 3)
#    include <ext/hash_fun.h>
#  endif
#endif

#ifdef _WIN32
# 	ifdef DLL_TULIP
#		define TLP_SCOPE         __declspec(dllexport)
# 	else
#		define TLP_SCOPE       __declspec(dllimport)
# 	endif
#endif
#ifndef TLP_SCOPE
#define TLP_SCOPE 
#endif

#ifdef _WIN32
# 	ifdef DLL_TULIP_GL
#		define TLP_GL_SCOPE         __declspec(dllexport)
# 	else
#		define TLP_GL_SCOPE       __declspec(dllimport)
# 	endif
#endif
#ifndef TLP_GL_SCOPE
#define TLP_GL_SCOPE           
#endif

#ifdef _WIN32
# 	ifdef DLL_TULIP_QT2
#		define TLP_QT_SCOPE       __declspec(dllimport)
#	else
# 		ifdef DLL_TULIP_QT
#			define TLP_QT_SCOPE         __declspec(dllexport)
# 		else
#			define TLP_QT_SCOPE       __declspec(dllimport)
# 		endif
#	endif
#endif
#ifndef TLP_QT_SCOPE
#define TLP_QT_SCOPE           
#endif

#ifdef _WIN32
#   ifdef DLL_TULIP_QT2
#		define TLP_QT_SIMPLE_SCOPE 
#	else 
# 		ifdef DLL_TULIP_QT
#			define TLP_QT_SIMPLE_SCOPE  __declspec(dllexport)
# 		else
#			define TLP_QT_SIMPLE_SCOPE       
# 		endif
#	endif
#endif
#ifndef TLP_QT_SIMPLE_SCOPE
#define TLP_QT_SIMPLE_SCOPE           
#endif

#ifdef _WIN32
# 	ifdef DLL_TULIP_PLUGINSMANAGER
#		define TLP_PLUGINSMANAGER_SCOPE         __declspec(dllexport)
# 	else
#		define TLP_PLUGINSMANAGER_SCOPE       __declspec(dllimport)
# 	endif
#endif
#ifndef TLP_PLUGINSMANAGER_SCOPE
#define TLP_PLUGINSMANAGER_SCOPE           
#endif

#endif //TULIPCONF_H
