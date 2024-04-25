/*Authors:
    Jakub Dawidowicz
    Szymon Potrzebowski
    Weronika Piecuch
*/

#ifndef MONEYBAG_H
#define MONEYBAG_H

#include <iostream>
#include <string>

#define LIVRE_IN_DENIERS 240
#define SOLIDUS_IN_DENIERS 12

class Moneybag {
   public:
    using coin_number_t = uint64_t;

   private:
    coin_number_t livres;
    coin_number_t soliduses;
    coin_number_t deniers;

   public:
    constexpr Moneybag(const coin_number_t l, const coin_number_t s,
                       const coin_number_t d)
        : livres(l), soliduses(s), deniers(d) {}

    constexpr Moneybag(const Moneybag& moneybag)
        : livres(moneybag.livre_number()),
          soliduses(moneybag.solidus_number()),
          deniers(moneybag.denier_number()) {}

    constexpr coin_number_t livre_number() const { return livres; }

    constexpr coin_number_t solidus_number() const { return soliduses; }

    constexpr coin_number_t denier_number() const { return deniers; }

    constexpr Moneybag& operator=(const Moneybag& other) {
        if (this == &other) return *this;
        livres = other.livre_number();
        soliduses = other.solidus_number();
        deniers = other.denier_number();
        return *this;
    }

    constexpr std::partial_ordering operator<=>(const Moneybag& other) const {
        if (*this == other) return std::partial_ordering::equivalent;
        if (livres <= other.livre_number() &&
            soliduses <= other.solidus_number() &&
            deniers <= other.denier_number())
            return std::partial_ordering::less;
        if (livres >= other.livre_number() &&
            soliduses >= other.solidus_number() &&
            deniers >= other.denier_number())
            return std::partial_ordering::greater;
        return std::partial_ordering::unordered;
    }

    explicit constexpr operator bool() const {
        return (livres or soliduses or deniers);
    }

    constexpr bool operator==(const Moneybag& other) const {
        return livres == other.livre_number() &&
               soliduses == other.solidus_number() &&
               deniers == other.denier_number();
    }

    constexpr const Moneybag operator+(const Moneybag& other) const {
        if (UINT64_MAX - livres < other.livre_number() ||
            UINT64_MAX - soliduses < other.solidus_number() ||
            UINT64_MAX - deniers < other.denier_number()) {
            throw std::out_of_range("Out of range exception in addition");
            return Moneybag(*this);
        } else {
            return Moneybag(livres + other.livre_number(),
                            soliduses + other.solidus_number(),
                            deniers + other.denier_number());
        }
    }

    constexpr Moneybag& operator+=(const Moneybag& other) {
        *this = *this + other;
        return *this;
    }

    constexpr const Moneybag operator-(const Moneybag& other) const {
        if (livres < other.livre_number() ||
            soliduses < other.solidus_number() ||
            deniers < other.denier_number()) {
            throw std::out_of_range("Out of range exception in substraction");
            return Moneybag(*this);
        } else {
            return Moneybag(livres - other.livre_number(),
                            soliduses - other.solidus_number(),
                            deniers - other.denier_number());
        }
    }

    constexpr Moneybag& operator-=(const Moneybag& other) {
        *this = *this - other;
        return *this;
    }

    constexpr const Moneybag operator*(coin_number_t other) const {
        if (UINT64_MAX / other < livres || UINT64_MAX / other < soliduses ||
            UINT64_MAX / other < deniers) {
            throw std::out_of_range("Out of range exception in multiplication");
            return Moneybag(*this);
        } else {
            return Moneybag(livres * other, soliduses * other, deniers * other);
        }
    }

    constexpr const Moneybag& operator*=(coin_number_t other) {
        *this = *this * other;
        return *this;
    }
};

constexpr const Moneybag operator*(Moneybag::coin_number_t lhs,
                                   const Moneybag& rhs) {
    return (rhs * lhs);
}

inline std::ostream& operator<<(std::ostream& os, const Moneybag& obj) {
    os << "(" << obj.livre_number();
    if (obj.livre_number() == 1)
        os << " livr, ";
    else
        os << " livres, ";
    os << obj.solidus_number();
    if (obj.solidus_number() == 1)
        os << " solidus, ";
    else
        os << " soliduses, ";
    os << obj.denier_number();
    if (obj.denier_number() == 1)
        os << " denier)";
    else
        os << " deniers)";
    return os;
}

const constinit Moneybag Livre(1, 0, 0);
const constinit Moneybag Solidus(0, 1, 0);
const constinit Moneybag Denier(0, 0, 1);

class Value {
   private:
    using value_number_t = __uint128_t;
    value_number_t val;

   public:
    constexpr Value() : val(0) {}

    constexpr Value(const Moneybag::coin_number_t v) : val(v) {}

    constexpr Value(const Moneybag& moneybag)
        : val((__uint128_t)moneybag.livre_number() * LIVRE_IN_DENIERS +
              (__uint128_t)moneybag.solidus_number() * SOLIDUS_IN_DENIERS +
              (__uint128_t)moneybag.denier_number()) {}

    constexpr Value(const Value& other) = default;

    constexpr Value& operator=(const Value& other) {
        if (this == &other) return *this;

        val = other.val;
        return *this;
    }

    constexpr std::strong_ordering operator<=>(const Value& other) const {
        return val <=> other.val;
    }

    constexpr bool operator==(const Value& other) const {
        return val == other.val;
    }

    constexpr std::strong_ordering operator<=>(
        const value_number_t& other) const {
        return val <=> other;
    }

    constexpr bool operator==(const value_number_t& other) const {
        return val == other;
    }

    explicit inline operator std::string() const {
        Value::value_number_t value_acc = val;
        std::string result = "";
        do {
            result += (char)'0' + (value_acc % 10);
            value_acc /= 10;
        } while (value_acc > 0);
        return std::string(result.rbegin(), result.rend());
    }
};

#endif
