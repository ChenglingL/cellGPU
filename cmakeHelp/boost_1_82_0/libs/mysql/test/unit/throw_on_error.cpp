//
// Copyright (c) 2019-2023 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/mysql/client_errc.hpp>
#include <boost/mysql/diagnostics.hpp>
#include <boost/mysql/error_code.hpp>
#include <boost/mysql/error_with_diagnostics.hpp>
#include <boost/mysql/throw_on_error.hpp>

#include <boost/system/system_error.hpp>
#include <boost/test/unit_test.hpp>

#include "create_diagnostics.hpp"

using boost::mysql::error_code;
using boost::mysql::error_with_diagnostics;
using boost::mysql::throw_on_error;
using boost::mysql::test::create_diagnostics;

namespace {

BOOST_AUTO_TEST_SUITE(test_throw_on_error)

BOOST_AUTO_TEST_CASE(success)
{
    error_code ec;
    auto diag = create_diagnostics("abc");
    BOOST_CHECK_NO_THROW(throw_on_error(ec, diag));
}

BOOST_AUTO_TEST_CASE(failure)
{
    error_code ec(boost::mysql::client_errc::incomplete_message);
    auto diag = create_diagnostics("abc");
    BOOST_CHECK_EXCEPTION(
        throw_on_error(ec, diag),
        error_with_diagnostics,
        [&](const error_with_diagnostics& err) { return err.code() == ec && err.get_diagnostics() == diag; }
    );
}

BOOST_AUTO_TEST_SUITE_END()

}  // namespace