/*

 Rozmiar int 4
 Rozmiar unsigned int 4
 Rozmiar char 1
 Rozmiar unsigned char 1
 Rozmiar short 2
 Rozmiar unsigned short 2
 Rozmiar long 4
 Rozmiar unsigned long 4
 Rozmiar double 8
 Rozmiar unsigned long long 8
 Rozmiar long long 8
 Rozmiar long long int 8
 Rozmiar long long double 16
 Rozmiar short int 2
 Rozmiar long int 4
 Rozmiar size_t 8


fscanf
sscanf -> sscanf( input_variable, "%s %s %c%z %hu %llu [^]", variables to assign to );
scanf

void * memcpy( void * destination, const void * source, size_t num );
------
Kopiuje num bajtów z miejsca wskazywanego przez source do pamięci wskazywanej przez destination
    void* destination	Wskaźnik na pamięć, do której nastąpi kopiowanie.
    const void* source	Wskaźnik na pamięć, z której nastąpi kopiowanie.
    size_t num	Liczba bajtów do skopiowania.

void * memset( void * ptr, int value, std::size_t num );
------
Ustawia pierwsze num bajtów bloku wskazywanego przez ptr na value (traktowane jako unsigned char)
    ptr	wskaźnik na blok pamięci do wypełnienia
    value	wartość, którą zostanie wypełniony blok (traktowana jako unsigned char)
    num	liczba bajtów do wypełnienia

char * strcat( char * destination, const char * source );
------
Funkcja dopisuje do łańcucha destination łańcuch source.
Znak \0 z końca łańcucha destination jest nadpisywany przez pierwszy znak łańcucha source.
Łańcuch źródłowy jest dopisywany do łańcucha docelowego włącznie ze znakiem '\0'.
    destination	łańcuch znaków do którego jest dopisywany łańcuch źródłowy
    source	dopisywany łańcuch znaków

char * strchr( const char * str, int z );
------
Funkcja zwraca wskaźnik na pierwsze znalezione wystąpienie znaku w łańcuchu znaków, który został przekazany jako argument.
Przeszukiwany jest cały łańcuch aż do napotkania znaku '\0'.
    str	Przeszukiwany łańcuch znaków.
    z	Kod ASCII znaku, który jest poszukiwany

int strcmp( const char * str1, const char * str2 );
------
Funkcja porównuje dwa łańcuchy znaków str1 i str2, oraz zwraca liczbę będącą opisem zależności między nimi.
    str1	łańcuch znaków
    str2	łańcuch znaków
--- Wartości zwracane ---
0(zero)	str1 = str2
mniejsza od 0(zero)	str1 < str2
większa od 0(zero)	str1 > str2

char * strcpy( char * dest, const char * src );
------
Funkcja kopiuje łańcuch znaków (src) do tablicy znaków (dest).
Funkcja nie sprawdza czy łańcuch kopiowany zmieści się w tablicy docelowej.
zrodlo	wskaźnik do źródłowej tablicy znaków
przeznaczenie	wskaźnik do docelowej tablicy znaków

size_t strcspn( const char * str1, const char * str2 );
------
Przeszukuje łańcuch znaków str1, w celu znalezienia pierwszego wystąpienia znaku zawartego w łańcuchu znaków str2.
    str1	Przeszukiwany łańcuch znaków.
    str2	Łańcuch znaków szukanych (pula znaków).

int stricmp( const char * str1, const char * str2 );
------
Funkcja porównuje dwa łańcuchy znaków str1 i str2, oraz zwraca liczbę będącą opisem zależności między nimi.
Funkcja ignoruje wielkość znaków.
--- Wartości zwracane ---
0(zero)	str1 = str2
mniejsza od 0(zero)	str1 < str2
większa od 0(zero)	str1 > str2

char * strncat( char * destination, char * source, size_t num );
------
Funkcja scala dwa łańcuchy znaków w jeden.
Argument num określa maksymalną liczbę znaków, która może zostać dopisana do łańcucha docelowego.
Łańcuch docelowy jest zawsze zakończony znakiem terminalnym '\0'.
    char*	destination	Łańcuch docelowy do którego zostanie dopisany łańcuch źródłowy.
    char*	source	Łańcuch źródłowy, który ma zostać dopisany do łańcucha docelowego.
    size_t	num	Maksymalna ilość znaków, jaka może zostać dopisana do łańcucha docelowego.

int strncmp( const char * str1, const char * str2, size_t liczba );
------
Funkcja porównuje dwa łańcuchy str1 i str2, oraz zwraca liczbę będącą opisem zależności między nimi.
Funkcja działa podobnie jak strcmp, ale posiada dodatkowy argument liczba,
który określa liczbę znaków biorących udział w porównywaniu.
Dodatkowo funkcja może zakończyć działanie,
gdy znaki nie będą sobie równe lub gdy natrafi w którymś z łańcuchów na znak jego końca.
    str1	łańcuch znaków
    str2	łańcuch znaków
--- Wartości zwracane ---
liczba	maksymalna liczba znaków porównywanych
0(zero)	str1 = str2
mniejsza od 0(zero)	str1 < str2
większa od 0(zero)	str1 > str2


char * strncpy( char * dest, const char * src, size_t count );
------
Kopiuje określoną liczbę znaków z łańcucha źródłowego (src) do łańcucha docelowego (dest).
Jeżeli źródłowy łańcuch znaków jest krótszy niż wartość przekazana poprzez argument count
to łańcuch znaków w buforze docelowym będzie zakończony znakiem terminalnym '\0'.
W przeciwnym wypadku łańcuch znaków w buforze docelowym nie będzie zakończony znakiem terminalnym.
    dest	Miejsce w które ma zostać skopiowany łańcuch znaków
    src	Łańcuch znaków, który ma zostać skopiowany
    count	Maksymalna liczba znaków jaka może być skopiowana do dest

char * strpbrk( const char * str1, const char * str2 );
------
Przeszukuje łańcuch znaków str1, w celu znalezienia pierwszego wystąpienia znaku zawartego w łańcuchu znaków str2.
    str1	Przeszukiwany łańcuch znaków.
    str2	Łańcuch znaków szukanych (pula znaków).

char * strrchr( const char * str, int ch );
------
Przeszukuje łańcuch znaków str w poszukiwaniu ostatniego wystąpienia znaku ch.
    str	przeszukiwany łańcuch znaków
    ch	reprezentacja kod ASCII znaku

size_t strspn( const char * str1, const char * str2 );
------
Funkcja zwraca indeks pierwszego znaku (należącego do str1), który nie występuje w łańcuchu znaków str2.
Znak terminalny w str2 nie wlicza się do przeszukiwanej puli znaków.
    str1	Przeszukiwany łańcuch znaków
    str2	Łańcuch zawierający szukane znaki

const char * strstr( const char * str1, const char * str2 );
------
Funkcja przeszukuje łańcuch znaków str1 w poszukiwaniu łańcucha znaków str2.
Jeśli w łańcuchu przeszukiwanym znajduje się więcej niż jedno wystąpienie poszukiwanego ciągu znaków
to funkcja zwróci adres na pierwsze wystąpienie.
    str1 - przeszukiwany łańcuch znaków
    str2 - łańcuch zawierający szukane znaki


char * strtok( char * str, const char * korektor );
------
Funkcja zastępuje pierwszy znaleziony znak w str znakiem terminalnym. Pulę szukanych znaków określa argument korektor.
Jedno wywołanie funkcji zastępuje jeden znak.
Aby rozpocząć przeszukiwanie łańcucha znaków od miejsca ostatniego zakończenia należy
wywołać ponownie funkcję z argumentem str o wartości NULL.
    str	- Łańcuch znaków przeznaczony do korekty
    korektor - łańcuch znaków, który określa jakie znaki mają zostać zastąpione znakiem terminalnym

char * strdup( const char * sTekst );
------
const char * sTekst	- Łańcuch znaków, który ma zostać skopiowany. Łańcuch znaków musi być zakończony znakiem terminalnym.


int fseek( FILE * stream, long offset, int origin );
------
    FILE *stream	Określa strumień na którym ma zostać wykonana operacja.
    long offset	Wartość określająca o ile bajtów należy przesunąć kursor odczytu/zapisu danych. Pozycja względem której wykonywane będzie przesunięcie kursora jest określana za pomocą argumentu origin.
    int origin	Argument może przyjmować jedną z poniższych wartości:
    Wartość	Opis
    SEEK_SET	Przesunięcie kursora jest wyrażone względem początku pliku.
    SEEK_CUR	Przesunięcie kursora jest wyrażane względem aktualnej pozycji.
    SEEK_END	Przesunięcie kursora jest wyrażone względem końca pliku.


char * fgets( char * str, int num, FILE * stream );
------
Funkcja wczytuje tekst ze wskazanego strumienia aż do napotkania znaku przejścia do nowej linii
lub do wczytania num-1 znaków (w zależności od tego co nastąpi pierwsze).
Funkcja kończy operację wczytywania danych również wtedy
gdy w buforze danych strumienia wejścia nie pozostało więcej danych do odczytania.
Wczytany wiersz jest zawsze zakończony znakiem terminalnym (\0).
Znak przejścia do nowej linii jest zapisywany do bufora, jeżeli wystąpił on we wczytanym w strumieniu danych.
    char* str	Bufor do którego zostaną zapisane odczytane znaki.
    int num	Maksymalna liczba znaków jaka może zostać zapisana do bufora (włącznie ze znakiem terminalnym).
    FILE* stream	Określa strumień na którym ma zostać wykonana operacja.


size_t fread( void * buffer, size_t size, size_t count, FILE * stream );
------
    void *buffer	Bufor do którego zostaną zapisane odczytane dane.
    size_t size	    Rozmiar jednego elementu danych, wyrażony w bajtach.
    size_t count	Maksymalna liczba elementów, jaka może zostać wczytana.
    FILE *stream	Określa strumień na którym ma zostać wykonana operacja.


char * gets( char * buffer );
------
Funkcja wczytuje tekst ze standardowego wejścia aż do napotkania znaku przejścia do nowej linii.
Funkcja kończy operację wczytywania danych również wtedy,
gdy w buforze danych strumienia wejścia nie pozostało więcej danych do odczytania.
Wczytany wiersz jest zawsze zakończony znakiem terminalnym (\0).
Znak przejścia do nowej linii nie jest zapisywany do bufora.

int fgetpos( FILE * stream, fpos_t * pos );
------
Pobiera aktualną pozycję kursora odczytu/zapisu danych dla wskazanego strumienia.
    FILE *stream	Określa strumień na którym ma zostać wykonana operacja.
    fpos_t *pos	Wskaźnik na zmienną do której ma zostać pobrana aktualna pozycja kursora odczytu/zapisu danych.


int fsetpos( FILE * stream, const fpos_t * pos );
 ------
Ustawia pozycję kursora odczytu/zapisu danych dla wskazanego strumienia.

*/