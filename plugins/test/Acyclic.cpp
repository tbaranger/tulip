/**
 *
 * This file is part of Tulip (www.tulip-software.org)
 *
 * Authors: David Auber and the Tulip development Team
 * from LaBRI, University of Bordeaux 1 and Inria Bordeaux - Sud Ouest
 *
 * Tulip is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Tulip is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 */

#include <tulip/AcyclicTest.h>
#include <tulip/GraphTest.h>

class AcyclicTest : public tlp::GraphTest {
public:
  PLUGININFORMATIONS("Acyclicity Test", "Tulip team", "18/04/2012", "Tests whether a graph is acyclic or not.", "1.0", "Acyclicity")
  AcyclicTest(const tlp::PluginContext* context) : tlp::GraphTest(context) {
  }

  virtual bool run() {
    return tlp::AcyclicTest::isAcyclic(graph);
  }

};
PLUGIN(AcyclicTest)

class MakeAcyclic : public tlp::Algorithm {
public:
  PLUGININFORMATIONS("Make Acyclic", "Tulip team", "18/04/2012", "Makes a graph acyclic.", "1.0", "Acyclicity")
  MakeAcyclic(const tlp::PluginContext* context) : tlp::Algorithm(context) {
  }

  virtual bool run() {
    std::vector<tlp::edge> edges;
    std::vector<tlp::SelfLoops> selfLoops;
    tlp::AcyclicTest::makeAcyclic(graph, edges, selfLoops);
    return true;
  }

};
PLUGIN(MakeAcyclic)
