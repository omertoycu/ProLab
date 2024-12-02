import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Oyuncu {
    private int oyuncuID;
    private String oyuncuAdi;
    private int skor;
    private List<SavasAraci> kartListesi;

    // Parametreli Yapıcı
    public Oyuncu(int oyuncuID, String oyuncuAdi, int skor, List<SavasAraci> kartListesi) {
        this.oyuncuID = oyuncuID;
        this.oyuncuAdi = oyuncuAdi;
        this.skor = skor;
        this.kartListesi = kartListesi;
    }

    // Parametresiz Yapıcı
    public Oyuncu() {
        this.oyuncuID = 0; // Varsayılan oyuncuID
        this.oyuncuAdi = "Bilinmeyen"; // Varsayılan oyuncuAdi
        this.skor = 0; // Varsayılan skor
        this.kartListesi = null; // Varsayılan kartListesi
    }

    public void kartCikar(SavasAraci kart) {
        this.kartListesi.remove(kart);
    }

    // Skor gösterme fonksiyonu
    public void SkorGoster() {
        System.out.println(oyuncuAdi + " Skoru: " + skor);
    }

    // Kart seçme fonksiyonu
    public SavasAraci kartSec(boolean bilgisayar) {
        if (bilgisayar) {
            // Bilgisayarın kart seçmesi (random)
            Random rand = new Random();
            SavasAraci secilenKart = kartListesi.get(rand.nextInt(kartListesi.size()));
            System.out.println(oyuncuAdi + " " + secilenKart.getClass().getSimpleName() + " kartını seçti.");
            kartListesi.remove(secilenKart); // Seçilen kartı elden çıkar
            return secilenKart;
        } else {
            // Kullanıcının kart seçmesi
            Scanner scanner = new Scanner(System.in);
            System.out.println(oyuncuAdi + " Kart Seçin:");
            for (int i = 0; i < kartListesi.size(); i++) {
                System.out.println((i + 1) + ". " + kartListesi.get(i).getClass().getSimpleName());
            }
            int secim = scanner.nextInt();
            SavasAraci secilenKart = kartListesi.get(secim - 1);
            System.out.println(oyuncuAdi + " " + secilenKart.getClass().getSimpleName() + " kartını seçti.");
            kartListesi.remove(secilenKart); // Seçilen kartı elden çıkar
            return secilenKart;
        }
    }

    // Getter ve Setter'lar
    public int getOyuncuID() {
        return oyuncuID;
    }

    public void setOyuncuID(int oyuncuID) {
        this.oyuncuID = oyuncuID;
    }

    public String getOyuncuAdi() {
        return oyuncuAdi;
    }

    public void setOyuncuAdi(String oyuncuAdi) {
        this.oyuncuAdi = oyuncuAdi;
    }

    public int getSkor() {
        return skor;
    }

    public void setSkor(int skor) {
        this.skor = skor;
    }

    public List<SavasAraci> getKartListesi() {
        return kartListesi;
    }

    public void setKartListesi(List<SavasAraci> kartListesi) {
        this.kartListesi = kartListesi;
    }
}
