#include "gmock/gmock.h"
#include "nemo_api.cpp"
#include "kiwer_api.cpp"

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
