#pragma once
#undef BOOST_PP_ARRAY_ENUM
#undef BOOST_PREPROCESSOR_ARRAY_ENUM_HPP
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/array/enum.hpp>

#define GEN_NAME(x,y) x ## y
#define TYPEARRAY (12, (void * a,void * b, void * c, void * d, void * e,void * f,void * g,void * h, void *i, void * j,void *k, void * l))
#define NAMEARRAY (12, (a,b,c,d,e,f,g,h,i,j,k,l))
#define GET_ELEMENT_NAME(z, n, data) BOOST_PP_ARRAY_ELEM(n, NAMEARRAY)
#define GET_ELEMENT_TYPE(z, n, data) BOOST_PP_ARRAY_ELEM(n, TYPEARRAY)
#define CREATE_HEADER(NAME, ARGCOUNT, RET) RET NAME(BOOST_PP_ENUM(ARGCOUNT, GET_ELEMENT_TYPE, ""))
#define CREATE_WRAPPERCALL(NAME, ARGCOUNT, RET) CREATE_HEADER(NAME, ARGCOUNT, RET){RET v; return v;};
#define CALL_UNDERLYING(NAME, ...) GEN_NAME(NAME, _CALL)(__VA_ARGS__)
#define CALL_UNDERLYING_ARGS(NAME, ARGCOUNT) CALL_UNDERLYING(NAME, BOOST_PP_ENUM(ARGCOUNT, GET_ELEMENT_NAME, ""));

#define UNSUPPORTED_CALL(NAME, ARGCOUNT, RET) \
	CREATE_WRAPPERCALL(GEN_NAME(NAME, _CALL), ARGCOUNT, RET) \
	CREATE_HEADER(NAME, ARGCOUNT, RET) { \
		RET ret_value; \
		ret_value = CALL_UNDERLYING(NAME, BOOST_PP_ENUM(ARGCOUNT, GET_ELEMENT_NAME, ""));


#define TIMER_MACRO(NAME, ELEMENTS, STREAM, RET) \
		BUILD_TIMER_CLASS \
		TIMER_PTR->StartTimer(STREAM); \
		RET ret_value = CALL_UNDERLYING(NAME, BOOST_PP_ENUM(ELEMENTS, GET_ELEMENT_NAME, "")); \
		TIMER_PTR->EndTimer(STREAM);

#define WRAP_SUPPORTED_CALL_TIME(NAME, ARGCOUNT, RET)\
	CREATE_WRAPPERCALL(GEN_NAME(NAME,_CALL), ARGCOUNT, RET) \
	CREATE_HEADER(NAME, ARGCOUNT, RET) {\
		BUILD_STORAGE_CLASS 	
