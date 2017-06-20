//
//  ReinforcementLearningBehaviour_1.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 19/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef ReinforcementLearningBehaviour_1_hpp
#define ReinforcementLearningBehaviour_1_hpp

#include "StateActionContainer.hpp"

#include "Behaviour.hpp"

#define EPSILON (0.30f)

class ReinforcementLearningBehaviour_1 : public Behaviour {
public:
    ReinforcementLearningBehaviour_1(EnemyCharacterController* controller, AIObserver* observer);
    virtual ~ReinforcementLearningBehaviour_1();
    void update(FightState_Discrete discreteState);
private:
    FightState_Discrete currentDiscreteState;
    FightState_Discrete lastDiscreteState;
    Action lastAction;
    
    double getActionSituationWeigth(ActionSituation as);
    
};

#endif /* ReinforcementLearningBehaviour_1_hpp */
