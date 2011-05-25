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
 * Testing_Execution_Strategy.h
 *
 *
 *  Created on: 28-Dec-2010
 *      
 */

#ifndef TESTING_EXECUTION_STRATEGY_H_
#define TESTING_EXECUTION_STRATEGY_H_

#include "Execution_Strategy.h"
#include "Pipeline.h"
#include "Model.h"

/**
 * This is a default implementation for the Execution_Strategy
 * interface for testing using a model.
 */
class Testing_Execution_Strategy: public Execution_Strategy {
public:
    Testing_Execution_Strategy(Pipeline&, Model&);
    virtual ~Testing_Execution_Strategy();

    //!Define what filters need to added and when
    //!Runs the assembled pipeline once
    void execute();

private:
    Pipeline& _pipeline;
    Model& _model;
};

#endif /* TESTING_EXECUTION_STRATEGY_H_ */
