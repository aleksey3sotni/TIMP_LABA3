#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("РАЗРА",modAlphaCipher("РАЗ").encrypt("ААААА")); 
    }
    TEST(LongKey) {
        CHECK_EQUAL("РАЗЗА",modAlphaCipher("РАЗЗАРР").encrypt("ААААА"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("РАЗРА",modAlphaCipher("раз").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("Р1З"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("Р,А,З"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("Р А З"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"),cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("Р");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ВЯСРЗЩЪЫЯБЭ", p->encrypt("СОБАЧИЙКОРМ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("ВЯСРЗЩЪЫЯБЭ", p->encrypt("собачийкорм"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("ВЯСРЗЩЪЫЯБЭ", p->encrypt("СОБАЧИЙ КОРМ!!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("ВЯСРЗЩЪЫЯБЭ", p->encrypt("С56ОБАЧИЙКОРМ"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("2+2*2=5000?"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("РНАЯЦЗИЙНПЛ", modAlphaCipher("Я").encrypt("СОБАЧИЙКОРМ"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("СОБАЧИЙКОРМ", p->decrypt("ВЯСРЗЩЪЫЯБЭ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("вЯСРЗщЪЫЯБЭ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("ВЯСР ЗЩЪЫЯБЭ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("6ЯСРЗЩЪЫЯБЭ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("!ВЯСРЗЩЪЫЯБЭ!"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("СОБАЧИЙКОРМ", modAlphaCipher("Я").decrypt("РНАЯЦЗИЙНПЛ"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
