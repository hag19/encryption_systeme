/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 125.
 */

#include "../include/Stats.h"

Stats Stats_zero() {
  return (Stats){
    .forward_force = 0.,
    .backward_force = 0.,
    .right_force = 0.,
    .left_force = 0.,
    .mass = 0.,
    .health = 0.,
    .armor = 0.,
    .damage = 0.,
    .repair = 0.,
    .points = 0
  };
}

Stats Stats_base(double mass, double health, double armor, int points) {
  Stats stats = Stats_zero();
  stats.mass = mass;
  stats.health = health;
  stats.armor = armor;
  stats.points = points;
  return stats;
}

void Stats_add(Stats * current, const Stats * other) {
  current->forward_force += other->forward_force;
  current->backward_force += other->backward_force;
  current->right_force += other->right_force;
  current->left_force += other->left_force;
  current->mass += other->mass;
  current->health += other->health;
  current->armor += other->armor;
  current->damage += other->damage;
  current->repair += other->repair;
  current->points += other->points;
}

void Stats_display(FILE * flow, const Stats * stats) {
  fprintf(flow, "Stats : {\n"
  " - forward force : %g\n"
  " - backward force : %g\n"
  " - left force : %g\n"
  " - right force : %g\n"
  " - mass : %g\n"
  " - health : %g\n"
  " - armor : %g\n"
  " - damage : %g\n"
  " - repair : %g\n"
  " - points : %d\n"
  "}\n",
  stats->forward_force,
  stats->backward_force,
  stats->left_force,
  stats->right_force,
  stats->mass,
  stats->health,
  stats->armor,
  stats->damage,
  stats->repair,
  stats->points);
}