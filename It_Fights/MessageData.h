//
//  MessageData.h
//  It_Fights
//
//  Created by Rubén Osorio López on 1/4/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef MessageData_h
#define MessageData_h


struct PairI {
    int x;
    int y;
};

struct MessageData{
    enum{
        EMPTY,
        STRING_PTR,
        PAIR_OF_INTS
    }type;
    union{
        std::string * string_ptr;
        PairI intPair;
    };
};

#endif /* MessageData_h */





// Leave this here just in case

//    MessageData& operator=(MessageData other)
//    {
//        type = other.type;
//        switch(type){
//            EMPTY:
//                break;
//            STRING_PTR:
//                string_ptr = other.string_ptr;
//                break;
//            PAIR_OF_INTS:
//                intPair = other.intPair;
//                break;
//            default:
//                std::cerr << "Type of message data not supported when using the assign operator" << std::endl;
//                break;
//        }
//    }
