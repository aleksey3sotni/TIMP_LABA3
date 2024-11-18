#include <UnitTest++/UnitTest++.h>
#include "modCipher.h"
#include <string>

SUITE(CipherTest) {
    TEST(ValidKey) {
        CHECK_EQUAL(coder(2, "PLAYBOIE"), "PABILYOE");
    }
    TEST(EmptyKey) {
        CHECK_THROW(getValidKey(0, "TEST"), cipher_error);
    }
    TEST(NegativeKey) {
        CHECK_THROW(getValidKey(-7, "TEST"), cipher_error);
    }
    TEST(LargeKey) {
        CHECK_THROW(getValidKey(87, "TEST"), cipher_error);
    }

    
    TEST(ValidText) {
        CHECK_EQUAL(coder(2, "PLAYBOIE"), "PABILYOE");
    }
    TEST(LowText) {
        CHECK_EQUAL(coder(2, "playBOIe"), "PABILYOE");
    }
    TEST(SpaceText) {
        CHECK_EQUAL(coder(2, "PLAY BOIE"), "PABILYOE");
    }
    TEST(EmptyText) {
        CHECK_THROW(coder(2, " "), cipher_error);
    }
    TEST(ValiDTextWithoutletters) {
        CHECK_THROW(coder(2, "?%»%"), cipher_error);
    }
    TEST(TextWithNumber) {
        CHECK_EQUAL(coder(4, "play12BOIe"), "PABILYOE");
    }
    TEST(TextWithSpaceAndPunct) {
        CHECK_EQUAL(coder(2, "play boy! "), "PABYLYO");
    }
    
    
    TEST(ValidDecrypt) {
        CHECK_EQUAL(decoder(2, "PABILYOE"), "PLAYBOIE");
    }
    TEST(LowDecrypt) {
        CHECK_EQUAL(decoder(2, "paBIlYOE"), "PLAYBOIE");
    }
    TEST(SpaceDecrypt) {
        CHECK_EQUAL(decoder(2, "PABI LYOE"), "PLAYBOIE");
    }
    TEST(EmptyDecrypt) {
        CHECK_THROW(decoder(2, " "), cipher_error);
    }
    TEST(TextNumberDecrypt) {
        CHECK_EQUAL(decoder(2, "PABI12LYOE"), "PLAYBOIE");
    }
    TEST(TextSymbolDecrypt) {
        CHECK_EQUAL(decoder(2, "PABI!?LYOE"), "PLAYBOIE");
    }
}

int main() {
    return UnitTest::RunAllTests();
}
