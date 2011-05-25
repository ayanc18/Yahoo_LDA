/*****************************************************************************
     The contents of this file are subject to the Mozilla Public License
     Version 1.1 (the "License"); you may not use this file except in
     compliance with the License. You may obtain a copy of the License at
     http://www.mozilla.org/MPL/

     Software distributed under the License is distributed on an "AS IS"
     basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
     License for the specific language governing rights and limitations
     under the License.

     The Original Code is Copyright (C) by Yahoo! Research.

     The Initial Developer of the Original Code is Shravan Narayanamurthy.

     All Rights Reserved.
******************************************************************************/
/*
 * Simple_Execution_Strategy.cpp
 *
 *  Created on: 28-Dec-2010
 *      
 */

#include "Testing_Execution_Strategy.h"
#include "Context.h"
#include "Pipeline.h"
#include "tbb/tick_count.h"
#include "glog/logging.h"

Testing_Execution_Strategy::Testing_Execution_Strategy(Pipeline& pipeline,
        Model& model) :
    _pipeline(pipeline), _model(model) {
}

Testing_Execution_Strategy::~Testing_Execution_Strategy() {
}

void Testing_Execution_Strategy::execute() {
    Context& context = Context::get_instance();
    int start_iter = 0;
    int end_iter = 1;
    int loglikelihood_interval = context.get_int("printloglikelihood");

    LOG(WARNING) << "Starting Parallel testing Pipeline";
    for (int iter = start_iter; iter < end_iter; ++iter) {
        bool compute_loglikelihood = (iter == start_iter) || (iter
                % loglikelihood_interval == 0);
        _pipeline.init();
        _pipeline.add_reader();
        _pipeline.add_tester();
        if (compute_loglikelihood)
            _pipeline.add_eval();
        _pipeline.add_writer();
        tbb::tick_count t0 = tbb::tick_count::now();
        _pipeline.run();
        tbb::tick_count t1 = tbb::tick_count::now();
        LOG(WARNING) << "Iteration " << iter << " done. Took "
                << (t1 - t0).seconds() / 60 << " mins" << endl;
        if (compute_loglikelihood) {
            double word_loglikelihood = _model.get_eval();
            double doc_loglikelihood = _pipeline.get_eval();
            LOG(WARNING)
                    << ">>>>>>>>>> Log-Likelihood (model, doc, total): "
                    << word_loglikelihood << " , " << doc_loglikelihood
                    << " , " << word_loglikelihood + doc_loglikelihood;
        }
        _pipeline.clear();
        _pipeline.destroy();
    }
    LOG(WARNING) << "Parallel testing Pipeline done";
}
