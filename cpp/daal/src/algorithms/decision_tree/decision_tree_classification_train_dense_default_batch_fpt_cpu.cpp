/* file: decision_tree_classification_train_dense_default_batch_fpt_cpu.cpp */
/*******************************************************************************
* Copyright 2014-2019 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of Decision tree training functions for the defaultDense method.
//--
*/

#include "src/algorithms/decision_tree/decision_tree_classification_train_container.h"
#include "src/algorithms/decision_tree/decision_tree_classification_train_dense_default_impl.i"

namespace daal
{
namespace algorithms
{
namespace decision_tree
{
namespace classification
{
namespace training
{
namespace interface2
{
template class BatchContainer<DAAL_FPTYPE, defaultDense, DAAL_CPU>;
} // namespace interface2

namespace internal
{
template class DecisionTreeTrainBatchKernel<DAAL_FPTYPE, decision_tree::classification::Parameter, defaultDense, DAAL_CPU>;

} // namespace internal
} // namespace training
} // namespace classification
} // namespace decision_tree
} // namespace algorithms
} // namespace daal
