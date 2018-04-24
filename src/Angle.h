#ifndef ANGLE_H_
#define ANGLE_H_

#include <cmath>
#include <ostream>

template <typename T>
class Deg;

template <typename T>
class Rad {
public:
    static constexpr T PERIOD = 2.0 * M_PI;
    constexpr Rad() = default;
    ~Rad() = default;

    constexpr Rad(Deg<T> value) : value(value.to_radians().value) {}
    explicit constexpr Rad(T value) : value(value) {}
    template <typename U>
    explicit constexpr Rad(Deg<U> value) : value(static_cast<T>(value.value)) {}

    constexpr Rad<T>& operator+=(Rad<T> rhs) {
        *this = (*this + rhs);
        return *this;
    }
    constexpr Rad<T>& operator-=(Rad<T> rhs) {
        *this = (*this - rhs);
        return *this;
    }
    constexpr Rad<T>& operator*=(T rhs) {
        this->value *= rhs;
        return *this;
    }
    constexpr Rad<T>& operator/=(T rhs) {
        this->value /= rhs;
        return *this;
    }

    explicit constexpr operator Rad<T>() const { return to_degrees(); }

    constexpr Deg<T> to_degrees() const {
        return Deg<T>(value * (Deg<T>::PERIOD / Rad<T>::PERIOD));
    }

    static inline Rad<T> asin(T val) { return Rad<T>(std::asin(val)); }
    static inline Rad<T> acos(T val) { return Rad<T>(std::acos(val)); }
    static inline Rad<T> atan(T val) { return Rad<T>(std::atan(val)); }
    static inline Rad<T> atan2(T y, T x) { return Rad<T>(std::atan2(y, x)); }


    T value;
};

template <typename T>
class Deg {
public:
    static constexpr T PERIOD = 360.0;
    constexpr Deg() = default;
    ~Deg() = default;

    constexpr Deg(Rad<T> value) : value(value.to_degrees().value) {}
    explicit constexpr Deg(T value) : value(value) {}
    template <typename U>
    explicit constexpr Deg(Deg<U> value) : value(static_cast<T>(value.value)) {}

    constexpr Deg<T>& operator+=(Deg<T> rhs) {
        *this = (*this + rhs);
        return *this;
    }
    constexpr Deg<T>& operator-=(Deg<T> rhs) {
        *this = (*this - rhs);
        return *this;
    }
    constexpr Deg<T>& operator*=(T rhs) {
        this->value *= rhs;
        return *this;
    }
    constexpr Deg<T>& operator/=(T rhs) {
        this->value /= rhs;
        return *this;
    }

    explicit constexpr operator Rad<T>() const { return to_radians(); }

    constexpr Rad<T> to_radians() const {
        return Rad<T>(value * (Rad<T>::PERIOD / Deg<T>::PERIOD));
    }

    static inline Deg<T> asin(T val) { return Rad<T>::asin(val).to_degrees(); }
    static inline Deg<T> acos(T val) { return Rad<T>::acos(val).to_degrees(); }
    static inline Deg<T> atan(T val) { return Rad<T>::atan(val).to_degrees(); }
    static inline Deg<T> atan2(T y, T x) {
        return Rad<T>::atan2(y, x).to_degrees();
    }

    T value;
};

template <typename T>
inline constexpr bool operator==(Deg<T> lhs, Deg<T> rhs) {
    return lhs.value == rhs.value;
}
template <typename T>
inline constexpr bool operator!=(Deg<T> lhs, Deg<T> rhs) {
    return !(lhs == rhs);
}
template <typename T>
inline constexpr bool operator<(Deg<T> lhs, Deg<T> rhs) {
    return lhs.value < rhs.value;
}
template <typename T>
inline constexpr bool operator>(Deg<T> lhs, Deg<T> rhs) {
    return lhs.value > rhs.value;
}
template <typename T>
inline constexpr bool operator<=(Deg<T> lhs, Deg<T> rhs) {
    return lhs.value <= rhs.value;
}
template <typename T>
inline constexpr bool operator>=(Deg<T> lhs, Deg<T> rhs) {
    return lhs.value >= rhs.value;
}
template <typename T>
inline constexpr Deg<T> operator+(Deg<T> lhs, Deg<T> rhs) {
    return Deg<T>(lhs.value + rhs.value);
}
template <typename T>
inline constexpr Deg<T> operator-(Deg<T> lhs, Deg<T> rhs) {
    return Deg<T>(lhs.value - rhs.value);
}
template <typename T>
inline constexpr Deg<T> operator*(Deg<T> lhs, T rhs) {
    return Deg<T>(lhs.value * rhs);
}
template <typename T>
inline constexpr Deg<T> operator/(Deg<T> lhs, T rhs) {
    return Deg<T>(lhs.value / rhs);
}
template <typename T>
inline constexpr T operator/(Deg<T> lhs, Deg<T> rhs) {
    return lhs.value / rhs.value;
}
template <typename T>
inline constexpr Deg<T> operator-(Deg<T> val) {
    return Deg<T>(-val.value);
}

template <typename T>
inline constexpr bool operator==(Rad<T> lhs, Rad<T> rhs) {
    return lhs.value == rhs.value;
}
template <typename T>
inline constexpr bool operator!=(Rad<T> lhs, Rad<T> rhs) {
    return !(lhs == rhs);
}
template <typename T>
inline constexpr bool operator<(Rad<T> lhs, Rad<T> rhs) {
    return lhs.value < rhs.value;
}
template <typename T>
inline constexpr bool operator>(Rad<T> lhs, Rad<T> rhs) {
    return lhs.value > rhs.value;
}
template <typename T>
inline constexpr bool operator<=(Rad<T> lhs, Rad<T> rhs) {
    return lhs.value <= rhs.value;
}
template <typename T>
inline constexpr bool operator>=(Rad<T> lhs, Rad<T> rhs) {
    return lhs.value >= rhs.value;
}
template <typename T>
inline constexpr Rad<T> operator+(Rad<T> lhs, Rad<T> rhs) {
    return Rad<T>(lhs.value + rhs.value);
}
template <typename T>
inline constexpr Rad<T> operator-(Rad<T> lhs, Rad<T> rhs) {
    return Rad<T>(lhs.value - rhs.value);
}
template <typename T>
inline constexpr Rad<T> operator*(Rad<T> lhs, T rhs) {
    return Rad<T>(lhs.value * rhs);
}
template <typename T>
inline constexpr Rad<T> operator/(Rad<T> lhs, T rhs) {
    return Rad<T>(lhs.value / rhs);
}
template <typename T>
inline constexpr T operator/(Rad<T> lhs, Rad<T> rhs) {
    return lhs.value / rhs.value;
}
template <typename T>
inline constexpr Rad<T> operator-(Rad<T> val) {
    return Rad<T>(-val.value);
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, Deg<T> deg) {
    stream << deg.value << "º";
    return stream;
}
template <typename T>
std::ostream& operator<<(std::ostream& stream, Rad<T> deg) {
    stream << deg.value << " r";
    return stream;
}

template <template <typename> typename Angle, typename T>
inline T sin(Angle<T> angle) {
    return std::sin(static_cast<Rad<T>>(angle).value);
}
template <template <typename> typename Angle, typename T>
inline T cos(Angle<T> angle) {
    return std::cos(static_cast<Rad<T>>(angle).value);
}
template <template <typename> typename Angle, typename T>
inline T tan(Angle<T> angle) {
    return std::tan(static_cast<Rad<T>>(angle).value);
}

#endif
