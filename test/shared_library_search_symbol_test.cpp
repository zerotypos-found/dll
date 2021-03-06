// Copyright 2011-2012 Renato Tegon Forti
// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#include <boost/dll.hpp>
#include <boost/test/minimal.hpp>

// Unit Tests

extern "C" void BOOST_SYMBOL_EXPORT exef() {
}

int test_main(int argc, char* argv[])
{
    using namespace boost::dll;

    BOOST_CHECK(argc >= 2);
    boost::filesystem::path shared_library_path = argv[1];
    BOOST_CHECK(shared_library_path.string().find("test_library") != std::string::npos);
    std::cout << "Library: " << shared_library_path;

    {
        shared_library sl(shared_library_path);
        BOOST_CHECK(sl.has("say_hello"));
        BOOST_CHECK(sl.has("lib_version"));
        BOOST_CHECK(sl.has("integer_g"));
        BOOST_CHECK(sl.has(std::string("integer_g")));
        BOOST_CHECK(!sl.has("i_do_not_exist"));
        BOOST_CHECK(!sl.has(std::string("i_do_not_exist")));
    }
   
    {
        shared_library sl(program_location());
        BOOST_CHECK(sl.has("exef"));
        BOOST_CHECK(!sl.has("i_do_not_exist"));
    }


    exef(); // Make sure that this function still callable in traditional way
    return 0;
}

