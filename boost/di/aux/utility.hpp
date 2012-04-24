//
// Copyright (c) 2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_AUX_UTILITY_HPP
#define BOOST_DI_AUX_UTILITY_HPP

#include <boost/shared_ptr.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include "boost/di/config.hpp"

namespace boost {
namespace di {
namespace aux {

template<typename TDependency, int N, typename TResult = void>
struct enable_if_ctor_size
    : enable_if_c<mpl::size<typename TDependency::ctor>::value == N, TResult>
{ };

template<typename TDependency, int N>
struct at_ctor
    : mpl::at_c<typename TDependency::ctor, N>
{ };

template<typename TCallStack, typename TDependency>
struct update_call_stack
    : mpl::push_back<TCallStack, typename TDependency::given>
{ };

template<typename TElement>
class make_plain
{
    BOOST_MPL_HAS_XXX_TRAIT_DEF(element_type)

    template<typename T>
    struct remove_accessors
        : remove_cv<
            typename remove_pointer<
                typename remove_reference<T>::type
            >::type
          >
    { };

    template<typename T, typename Enable = void>
    struct deref_element_type
    {
        typedef T type;
    };

    template<typename T>
    struct deref_element_type<T, typename enable_if<has_element_type<T> >::type>
    {
        typedef typename T::element_type type;
    };

public:
    typedef typename deref_element_type<
        typename remove_accessors<
            typename deref_element_type<
                typename remove_accessors<TElement>::type
            >::type
        >::type
    >::type type;
};

} // namespace aux
} // namespace di
} // namespace boost

#endif

