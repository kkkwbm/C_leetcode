/*
 * Unit Test Bootstrap
 * Autor: Tomasz Jaworski, 2018-2020
 *
 * Test dla zadania Kolokwium 20/02/2024 - zadanie na 3,0
 * Autor testowanej odpowiedzi: Bartosz Wijata
 * Test wygenerowano automatycznie o 2024-02-20 18:18:51.096127
 *
 * Debug: 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include <assert.h>

#if !defined(__clang__) && !defined(__GNUC__)
// Zakomentuj poniższy błąd, jeżeli chcesz przetestować testy na swoim kompilatorze C.
#error System testow jednostkowych jest przeznaczony dla kompilatorów GCC/Clang.
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
// Zakomentuj poniższy błąd, jeżeli chcesz przetestować testy na platformie Windows.
#error System testow jednostkowych NIE jest przeznaczony dla testów uruchamianych na platformach Windows.
#endif

#define _RLDEBUG_API_
#include "unit_helper_v2.h"
#include "rdebug.h"

#include "tested_declarations.h"
#include "rdebug.h"

//
// Elementy globalne dla całego testu
//



            CREATE_FUNCTION_COUNT01(uintmax_t)

           int additional_hash_function(int a)
            {
                return a + 5;
            }


    


//
//  Test 1: Sprawdzanie poprawności działania funkcji count01_uintmax_t
//
void UTEST1(void)
{
    // informacje o teście
    test_start(1, "Sprawdzanie poprawności działania funkcji count01_uintmax_t", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            const uintmax_t input_values[] = {1913494748764971136LLU, 16843862952949634276LLU, 12057371162922232199LLU, 16797422918463995184LLU, 4533291758323040226LLU, 0LLU, 6148914691236517205LLU, 12297829382473034410LLU};
            int expected_values[] = {15, 14, 17, 16, 13, 0, 32, 31};

            for (int i = 0; i < 8; ++i)
            {
                int res = count01_uintmax_t(input_values[i]);

                test_error(res == expected_values[i], "Funkcja counter01_uintmax_t() powinna zwrócić wartość równą %d, a zapisałą %d", expected_values[i], res);
            }

            test_no_heap_leakage();
            onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 2: Sprawdzanie poprawności działania funkcji count01_int
//
void UTEST2(void)
{
    // informacje o teście
    test_start(2, "Sprawdzanie poprawności działania funkcji count01_int", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

            const int input_values[] = {188, 25, 163, 164, 217, 85, 170};
            int expected_values[] = {2, 2, 3, 3, 3, 4, 4};

            for (int i = 0; i < 7; ++i)
            {
                int res = count01_int(input_values[i]);

                test_error(res == expected_values[i], "Funkcja counter01_int() powinna dla liczby %d zwrócić wartość równą %d, a zapisałą %d",input_values[i], expected_values[i], res);
            }

            test_no_heap_leakage();
            onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 3: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 4300 bajtów (wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST3(void)
{
    // informacje o teście
    test_start(3, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 4300 bajtów (wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(4300);
    
    //
    // -----------
    //
    
                       const char *expected_products[][60] = {{"Intel Core i5 10400F", "Intel Core i5 10400F", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "ASRock B550M Pro4", "Zotac GeForce RTX 3060 Ti GAMING Twin Edge White 8GB GDDR6X", "Axagon ADA-71 Soundbox", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "ASRock B550M Pro4", "ASUS PRIME B450 PLUS", "GOODRAM 16GB 3200MHz", "Intel Core i5 10400F", "ASRock B550M Pro4", "AMD Ryzen 5 5600", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "ASUS PRIME B450 PLUS", "AMD Ryzen 5 5600", "Corsair 16GB 3200MHz", "AMD Ryzen 5 5600", "ASRock B550M Pro4", "ASUS PRIME B450 PLUS", "ASUS PRIME B450 PLUS", "Axagon ADA-71 Soundbox", "GOODRAM 16GB 3200MHz", "GOODRAM 16GB 3200MHz", "ASRock B550M Pro4", "ASRock B550M Pro4"}, {"ASRock B550M Pro4", "Intel Core i5 10400F", "Kingston FURY 16GB 3600MHz", "Edifier GS02 USB", "Netgear A7000-100PES", "Gigabyte B550 AORUS ELITE AX V2", "WD 500GB 2.5 SATA SSD Blue SA510", "ASRock B550M Pro4", "Kingston FURY 16GB 3600MHz", "Kingston FURY 16GB 3600MHz", "WD 500GB 2.5 SATA SSD Blue SA510", "WD 500GB 2.5 SATA SSD Blue SA510", "ASRock B550M Pro4", "Gigabyte B550 AORUS ELITE AX V2", "Edimax EU-4208", "Intel Core i5 12400F", "WD 500GB 2.5 SATA SSD Blue SA510", "Edifier GS02 USB", "Intel Core i5 10400F", "Palit GeForce RTX 4080 GamingPro OC 16GB GDDR6X", "Intel Core i5 10400F", "Gigabyte B550 AORUS ELITE AX V2", "Gigabyte B550 AORUS ELITE AX V2", "Gigabyte B550 AORUS ELITE AX V2", "Edifier GS02 USB", "Kingston FURY 16GB 3600MHz", "Kingston FURY 16GB 3600MHz"}, {"ASUS PRIME B450 PLUS", "ASUS AC58 USB", "Intel Core i5 10400F", "ASUS PRIME B450 PLUS", "ASRock B550M Pro4", "Intel Core i5 12400F", "GOODRAM 16GB 3200MHz", "Intel Core i5 12400F", "ASUS PRIME B450 PLUS", "ASRock B550M Pro4", "Intel Core i5 10400F", "Patriot 16GB 3733MHz", "Intel Core i5 12400F", "Kingston FURY 16GB 3600MHz", "Edimax EU-4208", "ASUS AC58 USB", "ASRock B550M Pro4", "AMD Ryzen 5 5600"}, {"WD 500GB 2.5 SATA SSD Blue SA510", "Zotac GeForce RTX 3060 Ti GAMING Twin Edge White 8GB GDDR6X", "WD 500GB 2.5 SATA SSD Blue SA510", "Creative Sound Blaster Audigy RX", "Zotac GeForce RTX 3060 Ti GAMING Twin Edge White 8GB GDDR6X", "Zotac GeForce RTX 3060 Ti GAMING Twin Edge White 8GB GDDR6X", "AMD Ryzen 7 5800X", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "WD 500GB 2.5 SATA SSD Blue SA510"}};
                       const char *expected_categories[] = {"Karty sieciowe", "Procesory", "Plyty glowne", "Dyski twarde"}; 
                       const unsigned int expected_price[][50] = {{51420, 64537, 40337, 92, 21542, 82611, 91096, 18683, 52828, 3545, 72475, 82812, 6358, 3736, 91962, 28896, 66305, 8689, 13893, 71485, 18745, 25222, 7567, 36873, 61731, 43650, 30820}, {76273, 45090, 44545, 95051, 6779, 12913, 84293, 87365, 70192, 61430, 57013, 64283, 74428, 11834, 16687, 27143, 38019, 69260, 70995, 66181, 65687, 48315, 84122, 72031, 42887, 99818, 71561}, {90784, 5094, 11635, 18096, 48131, 11035, 734, 34911, 42832, 28470, 39905, 60330, 32911, 39275, 15631, 82196, 11601, 96570}, {46070, 13818, 79133, 86996, 21233, 96917, 59979, 23812, 44004}}; 
                       const int expected_number_of_products[] = {27, 27, 18, 9}; 
                       const unsigned int expected_hashes[][50] = {{4, 3, 5, 2, 5, 6, 4, 4, 4, 4, 5, 4, 4, 3, 5, 2, 3, 3, 5, 5, 5, 4, 3, 4, 4, 6, 3}, {5, 4, 4, 6, 4, 4, 7, 8, 4, 3, 6, 4, 5, 4, 4, 4, 5, 4, 7, 5, 4, 5, 6, 5, 4, 5, 5}, {5, 3, 5, 4, 3, 5, 3, 4, 5, 4, 4, 6, 3, 6, 3, 5, 6, 5}, {4, 4, 6, 6, 5, 7, 6, 4, 5}}; 
        
                struct double_linked_list_t *list =NULL;

                int res = read_list(&list, "mark", count01_int);
                
                test_error(res == 0, "Oczekiwano kodu błędu 0 a otrzymano %d", res);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                test_error(list != NULL, "Funkcja read_list() powinna przypisać adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                test_error(list->head != NULL, "Funkcja read_list() powinna przypisać pod pole head struktury list adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                test_error(list->tail != NULL, "Funkcja read_list() powinna przypisać pod pole tail struktury list adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        

                struct node_t* node = list->head;
        
                for (int i = 0; i < 4; ++i)
                {
                    test_error(node != NULL, "Nieoczekiwany koniec listy");
        
        
                    onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                    test_error(strcmp(node->categories->name, expected_categories[i]) == 0, "Funkcja read_lists() powinna zapisać pod %d elementem wyraz %s, a zapisałą %s", i, expected_categories[i], node->categories->name);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                            
                    int j;
            
                    for (j = 0; j < expected_number_of_products[i]; ++j)
                    {
                        test_error(strcmp(node->categories->products[j]->product_name, expected_products[i][j]) == 0, "Nazwa produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%s', a jest '%s'", i, j, expected_products[i][j], node->categories->products[j]->product_name);
                                
                        test_error(node->categories->products[j]->price == expected_price[i][j], "Cena produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%d', a jest '%d'", i, j, expected_price[i][j], node->categories->products[j]->price);
            
                        onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                                
                        test_error(node->categories->products[j]->hash_value == expected_hashes[i][j], "Funkcja read_lists() powinna zapisać pod %d elementem wartość hashującą równą %d, a zapisałą %d", i, expected_hashes[i][j], node->categories->products[j]->hash_value);

                    }
                    
                    node = node->next;
                }

                test_error(node == NULL, "Pole next w ostatnim elemencie listy powinno być ustawione na NULL");

                
                node = list->tail;
        
                for (int i = 4 - 1; i >= 0; --i)
                {
                    test_error(node != NULL, "Nieoczekiwany koniec listy");
        
                    onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                    test_error(strcmp(node->categories->name, expected_categories[i]) == 0, "Funkcja read_lists() powinna zapisać pod %d elementem wyraz %s, a zapisałą %s", i, expected_categories[i], node->categories->name);
                    int j;
            
                    for (j = 0; j < expected_number_of_products[i]; ++j)
                    {
                        test_error(strcmp(node->categories->products[j]->product_name, expected_products[i][j]) == 0, "Nazwa produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%s', a jest '%s'", i, j, expected_products[i][j], node->categories->products[j]->product_name);
                                
                        test_error(node->categories->products[j]->price == expected_price[i][j], "Cena produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%d', a jest '%d'", i, j, expected_price[i][j], node->categories->products[j]->price);
            
                        onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                                
                        test_error(node->categories->products[j]->hash_value == expected_hashes[i][j], "Funkcja read_lists() powinna zapisać pod %d elementem wartość hashującą równą %d, a zapisałą %d", i, expected_hashes[i][j], node->categories->products[j]->hash_value);

                    }
                    
                    node = node->prev;
                }

                test_error(node == NULL, "Pole prev w pierwszym elemencie listy powinno być ustawione na NULL");
                printf("jasio");
                free_list(list);
                
                test_no_heap_leakage();
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)        

    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 4: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 3462 bajtów (wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST4(void)
{
    // informacje o teście
    test_start(4, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 3462 bajtów (wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(3462);
    
    //
    // -----------
    //
    
                       const char *expected_products[][60] = {{"Creative Sound Blaster Audigy RX", "TP-Link Archer T2U Nano", "ASUS PRIME B450 PLUS", "ASUS PRIME B450 PLUS", "Gigabyte B550 AORUS ELITE AX V2", "Palit GeForce RTX 4080 GamingPro OC 16GB GDDR6X", "Gigabyte B550 AORUS ELITE AX V2", "Netgear A7000-100PES", "Axagon ADA-71 Soundbox", "Zotac GeForce RTX 3060 Ti GAMING Twin Edge White 8GB GDDR6X", "Netgear A7000-100PES", "TP-Link Archer T2U Nano", "Gainward GeForce RTX 3060 Ghost 12GB GDDR6", "Creative Sound Blaster Audigy RX", "ASUS AC58 USB", "Zotac GeForce RTX 3060 Ti GAMING Twin Edge White 8GB GDDR6X", "Gainward GeForce RTX 3060 Ghost 12GB GDDR6", "TP-Link Archer T2U Nano", "Axagon ADA-71 Soundbox", "Creative Sound Blaster Audigy RX", "Creative Sound Blaster Audigy RX", "Gigabyte B550 AORUS ELITE AX V2", "Netgear A7000-100PES", "ASUS PRIME B450 PLUS", "TP-Link Archer T2U Nano", "Zotac GeForce RTX 3060 Ti GAMING Twin Edge White 8GB GDDR6X", "Zotac GeForce RTX 3060 Ti GAMING Twin Edge White 8GB GDDR6X", "Edimax EU-4208", "Zotac GeForce RTX 3060 Ti GAMING Twin Edge White 8GB GDDR6X", "Creative Sound Blaster Audigy RX"}, {"Corsair 16GB 3200MHz", "Corsair 16GB 3200MHz", "ASUS AC58 USB", "Netgear A7000-100PES", "ASRock B550M Pro4", "Netgear A7000-100PES", "Intel Core i5 12400F", "AMD Ryzen 7 5800X", "Edimax EU-4208", "Edimax EU-4208"}, {"Creative Sound Blaster Audigy RX", "Creative Sound Blaster Audigy RX", "Kingston 1TB M.2 PCIe Gen4 NVMe KC3000", "Palit GeForce RTX 4080 GamingPro OC 16GB GDDR6X", "Kingston 1TB M.2 PCIe Gen4 NVMe KC3000", "Palit GeForce RTX 4080 GamingPro OC 16GB GDDR6X", "ASUS AC58 USB", "Kingston 1TB M.2 PCIe Gen4 NVMe KC3000", "Kingston 1TB M.2 PCIe Gen4 NVMe KC3000", "Kingston 1TB M.2 PCIe Gen4 NVMe KC3000"}, {"ASUS PRIME B450 PLUS", "ASUS PRIME B450 PLUS", "AMD Ryzen 5 5600", "MSI MAG B550 TOMAHAWK MAX WIFI", "ASUS PRIME B450 PLUS", "ASUS PRIME B450 PLUS", "Edimax EU-4208", "MSI MAG B550 TOMAHAWK MAX WIFI", "ASUS PRIME B450 PLUS", "AMD Ryzen 5 5600"}};
                       const char *expected_categories[] = {"Procesory", "Karty graficzne", "Pamiec RAM", "Dyski twarde"}; 
                       const unsigned int expected_price[][50] = {{72123, 6219, 4496, 4861, 27768, 39684, 86752, 9364, 54650, 9583, 9690, 29330, 70409, 61084, 64631, 31589, 52854, 48679, 62916, 72958, 49520, 33242, 27719, 73270, 63513, 82003, 31009, 40213, 33341, 67535}, {63833, 65481, 57389, 37647, 57213, 31562, 72310, 79825, 12520, 78724}, {57611, 41129, 23800, 54428, 65527, 45444, 96260, 4393, 3464, 19081}, {38351, 58079, 64579, 31716, 24541, 89131, 81231, 2929, 3340, 40295}}; 
                       const int expected_number_of_products[] = {30, 10, 10, 10}; 
                       const unsigned int expected_hashes[][50] = {{5, 4, 3, 4, 3, 4, 5, 5, 6, 5, 5, 5, 5, 4, 3, 5, 4, 4, 4, 3, 3, 4, 4, 4, 3, 5, 4, 6, 4, 3}, {5, 3, 4, 4, 4, 5, 5, 5, 3, 4}, {4, 6, 3, 5, 2, 4, 3, 5, 3, 6}, {5, 4, 3, 3, 4, 6, 5, 4, 3, 5}}; 
        
                struct double_linked_list_t *list =NULL;

                int res = read_list(&list, "million", count01_int);
                
                test_error(res == 0, "Oczekiwano kodu błędu 0 a otrzymano %d", res);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                test_error(list != NULL, "Funkcja read_list() powinna przypisać adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                test_error(list->head != NULL, "Funkcja read_list() powinna przypisać pod pole head struktury list adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                test_error(list->tail != NULL, "Funkcja read_list() powinna przypisać pod pole tail struktury list adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        

                struct node_t* node = list->head;
        
                for (int i = 0; i < 4; ++i)
                {
                    test_error(node != NULL, "Nieoczekiwany koniec listy");
        
        
                    onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                    test_error(strcmp(node->categories->name, expected_categories[i]) == 0, "Funkcja read_lists() powinna zapisać pod %d elementem wyraz %s, a zapisałą %s", i, expected_categories[i], node->categories->name);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                            
                    int j;
            
                    for (j = 0; j < expected_number_of_products[i]; ++j)
                    {
                        test_error(strcmp(node->categories->products[j]->product_name, expected_products[i][j]) == 0, "Nazwa produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%s', a jest '%s'", i, j, expected_products[i][j], node->categories->products[j]->product_name);
                                
                        test_error(node->categories->products[j]->price == expected_price[i][j], "Cena produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%d', a jest '%d'", i, j, expected_price[i][j], node->categories->products[j]->price);
            
                        onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                                
                        test_error(node->categories->products[j]->hash_value == expected_hashes[i][j], "Funkcja read_lists() powinna zapisać pod %d elementem wartość hashującą równą %d, a zapisałą %d", i, expected_hashes[i][j], node->categories->products[j]->hash_value);

                    }
                    
                    node = node->next;
                }

                test_error(node == NULL, "Pole next w ostatnim elemencie listy powinno być ustawione na NULL");

                
                node = list->tail;
        
                for (int i = 4 - 1; i >= 0; --i)
                {
                    test_error(node != NULL, "Nieoczekiwany koniec listy");
        
                    onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                    test_error(strcmp(node->categories->name, expected_categories[i]) == 0, "Funkcja read_lists() powinna zapisać pod %d elementem wyraz %s, a zapisałą %s", i, expected_categories[i], node->categories->name);
                    int j;
            
                    for (j = 0; j < expected_number_of_products[i]; ++j)
                    {
                        test_error(strcmp(node->categories->products[j]->product_name, expected_products[i][j]) == 0, "Nazwa produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%s', a jest '%s'", i, j, expected_products[i][j], node->categories->products[j]->product_name);
                                
                        test_error(node->categories->products[j]->price == expected_price[i][j], "Cena produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%d', a jest '%d'", i, j, expected_price[i][j], node->categories->products[j]->price);
            
                        onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                                
                        test_error(node->categories->products[j]->hash_value == expected_hashes[i][j], "Funkcja read_lists() powinna zapisać pod %d elementem wartość hashującą równą %d, a zapisałą %d", i, expected_hashes[i][j], node->categories->products[j]->hash_value);

                    }
                    
                    node = node->prev;
                }

                test_error(node == NULL, "Pole prev w pierwszym elemencie listy powinno być ustawione na NULL");
                printf("jasio");
                free_list(list);
                
                test_no_heap_leakage();
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)        

    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 5: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 2680 bajtów (wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST5(void)
{
    // informacje o teście
    test_start(5, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 2680 bajtów (wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(2680);
    
    //
    // -----------
    //
    
                       const char *expected_products[][60] = {{"Gainward GeForce RTX 3060 Ghost 12GB GDDR6", "WD 500GB 2.5 SATA SSD Blue SA510", "TP-Link Archer T2U Nano", "Intel Core i5 10400F", "ASUS Xonar AE", "Gainward GeForce RTX 3060 Ghost 12GB GDDR6", "ASUS Xonar AE", "Creative Sound Blaster Audigy RX", "WD 500GB 2.5 SATA SSD Blue SA510", "WD 500GB 2.5 SATA SSD Blue SA510", "ASUS Xonar AE", "Intel Core i5 10400F", "WD 500GB 2.5 SATA SSD Blue SA510", "ASUS Xonar AE", "Axagon ADA-71 Soundbox", "Intel Core i5 10400F", "TP-Link Archer T2U Nano", "TP-Link Archer T2U Nano", "ASUS Xonar AE", "Gainward GeForce RTX 3060 Ghost 12GB GDDR6", "Creative Sound Blaster Audigy RX"}, {"ASUS AC58 USB", "Kingston FURY 16GB 3600MHz", "Kingston FURY 16GB 3600MHz", "AMD Ryzen 5 5600", "ASRock B550M Pro4", "ASRock B550M Pro4", "AMD Ryzen 5 5600"}, {"Corsair 16GB 3200MHz", "TP-Link Archer T2U Nano", "TP-Link Archer T2U Nano", "Corsair 16GB 3200MHz", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "Corsair 16GB 3200MHz", "TP-Link Archer T2U Nano"}, {"Palit GeForce RTX 4080 GamingPro OC 16GB GDDR6X", "Palit GeForce RTX 4080 GamingPro OC 16GB GDDR6X", "ASUS Xonar AE", "ASUS Xonar AE", "AMD Ryzen 5 5600", "Netgear A7000-100PES", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "GOODRAM 256GB 2.5 SATA SSD CX400", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "ASUS Xonar AE", "Netgear A7000-100PES", "ASUS Xonar AE", "Axagon ADA-71 Soundbox", "ASUS Xonar AE"}};
                       const char *expected_categories[] = {"Dyski twarde", "Pamiec RAM", "Karty sieciowe", "Karty graficzne"}; 
                       const unsigned int expected_price[][50] = {{60555, 20213, 72068, 2370, 30171, 99765, 51791, 92479, 64128, 81303, 67006, 50015, 25647, 98039, 24319, 6906, 25849, 88408, 93839, 62272, 61706}, {35996, 75851, 41131, 40090, 8238, 76799, 44794}, {12084, 44415, 55677, 54741, 35385, 13214, 5592}, {88380, 74851, 32826, 66967, 24215, 11619, 53607, 85259, 14489, 56116, 42622, 23996, 59090, 93475}}; 
                       const int expected_number_of_products[] = {21, 7, 7, 14}; 
                       const unsigned int expected_hashes[][50] = {{5, 5, 4, 4, 5, 6, 5, 5, 3, 5, 4, 4, 4, 4, 3, 4, 4, 6, 5, 3, 4}, {4, 6, 6, 5, 3, 4, 5}, {4, 5, 5, 7, 5, 3, 4}, {5, 5, 3, 5, 5, 5, 5, 6, 4, 5, 4, 4, 5, 6}}; 
        
                struct double_linked_list_t *list =NULL;

                int res = read_list(&list, "loud", count01_int);
                
                test_error(res == 0, "Oczekiwano kodu błędu 0 a otrzymano %d", res);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                test_error(list != NULL, "Funkcja read_list() powinna przypisać adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                test_error(list->head != NULL, "Funkcja read_list() powinna przypisać pod pole head struktury list adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                test_error(list->tail != NULL, "Funkcja read_list() powinna przypisać pod pole tail struktury list adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        

                struct node_t* node = list->head;
        
                for (int i = 0; i < 4; ++i)
                {
                    test_error(node != NULL, "Nieoczekiwany koniec listy");
        
        
                    onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                    test_error(strcmp(node->categories->name, expected_categories[i]) == 0, "Funkcja read_lists() powinna zapisać pod %d elementem wyraz %s, a zapisałą %s", i, expected_categories[i], node->categories->name);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                            
                    int j;
            
                    for (j = 0; j < expected_number_of_products[i]; ++j)
                    {
                        test_error(strcmp(node->categories->products[j]->product_name, expected_products[i][j]) == 0, "Nazwa produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%s', a jest '%s'", i, j, expected_products[i][j], node->categories->products[j]->product_name);
                                
                        test_error(node->categories->products[j]->price == expected_price[i][j], "Cena produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%d', a jest '%d'", i, j, expected_price[i][j], node->categories->products[j]->price);
            
                        onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                                
                        test_error(node->categories->products[j]->hash_value == expected_hashes[i][j], "Funkcja read_lists() powinna zapisać pod %d elementem wartość hashującą równą %d, a zapisałą %d", i, expected_hashes[i][j], node->categories->products[j]->hash_value);

                    }
                    
                    node = node->next;
                }

                test_error(node == NULL, "Pole next w ostatnim elemencie listy powinno być ustawione na NULL");

                
                node = list->tail;
        
                for (int i = 4 - 1; i >= 0; --i)
                {
                    test_error(node != NULL, "Nieoczekiwany koniec listy");
        
                    onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                    test_error(strcmp(node->categories->name, expected_categories[i]) == 0, "Funkcja read_lists() powinna zapisać pod %d elementem wyraz %s, a zapisałą %s", i, expected_categories[i], node->categories->name);
                    int j;
            
                    for (j = 0; j < expected_number_of_products[i]; ++j)
                    {
                        test_error(strcmp(node->categories->products[j]->product_name, expected_products[i][j]) == 0, "Nazwa produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%s', a jest '%s'", i, j, expected_products[i][j], node->categories->products[j]->product_name);
                                
                        test_error(node->categories->products[j]->price == expected_price[i][j], "Cena produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%d', a jest '%d'", i, j, expected_price[i][j], node->categories->products[j]->price);
            
                        onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                                
                        test_error(node->categories->products[j]->hash_value == expected_hashes[i][j], "Funkcja read_lists() powinna zapisać pod %d elementem wartość hashującą równą %d, a zapisałą %d", i, expected_hashes[i][j], node->categories->products[j]->hash_value);

                    }
                    
                    node = node->prev;
                }

                test_error(node == NULL, "Pole prev w pierwszym elemencie listy powinno być ustawione na NULL");
                printf("jasio");
                free_list(list);
                
                test_no_heap_leakage();
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)        

    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 6: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 2259 bajtów (wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST6(void)
{
    // informacje o teście
    test_start(6, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 2259 bajtów (wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(2259);
    
    //
    // -----------
    //
    
                       const char *expected_products[][60] = {{"Netgear A7000-100PES", "AMD Ryzen 7 5800X", "AMD Ryzen 7 5800X", "ASUS Xonar AE", "Edimax EU-4208"}, {"Palit GeForce RTX 4080 GamingPro OC 16GB GDDR6X", "Edifier GS02 USB", "Edifier GS02 USB", "MSI MAG B550 TOMAHAWK MAX WIFI", "Edifier GS02 USB"}, {"WD 500GB 2.5 SATA SSD Blue SA510", "Netgear A7000-100PES", "Zotac GeForce RTX 3060 Ti GAMING Twin Edge White 8GB GDDR6X", "Edimax EU-4208", "WD 500GB 2.5 SATA SSD Blue SA510", "ASRock B550M Pro4", "Netgear A7000-100PES", "AMD Ryzen 5 5600", "AMD Ryzen 5 5600", "ASRock B550M Pro4"}, {"Gigabyte B550 AORUS ELITE AX V2", "ASUS AC58 USB", "Gigabyte B550 AORUS ELITE AX V2", "Edimax EU-4208", "ASUS AC58 USB"}, {"Axagon ADA-71 Soundbox", "ASUS PRIME B450 PLUS", "AMD Ryzen 7 5800X", "ASUS PRIME B450 PLUS", "MSI MAG B550 TOMAHAWK MAX WIFI", "Kingston FURY 16GB 3600MHz", "Gigabyte B550 AORUS ELITE AX V2", "Intel Core i5 12400F", "Axagon ADA-71 Soundbox", "Palit GeForce RTX 4080 GamingPro OC 16GB GDDR6X", "ASUS PRIME B450 PLUS", "Intel Core i5 12400F", "Gigabyte B550 AORUS ELITE AX V2", "GOODRAM 256GB 2.5 SATA SSD CX400", "Gigabyte B550 AORUS ELITE AX V2"}};
                       const char *expected_categories[] = {"Pamiec RAM", "Plyty glowne", "Karty graficzne", "Procesory", "Dyski twarde"}; 
                       const unsigned int expected_price[][50] = {{38277, 39711, 30114, 19016, 55981}, {91145, 53099, 72176, 42464, 58058}, {93502, 91937, 72953, 8414, 57411, 66310, 87072, 62013, 18149, 42197}, {67075, 83178, 47836, 24637, 53403}, {67637, 29506, 84177, 33067, 20007, 44062, 27108, 26972, 35561, 4403, 11823, 76498, 71732, 74981, 73044}}; 
                       const int expected_number_of_products[] = {5, 5, 10, 5, 15}; 
                       const unsigned int expected_hashes[][50] = {{38282, 39716, 30119, 19021, 55986}, {91150, 53104, 72181, 42469, 58063}, {93507, 91942, 72958, 8419, 57416, 66315, 87077, 62018, 18154, 42202}, {67080, 83183, 47841, 24642, 53408}, {67642, 29511, 84182, 33072, 20012, 44067, 27113, 26977, 35566, 4408, 11828, 76503, 71737, 74986, 73049}}; 


                struct double_linked_list_t *list =NULL;

                int res = read_list(&list, "remember", additional_hash_function);

                test_error(res == 0, "Oczekiwano kodu błędu 0 a otrzymano %d", res);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                test_error(list != NULL, "Funkcja read_list() powinna przypisać adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                test_error(list->head != NULL, "Funkcja read_list() powinna przypisać pod pole head struktury list adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                test_error(list->tail != NULL, "Funkcja read_list() powinna przypisać pod pole tail struktury list adres zaalokowanej pamięci, a przypisała NULL");
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)


                struct node_t* node = list->head;
                for (int i = 0; i < 5; ++i)
                {
                    test_error(node != NULL, "Nieoczekiwany koniec listy");
        
        
                    onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                    test_error(strcmp(node->categories->name, expected_categories[i]) == 0, "Funkcja read_lists() powinna zapisać pod %d elementem wyraz %s, a zapisałą %s", i, expected_categories[i], node->categories->name);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                            
                    int j;
            
                    for (j = 0; j < expected_number_of_products[i]; ++j)
                    {
                        test_error(strcmp(node->categories->products[j]->product_name, expected_products[i][j]) == 0, "Nazwa produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%s', a jest '%s'", i, j, expected_products[i][j], node->categories->products[j]->product_name);
                                
                        test_error(node->categories->products[j]->price == expected_price[i][j], "Cena produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%d', a jest '%d'", i, j, expected_price[i][j], node->categories->products[j]->price);
            
                        onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                                
                        test_error(node->categories->products[j]->hash_value == expected_hashes[i][j], "Funkcja read_lists() powinna zapisać pod %d elementem wartość hashującą równą %d, a zapisałą %d", i, expected_hashes[i][j], node->categories->products[j]->hash_value);

                    }
                    
                    node = node->next;
                }

                test_error(node == NULL, "Pole next w ostatnim elemencie listy powinno być ustawione na NULL");


                node = list->tail;
        
                for (int i = 5 - 1; i >= 0; --i)
                {
                    test_error(node != NULL, "Nieoczekiwany koniec listy");
        
                    onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                    test_error(strcmp(node->categories->name, expected_categories[i]) == 0, "Funkcja read_lists() powinna zapisać pod %d elementem wyraz %s, a zapisałą %s", i, expected_categories[i], node->categories->name);
                    int j;
            
                    for (j = 0; j < expected_number_of_products[i]; ++j)
                    {
                        test_error(strcmp(node->categories->products[j]->product_name, expected_products[i][j]) == 0, "Nazwa produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%s', a jest '%s'", i, j, expected_products[i][j], node->categories->products[j]->product_name);
                                
                        test_error(node->categories->products[j]->price == expected_price[i][j], "Cena produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%d', a jest '%d'", i, j, expected_price[i][j], node->categories->products[j]->price);
            
                        onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                                
                        test_error(node->categories->products[j]->hash_value == expected_hashes[i][j], "Funkcja read_lists() powinna zapisać pod %d elementem wartość hashującą równą %d, a zapisałą %d", i, expected_hashes[i][j], node->categories->products[j]->hash_value);

                    }
                    
                    node = node->prev;
                }

                test_error(node == NULL, "Pole prev w pierwszym elemencie listy powinno być ustawione na NULL");

                free_list(list);

                test_no_heap_leakage();
                onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)        

    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 7: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 0 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST7(void)
{
    // informacje o teście
    test_start(7, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 0 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    

                struct double_linked_list_t *list = NULL;

                int res = read_list(&list, "remember", count01_int);
                test_error(res == -4, "Oczekiwano kod błędu -4 a otrzymano %d", res);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 8: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 16 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST8(void)
{
    // informacje o teście
    test_start(8, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 16 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(16);
    
    //
    // -----------
    //
    

                struct double_linked_list_t *list = NULL;

                int res = read_list(&list, "remember", count01_int);
                test_error(res == -4, "Oczekiwano kod błędu -4 a otrzymano %d", res);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 9: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 176 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST9(void)
{
    // informacje o teście
    test_start(9, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 176 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(176);
    
    //
    // -----------
    //
    

                struct double_linked_list_t *list = NULL;

                int res = read_list(&list, "remember", count01_int);
                test_error(res == -4, "Oczekiwano kod błędu -4 a otrzymano %d", res);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 10: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 200 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST10(void)
{
    // informacje o teście
    test_start(10, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 200 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(200);
    
    //
    // -----------
    //
    

                struct double_linked_list_t *list = NULL;

                int res = read_list(&list, "remember", count01_int);
                test_error(res == -4, "Oczekiwano kod błędu -4 a otrzymano %d", res);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 11: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 216 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST11(void)
{
    // informacje o teście
    test_start(11, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 216 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(216);
    
    //
    // -----------
    //
    

                struct double_linked_list_t *list = NULL;

                int res = read_list(&list, "remember", count01_int);
                test_error(res == -4, "Oczekiwano kod błędu -4 a otrzymano %d", res);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 12: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 192 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST12(void)
{
    // informacje o teście
    test_start(12, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 192 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(192);
    
    //
    // -----------
    //
    

                struct double_linked_list_t *list = NULL;

                int res = read_list(&list, "remember", count01_int);
                test_error(res == -4, "Oczekiwano kod błędu -4 a otrzymano %d", res);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 13: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 202 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST13(void)
{
    // informacje o teście
    test_start(13, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 202 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(202);
    
    //
    // -----------
    //
    

                struct double_linked_list_t *list = NULL;

                int res = read_list(&list, "remember", count01_int);
                test_error(res == -4, "Oczekiwano kod błędu -4 a otrzymano %d", res);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 14: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 186 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST14(void)
{
    // informacje o teście
    test_start(14, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 186 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(186);
    
    //
    // -----------
    //
    

                struct double_linked_list_t *list = NULL;

                int res = read_list(&list, "remember", count01_int);
                test_error(res == -4, "Oczekiwano kod błędu -4 a otrzymano %d", res);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 15: Sprawdzenie funkcji read_list()
//
void UTEST15(void)
{
    // informacje o teście
    test_start(15, "Sprawdzenie funkcji read_list()", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
            {
                int res = read_list(NULL, "remember", count01_int);
                test_error(res == -1, "Oczekiwano kodu błędu -1 a otrzymano %d", res);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            }

            {
                struct double_linked_list_t *list;
                int res = read_list(&list, NULL, count01_int);
                test_error(res == -1, "Oczekiwano kodu błędu -1 a otrzymano %d", res);
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            }

            {
                int res = read_list(NULL,NULL, count01_int);
                test_error(res == -1, "Oczekiwano kodu błędu -1 a otrzymano %d", res);

                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            }

            {
                int res = read_list(NULL,NULL, NULL);
                test_error(res == -1, "Oczekiwano kodu błędu -1 a otrzymano %d", res);

                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            }

        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 16: Sprawdzenie funkcji read_list()
//
void UTEST16(void)
{
    // informacje o teście
    test_start(16, "Sprawdzenie funkcji read_list()", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                struct double_linked_list_t *list = NULL;
                int res = read_list(&list, "at", count01_int);

                test_error(res == -2, "Oczekiwano kodu błędu -2 a otrzymano %d", res);

                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 17: Sprawdzenie funkcji read_list()
//
void UTEST17(void)
{
    // informacje o teście
    test_start(17, "Sprawdzenie funkcji read_list()", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                struct double_linked_list_t *list = NULL;
                int res = read_list(&list, "sudden", count01_int);
                test_error(res == -3, "Oczekiwano kodu błędu -3 a otrzymano %d", res);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 18: Sprawdzenie funkcji read_list()
//
void UTEST18(void)
{
    // informacje o teście
    test_start(18, "Sprawdzenie funkcji read_list()", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                struct double_linked_list_t *list = NULL;
                int res = read_list(&list, "hope", count01_int);
                test_error(res == -3, "Oczekiwano kodu błędu -3 a otrzymano %d", res);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 19: Sprawdzenie funkcji read_list()
//
void UTEST19(void)
{
    // informacje o teście
    test_start(19, "Sprawdzenie funkcji read_list()", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                struct double_linked_list_t *list = NULL;
                int res = read_list(&list, "week", count01_int);
                test_error(res == -3, "Oczekiwano kodu błędu -3 a otrzymano %d", res);

                test_no_heap_leakage();
                onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 20: Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 2811 bajtów (wystarczająco do wczytania wszystkich danych z pliku)
//
void UTEST20(void)
{
    // informacje o teście
    test_start(20, "Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 2811 bajtów (wystarczająco do wczytania wszystkich danych z pliku)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(2811);
    
    //
    // -----------
    //
    
                    const char *expected_products[][60] = {{"Axagon ADA-71 Soundbox", "AMD Ryzen 7 5800X", "WD 500GB 2.5 SATA SSD Blue SA510", "Gainward GeForce RTX 3060 Ghost 12GB GDDR6", "Gainward GeForce RTX 3060 Ghost 12GB GDDR6", "Axagon ADA-71 Soundbox", "AMD Ryzen 7 5800X", "Kingston FURY 16GB 3600MHz", "AMD Ryzen 7 5800X", "Edimax EU-4208", "ASUS PRIME B450 PLUS", "ASRock B550M Pro4", "Gainward GeForce RTX 3060 Ghost 12GB GDDR6", "Kingston FURY 16GB 3600MHz", "Axagon ADA-71 Soundbox", "WD 500GB 2.5 SATA SSD Blue SA510", "ASUS PRIME B450 PLUS", "Axagon ADA-71 Soundbox"}, {"ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "GOODRAM 256GB 2.5 SATA SSD CX400", "GOODRAM 256GB 2.5 SATA SSD CX400", "AMD Ryzen 5 5600", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6"}, {"Gigabyte B550 AORUS ELITE AX V2", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "AMD Ryzen 7 5800X", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "Patriot 16GB 3733MHz", "WD 500GB 2.5 SATA SSD Blue SA510"}, {"ASUS PRIME B450 PLUS", "ASUS PRIME B450 PLUS", "Netgear A7000-100PES", "ASRock B550M Pro4", "Gigabyte B550 AORUS ELITE AX V2", "Intel Core i5 10400F"}, {"ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "Intel Core i5 10400F", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "ASUS AC58 USB", "ASUS GeForce RTX 2060 DUAL EVO OC 6GB GDDR6", "ASUS AC58 USB", "WD 500GB 2.5 SATA SSD Blue SA510", "WD 500GB 2.5 SATA SSD Blue SA510", "Intel Core i5 10400F", "Intel Core i5 10400F", "Intel Core i5 10400F", "ASUS AC58 USB"}};
                    const char *expected_categories[] = {"Plyty glowne", "Dyski twarde", "Pamiec RAM", "Karty sieciowe", "Karty dzwiekowe"}; 
                    const unsigned int expected_price[][50] = {{28094, 92958, 26542, 48102, 10749, 77731, 66415, 90188, 60582, 73644, 39093, 81402, 64216, 80988, 12559, 66565, 88683, 25549}, {41597, 22991, 19706, 75504, 97184, 10836}, {45824, 63073, 2257, 90014, 35848, 4959}, {61168, 26745, 7370, 16719, 38451, 14455}, {15814, 93674, 11513, 36703, 11763, 35584, 67294, 7995, 41494, 35717, 5526, 605}}; 
                    const int expected_number_of_products[] = {18, 6, 6, 6, 12}; 
                    const unsigned int expected_hashes[][50] = {{4, 5, 4, 4, 4, 5, 4, 4, 5, 4, 6, 4, 4, 4, 3, 4, 7, 4}, {5, 4, 4, 4, 4, 6}, {3, 4, 4, 4, 3, 4}, {3, 4, 4, 4, 5, 3}, {3, 6, 4, 4, 4, 3, 4, 3, 5, 5, 5, 4}}; 


                    struct double_linked_list_t *list =NULL;

                    int res = read_list(&list, "team", count01_int);

                    test_error(res == 0, "Oczekiwano kodu błędu 0 a otrzymano %d", res);
                    onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                    test_error(list != NULL, "Funkcja read_list() powinna przypisać adres zaalokowanej pamięci, a przypisała NULL");
                    onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                    test_error(list->head != NULL, "Funkcja read_list() powinna przypisać pod pole head struktury list adres zaalokowanej pamięci, a przypisała NULL");
                    onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

                    test_error(list->tail != NULL, "Funkcja read_list() powinna przypisać pod pole tail struktury list adres zaalokowanej pamięci, a przypisała NULL");
                    onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)


                    
                    struct node_t* node = list->head;
            
                    for (int i = 0; i < 5; ++i)
                    {
                        test_error(node != NULL, "Nieoczekiwany koniec listy");
            
            
                        onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
                        test_error(strcmp(node->categories->name, expected_categories[i]) == 0, "Funkcja read_lists() powinna zapisać pod %d elementem wyraz %s, a zapisałą %s", i, expected_categories[i], node->categories->name);
                        onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                                
                        int j;
                
                        for (j = 0; j < expected_number_of_products[i]; ++j)
                        {
                            test_error(strcmp(node->categories->products[j]->product_name, expected_products[i][j]) == 0, "Nazwa produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%s', a jest '%s'", i, j, expected_products[i][j], node->categories->products[j]->product_name);
                                    
                            test_error(node->categories->products[j]->price == expected_price[i][j], "Cena produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%d', a jest '%d'", i, j, expected_price[i][j], node->categories->products[j]->price);
                
                            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                                    
                            test_error(node->categories->products[j]->hash_value == expected_hashes[i][j], "Funkcja read_lists() powinna zapisać pod %d elementem wartość hashującą równą %d, a zapisałą %d", i, expected_hashes[i][j], node->categories->products[j]->hash_value);
        
                        }
                        
                        node = node->next;
                    }
        
                    test_error(node == NULL, "Pole next w ostatnim elemencie listy powinno być ustawione na NULL");
        
                    
                    node = list->tail;
            
                    for (int i = 5 - 1; i >= 0; --i)
                    {
                        test_error(node != NULL, "Nieoczekiwany koniec listy");
            
                        onerror_terminate(); // przerwnie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
            
                        test_error(strcmp(node->categories->name, expected_categories[i]) == 0, "Funkcja read_lists() powinna zapisać pod %d elementem wyraz %s, a zapisałą %s", i, expected_categories[i], node->categories->name);
                        int j;
                
                        for (j = 0; j < expected_number_of_products[i]; ++j)
                        {
                            test_error(strcmp(node->categories->products[j]->product_name, expected_products[i][j]) == 0, "Nazwa produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%s', a jest '%s'", i, j, expected_products[i][j], node->categories->products[j]->product_name);
                                    
                            test_error(node->categories->products[j]->price == expected_price[i][j], "Cena produktu zapisana pod indeksem %d %d jest nieprawidłowe, powinno być '%d', a jest '%d'", i, j, expected_price[i][j], node->categories->products[j]->price);
                
                            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
                                    
                            test_error(node->categories->products[j]->hash_value == expected_hashes[i][j], "Funkcja read_lists() powinna zapisać pod %d elementem wartość hashującą równą %d, a zapisałą %d", i, expected_hashes[i][j], node->categories->products[j]->hash_value);
        
                        }
                        
                        node = node->prev;
                    }

                    test_error(node == NULL, "Pole prev w pierwszym elemencie listy powinno być ustawione na NULL");

            printf("***START***\n");
            display_list(list);
            printf("***END***\n");

            free_list(list);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)

        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 21: Sprawdzenie funkcji display_list()
//
void UTEST21(void)
{
    // informacje o teście
    test_start(21, "Sprawdzenie funkcji display_list()", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                display_list(NULL);

        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}



//
//  Test 1: Reakcja na brak pamięci (limit sterty ustawiono na 7 bajtów)
//
void MTEST1(int argc, char** argv, char** envp)
{
    // informacje o teście
    test_start(1, "Reakcja na brak pamięci (limit sterty ustawiono na 7 bajtów)", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(7);
    
    //
    // -----------
    //
    
            printf("***START***\n");
            int ret_code = rdebug_call_main(tested_main, argc, argv, envp);
            printf("\n***END***\n");
            test_error(ret_code == 8, "Funkcja main zakończyła się kodem %d a powinna 8", ret_code);

            test_no_heap_leakage();
            onerror_terminate(); // przerwanie wszystkich testów jednostkowych (np. coś jest mocno nie tak z kodem)
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}


enum run_mode_t { rm_normal_with_rld = 0, rm_unit_test = 1, rm_main_test = 2 };

int __wrap_main(volatile int _argc, char** _argv, char** _envp)
{
    int volatile vargc = _argc;
    char ** volatile vargv = _argv, ** volatile venvp = _envp;
	volatile enum run_mode_t run_mode = rm_unit_test; // -1
	volatile int selected_test = -1;

    if (vargc > 1)
	{
	    char* smode = strtok(vargv[1], ",");
	    char* stest = strtok(NULL, "");
		char *errptr = NULL;
		run_mode = (enum run_mode_t)strtol(smode, &errptr, 10);
		if (*errptr == '\x0')
		{
			memmove(vargv + 1, vargv + 2, sizeof(char*) * (vargc - 1));
			vargc--;

			if (stest != NULL)
			{
			    int val = (int)strtol(stest, &errptr, 10);
			    if (*errptr == '\x0')
			        selected_test = val;
			}
		}
	}

    // printf("runmode=%d; selected_test=%d\n", run_mode, selected_test);

    // inicjuj testy jednostkowe
    unit_test_init(run_mode, "unit_test_v2.c");
    test_limit_init();
    rldebug_set_reported_severity_level(MSL_FAILURE);

    if (run_mode == rm_normal_with_rld)
    {
        // konfiguracja ograniczników
        rldebug_reset_limits();
        

        // uruchom funkcję main Studenta a potem wyświetl podsumowanie sterty i zasobów
        volatile int ret_code = rdebug_call_main(tested_main, vargc, vargv, venvp);

        rldebug_reset_limits();
        

        int leaks_detected = rldebug_show_leaked_resources(0);
        if (leaks_detected)
            raise(SIGHEAP);

        return ret_code;
    }

    
    if (run_mode == rm_unit_test)
    {
        test_title("Testy jednostkowe");

        void (*pfcn[])(void) =
        { 
            UTEST1, // Sprawdzanie poprawności działania funkcji count01_uintmax_t
            UTEST2, // Sprawdzanie poprawności działania funkcji count01_int
            UTEST3, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 4300 bajtów (wystarczająco do wczytania wszystkich danych z pliku)
            UTEST4, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 3462 bajtów (wystarczająco do wczytania wszystkich danych z pliku)
            UTEST5, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 2680 bajtów (wystarczająco do wczytania wszystkich danych z pliku)
            UTEST6, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 2259 bajtów (wystarczająco do wczytania wszystkich danych z pliku)
            UTEST7, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 0 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
            UTEST8, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 16 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
            UTEST9, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 176 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
            UTEST10, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 200 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
            UTEST11, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 216 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
            UTEST12, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 192 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
            UTEST13, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 202 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
            UTEST14, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 186 bajtów (nie wystarczająco do wczytania wszystkich danych z pliku)
            UTEST15, // Sprawdzenie funkcji read_list()
            UTEST16, // Sprawdzenie funkcji read_list()
            UTEST17, // Sprawdzenie funkcji read_list()
            UTEST18, // Sprawdzenie funkcji read_list()
            UTEST19, // Sprawdzenie funkcji read_list()
            UTEST20, // Sprawdzenie funkcji read_list() - limit pamięci ustawiony na 2811 bajtów (wystarczająco do wczytania wszystkich danych z pliku)
            UTEST21, // Sprawdzenie funkcji display_list()
            NULL
        };

        for (int idx = 0; pfcn[idx] != NULL && !test_get_session_termination_flag(); idx++)
        {
            if (selected_test == -1 || selected_test == idx + 1)
                pfcn[idx]();

            // limit niezaliczonych testów, po jakim testy jednostkowe zostaną przerwane
            if (test_session_get_fail_count() >= 1000)
                test_terminate_session();
        }


        test_title("RLDebug :: Analiza wycieku zasobów");
        // sprawdź wycieki pamięci
        int leaks_detected = rldebug_show_leaked_resources(1);
        test_set_session_leaks(leaks_detected);

        // poinformuj serwer Mrówka o wyniku testu - podsumowanie
        test_title("Podsumowanie");
        if (selected_test == -1)
            test_summary(21); // wszystkie testy muszą zakończyć się sukcesem
        else
            test_summary(1); // tylko jeden (selected_test) test musi zakończyć się  sukcesem
        return EXIT_SUCCESS;
    }
    

    if (run_mode == rm_main_test)
    {
        test_title("Testy funkcji main()");

        void (*pfcn[])(int, char**, char**) =
        { 
            MTEST1, // Reakcja na brak pamięci (limit sterty ustawiono na 7 bajtów)
            NULL
        };

        for (volatile int idx = 0; pfcn[idx] != NULL && !test_get_session_termination_flag(); idx++)
        {
            if (selected_test == -1 || selected_test == idx + 1)
                pfcn[idx](vargc, vargv, venvp);

            // limit niezaliczonych testów, po jakim testy jednostkowe zostaną przerwane
            if (test_session_get_fail_count() >= 1000)
                test_terminate_session();
        }


        test_title("RLDebug :: Analiza wycieku zasobów");
        // sprawdź wycieki pamięci
        int leaks_detected = rldebug_show_leaked_resources(1);
        test_set_session_leaks(leaks_detected);

        // poinformuj serwer Mrówka o wyniku testu - podsumowanie
        test_title("Podsumowanie");
        if (selected_test == -1)
            test_summary(1); // wszystkie testy muszą zakończyć się sukcesem
        else
            test_summary(1); // tylko jeden (selected_test) test musi zakończyć się  sukcesem

        return EXIT_SUCCESS;
    }

    printf("*** Nieznana wartość RunMode: %d", (int)run_mode);
    abort();
}