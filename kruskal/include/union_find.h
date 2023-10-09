/*
 * Prototypes for union_find.c
 */

#ifndef UNION_FIND_H
#define UNION_FIND_H

/// @brief Makes a set with the given element
/// @param x The element to make a set with
/// @param parent The parent array
/// @param rank The rank array
void make_set(int x, int *parent, int *rank);

/// @brief Finds the set of the given element
/// @param x The element to find the set of
/// @param parent The parent array
int find(int x, int *parent);

/// @brief Joins the sets of the given elements
/// @param x The first element to join with
/// @param y The second element to join with
/// @param parent The parent array
/// @param rank The rank array
void join(int x, int y, int *parent, int *rank);

#endif