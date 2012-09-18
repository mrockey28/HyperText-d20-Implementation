#ifndef TYPES_H
#define TYEPS_H

#include <string>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>

typedef unsigned short 	uint8;
typedef unsigned int 	uint16;
typedef unsigned long 	uint32;
typedef short 			int8;
typedef int 			int16;
typedef long 			int32;

typedef std::string		string;

#define TRUE	1
#define FALSE	0

#define DEFINE_SIMPLE_ENUM(EnumName, seq) \
struct EnumName {\
   enum type \
   { \
      BOOST_PP_SEQ_FOR_EACH_I(DEFINE_SIMPLE_ENUM_VAL, EnumName, seq)\
   }; \
   type v; \
   EnumName(type v) : v(v) {} \
   operator type() const {return v;} \
private: \
    template<typename T> \
    operator T () const;};\

#define DEFINE_SIMPLE_ENUM_VAL(r, data, i, record) \
    BOOST_PP_TUPLE_ELEM(2, 0, record) = BOOST_PP_TUPLE_ELEM(2, 1, record),


#endif
