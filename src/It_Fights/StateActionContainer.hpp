//
//  StateActionContainer.hpp
//  It_Fights
//
//  Created by Rubén Osorio López on 19/6/17.
//  Copyright © 2017 Rubén Osorio López. All rights reserved.
//

#ifndef StateActionContainer_hpp
#define StateActionContainer_hpp

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/unordered_map.hpp>

#include <mutex>
#include <shared_mutex>
#include <thread>

#define NumberOfActions 7

struct ActionSituation {
  unsigned int timesExecuted;
  double meanDeltaFitness;
  double maxFitness;

  friend class boost::serialization::access;
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    ar& timesExecuted;
    ar& meanDeltaFitness;
    ar& maxFitness;
  }

  static ActionSituation getEmptyValue();
};

struct StateActionSituation {
  ActionSituation actionArray[7];

  friend class boost::serialization::access;
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    ar& actionArray;
  }

  static StateActionSituation getEmptyValue();
};

class StateActionContainer {
 public:
  static StateActionContainer& Instance();

  //*************************************//
  //******** REAL PUBLIC MEMBERS ********//
  //*************************************//

  std::unordered_map<std::string, StateActionSituation>* getStateActionMap();

  void resetPreviousKnowledge();

  bool hasState(std::string state);

  StateActionSituation getStateActionSituationFor(std::string state);

  void putStateActionSituation(std::string state,
                               StateActionSituation situation);

 private:
  static void CleanUp();

  StateActionContainer();
  ~StateActionContainer() {}

  StateActionContainer(StateActionContainer const&);
  StateActionContainer& operator=(StateActionContainer const&);

  static StateActionContainer* MInstance;

  //@@TODO: Put mutex;
  mutable std::shared_mutex mutex;

  //*************************************//
  //******* REAL PRIVATE MEMBERS ********//
  //*************************************//

  std::unordered_map<std::string, StateActionSituation> stateActionMap;

  void saveToFile();

  friend class boost::serialization::access;
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    ar& stateActionMap;
  }
};

#endif /* StateActionContainer_hpp */
