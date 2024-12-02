import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.io.IOException;

public class Oyun {

    public static void main(String[] args) throws IOException {
        // Dosyaya yazma işlemi için PrintStream oluşturuyoruz
        FileOutputStream fos = new FileOutputStream("savas_sim.txt"); // Çıktıyı 'savas_sim.txt' dosyasına yazacak
        PrintStream ps = new PrintStream(fos);

        // Konsola ve dosyaya yazma işlemi için TeeOutputStream kullanıyoruz
        System.setOut(new PrintStream(new TeeOutputStream(System.out, ps))); // Konsola ve dosyaya yönlendiriyoruz

        // Kartları oluşturma
        List<SavasAraci> userCards = new ArrayList<>();
        List<SavasAraci> computerCards = new ArrayList<>();
        List<SavasAraci> lockedCards = new ArrayList<>(); // Kilitli kartlar burada saklanacak
        int userControl = 0, computerControl = 0;

        // Hava Araçları
        userCards.add(new Ucak(20, 0, "Hava", 10, 10, "Ucak"));
        computerCards.add(new Ucak(20, 0, "Hava", 10, 10, "Ucak"));
        lockedCards.add(new Siha(15, 0, "Hava", 10, 10, 10, "Siha"));

        // Kara Araçları
        userCards.add(new Obus(20, 0, "Kara", 10, 5, "Obus"));
        computerCards.add(new Obus(20, 0, "Kara", 10, 5, "Obus"));
        lockedCards.add(new KFS(10, 0, "Kara", 10, 10, 20, "KFS"));

        // Deniz Araçları
        userCards.add(new Firkateyn(25, 0, "Deniz", 10, 5, "Firkateyn"));
        computerCards.add(new Firkateyn(25, 0, "Deniz", 10, 5, "Firkateyn"));
        lockedCards.add(new Sida(15, 0, "Deniz", 10, 10, 10, "Sida"));

        // Kartları rastgele dağıt
        List<SavasAraci> userDeck = dealDeck(userCards);
        List<SavasAraci> computerDeck = dealDeck(computerCards);

        // Kullanıcı ve Bilgisayar Nesnelerini Oluştur
        Oyuncu user = new Oyuncu(1, "Kullanici", 0, userDeck);
        Oyuncu computer = new Oyuncu(2, "Bilgisayar", 0, computerDeck);

        /*
        // Kullanıcı ve Bilgisayar Kartlarını Yazdır
        System.out.println("Kullanıcı Kartları:");
        printDeck(userDeck);

        System.out.println("\nBilgisayar Kartları:");
        printDeck(computerDeck);
        */

        // Oyun Döngüsü
        for (int tur = 1; tur <= 5; tur++) {
            // Bilgisayarın Kart Seçmesi
            List<SavasAraci> computerSelect = computerSelectCard(computer);

            // Kullanıcının Kart Seçmesi
            List<SavasAraci> userSelect = userSelectCard(user);

            // Kart Karşılaştırması
            System.out.println("\n--- Kart Karşılaştırma Başlıyor ---");
            compareCards(userSelect, computerSelect, user, computer);

            // Kilitli Kartları Açma Kontrolü
            if (user.getSkor() == 20 && userControl == 0) {
                userControl = 1;
                userCards.addAll(lockedCards); // Kilitli kartları oyuna dahil et
                System.out.println("\nYeni Kartlar Açıldı! Artık Siha, KFS ve Sida user tarafından kullanılabilir.");
            }
            if (computer.getSkor() == 20 && computerControl == 0) {
                computerControl = 1;
                computerCards.addAll(lockedCards); // Kilitli kartları oyuna dahil et
                System.out.println("\nYeni Kartlar Açıldı! Artık Siha, KFS ve Sida computer tarafından kullanılabilir.");
            }
            if (userControl == 1 && computerControl == 1){
                lockedCards.clear(); // Kilitli kart listesini temizle
            }

            // Skorları Yazdır
            System.out.println("\nSon Skorlar:");
            System.out.println("Kullanıcı Skoru: " + user.getSkor());
            System.out.println("Bilgisayar Skoru: " + computer.getSkor());

            if (tur != 5) {
                userDeck = addCard(userDeck, userCards);
                computerDeck = addCard(computerDeck, computerCards);
            }

            // Eksik Kart Kontrolü
            if (userDeck.size() < 3 || computerDeck.size() < 3) {
                if (userDeck.size() < 3) {
                    while (userDeck.size() < 3){
                        addCard(userDeck, userCards);
                    }
                }

                if (computerDeck.size() < 3) {
                    while (computerDeck.size() < 3){
                        addCard(computerDeck, computerCards);
                    }
                }

                compareCards(userDeck, computerDeck, user, computer);
                System.out.println("\nOyun Bitti!");
                if (user.getSkor() > computer.getSkor()) {
                    System.out.println("Kazanan: Kullanıcı!");
                }
                if (computer.getSkor() > user.getSkor()){
                    System.out.println("Kazanan: Bilgisayar!");
                }
                if (computer.getSkor() == user.getSkor()){
                    System.out.println("Oyun Berabere!");
                }
                break;
            }

            // Oyun Bitiş Kontrolü
            if (tur == 5) {
                System.out.println("\nOyun Bitti!");
                if (user.getSkor() > computer.getSkor()) {
                    System.out.println("Kazanan: Oyuncu!");
                }
                if (computer.getSkor() > user.getSkor()){
                    System.out.println("Kazanan: Bilgisayar!");
                }
                if (computer.getSkor() == user.getSkor()){
                    System.out.println("Oyun Berabere!");
                }
            }
        }
    }





        // Kartları rastgele dağıtan fonksiyon
    public static List<SavasAraci> dealDeck(List<SavasAraci> cards) {
        List<SavasAraci> deck = new ArrayList<>();
        Random rand = new Random();

        // 6 kart dağıtılacak
        for (int i = 0; i < 6; i++) {
            SavasAraci selectedCard = cards.get(rand.nextInt(cards.size())).clone();
            deck.add(selectedCard);
        }
        return deck;
    }

    // Bilgisayarın kart seçmesi
    public static List<SavasAraci> computerSelectCard(Oyuncu computer) {
        List<SavasAraci> deck = new ArrayList<>(computer.getKartListesi());
        List<SavasAraci> selectedCards = new ArrayList<>();
        List<SavasAraci> activeDeck = new ArrayList<>();

        // Dayanıklılığı 0 olmayan kartları activeDeck listesine ekle
        for (SavasAraci kart : deck) {
            if (kart.getDayaniklilik() > 0) {
                activeDeck.add(kart);
            }
        }
        for (int i = 0; i < 3; i++) {
            Random rand = new Random();
            SavasAraci selectedCard = activeDeck.get(rand.nextInt(activeDeck.size()));
            deck.remove(selectedCard); // Kartı seçtikten sonra listeden çıkar
            activeDeck.remove(selectedCard);
            selectedCards.add(selectedCard);
        }

        System.out.println("\nBilgisayarın Seçtiği Kartlar:");
        printDeck(selectedCards);
        return selectedCards;
    }

    // Kullanıcının kart seçmesi
    public static List<SavasAraci> userSelectCard(Oyuncu user) {
        List<SavasAraci> deck = new ArrayList<>(user.getKartListesi());
        List<SavasAraci> selectedCards = new ArrayList<>();
        List<SavasAraci> activeDeck = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);

        // Dayanıklılığı 0 olmayan kartları activeDeck listesine ekle
        for (SavasAraci kart : deck) {
            if (kart.getDayaniklilik() > 0) {
                activeDeck.add(kart);
            }
        }
        for (int i = 0; i < 3; i++) {
            System.out.println("\nKullanıcının Destesi:");
            printDeck(activeDeck);
            System.out.println("\nKullanıcı Kart Seçimi:");

            int secim = scanner.nextInt() - 1; // Index 0'dan başladığı için bir azaltıyoruz
            SavasAraci selectedCard = activeDeck.get(secim);
            selectedCards.add(selectedCard);
            deck.remove(selectedCard);
            activeDeck.remove(selectedCard);
        }

        System.out.println("\nKullanıcının Seçtiği Kartlar:");
        printDeck(selectedCards);
        return selectedCards;
    }

    public static List<SavasAraci> addCard(List<SavasAraci> deck, List<SavasAraci> userCards){
        Random rand = new Random();

        SavasAraci newCard = userCards.get(rand.nextInt(userCards.size()));
        deck.add(newCard);

        System.out.println("Yeni Kart Eklendi: " + newCard.getClass().getSimpleName());
        return deck;
    }

    // Kartları yazdıran fonksiyon
    public static void printDeck(List<SavasAraci> deck) {
        for (int i = 0; i < deck.size(); i++) {
            SavasAraci card = deck.get(i);
            System.out.println((i + 1) + ". " + card.getClass().getSimpleName());
        }
    }

    public static void compareCards(List<SavasAraci> userDeck, List<SavasAraci> computerDeck, Oyuncu user, Oyuncu computer) {
        for (int i = 2; i >= 0; i--) {
            SavasAraci userCard = userDeck.get(i);
            SavasAraci computerCard = computerDeck.get(i);

            System.out.println("\nSavaş Başlıyor:");
            System.out.println("Oyuncunun Kartı: " + userCard.getClass().getSimpleName());
            System.out.println("Bilgisayarın Kartı: " + computerCard.getClass().getSimpleName());

            // Saldırı avantajlarını hesapla
            int userAttack = userCard.getVurus();
            int computerAttack = computerCard.getVurus();

            if (userCard instanceof KaraAraci && computerCard instanceof DenizAraci) {
                userAttack += ((KaraAraci) userCard).getDenizVurusAvantaji();
            } else if (userCard instanceof DenizAraci && computerCard instanceof HavaAraci) {
                userAttack += ((DenizAraci) userCard).getHavaVurusAvantaji();
            } else if (userCard instanceof HavaAraci && computerCard instanceof KaraAraci) {
                userAttack += ((HavaAraci) userCard).getKaraVurusAvantaji();
            }

            if (computerCard instanceof KaraAraci && userCard instanceof DenizAraci) {
                computerAttack += ((KaraAraci) computerCard).getDenizVurusAvantaji();
            } else if (computerCard instanceof DenizAraci && userCard instanceof HavaAraci) {
                computerAttack += ((DenizAraci) computerCard).getHavaVurusAvantaji();
            } else if (computerCard instanceof HavaAraci && userCard instanceof KaraAraci) {
                computerAttack += ((HavaAraci) computerCard).getKaraVurusAvantaji();
            }

            // Dayanıklılığı güncelle
            userCard.setDayaniklilik(userCard.getDayaniklilik() - computerAttack);
            computerCard.setDayaniklilik(computerCard.getDayaniklilik() - userAttack);

            // Kartları kontrol et
            if (computerCard.getDayaniklilik() <= 0) {
                computerCard.setDayaniklilik(0); // Negatif değer sıfıra sabitlenir
                computer.kartCikar(computerCard);
                user.setSkor(user.getSkor() + computerCard.getSeviyePuani() + 10);
                System.out.println("Bilgisayarın " + computerCard.getClass().getSimpleName() + " kartı elendi!");
                computerDeck.remove(i);

            } else {
                System.out.println("Bilgisayarın " + computerCard.getClass().getSimpleName() + " dayanıklılık: " + computerCard.getDayaniklilik());
            }

            if (userCard.getDayaniklilik() <= 0) {
                userCard.setDayaniklilik(0); // Negatif değer sıfıra sabitlenir
                user.kartCikar(computerCard);
                computer.setSkor(computer.getSkor() + userCard.getSeviyePuani() + 10);
                System.out.println("Kullanıcının " + userCard.getClass().getSimpleName() + " kartı elendi!");
                userDeck.remove(i);
            } else {
                System.out.println("Kullanıcının " + userCard.getClass().getSimpleName() + " dayanıklılık: " + userCard.getDayaniklilik());
            }
        }
    }
}
