/*
    Copyright 1999-2009, Felspar Co Ltd. http://fost.3.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include "fost-schema.hpp"
#include <fost/detail/schema.hpp>
#include <fost/detail/db.hpp>

#include <fost/exception/null.hpp>
#include <fost/exception/no_attribute.hpp>


using namespace fostlib;


namespace {
    boost::shared_ptr< meta_attribute > make_attribute(
        const string &name, const string &type, bool key, bool not_null,
        const nullable< std::size_t > &size, const nullable< std::size_t > &precision
    ) {
        boost::shared_ptr< meta_attribute > attr(  field_base::fetch( type ).meta_maker(
            name, key, not_null, size, precision
        ) );
        return attr;
    }
    template< typename const_iterator >
    const_iterator find_attr( const_iterator p, const const_iterator end, const string &n ) {
        for( ; p != end; ++p )
            if ( (*p)->name() == n )
                return p;
        return end;
    }
}

fostlib::meta_instance::meta_instance( const string &n )
: enclosure( n ) {
}
fostlib::meta_instance::meta_instance( const enclosure &e, const string &n )
: enclosure( e, n ) {
}


meta_instance &fostlib::meta_instance::primary_key(
    const string &name, const string &type,
    const nullable< std::size_t > &size, const nullable< std::size_t > &precision
) {
    if ( find_attr( m_columns.begin(), m_columns.end(), name ) != m_columns.end() )
        throw exceptions::null( L"Cannot have two attributes with the same name" );
    m_columns.push_back( make_attribute( name, type, true, true, size, precision ) );
    return *this;
}
meta_instance &fostlib::meta_instance::field(
    const string &name, const string &type, bool not_null,
    const nullable< std::size_t > &size, const nullable< std::size_t > &precision
) {
    if ( find_attr( m_columns.begin(), m_columns.end(), name ) != m_columns.end() )
        throw exceptions::null( L"Cannot have two attributes with the same name" );
    m_columns.push_back( make_attribute( name, type, false, not_null, size, precision ) );
    return *this;
}


const meta_attribute &fostlib::meta_instance::operator[] ( const string &n ) const {
    columns_type::const_iterator p( find_attr( m_columns.begin(), m_columns.end(), n ) );
    if ( p != m_columns.end() )
        return **p;
    else
        throw exceptions::null( L"Could not find attribute definition", n );
}


boost::shared_ptr< instance > fostlib::meta_instance::create() const {
    return create( json() );
}
boost::shared_ptr< instance > fostlib::meta_instance::create( const json &j ) const {
    return boost::shared_ptr< instance >( new instance( *this, j ) );
}
