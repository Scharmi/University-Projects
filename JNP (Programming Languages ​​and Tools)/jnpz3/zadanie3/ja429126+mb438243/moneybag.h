#pragma once

class Moneybag {
public:
    typedef uint64_t coin_number_t;

    // Tworzenie obiektu Moneybag poprzez podanie liczby odpowiednich monet.
    constexpr Moneybag(coin_number_t l, coin_number_t s, coin_number_t d) : livres(l), soliduses(s), deniers(d) {}

    // Tworzenie obiektu moneybag poprzez skopiowanie wartości innego obiektu Moneybag.
    Moneybag(const Moneybag& that) : livres(that.livres), soliduses(that.soliduses), deniers(that.deniers) {}

    // Tworzenie obiektu moneybag poprzez skopiowanie wartości innego obiektu Moneybag za pomoca operatora '='.
    Moneybag& operator=(const Moneybag& that) {
        livres = that.livres;
        soliduses = that.soliduses;
        deniers = that.deniers;
        return *this;
    }

    // Funkcje zwracające liczbę monet określanego typu w danym Moneybagu.
    coin_number_t livre_number() const { return livres; }

    coin_number_t solidus_number() const { return soliduses; }

    coin_number_t denier_number() const { return deniers; }

    // Overloading operatorów '+' i '+=' w celu umożliwienia dodania do siebie zawartości dwóch sakiewek.
    Moneybag& operator+=(const Moneybag& that) {
        bool livresOOR = livres > UINT64_MAX - that.livres;
        bool solidusesOOR = soliduses > UINT64_MAX - that.soliduses;
        bool deniersOOR = deniers > UINT64_MAX - that.deniers;

        if (livresOOR || solidusesOOR || deniersOOR)
            throw std::out_of_range("Sum couldn't be calculated, due to result being out of range.");

        livres += that.livres;
        soliduses += that.soliduses;
        deniers += that.deniers;
        return *this;
    }

    const Moneybag operator+(const Moneybag& other) const {
        Moneybag result = *this;
        result += other;
        return result;
    }

    // Overloadng operatorów '-' i '-=' w celu umożliwienia odjęcia od siebie zawartości dwóch sakiewek.
    Moneybag& operator-=(const Moneybag& that) {
        if (livres < that.livres || soliduses < that.soliduses || deniers < that.deniers)
            throw std::out_of_range("Difference couldn't be calculated, due to result being out of range.");
        else {
            livres -= that.livres;
            soliduses -= that.soliduses;
            deniers -= that.deniers;
        }

        return *this;
    }

    const Moneybag operator-(const Moneybag& other) const {
        Moneybag result = *this;
        result -= other;
        return result;
    }

    // Overloading operatora '*=' w celu umożliwienia pomnożenia zawartości sakiewki przez nieujemną liczbę calkowitą.
    // Overloading operatora '*' znajduje się poza deklaracją klasy, w celu zapewnienia przemienności operacji.
    Moneybag& operator*=(const coin_number_t& that) {
        coin_number_t potential_l = livres * that;
        coin_number_t potential_s = soliduses * that;
        coin_number_t potential_d = deniers * that;

        if (that)
            if (potential_l / that != livres || potential_s / that != soliduses || potential_d / that != deniers)
                throw std::out_of_range("Multiplication couldn't be calculated, due to result being out of range.");

        livres = potential_l;
        soliduses = potential_s;
        deniers = potential_d;

        return *this;
    }

    // Overloading operatorów porównujących, gwarantujących porządek częsciowy na obiektach Moneybag.
    std::partial_ordering operator<=>(const Moneybag& m) const {
        if (this->livres == m.livres && this->soliduses == m.soliduses && this->deniers == m.deniers)
            return std::partial_ordering::equivalent;
        if (this->livres >= m.livres && this->soliduses >= m.soliduses && this->deniers >= m.deniers)
            return std::partial_ordering::greater;
        if (this->livres <= m.livres && this->soliduses <= m.soliduses && this->deniers <= m.deniers)
            return std::partial_ordering::less;
        return std::partial_ordering::unordered;
    }

    bool operator==(const Moneybag& m) const {
        return this->livres == m.livres && this->soliduses == m.soliduses && this->deniers == m.deniers;
    }

    // Rzutowanie obiektu Moneybag na typ bool:
    //  true  - kiedy zawiera przynejmaniej jedną monetę dowolnego typu.
    //  false - w przeciwnym wypadku.
    explicit operator bool() const { return livres > 0 || deniers > 0 || soliduses > 0; }

private:
    coin_number_t livres;
    coin_number_t soliduses;
    coin_number_t deniers;

    friend std::ostream& operator<<(std::ostream&, const Moneybag&);
};

class Value {
public:
    Value() : value(0) {}

    Value(Moneybag::coin_number_t val) : value(val) {}

    Value(const Value& that) : value(that.value) {}

    Value(const Moneybag& that) : value(checkWorth(that.livre_number(), that.solidus_number(), that.denier_number())) {}

    Value& operator=(const Value& that) {
        value = that.value;
        return *this;
    }

    Value& operator=(const Moneybag& that) {
        value = checkWorth(that.livre_number(), that.solidus_number(), that.denier_number());
        return *this;
    }

    // Overloading operatorów porównujących, gwarantujących porządek częściowy na obiektach Value.
    auto operator<=>(const Value& v) const = default;

    std::strong_ordering operator<=>(const uint64_t& i) const {
        if (this->value == i) return std::strong_ordering::equal;
        if (this->value > i) return std::strong_ordering::greater;
        return std::strong_ordering::less;
    }

    bool operator==(const Value& v) const { return this->value == v.value; }

    bool operator==(const uint64_t& i) const { return this->value == i; }

    explicit operator std::string() const {
        std::string str;
        __uint128_t num = this->value;
        do {
            int digit = num % 10;
            str = std::to_string(digit) + str;
            num = (num - digit) / 10;
        } while (num != 0);
        return str;
    }

private:
    static const uint64_t SOLIDUSES_TO_DENIERS = 12;
    static const uint64_t LIVRES_TO_DENIERS = 240;

    __uint128_t value;

    // Funkcja obliczająca wartość w denararach dla ilości podanych monet.
    __uint128_t checkWorth(__uint128_t livres, __uint128_t soliduses, __uint128_t deniers) {
        __uint128_t livres_in_deniers = livres * LIVRES_TO_DENIERS;
        __uint128_t soliduses_in_deniers = soliduses * SOLIDUSES_TO_DENIERS;

        if (livres_in_deniers / LIVRES_TO_DENIERS != livres || soliduses_in_deniers / SOLIDUSES_TO_DENIERS != soliduses)
            throw std::out_of_range("Creating Value failed, due to result being out of range.");

        __uint128_t result = deniers + livres_in_deniers + soliduses_in_deniers;

        return result;
    }
};

// Overloading operatora wypisującego na wyjście reprezentacje zawartości Moneybaga.
inline std::ostream& operator<<(std::ostream& os, const Moneybag& m) {
    os << "(" << m.livres;
    if (m.livres == 1)
        os << " livr, ";
    else
        os << " livres, ";

    os << m.soliduses;
    if (m.soliduses == 1)
        os << " solidus, ";
    else
        os << " soliduses, ";

    os << m.deniers;
    if (m.deniers == 1)
        os << " denier)";
    else
        os << " deniers)";

    return os;
}

// Zapewnienie przemienności mnożenia.
inline static const Moneybag operator*(const Moneybag& m, const uint64_t& that) {
    Moneybag result = m;
    result *= that;
    return result;
}

inline static const Moneybag operator*(const uint64_t& that, const Moneybag& m) { return m * that; }

// Stałe wartości dla jednego Denara, Solida i Liwra.
static constexpr Moneybag Denier = Moneybag(0, 0, 1);
static constexpr Moneybag Solidus = Moneybag(0, 1, 0);
static constexpr Moneybag Livre = Moneybag(1, 0, 0);
