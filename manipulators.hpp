#ifndef MANIPULATORS_HPP
#define MANIPULATORS_HPP

#include <type_traits>
#include <limits>
#include <cassert>
#include <typeinfo>

namespace bit {

template < class T, class U >
T narrow_cast(U v){
    auto r = static_cast<T>(v);
    if ( static_cast<U>(r) != v ){
        throw std::bad_cast{};
    }
    return r;
}

template < class B, class N, class = std::enable_if_t<std::is_unsigned<N>::value>>
constexpr B set(B b, N no){
    return b | static_cast<B>(1u << no);
}

template < class B, class N, class ... Args, class = std::enable_if_t<std::is_unsigned<N>::value>>
constexpr B set(B b, N no, Args ... nos){
    return set(b, nos...) | static_cast<B>(1u << no);
}

template < class B, class N, class = std::enable_if_t<std::is_unsigned<N>::value>>
constexpr B unset(B b, N no){
    return b & static_cast<B>(~(1u << no));
}

template < class B, class N, class ... Args, class = std::enable_if_t<std::is_unsigned<N>::value>>
constexpr B unset(B b, N no, Args ... nos){
    return unset(b, nos...) & static_cast<B>(~(1u << no));
}


template < class B, class N, class = std::enable_if_t<std::is_unsigned<N>::value>>
constexpr B toggle(B b, N no){
    return b ^ static_cast<B>(1u << no);
}

template < class B, class N, class ... Args, class = std::enable_if_t<std::is_unsigned<N>::value>>
constexpr B toggle(B b, N no, Args ... nos){
    return toggle(b, nos...) ^ static_cast<B>(1u << no);
}


template < class B >
class BitField{
public:
    BitField(B b) : bitField(b){}

    template < class N, class = std::enable_if_t<std::is_unsigned<N>::value>>
    BitField& set(N no){
        bitField = bit::set(bitField, no);
        return *this;
    }

    template < class N, class = std::enable_if_t<std::is_unsigned<N>::value>>
    BitField& unset(N no){
        bitField = bit::unset(bitField, no);
        return *this;
    }

    template < class N, class = std::enable_if_t<std::is_unsigned<N>::value>>
    BitField& toggle(N no){
        bitField = bit::toggle(bitField, no);
        return *this;
    }

    operator B() const { return bitField; }

private:
    B bitField;
};

template < class B >
BitField<B> makeBitField(B b){
    return BitField<B>(b);
}


} //namespace bit

#endif // MANIPULATORS_HPP
