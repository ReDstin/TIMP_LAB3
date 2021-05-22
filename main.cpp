#include <UnitTest++/UnitTest++.h>
#include "/home/student/na_ydivlenie_rabotaet/timp_1/modAlphaCipher.h" 
#include "/home/student/na_ydivlenie_rabotaet/timp_1/modAlpha.cpp" 
#include <iostream>
SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("БВББВ",modAlphaCipher("БВГ").encrypt("ААААА"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("БВББВ",modAlphaCipher("БВГДЕЖЗИ").encrypt("ААААА"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("БВББВ",modAlphaCipher("бвб").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("Б1"), cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("Б,В"), cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("Б В"), cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""), cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"), cipher_error);

    }
}
struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};
SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("РЖУСПГЙШЖГБ",p->encrypt("ПЕТРОВИЧЕВ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("РЖУСПГЙШЖГБ",p->encrypt("петровичев"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("РЖУСПГЙШЖГБ",p→encrypt("ПЕТРОВИЧ,ЕВ"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("РЖУСПГЙШЖГБ", p->encrypt("петрович100ев"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {

        CHECK_THROW(p->encrypt("1234+8765=9999"),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("",modAlphaCipher("Я").encrypt("ПЕТРОВИЧЕВ"));
    }
}
SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ПЕТРОВИЧЕВ",p->decrypt("РЖУСПГЙШЖГБ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("РЖУспгйшЖГБ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("РЖУ СПГ ЙШ ЖГБ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("РЖУСПГЙШ100ЖГБ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("РЖУСПГЙШ,ЖГБ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ПЕТРОВИЧЕВ",modAlphaCipher("Я").decrypt("АЫВАЫВ"));
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}


/*
for(int i = 0; i < razmer; i++)
    if (tmp[i] == L`A` || tmp[i] == L`а`)А`А` || tmp[i] ==L`а`) || tmp[i] == L`А` | tmp[i] ==
        L`а`)а`А` || tmp[i] == L`а`)) error++;
        if (error == razmer)
throw cipher_error(string (“Вырожденный ключ: ») + s);
 \*