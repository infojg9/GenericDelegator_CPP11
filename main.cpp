/**
 * Author: https://github.com/infojg9
 * MIT/BSD Redistributable License
 */

#include <iostream>
#include "CGenericDelegater.h"

using namespace std;

/// Delegation Test class
class DelegatorTest {
public:
  int display(int iParam1) {
    cout<<__func__<<" iParam1: "<<iParam1<<endl;
    return iParam1;
  }

  int display2(int iParam2) {
    cout<<__func__<<" iParam2: "<<iParam2<<endl;
    return iParam2;
  }
};

int main() {

  DelegatorTest obDelegatorTest;

/// Use compiler flag for target specific selection: -DGENERIC_DELEGATE_ON
#ifdef GENERIC_DELEGATE_ON
  /// Explicit delegation call: convention 1: longer but simple
  auto obGenDelegate = CGenericDelegater<int, int>::makeDelegation
                         <DelegatorTest, &DelegatorTest::display>(&obDelegatorTest);

  auto obGenDelegate2 = CGenericDelegater<int , int>::makeDelegation
                          <DelegatorTest, &DelegatorTest::display2>(&obDelegatorTest);
  obGenDelegate(7);
  obGenDelegate2(12);
  cout<<"obGenDelegate==obGenDelegate2: "
      <<(obGenDelegate == obGenDelegate2 ? "True" : "False")<<endl;

  /// Implicit delegation call: convention 2: short but complex
  auto obGenDelegate3 = GENERIC_DELEGATE(&DelegatorTest::display, &obDelegatorTest);
  auto obGenDelegate4 = GENERIC_DELEGATE(&DelegatorTest::display2, &obDelegatorTest);

  cout<<"obGenDelegate3==obGenDelegate3: "
      <<(obGenDelegate3 == obGenDelegate3 ? "True" : "False")<<endl;

  obGenDelegate3(20);
  obGenDelegate4(30);
#endif

  return 0;
}
