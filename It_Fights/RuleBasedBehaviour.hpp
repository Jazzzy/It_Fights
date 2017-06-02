//
//  RuleBasedBehaviour.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 24/5/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef RuleBasedBehaviour_hpp
#define RuleBasedBehaviour_hpp

#include "Behaviour.hpp"

class RuleBasedBehaviour : public Behaviour {
public:
    RuleBasedBehaviour(EnemyCharacterController* controller, AIObserver* observer);
    virtual ~RuleBasedBehaviour();
    virtual void update();
    
};


#endif /* RuleBasedBehaviour_hpp */
