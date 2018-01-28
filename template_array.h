#include <utility>

namespace template_array {

template <int... Elems> struct Array {
  template <int Elem> using prepend = Array<Elem, Elems...>;
  template <int Elem> using append = Array<Elems..., Elem>;
};

template <int Elem, int Length> struct MakeArrayImpl {
  using type =
      typename MakeArrayImpl<Elem, Length - 1>::type::template prepend<Elem>;
};

template <int Elem> struct MakeArrayImpl<Elem, 0> { using type = Array<>; };
template <int Elem, int Length>
using MakeArray = typename MakeArrayImpl<Elem, Length>::type;

template <int K, int Elem, typename A> struct SetElemImpl;

template <int K, int Elem, int V, int... Vs>
struct SetElemImpl<K, Elem, Array<V, Vs...>> {
  using type = typename std::conditional<
      K == 0, typename SetElemImpl<K - 1, Elem,
                                   Array<Vs...>>::type::template prepend<Elem>,
      typename SetElemImpl<K - 1, Elem,
                           Array<Vs...>>::type::template prepend<V>>::type;
};

template <int K, int Elem> struct SetElemImpl<K, Elem, Array<>> {
  using type = Array<>;
};

template <int K, int Elem, typename A>
using SetElem = typename SetElemImpl<K, Elem, A>::type;

template <int Elem> struct ElemWrapper { constexpr static int elem{Elem}; };

template <int K, typename A> struct GetElemImpl;

template <int Elem, int... Elems> struct GetElemImpl<0, Array<Elem, Elems...>> {
  using type = ElemWrapper<Elem>;
};

template <int K, int Elem, int... Elems>
struct GetElemImpl<K, Array<Elem, Elems...>> {
  using type = typename GetElemImpl<K - 1, Array<Elems...>>::type;
};

template <int K, typename A> constexpr int GetElem() {
  return GetElemImpl<K, A>::type::elem;
}

template <typename A> struct SizeImpl;

template <int... Elems> struct SizeImpl<Array<Elems...>> {
  using type = ElemWrapper<sizeof...(Elems)>;
};

template <typename A> constexpr int Size() { return SizeImpl<A>::type::elem; }

template <int Elem, typename A>
using Append = typename A::template append<Elem>;

template <int Elem, typename A>
using Prepend = typename A::template prepend<Elem>;

}
