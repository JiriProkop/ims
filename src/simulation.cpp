#include "simulation.hpp"


Simulation::Simulation(bool signalizedIntersection) { this->signalizedIntersection = signalizedIntersection; }

void Simulation::makeStep() {
    if (signalizedIntersection) {
        signalizedIntersectionRules();
    } else {
        unsignalizedIntersectionRules();
    }
}



void Simulation::signalizedIntersectionRules() {
    // TODO
}

void Simulation::unsignalizedIntersectionRules() {
    // TODO
}
// with lights
// auta: kdyz je cervena nebo jsou na chodniku jeste lidi, stuj.
//       jinak jed
// lidi: kdyz je zelena a nebo cervena, ale jsi jeste na chodniku, jdi
//       jinak stuj

// also, pokud chci projit nekudy, kde je auto, cekam
//       stejne u auta

// kdyz chci jit nekam, kam chce uz also nekdo jit, random se vybere kdo pujde.

// one sim round is 1 second

// without lights
// crossing for pedestrians or cars kdyz nejsou na hlavni:
// l_veh - vzdalenost od auta od prechodu nebo od auta
// v_veh - budouci nebo stavajici rychlost auta
// l_ped - vzdalenost chodce od konce prechodu/pruhu
// v_ped - ocekavan rychlost chodce/auta. Da se pouzit prumer.
// t - podle akceptace chodce/auta, u chodce se muze urcit podle agresivity chodce
// ROVNICE: l_veh/v_veh - l_ped/v_ped >= t

// rychlost aut
// prumer 25 km/h ~= 7 m/s coz by bylo 14 policek :aware:
// proto bude potreba vzit v potaz i zrychleni a zpomaleni
// zrychleni i zpomalnei - 2 m/s^2
//      special case: possible kolize - zastaveni skoro hned
