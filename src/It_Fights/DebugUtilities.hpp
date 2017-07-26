//
//  DebugUtilities.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 27/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef DebugUtilities_hpp
#define DebugUtilities_hpp

#include <iostream>

#define TO_STREAM(stream, variable)                            \
  (stream) << #variable " (" << typeid(variable).name() << ")" \
           << ": " << (variable) << std::endl;
#define printv(variable) TO_STREAM(std::cout, (variable))
#define prints(string) std::cout << string << std::endl

#endif /* DebugUtilities_hpp */
