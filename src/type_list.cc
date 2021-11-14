// Type your code here, or load an example.
#include <cstddef>
#include <type_traits>
#include <tuple>
#include <typeinfo>
#include <iostream>
namespace mg
{
    template <bool B>
    using bool_constant = std::integral_constant<bool, B>;
    using true_t = bool_constant<true>;
    using false_t = bool_constant<false>;
    
    template <typename T>
    struct to_std_bool{};
    template <>
    struct to_std_bool<true_t>
    {
        constexpr static bool value = true;
    };
    template <>
    struct to_std_bool<false_t>
    {
        constexpr static bool value = false;
    };
    template< class T >
    constexpr bool to_std_bool_v = to_std_bool<T>::value;

    template <typename T, typename U>
    struct is_same
    {
        using type = false_t;
    };
    template <typename T>
    struct is_same<T,T>
    {
        using type = true_t;
    };
    template <typename T, typename U = void>
    using is_same_t = typename is_same<T,U>::type;
/**/
    template< typename... t>
    struct type_list
    {
    static constexpr size_t size = sizeof...(t);
    };
    template< typename... t>
  	constexpr bool length_v = type_list<t...>::size;
/*front is the same as first element*/
    template < typename head, typename... Rest>
    struct front {};

    template < typename head, typename... Rest>
    struct front <type_list<head, Rest...>>
    {
        using type = head;
    };
    template < typename head, typename... Rest>
    using front_t = typename front<head,Rest...>::type;
/*

TAIL are all elements except the first one

*/
    template < typename head, typename... Rest>
    struct tail {};

    template < typename head, typename... Rest>
    struct tail <type_list<head, Rest...>>
    {
        using type = type_list<Rest...>;
    };

    template < typename head, typename... Rest>
    using tail_t = typename tail<head,Rest...>::type;


/*
ELEMENT

*/
    template <typename list, size_t index>
    struct element_at 
    {
      using type = typename element_at<tail_t<list>,index-1>::type;
    };
    template <typename list>
    struct element_at<list, 0> : front<list>
    {};
    template < typename list, size_t index>
    using element_at_t = typename element_at<list,index>::type;

/*
last element
*/
    template <typename head, typename... Rest>
    struct last {};

    template <typename head, typename... Rest>
    struct last <type_list<head ,Rest...>>
    {
        using type =  typename element_at<type_list<head, Rest...>, type_list<head ,Rest...>::size-1>::type;

    };
    template < typename head, typename... Rest>
    using last_t = typename last<head,Rest...>::type;
    
}




constexpr void tests()
{

{
   static_assert(mg::to_std_bool_v<mg::is_same_t<mg::true_t, mg::true_t>>, "ok");
   static_assert(mg::to_std_bool_v<mg::is_same_t<mg::false_t, mg::false_t>>, "ok");
}
{
   static_assert(!mg::to_std_bool_v<mg::is_same_t<mg::true_t, mg::false_t>>, "ok");
   static_assert(!mg::to_std_bool_v<mg::is_same_t<mg::false_t, mg::true_t>>, "ok");
}
{
   using result = mg::type_list< mg::true_t, mg::true_t, mg::true_t>;
   static_assert(mg::to_std_bool_v<mg::is_same_t<result, result>>, "ok");
}
{
   using result = mg::type_list< mg::true_t>;
   static_assert(mg::to_std_bool_v<mg::is_same_t<result, result>>, "ok");
}
{
   using result = mg::front_t< mg::type_list<mg::true_t,mg::false_t> >;
   static_assert(mg::to_std_bool_v<mg::is_same_t<result, mg::true_t>>, "ok");
   static_assert(!mg::to_std_bool_v<mg::is_same_t<result, mg::false_t>>, "ok");
}
{
   using result = mg::front_t< mg::type_list<mg::true_t> >;
   static_assert(mg::to_std_bool_v<mg::is_same_t<result, mg::true_t>>, "ok");
   static_assert(!mg::to_std_bool_v<mg::is_same_t<result, mg::false_t>>, "ok");
}

{
   using result = mg::front_t< mg::type_list<mg::false_t,mg::true_t> >;
   static_assert(mg::to_std_bool_v<mg::is_same_t<result, mg::false_t>>, "ok");
}
{
     using tail_1 = mg::tail_t< mg::type_list<mg::false_t, mg::true_t, mg::false_t> >;
  using tail_2 = mg::tail_t< tail_1 >;
   static_assert(mg::to_std_bool_v<mg::is_same_t<tail_2, mg::type_list<mg::false_t> > >, "ok");
}
{
   using result = mg::front_t< mg::type_list<mg::false_t, mg::true_t, mg::false_t> >;
   static_assert(mg::to_std_bool_v<mg::is_same_t<result, mg::false_t>>, "ok");
}

{
   using result = mg::tail_t< mg::type_list<mg::false_t, mg::true_t, mg::false_t> >;
   static_assert(mg::to_std_bool_v<mg::is_same_t<result, mg::type_list<mg::true_t, mg::false_t> > >, "ok");
}

{
   using result = mg::tail_t< mg::type_list<mg::false_t, mg::false_t, mg::false_t> >;
   static_assert(mg::to_std_bool_v<mg::is_same_t<result, mg::type_list<mg::false_t, mg::false_t> > >, "ok");
}
{
    using list = mg::type_list<mg::false_t, mg::false_t, mg::false_t>;
   using result = mg::element_at_t<list,0>;
   static_assert(mg::to_std_bool_v<mg::is_same_t<result, mg::false_t > >, "ok");
}
{
    using list = mg::type_list<mg::true_t, mg::true_t, mg::false_t>;
    using result = mg::element_at_t<list,0>;
    static_assert(mg::to_std_bool_v<mg::is_same_t<result, mg::true_t > >, "ok");


}

  {
    using list = mg::type_list<mg::false_t, mg::true_t, mg::false_t>;
    using result = mg::element_at_t<list,1>;
    static_assert(mg::to_std_bool_v<mg::is_same_t<result, mg::true_t > >, "ok");
}
   {
    using list = mg::type_list<mg::false_t, mg::true_t, mg::false_t>;
    using result = mg::element_at_t<list,2>;
    static_assert(mg::to_std_bool_v<mg::is_same_t<result, mg::false_t > >, "ok");
} 

     {
    using list = mg::type_list<mg::false_t, mg::true_t, mg::false_t,mg::false_t,mg::false_t>;
       static_assert(list::size == 5, "ok");       
       
} 
  
{
    using list = mg::type_list<mg::false_t, mg::true_t, mg::false_t, mg::false_t, mg::true_t>;
    using result = mg::last_t<list>;
    static_assert(mg::to_std_bool_v<mg::is_same_t<result, mg::true_t > >, "ok");
} 
};

/*
Features to add.
remove_at,
replace_at


*/

int main()
{
    tests();


}