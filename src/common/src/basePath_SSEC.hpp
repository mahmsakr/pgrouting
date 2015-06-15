/*PGR

Copyright (c) 2015 Celia Virginia Vergara Castillo
vicky_vergara@hotmail.com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef SRC_COMMON_SRC_BASE_PATH_SSCE_H_
#define SRC_COMMON_SRC_BASE_PATH_SSCE_H_

#include <deque>
#include <iostream>
// #include <fstream>
#include "postgres.h"
#include "./pgr_types.h"

class Path {
 public:
    std::deque< pgr_path_element3_t > path;
    float8 cost;

    Path(): cost(0) {}

    void push_front(pgr_path_element3_t data) {
        path.push_back(data);
        cost += data.cost;
    }

    void push_back(pgr_path_element3_t data) {
        path.push_back(data);
        cost += data.cost;
    }

    pgr_path_element3_t set_data(
         int d_seq, 
         int64_t d_route,
         int64_t d_vertex,
         int64_t d_edge, 
         float8 d_cost) {
      pgr_path_element3_t data;
      data.seq = d_seq;
      data.route = d_route;
      data.vertex = d_vertex;
      data.edge = d_edge;
      data.cost = d_cost;
      return data;
    }

    void push_front(
         int d_seq, 
         int64_t d_route,
         int64_t d_vertex,
         int64_t d_edge, 
         float8 d_cost) {
      path.push_front(set_data(d_seq, d_route, d_vertex, d_edge, d_cost));
      cost += path[0].cost;
    }

    void push_back(
         int d_seq, 
         int64_t d_route,
         int64_t d_vertex,
         int64_t d_edge, 
         float8 d_cost) {
      path.push_back(set_data(d_seq, d_route, d_vertex, d_edge, d_cost));
      cost += path[path.size() - 1].cost;
    }

    void clear() {
        path.clear();
        cost = 0;
    }

    void print_path(std::ostream& log) const {
       for (unsigned int i = 0; i < path.size(); ++i)
          log << path[i].seq << "\t"
              << path[i].route << "\t"
              << path[i].vertex << "\t"
              << path[i].edge << "\t"
              << path[i].cost << "\n";
    }

    void print_path() const {
       print_path(std::cout);
    }


    Path  getSubpath(unsigned int j) const {
        Path  result;
        if (j == 0)  return result;
        for (auto i = path.begin(); i != path.begin() + j; ++i) result.push_back((*i));
        // for (const auto &e: path) { result.push_back(e); }
        return result;
    }


    bool isEqual(const Path &subpath) const {
        if (subpath.path.empty()) return true;
        if (subpath.path.size() >= path.size()) return false;
        std::deque<pgr_path_element3_t>::const_iterator i, j;
        for (i = path.begin(), j = subpath.path.begin();
             j != subpath.path.end();
             ++i, ++j)
             if ((*i).vertex !=  (*j).vertex) return false;
        return true;
#if 0
        auto i = path.begin();
        auto j = subpath.path.begin();
        for ( ; j != subpath.path.end(); ++i, ++j)
             if ((*i).vertex !=  (*j).vertex) return false;
        return true;
#endif
    }

    void appendPath(const Path &o_path) {
        path.insert(path.end(), o_path.path.begin(), o_path.path.end());
        cost +=  o_path.cost;
    }

    void empty_path(unsigned int d_vertex) {
        path.push_back(set_data(1, d_vertex, d_vertex, -1, 0));
    }

 void dpPrint(
        pgr_path_element3_t **ret_path,
        int &sequence) const {

    int64_t nodeId, edgeId, routeId;
    double cost;

    for (unsigned int i = 0; i < path.size(); i++) {
      routeId = path[i].route;
      nodeId = path[i].vertex;
      edgeId = path[i].edge;
      cost = path[i].cost;
      

      (*ret_path)[sequence].route = routeId;
      (*ret_path)[sequence].vertex = nodeId;
      (*ret_path)[sequence].edge = edgeId;
      (*ret_path)[sequence].cost = cost;
      sequence++;
    }
  }

   void dpPrint(
        pgr_path_element3_t **ret_path,
        int &sequence, int routeId) const {

    int64_t nodeId, edgeId;
    double cost;

    for (unsigned int i = 0; i < path.size(); i++) {
      nodeId = path[i].vertex;
      edgeId = path[i].edge;
      cost = path[i].cost;


      (*ret_path)[sequence].route = (uint64_t)routeId;
      (*ret_path)[sequence].vertex = nodeId;
      (*ret_path)[sequence].edge = edgeId;
      (*ret_path)[sequence].cost = cost;
      sequence++;
    }
  }


};
#endif  // SRC_COMMON_SRC_BASE_PATH_SSCE_H_
