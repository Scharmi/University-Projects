#ifndef MONEYBAG_H
#define MONEYBAG_H

#include <cassert>
#include <iostream>
 
class Moneybag {
    public:
        using coin_number_t = uint64_t;

    private:
        uint64_t livre, solidus, denires;
 
    public:
        constexpr Moneybag (const uint64_t livre, const uint64_t solidus, 
                            const uint64_t denires) :
            livre(livre), solidus(solidus), denires(denires) {}

        constexpr uint64_t solidus_number() const {
            return solidus;
        } 
        constexpr uint64_t livre_number() const {
            return livre;
        }
        constexpr uint64_t denier_number() const {
            return denires;     
        }
 
        constexpr Moneybag& operator+=(const Moneybag &other) {
            uint64_t liv = livre + other.livre;
            uint64_t solid = solidus + other.solidus;
            uint64_t denir = denires + other.denires;
            if (__builtin_add_overflow(livre, other.livre, &liv) ||
                __builtin_add_overflow(solidus, other.solidus, &solid) ||
                __builtin_add_overflow(denires, other.denires, &denir)) {
                throw std::out_of_range("OVERFLOW PRZY DODAWANIU\n");
            }
            this->livre = liv;
            this->denires = denir;
            this->solidus =solid;
            return (*this);
        }

        constexpr Moneybag operator+(const Moneybag &other) const {
            return Moneybag(*this) += other;
        }

        constexpr Moneybag& operator-=(const Moneybag &other) {
            uint64_t liv = livre - other.livre;
            uint64_t solid = solidus - other.solidus;
            uint64_t denir = denires - other.denires;
            if (__builtin_sub_overflow(livre, other.livre, &liv) ||
                __builtin_sub_overflow(solidus, other.solidus, &solid) ||
                __builtin_sub_overflow(denires, other.denires, &denir)) {
                throw std::out_of_range("OVERFLOW PRZY ODEJMOWANIU\n");
            }
            this->livre = liv;
            this->denires = denir;
            this->solidus =solid;
            return(*this);
        }

        constexpr Moneybag operator-(const Moneybag &other) const {
            return Moneybag(*this) -= other;
        }
 
        constexpr Moneybag& operator*= (const auto number) {
            uint64_t liv = livre * (uint64_t)number;
            uint64_t solid = solidus * (uint64_t)number;
            uint64_t denir = denires * (uint64_t)number;
            if (__builtin_mul_overflow(livre, (uint64_t)number, &liv) ||
                __builtin_mul_overflow(solidus, (uint64_t)number, &solid) ||
                __builtin_mul_overflow(denires, (uint64_t)number, &denir)) {
                throw std::out_of_range("OVERFLOW PRZY MNOZENIU\n");    
            }
            this->livre = liv;
            this->denires = denir;
            this->solidus = solid;
            return(*this);
        }
 
        constexpr Moneybag operator*(const auto number) const {
            return Moneybag(*this) *= number;
        }
 
        constexpr bool operator==(const Moneybag &other) const {
            return(livre == other.livre && solidus == other.solidus 
                   && denires == other.denires);
        }
 
        inline explicit operator bool() const {
            return (livre > 0 || solidus > 0 || denires > 0);
        }

        constexpr std::partial_ordering operator<=>(const Moneybag &other) const {
            if (*this == other) {
                return std::partial_ordering::equivalent;
            } else if (livre <= other.livre && solidus <= other.solidus &&
                       denires <= other.denires) {
                return std::partial_ordering::less;
            } else if (livre >= other.livre && solidus >= other.solidus &&
                       denires >= other.denires) {
                return std::partial_ordering::greater;
            } else {
                return std::partial_ordering::unordered;
            }
       }
};

inline Moneybag operator*(const auto number, const Moneybag& right) {
    return right * number;
}
 
inline std::ostream & operator << (std::ostream &out, const Moneybag &c) {
    out << "(" << c.livre_number();
    if (c.livre_number() == 1) {
        out << " livr, ";
    } else {
        out << " livres, ";
    }
    out << c.solidus_number();
    if (c.solidus_number() == 1) {
        out << " solidus, ";
    } else {
        out << " soliduses, ";
    }
    out << c.denier_number();
    if (c.denier_number() == 1) {
        out << " denier)";
    } else {
        out << " deniers)";
    }
    return out;
}
 
constinit const Moneybag Livre(1, 0, 0);
constinit const Moneybag Solidus(0, 1, 0);
constinit const Moneybag Denier(0, 0, 1);
constinit const int LIVRE_TO_DENIER = 240;
constinit const int SOLIDUS_TO_DENIER = 12;
 
class Value {
    private: __uint128_t value;
 
    public: 
        constexpr Value (const Moneybag &bag): value (
                        LIVRE_TO_DENIER * (__uint128_t)bag.livre_number() +
                        SOLIDUS_TO_DENIER* (__uint128_t)bag.solidus_number() + 
                        (__uint128_t)bag.denier_number()) {}
        constexpr Value (const uint64_t number): value(number) {}
        constexpr Value () :value(0) {}
        constexpr Value& operator=(const Value &other) {
            if (value != other.value) {
                value = other.value;
            }
            return *this;
        }
        constexpr friend bool operator==(const Value &other, const Value &thisValue) {
            return (thisValue.value == other.value);
        }
        constexpr friend bool operator==(const uint64_t val, const Value &Value) {
            return (Value.value == val);
        }
        constexpr friend bool operator==(const Value &Value, const uint64_t val) {
            return (Value.value == val);
        }
        constexpr uint64_t operator=(const uint64_t val) { 
            if (value != val) {
                value = val;
            }
            return value;
        }
        std::strong_ordering constexpr operator<=>(const Value &other) const {
            if (value < other.value) {
                return std::strong_ordering::less;
            }
            else if (value > other.value) {
                return std::strong_ordering::greater;
            }
            else {
                return std::strong_ordering::equal;
            }
        }
 
        std::strong_ordering constexpr operator<=>(const uint64_t val) const {
            if (value < val) {
                return std::strong_ordering::less;
            }
            else if (value > val) {
                return std::strong_ordering::greater;
            } else {
                return std::strong_ordering::equal;
            }
        }
 
        inline explicit operator std::string() const {
            __uint128_t deniers = value;
            std::string output = "";
            if (deniers != 0) {
                while (deniers > 0) {
                    output += '0' + deniers % 10;
                    deniers /= 10;
                }
            } else {
                output += '0';
            }
            return std::string(output.rbegin(), output.rend()); 
        }
};
 
#endif /*MONEYBAG_H*/
