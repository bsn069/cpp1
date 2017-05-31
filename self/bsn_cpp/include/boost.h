#pragma once

#define BOOST_RATIO_EXTENSIONS
#define	BOOST_CHRONO_EXTENSIONS
#define BOOST_ASIO_DISABLE_STD_CHRONO

#include <boost/chrono.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/version.hpp>
#include <boost/config.hpp>
#include <boost/function.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/variant.hpp>
#include <boost/array.hpp>
//#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
//#include <boost/thread/mutex.hpp>
//#include <boost/thread/locks.hpp>
#include <boost/filesystem.hpp>
//#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>
//
#include <boost/math/constants/constants.hpp>
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/minmax.hpp>
#include <boost/algorithm/minmax_element.hpp>
//clamps the first argument between the second two
#include <boost/algorithm/clamp.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/algorithm/string.hpp>
// big value
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/ratio.hpp>
#include <boost/random.hpp>
#include <boost/crc.hpp>
#include <boost/assign.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/lock_factories.hpp>

using boost::shared_ptr;
using namespace boost::multiprecision;
using namespace boost::math;
using boost::integer_traits;
using boost::scoped_thread;
using boost::call_once;
using boost::once_flag;
using boost::thread_group;
using boost::make_unique_lock;
using boost::condition_variable_any;
using boost::circular_buffer;
using boost::tuple;
using boost::array;
using boost::variant;
using boost::char_separator;
using boost::tokenizer;
using boost::lock_guard;
using boost::mutex;
using boost::bind;
using boost::function;
using boost::thread;
using namespace boost::filesystem;
using boost::str;
using boost::wformat;
using boost::format;
using boost::lexical_cast;
using namespace boost::assign;
using namespace boost::this_thread;
using namespace boost::chrono;
using namespace boost::random;


