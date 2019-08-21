#include <serial_read.h>
#include <gtest/gtest.h>

TEST(SerialTests, testConstructor) {
    serialRead sr("/dev/null", 9600, false);
    EXPECT_EQ(true, true);
}

TEST(SerialTests, testRead) {
    serialRead sr("/dev/null", 9600, false);
    EXPECT_STREQ(sr.read_from_port().c_str(), "");
}

TEST(SerialTests, testWrite) {
    serialRead sr("/dev/null", 9600, false);
    sr.write_to_port("test");
    EXPECT_EQ(true, true);
}

TEST(SerialTest, closePort) {
    serialRead sr("/dev/null", 9600, false);
    sr.close_port();
    EXPECT_EQ(true, true);
}