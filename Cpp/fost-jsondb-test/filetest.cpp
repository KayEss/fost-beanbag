/*
    Copyright 2005-2009, Felspar Co Ltd. http://fost.3.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include "fost-jsondb-test.hpp"
#include <fost/string>
#include <fost/main>
#include <fost/test>
#include <fost/jsondb>


using namespace fostlib;


FSL_MAIN(
    L"fost-jsondb-test-file",
    L"fost-jsondb-test-file\nTest the file handling for Fost 4 JSON blobs\nCopyright (c) 2008, Felspar Co. Ltd."
)( fostlib::ostream &out, fostlib::arguments &args ) {
    string dbname( guid() );

    return 0;
}
