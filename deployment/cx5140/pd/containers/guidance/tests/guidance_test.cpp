/**
* @brief This file contains the test for Guidance
*        pd container
*
* Copyright by JBT
* All right reserved. Property of JBT.
* Restricted rights to use, duplicate or disclose
* of this file are granted through contract.
*/

#include "guidance_test.h"
#include "pd/headers/pd_data_types.h"
#include "pd/headers/pd_wrappers.h"

namespace pd::guidance::testing {
using namespace pd::guidance;
TEST_F(TestGuidance, Pull_MoveCmd) {
  pd::agv::Move_Cmd input{};
  EXPECT_CALL(mock_io_, Read_Move_Cmd_From_Host(_))
      .WillOnce(DoAll(SetArgReferee<0>(input),
                      Return(pd::wrappers::Std_ReturnType::READ_OK)));
  run();
}
}  // namespace pd::guidance::testing

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}