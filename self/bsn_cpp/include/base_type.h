#pragma once

/*
T_void;
T_bool;	b
T_char;	c pc
T_wchar;	wc pwc
T_int8;	i8
T_int16;	i16
T_int32;	i32
T_int64;	i64
T_uint8;	u8
T_uint16;	u16
T_uint32;	u32
T_uint64;	u64
T_byte;	by

T_nullptr
D_const
D_inline
*/


namespace N_Bsn
{




#define T_nullptr nullptr
typedef void				T_void;
typedef bool				T_bool;
typedef char				T_char;
typedef wchar_t				T_wchar;
typedef boost::int8_t		T_int8;
typedef boost::int16_t		T_int16;
typedef boost::int32_t		T_int32;
typedef boost::int64_t		T_int64;
typedef boost::uint8_t		T_uint8;
typedef boost::uint16_t		T_uint16;
typedef boost::uint32_t		T_uint32;
typedef boost::uint64_t		T_uint64;
typedef T_uint8				T_byte;














} // end namespace N_Bsn


