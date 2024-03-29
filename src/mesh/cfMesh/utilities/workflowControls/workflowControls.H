/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.1
    \\  /    A nd           | Web:         http://www.foam-extend.org
     \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
                     Author | F.Juretic (franjo.juretic@c-fields.com)
                  Copyright | Copyright (C) Creative Fields, Ltd.
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Class
    workflowControls

Description
    A controller fo managing the mesh generation workflow. It allows the user
    to stop the meshing process after selected steps in the workflow,
    and restart from a selected point.

SourceFiles
    workflowControls.C

\*---------------------------------------------------------------------------*/

#ifndef workflowControls_H
#define workflowControls_H

#include "IOdictionary.H"
#include "DynList.H"

#include <map>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class polyMeshGen;


class workflowControls
{
    // Private data
        //- reference to the mesh
        polyMeshGen& mesh_;

        //- current step in the workflow
        word currentStep_;

        //- step for restarting the workflow
        word restartAfterStep_;

        //- completed step before restart
        DynList<word> completedStepsBeforeRestart_;

        //- holds information whether the workflow has been restarted
        mutable bool isRestarted_;

    // static private data
        static const std::map<word, label> workflowSteps_;

    // Private member functions
        //- check if restart is requested
        bool restartRequested() const;

        //- sets the current step to completed
        void setStepCompleted() const;

        //- is the current step already completed
        bool isStepCompleted() const;

        //- shall the procedure stop after the current step
        bool exitAfterCurrentStep() const;

        //- return the latest completed step
        word lastCompletedStep() const;

        //- return the names of completed steps
        DynList<word> completedSteps() const;

        //- remove completedStep from the dictionary
        void clearCompletedSteps();

        //- shall the workflow stop after the current step
        bool stopAfterCurrentStep() const;

        //- shall the workflow run after the current step
        bool runAfterCurrentStep() const;

    // Static private member functions
        //- populate workflowSteps with values
        static std::map<word, label> populateWorkflowSteps();

public:

    // Constructors

        //- Construct from IOdictionary
        workflowControls(polyMeshGen& mesh);

    // Destructor
        ~workflowControls();

    // Public member functions

        //- shall the process run the current step
        bool runCurrentStep(const word&);

        //- set the workflow completed flag
        void workflowCompleted();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
