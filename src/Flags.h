#ifndef FLAGS_H_0099701e_0717_43a3_af27_83c111ea5574
#define FLAGS_H_0099701e_0717_43a3_af27_83c111ea5574

#include <cassert>
#include <cmath>
#include <initializer_list>
#include <limits>
#include <ostream>
#include <type_traits>

namespace flags {

template <typename T>
class Flags {
public:
    using Enum = T;
    using StorageType = typename std::underlying_type<T>::type;

    constexpr Flags() = default;
    constexpr Flags(T flag);
    constexpr Flags(std::initializer_list<T> flags);
    ~Flags() = default;

    constexpr Flags(const Flags& other) = default;
    constexpr Flags(Flags&& other) noexcept = default;
    constexpr Flags& operator=(const Flags& other) = default;
    constexpr Flags& operator=(Flags&& other) noexcept = default;

    constexpr bool operator==(const Flags<T>& flags) const;
    constexpr bool operator!=(const Flags<T>& flags) const;
    constexpr bool operator==(T flags) const;
    constexpr bool operator!=(T flags) const;

    constexpr Flags<T> operator|(const Flags<T>& rhs) const;
    constexpr Flags<T> operator&(const Flags<T>& rhs) const;
    constexpr Flags<T> operator^(const Flags<T>& rhs) const;
    constexpr Flags<T> operator~() const;

    constexpr Flags<T>& operator|=(const Flags<T>& rhs);
    constexpr Flags<T>& operator&=(const Flags<T>& rhs);
    constexpr Flags<T>& operator^=(const Flags<T>& rhs);

    constexpr void set_flag(T flag);
    constexpr bool has_flag(T flag) const;
    constexpr void clear_flag(T flag);
    constexpr void toggle_flag(T flag);

    constexpr void set_flags(const Flags<T>& flags);
    constexpr bool has_flags(const Flags<T>& flags) const;
    constexpr void clear_flags(const Flags<T>& flags);
    constexpr void toggle_flags(const Flags<T>& flags);

    constexpr StorageType get_value() const;

    void print_flag_names(
            std::ostream& stream, int max_bits = -1, bool verbose = false);
    void print_flag_bits(std::ostream& stream, int max_bits = -1);

    static constexpr Flags<T> from_value(StorageType value);
    static constexpr Flags<T> none();

private:
    StorageType m_value = 0x0;
};

template <typename T>
class FlagsIterator {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer_type = T*;
    using reference_type = T&;
    using iterator_category = std::forward_iterator_tag;

    FlagsIterator();
    FlagsIterator(int start_idx, Flags<T>* flags);

private:
    int m_bit_idx = -1;
    Flags<T>* m_flags = nullptr;
};

template <typename T>
inline constexpr Flags<T>::Flags(T flag)
    : m_value(static_cast<StorageType>(flag)) {}

template <typename T>
inline constexpr Flags<T>::Flags(std::initializer_list<T> flags) {
    for(auto& f : flags) {
        set_flag(f);
    }
}

template <typename T>
inline constexpr bool Flags<T>::operator==(const Flags<T>& flags) const {
    return m_value == flags.m_value;
}

template <typename T>
inline constexpr bool Flags<T>::operator!=(const Flags<T>& flags) const {
    return !(*this == flags);
}

template <typename T>
inline constexpr bool Flags<T>::operator==(T flags) const {
    return m_value == static_cast<StorageType>(flags);
}

template <typename T>
inline constexpr bool Flags<T>::operator!=(T flags) const {
    return !(*this == flags);
}

template <typename T>
inline constexpr Flags<T> Flags<T>::operator|(const Flags<T>& rhs) const {
    return Flags::from_value(m_value | rhs.m_value);
}

template <typename T>
inline constexpr Flags<T> Flags<T>::operator&(const Flags<T>& rhs) const {
    return Flags::from_value(m_value & rhs.m_value);
}

template <typename T>
inline constexpr Flags<T> Flags<T>::operator^(const Flags<T>& rhs) const {
    return Flags::from_value(m_value ^ rhs.m_value);
}

template <typename T>
inline constexpr Flags<T> Flags<T>::operator~() const {
    return Flags::from_value(~m_value);
}

template <typename T>
inline constexpr Flags<T>& Flags<T>::operator|=(const Flags<T>& rhs) {
    m_value |= rhs.m_value;
    return *this;
}

template <typename T>
inline constexpr Flags<T>& Flags<T>::operator&=(const Flags<T>& rhs) {
    m_value &= rhs.m_value;
    return *this;
}

template <typename T>
inline constexpr Flags<T>& Flags<T>::operator^=(const Flags<T>& rhs) {
    m_value ^= rhs.m_value;
    return *this;
}

template <typename T>
inline constexpr void Flags<T>::set_flag(T flag) {
    m_value |= static_cast<StorageType>(flag);
}

template <typename T>
inline constexpr bool Flags<T>::has_flag(T flag) const {
    return (m_value & static_cast<StorageType>(flag)) != 0;
}

template <typename T>
inline constexpr void Flags<T>::clear_flag(T flag) {
    m_value &= ~static_cast<StorageType>(flag);
}

template <typename T>
inline constexpr void Flags<T>::toggle_flag(T flag) {
    m_value ^= static_cast<StorageType>(flag);
}

template <typename T>
inline constexpr typename Flags<T>::StorageType Flags<T>::get_value() const {
    return m_value;
}

template <typename T>
inline constexpr Flags<T> Flags<T>::from_value(Flags::StorageType value) {
    auto val = Flags<T>();
    val.m_value = value;
    return val;
}

template <typename T>
inline constexpr void Flags<T>::set_flags(const Flags<T>& flags) {
    m_value |= flags.m_value;
}

template <typename T>
inline constexpr bool Flags<T>::has_flags(const Flags<T>& flags) const {
    return (m_value & flags.m_value) == flags.m_value;
}

template <typename T>
inline constexpr void Flags<T>::clear_flags(const Flags<T>& flags) {
    m_value &= ~flags.m_value;
}

template <typename T>
inline constexpr void Flags<T>::toggle_flags(const Flags<T>& flags) {
    m_value ^= flags.m_value;
}

template <typename T>
inline void Flags<T>::print_flag_names(
        std::ostream& stream, int max_bits, bool verbose) {
    bool first = true;
    if(max_bits == -1) {
        max_bits = static_cast<int>(
                std::log(std::numeric_limits<StorageType>::max()));
    }
    assert(max_bits > 0);

    for(int i = 0; i < max_bits; ++i) {
        StorageType val = (StorageType(1) << i);
        if(!verbose) {
            if((m_value & val) != 0) {
                if(!first) {
                    stream << ",";
                }
                stream << static_cast<T>(val);
                first = false;
            }
        } else {
            if(!first) {
                stream << ",";
            }
            if((m_value & val) != 0) {
                stream << "+" << static_cast<T>(val);
            } else {
                stream << "-" << static_cast<T>(val);
            }
            first = false;
        }
    }
}

template <typename T>
inline void Flags<T>::print_flag_bits(std::ostream& stream, int max_bits) {
    if(max_bits == -1) {
        max_bits = static_cast<int>(
                std::log(std::numeric_limits<StorageType>::max()));
    }
    for(int i = max_bits - 1; i >= 0; --i) {
        int mask = StorageType(1) << i;
        if((mask & m_value) != 0) {
            stream << "1";
        } else {
            stream << "0";
        }
    }
}

template <typename T>
inline constexpr Flags<T> Flags<T>::none() {
    return Flags<T>();
}

} // namespace flags

#endif
