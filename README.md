# Pilot-mieszkanie
W mieszkaniu do którego się wprowadziłem na czas studiów znajdował się telewizor bez pilota.\
Na początku planowałem po prostu z niego nie kożystać, ale zainspirowany [tym filmem](https://youtu.be/j1V2I-otdzk) postanowiłem wziąć sprawy w swoje ręce.
<p>Moim pierwszym rozwiązaniem był primtywny pilot na płytce stykowej</p>
![photo_2023-03-15_18-49-35](https://user-images.githubusercontent.com/26011660/225398730-0acf7538-1b64-4edc-8312-c3be6e7174ec.jpg)\
Pilot był zasilany bezpośrednio z 9V baterii, kod do pilota znajduje się tutaj\
Największym wyzwaniem w tym rozwiązaniu było znalezienie odpowiednich sygnałów IR do sterowania pilota.\
Rozwiązaniem było pożyczenie działającego pilota od mojego współlokatora i zczytanie sygnałów z interesujących mnie przycisków.\
<p>Podejście drugie</p>
Pilocik na płytce miał sporo problemów, między innymi:
1.Krótką żywotność baterii
1.Był wyjątkowo nie poręczny
1.Dioda IR była bardzo kierunkowa co utrudniało celowanie
Każdy z tych problemów można było adresować pojedyńczo, zdecydowałem się jednak na inne rozwiązanie.\
Postanowiłem przenieść diodę IR bezpośrednio pod telewizor i komunikować się z nią po lokalnym WiFi
Ostateczne rozwiązanie składa się z dwóch części:\
Arduino które operuje diodą i symuluje pilot do telewizora\
ESP które hostuje stronę i rozkazuje arduino co ma robić\
<p>Dodatkowe Udogodnienia</p>
Mając w pokoju permanentie działający serwer ESP skorzystałem z tego żeby rozwiązać parę innych powiązanych problemów:
1.Zasilacz w telewizorze wydaje cichy pisk, w ciągu dnia nie jest to problem ale w nocy doprawadzało mnie to do szału.
  1.Rozwiązaniem było dołączenie przekaźnika szeregowo z telewizorem w taki sposób, że teraz mogę z poziomu telefonu odłączyć i podłączyć telewizor do prądu. Ogranicza to również zużycie prądu telewizora.
1.Chciałem dodać backlight do telewizora
  1.Rozwiązanie było wyjątkowo proste, zasilacz już miałem jako, że był potrzebny do mikrokontrolerów wystarczyło dodać jeden tranzystor do sterowania zasilaniem i parę ekstra linijek kodu żeby móc sterować nim z telefonu.
