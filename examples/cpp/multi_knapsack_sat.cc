// Copyright 2010-2018 Google LLC
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Solve a scaled constrained two dimensional knapsack problem.
// Each bin must be filled with items with min and max weights, and min and max volumes.
// As is a knapsack, the objective is to maximize total value.
//
// Data is for 1 bin and 10 items. Scaling is done my having m bins and m copies of each items.

#include <string>
#include <vector>

#include "absl/strings/str_format.h"
#include "ortools/base/commandlineflags.h"
#include "ortools/sat/cp_model.h"
#include "ortools/sat/model.h"

DEFINE_int32(size, 16, "scaling factor of the model");
DEFINE_string(params, "", "Sat paramters");

namespace operations_research {
namespace sat {

static const int kWeightMin = 16000;
static const int kWeightMax = 22000;
static const int kVolumeMin = 1156;
static const int kVolumeMax = 1600;

// data for a single bin problem
static const int kItemsWeights[] = {1008, 2087, 5522, 5250,  5720,
                                    4998, 275,  3145, 12580, 382};
static const int kItemsVolumes[] = {281, 307, 206, 111, 275, 79, 23, 65, 261, 40};
static const int kNumItems = 10;

void MultiKnapsackSat(int scaling, const std::string& params) {
  CpModelBuilder builder;

  const int num_items = scaling * kNumItems;
  const int num_bins = scaling;

  std::vector<std::vector<BoolVar>> items_in_bins(num_bins);
  for (int b = 0; b < num_bins; ++b) {
    for (int i = 0; i < num_items; ++i) {
      items_in_bins[b].push_back(builder.NewBoolVar());
    }
  }

  std::vector<BoolVar> selected_items(num_items);
  for (int i = 0; i < num_items; ++i) {
    selected_items[i] = builder.NewBoolVar();
  }

  // Fill up scaled values, weights, volumes;
  std::vector<int64> weights(num_items);
  std::vector<int64> volumes(num_items);
  for (int i = 0; i < num_items; ++i) {
    const int index = i % kNumItems;
    weights[i] = kItemsWeights[index];
    volumes[i] = kItemsVolumes[index];
  }

  // Constraints per bins.
  std::vector<IntVar> bin_weights;
  for (int b = 0; b < num_bins; ++b) {
    IntVar bin_weight = builder.NewIntVar({kWeightMin, kWeightMax});
    bin_weights.push_back(bin_weight);
    builder.AddEquality(
        LinearExpr::BooleanScalProd(items_in_bins[b], weights), bin_weight);
    builder.AddLinearConstraint(
        LinearExpr::BooleanScalProd(items_in_bins[b], volumes),
        {kVolumeMin, kVolumeMax});
  }

  // Each is selected at most one time.
  for (int i = 0; i < num_items; ++i) {
    std::vector<BoolVar>  copies(num_bins);
    for (int b = 0; b < num_bins; ++b) {
      copies[b] = items_in_bins[b][i];
    }
    builder.AddEquality(LinearExpr::BooleanSum(copies), selected_items[i]);
  }

  // Symmetry breaking. Weights are decreasing accross bins.
  // for (int b = 0; b + 1 < num_bins; ++b) {
  //   builder.AddGreaterOrEqual(bin_weights[b], bin_weights[b + 1]);
  // }

  // Maximize value.
  builder.Maximize(LinearExpr::Sum(bin_weights));

  // And solve.
  Model model;
  if (!params.empty()) {
    model.Add(NewSatParameters(params));
  }
  const CpSolverResponse response = SolveWithModel(builder.Build(), &model);
  LOG(INFO) << CpSolverResponseStats(response);
}

}  // namespace sat
}  // namespace operations_research

int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  operations_research::sat::MultiKnapsackSat(FLAGS_size, FLAGS_params);
  return EXIT_SUCCESS;
}