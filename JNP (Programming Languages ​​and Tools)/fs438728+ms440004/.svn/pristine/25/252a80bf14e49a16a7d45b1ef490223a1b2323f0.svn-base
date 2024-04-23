#ifndef ORGANISM_H
#define ORGANISM_H

//TODO wyjebać potem
#include <iostream>
#include <concepts>
#include <tuple>
#include <optional>
#include <cstdint>

template<typename species_t, bool can_eat_meat, bool can_eat_plants>
    requires std::equality_comparable<species_t>
class Organism {
    public:
        constexpr Organism(const species_t & spec, const uint64_t vit):
            species(spec),
            vitality(vit) {};

        //funkcja zwraca kopie organizmu ze zmienioną witalnością
        constexpr Organism copy_with_new_vit(const uint64_t newVit) const {
            return Organism(get_species(), newVit);
        }

        constexpr uint64_t get_vitality() const {
            return vitality;
        }

        constexpr bool is_plant() const {
            return !can_eat_plants && !can_eat_meat;
        }

        constexpr bool is_omnivore() const {
            return can_eat_plants && can_eat_meat;
        }

        constexpr bool is_carnivore() const {
            return !can_eat_plants && can_eat_meat;
        }

        constexpr bool is_herbivore() const {
            return can_eat_plants && !can_eat_meat;
        }

        constexpr bool is_dead() const {
            return vitality == 0;
        }

        constexpr species_t get_species() const {
            return species;
        }

    private:
        const species_t species;
        uint64_t vitality;
};

//funkcja zwraca czy organism1 chce zjeść organism2
template <typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
constexpr inline bool eats(const Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
                           const Organism<species_t, sp2_eats_m, sp2_eats_p> organism2) {
    if constexpr (organism1.is_omnivore()) {
        return true;
    }
    if constexpr (organism1.is_herbivore() && organism2.is_plant()) {
        return true;
    }
    return organism1.is_carnivore() && !organism2.is_plant();
}

template <typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
constexpr bool same_species(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
                            Organism<species_t, sp2_eats_m, sp2_eats_p> organism2) {
    return organism1.get_species() == organism2.get_species() &&
           sp1_eats_m == sp2_eats_m &&
           sp1_eats_p == sp2_eats_p;
}

template<typename species_t>
using Herbivore = Organism<species_t, false, true>;

template<typename species_t>
using Omnivore = Organism<species_t, true, true>;

template<typename species_t>
using Plant = Organism<species_t, false, false>;

template<typename species_t>
using Carnivore = Organism<species_t, true, false>;

template <typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
constexpr std::tuple<Organism<species_t, sp1_eats_m, sp1_eats_p>,
                    Organism<species_t, sp2_eats_m, sp2_eats_p>,
                    std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>>
encounter(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
          Organism<species_t, sp2_eats_m, sp2_eats_p> organism2) {
    //zasada 1 - sprawdzona w nagłówku funkcji
    //zasada 2
    static_assert(!organism1.is_plant() || !organism2.is_plant());
    //zasada 3
    if (organism1.is_dead() || organism2.is_dead()) {
        //nic się nie dzieje
        return std::make_tuple(
                organism1.copy_with_new_vit(organism1.get_vitality()),
                organism2.copy_with_new_vit(organism2.get_vitality()),
                std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>()
        );
    }
    //zasada 4
    if (same_species(organism1, organism2)) {
        return std::make_tuple(
                Organism(organism1), Organism(organism2),
                Organism<species_t, sp1_eats_m, sp1_eats_p>(
                        organism1.get_species(),
                        (organism1.get_vitality() + organism2.get_vitality()) / 2)
        );
    }
    //zasada 5
    if (!eats(organism1, organism2) && !eats(organism2,organism1)) {
        //nic się nie dzieje
        return std::make_tuple(
                organism1.copy_with_new_vit(organism1.get_vitality()),
                organism2.copy_with_new_vit(organism2.get_vitality()),
                std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>()
        );
    }
    //zasada 6
    if (eats(organism1, organism2) && eats(organism2, organism1)) {
        if (organism1.get_vitality() > organism2.get_vitality()) {
            //pierwszy zjada drugiego
            return std::make_tuple(
                        organism1.copy_with_new_vit(
                                organism1.get_vitality() + organism2.get_vitality() / 2
                                ),
                        organism2.copy_with_new_vit(0),
                        std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>()
            );
        } else if (organism1.get_vitality() < organism2.get_vitality()) {
            //drugi zjada pierwszego
            return std::make_tuple(
                    organism1.copy_with_new_vit(0),
                    organism2.copy_with_new_vit(
                            organism1.get_vitality() / 2 + organism2.get_vitality()
                            ),
                    std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>()
            );
        }
        //else: oba organizmy umierają
        return std::make_tuple(
                organism1.copy_with_new_vit(0),
                organism2.copy_with_new_vit(0),
                std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>()
        );
    }
    //zasada 7
    if (organism1.is_plant() || organism2.is_plant()) {
        if (organism1.is_plant()) { //skoro przeszliśmy zasade 5 to będą się jeść
            return std::make_tuple(
                    organism1.copy_with_new_vit(0),
                    organism2.copy_with_new_vit(
                            organism1.get_vitality() + organism2.get_vitality()
                            ),
                    std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>()
            );
        } else { //organism2 jest rośliną
            return std::make_tuple(
                    organism1.copy_with_new_vit(
                            organism1.get_vitality() + organism2.get_vitality()
                            ),
                    organism2.copy_with_new_vit(0),
                    std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>()
            );
        }
    }
    //zasada 8
    if (eats(organism1, organism2) && !eats(organism2, organism1)) {
        if (organism1.get_vitality() > organism2.get_vitality()) {
            //pierwszy zjada drugiego
            return std::make_tuple(
                    organism1.copy_with_new_vit(
                            organism1.get_vitality() + organism2.get_vitality() / 2
                    ),
                    organism2.copy_with_new_vit(0),
                    std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>()
            );
        } else {
            //nic się nie dzieje
            return std::make_tuple(
                    organism1.copy_with_new_vit(organism1.get_vitality()),
                    organism2.copy_with_new_vit(organism2.get_vitality()),
                    std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>()
            );
        }
    } else { // !eats(organism1, organism2) && eats(organism2, organism1)
        if (organism1.get_vitality() < organism2.get_vitality()) {
            //drugi zjada pierwszego
            return std::make_tuple(
                    organism1.copy_with_new_vit(0),
                    organism2.copy_with_new_vit(
                            organism2.get_vitality() + organism1.get_vitality() / 2
                    ),
                    std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>()
            );
        } else {
            //nic się nie dzieje
            return std::make_tuple(
                    organism1.copy_with_new_vit(organism1.get_vitality()),
                    organism2.copy_with_new_vit(organism2.get_vitality()),
                    std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>()
            );
        }
    }
}
template <typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p, typename ... Args>
    constexpr Organism<species_t, sp1_eats_m, sp1_eats_p> 
    fold_encounter_series(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1, Organism<species_t, sp2_eats_m, sp2_eats_p> organism2, Args ... args) {
        auto organism = get<0>(encounter(organism1, organism2));
        if constexpr (sizeof...(args) > 0) {
            return fold_encounter_series(organism, args...);
        }
        else {
            return organism;
        }
    }
template <typename species_t, bool sp1_eats_m, bool sp1_eats_p, typename ... Args>
    constexpr Organism<species_t, sp1_eats_m, sp1_eats_p>
    encounter_series(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1, Args ... args) {
        if(sizeof...(args) > 0) {
            return fold_encounter_series(organism1, args...);
        }
        return organism1;
    }
#endif
